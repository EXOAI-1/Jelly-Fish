/* EXO-MEDUSA v6 kit - ESP32-C3 SuperMini - FAILPROOF + phone WiFi remote + BLE backup
 * tank-swim: LED off, leak on GPIO4, LEDC 2.x/3.x
 * Phone remote is the AP page (http://192.168.4.1). BLE still works as backup.
 *
 * PILOTAGE (les deux marchent en meme temps, le dernier ordre gagne) :
 *  WiFi : reseau "EXO-MEDUSA", mdp "medusa123", page http://192.168.4.1  (telephone = telecommande)
 *  Bluetooth : BLE (Nordic UART). App gratuite "Serial Bluetooth Terminal"
 *    (Android, onglet Bluetooth LE) ou "BLE Terminal" (iPhone).
 *    Commandes texte : V50 = vitesse 50% | V-40 = arriere | S = stop
 *                      A = cycle auto | ? = etat (temperature, batterie, tr/min)
 *  HONNETE : l'ESP32-C3 fait du Bluetooth Low Energy UNIQUEMENT (pas de
 *  Bluetooth "classique") : il n'apparait PAS dans les appareils audio du
 *  telephone, seulement dans les apps BLE. C'est normal.
 *  Si WiFi+BLE ensemble sont instables sur ta carte : mets ENABLE_BLE a 0.
 *
 * BROCHAGE : servo GPIO10 | ILS GPIO3 | NTC GPIO0 | Vbat GPIO1 | Hall GPIO2 | fuite GPIO4
 * SECURITES : patinage (Hall), thermique (52/58/65 C), batterie 3,35 V,
 *             fuite, watchdog 8 s, condo 470 uF. Voir notice etape 11.
 */
#define ENABLE_WIFI 1
#define ENABLE_BLE  1
#define ENABLE_LED  0     // anneau WS2812 8 LEDs sous la fenetre : dome lumineux facon Festo
                          // (installer la bibliotheque "Adafruit NeoPixel" dans le gestionnaire)
                          // si ENABLE_LED 1 : deplacer PIN_LEAK hors de GPIO4 (conflit anneau)

#include <esp_task_wdt.h>
#if ENABLE_LED
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel led(8, 4, NEO_GRB + NEO_KHZ800);   // GPIO4, 8 LEDs — fuite doit alors quitter GPIO4
void ledStatus(int mode_, bool swimming, float phase){
  uint32_t c;
  if (mode_==2)      c = led.Color(120,0,0);                       // FAUTE : rouge
  else if (mode_==1) c = led.Color(90,45,0);                       // pause thermique : orange
  else if (swimming){ int b = 30+90*(0.5f-0.5f*cosf(phase));       // nage : respiration bleue
                      c = led.Color(0, b/3, b); }
  else               c = led.Color(18,18,22);                      // glisse : blanc doux
  for (int i=0;i<8;i++) led.setPixelColor(i,c);
  led.show();
}
#endif
#include <math.h>
#if ENABLE_WIFI
#include <WiFi.h>
#include <WebServer.h>
#endif
#if ENABLE_BLE
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#endif

const int PIN_SERVO=10, PIN_REED=3, PIN_NTC=0, PIN_VBAT=1, PIN_HALL=2, PIN_LEAK=4;
const int CH=0, US_STOP=1500, TRIM=0;
const uint32_t SWIM_MS=8000, GLIDE_MS=4000; const int SWIM_SPEED=42;   // ~0.6-0.7 Hz : marge de couple x1.3-1.8 validee (voir SYSTEM_DESIGN)
const float T_SOFT=52.0, T_PAUSE=58.0, T_FAULT=65.0, T_RESUME=50.0, V_LOW=3.35;
const int HALL_DELTA=140; const uint32_t STALL_WIN=2500;

// Arduino-ESP32 3.x : LEDC par broche (ledcAttach / ledcWrite(pin, duty)).
// 2.x : LEDC par canal (ledcSetup / ledcAttachPin / ledcWrite(ch, duty)).
#if defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 3)
#define LEDC_V3 1
#else
#define LEDC_V3 0
#endif

enum Mode { RUN, PAUSED_HOT, FAULT_MODE };
Mode mode=RUN; String faultCause="";
int speedPct=0, cmdNow=0; bool running=true, remote=false;
uint32_t lastCmd=0, reedDown=0, lastPulse=0, stallRetries=0, lastRpmCalc=0;
int hallBase=0; bool hallHigh=false; volatile uint32_t pulseCount=0;
float tServo=25, vBat=4.0, rpm=0;

void writeServo(int pct){ pct=constrain(pct,-100,100);
  uint32_t duty=(uint32_t)(US_STOP+TRIM+pct*5)*65536/20000;  // 50 Hz, 16 bit : ±100% → ±500 us
#if LEDC_V3
  ledcWrite(PIN_SERVO, duty);
#else
  ledcWrite(CH, duty);
#endif
}
float readTemp(){ int a=analogRead(PIN_NTC);
  float r=10000.0*a/(4095.0-a+1);
  return 1.0/(1.0/298.15+log(r/10000.0)/3950.0)-273.15; }
float readVbat(){ return analogRead(PIN_VBAT)*3.3*2.0/4095.0; }
bool leak(){ return analogRead(PIN_LEAK)<1200; }
void fault(String w){ mode=FAULT_MODE; faultCause=w; writeServo(0); }
String statusTxt(){ String s="T:"+String(tServo,1)+"C V:"+String(vBat,2)+" R:"+String(rpm,1)+"tr/min";
  if(mode==FAULT_MODE) s+=" FAUTE:"+faultCause;
  if(mode==PAUSED_HOT) s+=" PAUSE-CHAUD"; return s; }

void handleCmd(String c){                       // commun WiFi + BLE
  c.trim(); c.toUpperCase();
  if(c.startsWith("V")){ speedPct=c.substring(1).toInt(); remote=true; lastCmd=millis(); }
  else if(c=="S"){ speedPct=0; remote=true; lastCmd=millis(); }
  else if(c=="A"){ remote=false; }
  else if(c=="R"){ if(mode==FAULT_MODE && !leak()){ mode=RUN; stallRetries=0; faultCause=""; } }
}

#if ENABLE_WIFI
WebServer srv(80);
const char PAGE[] PROGMEM = R"html(<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no,viewport-fit=cover">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<meta name="theme-color" content="#041018">
<title>EXO-MEDUSA</title>
<style>
*{box-sizing:border-box;-webkit-tap-highlight-color:transparent}
html,body{margin:0;min-height:100%;color:#d4eefc;
font-family:-apple-system,BlinkMacSystemFont,Segoe UI,sans-serif;text-align:center}
body{background:#030b12 radial-gradient(ellipse at 50% -10%,#0c4a6e 0%,#082032 38%,#030b12 70%);
padding:calc(14px + env(safe-area-inset-top)) 16px calc(24px + env(safe-area-inset-bottom))}
.bell{width:72px;height:48px;margin:4px auto 2px;border-radius:36px 36px 8px 8px;
background:radial-gradient(circle at 50% 30%,#7ec8ff 0%,#1a6a9a 45%,transparent 70%);opacity:.85}
h1{margin:0;font-size:1.28rem;letter-spacing:.22em;font-weight:650;color:#bfe9ff;text-shadow:0 0 18px #3aa8e0}
.tag{margin:.25rem 0 12px;font-size:.68rem;letter-spacing:.28em;text-transform:uppercase;opacity:.55}
.hint{background:rgba(10,40,64,.7);border:1px solid #1a4e72;border-radius:14px;padding:10px 12px;margin:0 0 14px;
font-size:.78rem;line-height:1.45;color:#9ccce8}
.hint b{color:#e8f6ff}
.live{display:inline-block;width:8px;height:8px;border-radius:50%;background:#3d6a80;margin-right:6px;vertical-align:middle}
.live.on{background:#5ee0a0;box-shadow:0 0 8px #5ee0a0}
.grid{display:grid;grid-template-columns:1fr 1fr;gap:8px;margin:0 0 12px}
.tile{background:rgba(8,28,44,.85);border:1px solid #16425e;border-radius:14px;padding:12px 8px;min-height:64px}
.tile b{display:block;font-size:1.28rem;color:#eef8ff;font-variant-numeric:tabular-nums}
.tile span{font-size:.62rem;letter-spacing:.14em;text-transform:uppercase;opacity:.5}
.fault{display:none;background:#3a1218;color:#ff9a9a;border:1px solid #8a3038;border-radius:14px;
padding:12px 14px;margin:0 0 12px;font-size:.9rem;min-height:44px;line-height:1.35}
.row{display:flex;gap:8px;margin:8px 0}
button{flex:1;min-height:52px;border:0;border-radius:16px;font-size:1.02rem;font-weight:700;letter-spacing:.08em;
color:#eef8ff;background:#14344c;cursor:pointer;touch-action:manipulation}
button.go{background:linear-gradient(180deg,#1c88b0,#0d5a78);min-height:64px;font-size:1.25rem}
button.stop{background:linear-gradient(180deg,#b04050,#6a1828);min-height:64px;font-size:1.25rem}
button.auto{background:linear-gradient(180deg,#1a5a82,#0e3048)}
button.rev{background:linear-gradient(180deg,#2a4a6a,#163040)}
button.quiet{background:#0e2436;color:#8eb4cc;font-weight:600;letter-spacing:.04em}
button:active{transform:scale(.97);filter:brightness(1.1)}
.sl{margin:10px 4px 0}
input[type=range]{-webkit-appearance:none;appearance:none;width:90%;height:44px;background:transparent;margin:0}
input[type=range]::-webkit-slider-runnable-track{height:8px;background:#15344c;border-radius:8px}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:28px;height:28px;margin-top:-10px;
border-radius:50%;background:#8ad4ff;box-shadow:0 0 12px #4ab4e8}
.spd{margin:0 0 8px;font-size:1.05rem}
.ok{color:#7ee0b0}.warn{color:#ffcc66}.bad{color:#ff8a8a}
.foot{margin-top:16px;font-size:.68rem;opacity:.4;line-height:1.4}
</style>
</head>
<body>
<div class="bell"></div>
<h1>EXO-MEDUSA</h1>
<div class="tag">v6 kit · phone remote</div>
<div class="hint"><span class="live" id="dot"></span>Connect to Wi-Fi <b>EXO-MEDUSA</b>, password <b>medusa123</b>, then open <b>http://192.168.4.1</b></div>
<div class="fault" id="fault"></div>
<div class="grid">
<div class="tile"><b id="t">—</b><span>temp °C</span></div>
<div class="tile"><b id="v">—</b><span>battery V</span></div>
<div class="tile"><b id="rpm">—</b><span>rpm</span></div>
<div class="tile"><b id="mode">—</b><span>mode</span></div>
</div>
<div class="row">
<button type="button" class="go" id="bSwim">SWIM</button>
<button type="button" class="stop" id="bStop">STOP</button>
</div>
<div class="row">
<button type="button" class="auto" id="bAuto">AUTO</button>
<button type="button" class="rev" id="bRev">REV</button>
</div>
<div class="sl"><input id="sl" type="range" min="-100" max="100" value="0"></div>
<div class="spd">speed <b id="sv">0</b>%</div>
<div class="row"><button type="button" class="quiet" id="bRst">RESET FAULT</button></div>
<div class="foot">BLE still works as backup · last command wins</div>
<script>
function $(i){return document.getElementById(i)}
function cmd(x){fetch('/c?x='+encodeURIComponent(x))}
var drag=0;
$('bSwim').onclick=function(){cmd('V55');$('sl').value=55;$('sv').textContent=55};
$('bStop').onclick=function(){cmd('S');$('sl').value=0;$('sv').textContent=0};
$('bAuto').onclick=function(){cmd('A')};
$('bRev').onclick=function(){cmd('V-35');$('sl').value=-35;$('sv').textContent=-35};
$('bRst').onclick=function(){cmd('R')};
$('sl').oninput=function(){drag=1;$('sv').textContent=this.value};
function setV(){cmd('V'+$('sl').value);drag=0}
$('sl').onchange=setV;
$('sl').addEventListener('touchend',setV);
function poll(){
fetch('/status').then(function(r){return r.json()}).then(function(j){
$('dot').className='live on';
$('t').textContent=Number(j.t).toFixed(1);
$('v').textContent=Number(j.v).toFixed(2);
$('rpm').textContent=Number(j.rpm).toFixed(1);
$('mode').textContent=j.mode+(j.remote?' · remote':' · auto')+(j.running?'':' · off');
$('mode').className=j.mode=='FAULT'?'bad':(j.mode=='PAUSED_HOT'?'warn':'ok');
if(j.fault){$('fault').style.display='block';$('fault').textContent=j.fault}
else $('fault').style.display='none';
if(!drag){$('sl').value=j.cmd;$('sv').textContent=j.cmd}
}).catch(function(){$('dot').className='live'});
}
setInterval(poll,1000);poll();
</script>
</body>
</html>)html";

String jsonStatus(){
  const char* m="RUN";
  if(mode==PAUSED_HOT) m="PAUSED_HOT";
  else if(mode==FAULT_MODE) m="FAULT";
  String f=faultCause;
  f.replace("\\","\\\\"); f.replace("\"","\\\"");
  String s; s.reserve(192);
  s+="{\"t\":"; s+=String(tServo,1);
  s+=",\"v\":"; s+=String(vBat,2);
  s+=",\"rpm\":"; s+=String(rpm,1);
  s+=",\"mode\":\""; s+=m;
  s+="\",\"fault\":\""; s+=f;
  s+="\",\"running\":"; s+=(running?"true":"false");
  s+=",\"remote\":"; s+=(remote?"true":"false");
  s+=",\"cmd\":"; s+=cmdNow;
  s+='}';
  return s;
}
void sendPage(){ srv.send_P(200,"text/html",PAGE); }
#endif

#if ENABLE_BLE
BLECharacteristic *bleTx=nullptr; bool bleUp=false;
class SrvCB: public BLEServerCallbacks {
  void onConnect(BLEServer*){ bleUp=true; }
  void onDisconnect(BLEServer* s){ bleUp=false; s->getAdvertising()->start(); } };
class RxCB: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* ch){
    String v=String(ch->getValue().c_str());
    handleCmd(v);
    if(v=="?" && bleTx){ bleTx->setValue(statusTxt().c_str()); bleTx->notify(); } } };
#endif

void setup(){
  pinMode(PIN_REED,INPUT_PULLUP); pinMode(PIN_LEAK,INPUT);
  analogReadResolution(12);
#if LEDC_V3
  ledcAttach(PIN_SERVO, 50, 16);
#else
  ledcSetup(CH, 50, 16); ledcAttachPin(PIN_SERVO, CH);
#endif
  writeServo(0);
  hallBase=analogRead(PIN_HALL);
#if ENABLE_LED
  led.begin(); led.show();
#endif
  esp_task_wdt_config_t w={.timeout_ms=8000,.idle_core_mask=0,.trigger_panic=true};
  esp_task_wdt_init(&w); esp_task_wdt_add(NULL);

#if ENABLE_WIFI
  WiFi.softAP("EXO-MEDUSA","medusa123");
  srv.on("/", sendPage);
  srv.on("/hotspot-detect.html", sendPage);
  srv.on("/generate_204", sendPage);
  srv.on("/c",[](){ handleCmd(srv.arg("x")); srv.send(200,"text/plain","ok"); });
  srv.on("/status",[](){ srv.send(200,"application/json",jsonStatus()); });
  srv.onNotFound(sendPage);
  srv.begin();
#endif
#if ENABLE_BLE
  BLEDevice::init("EXO-MEDUSA");
  BLEServer* bs=BLEDevice::createServer(); bs->setCallbacks(new SrvCB());
  BLEService* svc=bs->createService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
  bleTx=svc->createCharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E",
        BLECharacteristic::PROPERTY_NOTIFY);
  bleTx->addDescriptor(new BLE2902());
  BLECharacteristic* rx=svc->createCharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E",
        BLECharacteristic::PROPERTY_WRITE|BLECharacteristic::PROPERTY_WRITE_NR);
  rx->setCallbacks(new RxCB());
  svc->start(); bs->getAdvertising()->addServiceUUID(svc->getUUID());
  bs->getAdvertising()->start();
#endif
  lastPulse=millis();
}

void pollHall(){
  int d=abs(analogRead(PIN_HALL)-hallBase);
  if(d>HALL_DELTA && !hallHigh){ hallHigh=true; pulseCount++; lastPulse=millis(); }
  else if(d<HALL_DELTA/2) hallHigh=false;
}

void loop(){
  esp_task_wdt_reset();
#if ENABLE_WIFI
  srv.handleClient();
#endif
  pollHall();

  static uint32_t tMeas=0;
  if(millis()-tMeas>500){ tMeas=millis();
    tServo=0.7*tServo+0.3*readTemp(); vBat=0.8*vBat+0.2*readVbat();
    uint32_t dt=millis()-lastRpmCalc;
    if(dt>3000){ rpm=pulseCount*60000.0/(2.0*dt); pulseCount=0; lastRpmCalc=millis();
#if ENABLE_BLE
      if(bleUp && bleTx){ bleTx->setValue(statusTxt().c_str()); bleTx->notify(); }
#endif
    } }

  if(leak()) fault("FUITE - ouvrir et secher la capsule");
  if(vBat<V_LOW && millis()>15000){ writeServo(0);
    esp_deep_sleep_enable_gpio_wakeup(1ULL<<PIN_REED,ESP_GPIO_WAKEUP_GPIO_LOW);
    esp_deep_sleep_start(); }
  if(tServo>T_FAULT) fault("Surchauffe servo >65C");

  if(digitalRead(PIN_REED)==LOW){
    if(!reedDown) reedDown=millis();
    if(millis()-reedDown>3000){ writeServo(0);
      esp_deep_sleep_enable_gpio_wakeup(1ULL<<PIN_REED,ESP_GPIO_WAKEUP_GPIO_LOW);
      esp_deep_sleep_start(); }
  } else if(reedDown){
    if(millis()-reedDown<1000){
      if(mode==FAULT_MODE && !leak()){ mode=RUN; stallRetries=0; faultCause=""; }
      else running=!running; }
    reedDown=0; }

  if(mode==FAULT_MODE || !running){ cmdNow=0; writeServo(0); delay(10); return; }

  int capPct=100;
  if(mode==PAUSED_HOT){ cmdNow=0; writeServo(0); if(tServo<T_RESUME) mode=RUN; delay(10); return; }
  if(tServo>T_PAUSE){ mode=PAUSED_HOT; writeServo(0); delay(10); return; }
  if(tServo>T_SOFT) capPct=40;

  int cmd;
  if(remote && millis()-lastCmd<120000) cmd=speedPct;
  else { uint32_t t=millis()%(SWIM_MS+GLIDE_MS); cmd=(t<SWIM_MS)?SWIM_SPEED:0; }
  cmd=constrain(cmd,-capPct,capPct);
  cmdNow=cmd;

  if(abs(cmd)>25 && millis()-lastPulse>STALL_WIN){
    stallRetries++;
    if(stallRetries>3) fault("Rotor bloque/patinage - came et suiveurs");
    else { writeServo(0); delay(400); esp_task_wdt_reset();
           writeServo(-cmd/2); delay(600); esp_task_wdt_reset();
           writeServo(0); delay(200); lastPulse=millis(); } }
  if(millis()-lastPulse<1200) stallRetries=0;

#if ENABLE_LED
  static uint32_t tLed=0;
  if (millis()-tLed>80){ tLed=millis();
    float ph = 2*3.14159f*(millis()%(SWIM_MS+GLIDE_MS))/(float)SWIM_MS;
    ledStatus(mode==FAULT_MODE?2:(mode==PAUSED_HOT?1:0), cmd!=0, ph); }
#endif
  writeServo(cmd);
  delay(10);
}
