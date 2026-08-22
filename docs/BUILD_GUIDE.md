# EXO-MEDUSA Build Guide

**Consumer kit v6 · Bambu Lab A1**

A first tank-swim jellyfish. English. Short steps. Print this PDF twin at
`docs/EXO-MEDUSA_Build_Guide.pdf`. Do not change the STLs or the firmware.

---

## What you are building

You are building **EXO-MEDUSA**: an aquarium jellyfish about **Ø 280 × 380 mm**.

A dry electronics capsule sits in the middle. A 360° servo turns magnets
*inside* the can. Matching magnets *outside* follow through the wall. A
3-lobe cam then pumps a sliding ring **10 mm**, three times per turn. The
ring bends **eight tentacles** inward together. That pulse is the swim.

- Your **phone browser is the remote**. No app.
- There is **no steering**. It pulses and drifts. That is this kit.
- **No electrical part lives in the water.** The servo, battery, and ESP32
  stay dry inside the capsule.
- Firmware is **v6**. Leak sense is on **GPIO4** (not GPIO5 from the old
  French notice).

Drive is a **360° continuous servo**: **DS04-NFC** or **MG996R 360**. Not a
Furitek brushless motor. Not an ESC.

Tentacles in this kit are a **TPU paddle** (the original zip’s file 21,
22 × 209 mm) plus a **PET film** plus a **PETG barrette**. Kit path:
`print/stl/optional/legacy_21_flanc_TPU_NOT_piece19.stl` ×8, and
`print/stl/20_tentacle_bar_PETG_x8.stl` ×8 (alias `20_barrette_PETG_x8.stl`).
That paddle is not the missing Fin-Ray ladder from the French notice. It
still fits the 8.6 × 3.0 mm slots and will pulse in a tank. Do not print
`19_tentacle_skeleton_TPU_x8.stl` for these steps — different mesh.

Budget two weekends. One screwdriver. Super glue. A Bambu Lab A1.

---

## Safety — read this first

**N52 magnets.** They pinch hard and chip if they slam together. Keep them
away from children. **A swallowed N52 magnet is lethal.** Two magnets (or
one magnet and a metal object) can trap bowel. This is not a toy drawer.

**18650 cells.** Never short the + and − tabs. Never puncture. Charge only
through the **TP4056** module. No bare-cell chargers.

**CA glue (cyanoacrylate).** It bonds skin in about five seconds. Ventilate.
Have acetone or a CA debonder nearby. Not near eyes.

**Servo 5 V.** The servo red wire goes to the **boost 5 V output**. Do **not**
feed servo current through the ESP32. The ESP32 may share that same 5 V rail.
A **470 µF** capacitor sits across the servo 5 V (long leg on +). Missing
that cap is why a servo twitches and will not turn.

**Aquarium silicone.** 100 % clear. **No fungicide. No anti-mould.** Bathroom
silicone can kill fish and is the wrong tube.

**Bayonet lid.** Never force it. If it fights you, a wire is on the O-ring.

**Wet-side magnets.** The outer rotor lives in water. Nickel plating is not
enough. Coat every glued magnet with nail varnish or a thin epoxy film.

**Unsealed float dome.** If the dome leaks, the robot inverts. The dome is
the float, not decoration.

---

## What you need

Buy on Lazada / Shopee Thailand (or anywhere). Search terms below. Prices
are ballpark THB from the kit shop list, **except the servo** (the old BOM
had the wrong motor).

### Electronics

| What | Qty | Search | ~THB |
|---|---|---|---|
| 360° continuous servo (DS04-NFC or MG996R 360) | 1 | `DS04-NFC 360` or `MG996R 360 continuous` | — |
| ESP32-C3 SuperMini | 1 | ESP32-C3 SuperMini | 105 |
| 18650 + holder (3000 mAh) | 1 | 18650 battery holder | 140 |
| TP4056 **with protection** (DW01) | 1 | TP4056 protection | 35 |
| 5 V boost ≥ 2 A (MT3608) | 1 | MT3608 boost 5V | 35 |
| 470 µF 10 V electrolytic | 1 | 470uF electrolytic | 17.5 |
| SS49E linear Hall | 1 | SS49E hall sensor | 17.5 |
| NTC 10k B3950 | 1 | NTC 10k 3950 | 17.5 |
| Reed switch + a small magnet | 1 | reed switch glass | 35 |
| Resistors: 10k ×1, 100k ×2, 470k ×1 | 1 kit | resistor kit | 35 |

Servo 5 V comes from the boost, **not** through the ESP32. 470 µF sits
across that servo 5 V rail.

### Mechanics and glue

| What | Qty | Search | ~THB |
|---|---|---|---|
| N52 magnets 8 × 3 mm | 12 | N52 8x3 magnet | 105 |
| N52 magnets 5 × 2 mm | 2 | N52 5x2 magnet | 35 |
| NBR O-ring ~53 × 3 mm | 1 | o-ring 53x3 | 35 |
| Silicone grease (plumbing, not automotive) | 1 | silicone grease plumbing | 70 |
| PET film 0.3 mm A4 | 10 sheets | PET sheet 0.3mm A4 | 70 |
| M3 screws: 16 mm ×2, 10 mm ×3, 8 mm ×5 | 1 kit | M3 screw kit | 70 |
| Fishing sinkers ~40 g | 1 | fishing sinkers split shot | 70 |
| Aquarium silicone 100 % clear, **no fungicide** | 1–2 | aquarium silicone sealant clear 100% | 175 |
| 5-minute epoxy | 1 | epoxy glue 5 minutes | 70 |
| CA glue (super glue) | 1 | super glue CA | — |
| Thermal pad + a bit of foam | 1 | thermal pad servo | — |
| Nail varnish (wet-side magnets) | 1 | household | — |

Plus a PH1 screwdriver, cutter, metal rule, basic soldering iron, USB-C
**data** cable (not charge-only).

### Filament (Bambu Lab A1)

| Filament | ~mass | Use |
|---|---|---|
| PETG | ~450 g | capsule, stator, cam, ring, axle, rotors, barrettes |
| Transparent PETG | ~95 g | float dome 13e / disk 13f / plug 13g |
| TPU 95A | ~60 g | tentacle paddles ×8 (file 21) |

### Do not buy for this first swim

- Furitek Mini-Komodo (wrong drive)
- WS2812 LED ring
- SG90 (pendulum steering is not in this firmware)
- Qi wireless TX/RX
- Silicone tentacle molds (`22_moule_*`)

Priced rows above ≈ **1060 THB + servo + filament + CA / thermal pad**.

---

## Bambu Lab A1 print plan

Printer: **Bambu Lab A1**. Bed **256 × 256 × 256 mm**. Nozzle 0.4 mm.
A1 is **direct drive**, so TPU 95A at 30 mm/s is fine.

**There is no kit slicer profile.** Use Bambu Studio **Generic PETG** and
**Generic TPU**. Follow the table. Do not invent PLA.

### Print these five first — then stop

Magnet test: **01, 03, 04, 05, 07**. Glue magnets. Test through 3 mm
cardboard. Only then print the rest.

### Plates (suggested)

The A1 bed fits these groupings. Leave ~6 mm between parts.

| Plate | Files | Material | Notes |
|---|---|---|---|
| **1 — magnet test** | `01_capsule_upper.stl` · `03_stub_axle.stl` · `04_rotor_inner.stl` · `05_rotor_outer.stl` · `07_top_cap.stl` | PETG | Print, then **stop** for steps 1–4 |
| **2 — frame** | `08_stator.stl` · `09_slider_ring.stl` | PETG | Stator is 126 mm; ring is 113 mm. Side by side just fits |
| **3 — body + drive** | `02_fuselage.stl` · `06_cam_3lobe.stl` · `18_ballast_trellis.stl` · `20_tentacle_bar_PETG_x8.stl` ×8 | PETG | Fuselage stands 147 mm tall — under the 256 mm lid |
| **4 — float dome** | `13_float_dome.stl` | **Transparent PETG** | 160 mm across. One part per plate |
| **5 — float extras** | `13_float_disk.stl` · `13_float_plug.stl` | Transparent PETG | Disk is 145 mm. Do not put it on plate 4 |
| **6 — tentacles** | `optional/legacy_21_flanc_TPU_NOT_piece19.stl` ×**8** | **TPU 95A** | Each paddle is 22 × 209 mm (file 21). Eight in a row fit one A1 plate. 30 mm/s max |

Optional second TPU plate if the first warps or you want a spare.

### Orientation and settings (from the v6.2 notice)

| File | On the bed | Settings |
|---|---|---|
| 01 capsule | **Upside down**, top face on the bed | 40 % infill, 4 walls, **no support** |
| 02 fuselage | Collar on the bed, tail in the air | 4 walls, **no support** |
| 03 axle, 07 cap | Flat | **100 %** infill |
| 04 inner rotor | Magnet holes facing the bed | 50 % infill |
| 05 outer rotor, 06 cam | Upright, **large opening up** | 3–4 walls, **no support** |
| 08 stator | Upright | **Tree Slim** supports **under the ring only** |
| 09 sliding ring | Flat, bosses up | 3 walls |
| 19 TPU paddle (file 21) ×8 | Flat | TPU 95A, **30 mm/s max** |
| 20 tentacle bar ×8 | Flat, teton up | PETG, one plate |
| 13e / 13f / 13g | Skirt on bed / flat | Transparent PETG, **no support** |
| 18 ballast trellis | Bucket on the bed | 4 walls |

**Supports:** none, except the stator tree-slim under the ring. That is the
only support in this kit.

**Do not print** for a first swim: silicone molds, old clamp/rib/paddle
STLs, or `19_tentacle_skeleton_TPU_x8.stl` (a different reconstructed mesh).
The paddle you want is **`optional/legacy_21_flanc_TPU_NOT_piece19.stl`**
(original zip file 21). The barrette is **`20_tentacle_bar_PETG_x8.stl`**.

---

## Magnet test first

Print plate 1. Do **not** queue plates 2–6 yet.

1. Glue the six 8 × 3 mm magnets into **04** (step 1). Alternate N / S.
2. Screw 04 onto the servo horn (step 2).
3. Glue the six 8 × 3 mm magnets into **05** in the **opposite** pattern,
   plus two 5 × 2 mm Hall pips (step 3). Varnish the wet side.
4. Bolt axle **03** onto capsule **01** (step 4).

**Pass:** with ~3 mm of cardboard between 04 and 05, turning one rotor
turns the other. They snap into alignment. They must **attract**, not
repel.

**Fail:** one magnet is flipped. Soak, pop, re-glue. Fix this *before* you
spend PETG on the stator and cam.

How to find N and S: stack all twelve 8 × 3 mm magnets. They sort
themselves. Mark the top of the pile with a pen. Every marked face is the
same pole. Hole 1 = mark up. Hole 2 = mark down. Hole 3 = mark up. And so
on. For the outer rotor, **invert** that pattern.

---

## Cut eight films (do this while PETG prints)

File: `docs/GABARIT_FLANCS_1-1.pdf`

**Print that gabarit PDF on its own, at 100 % / actual size.** Do not
“fit to page.” Do **not** cut films from a thumbnail in this guide. The
outline is 212 mm long. A scaled print is waste.

1. Measure the **50.0 mm** control square on the paper. If it is not 50.0
   mm, reprint and fix the scale.
2. Tape or spray-mount the sheet on **0.3 mm PET**. One A4 holds two
   outlines → two films.
3. Cut the **solid** line with a cutter and a metal rule. Keep the 12 × 12
   mm teton at the root.
4. Before peeling, mark dashed **B1–B6** with a fine pen (placement guide
   along the TPU spine).
5. Repeat until you have **8 identical films**. Not 16.

Fold test: a film folded in half must spring back with **no white crease**.
A white crease means cheap PS, not PET. Buy again.

---

## Assembly 1–14

Have CA, silicone grease, PH1, and the varnished magnets ready.

### 1 — Inner rotor magnets (part 04)

Lay 04 flat, six round holes toward you. One CA drop per hole. Push each
8 × 3 mm magnet home so it is **flush**, not proud. Alternate N / S.

**Check:** a paperclip sticks to every magnet. Nothing sticks up.

A magnet glued the wrong way means the robot will not drive. Go slow.

### 2 — Screw 04 onto the servo

Clip the round servo horn onto the servo shaft. Set 04 on it, **magnets
up** (away from the servo). Four small screws through the rotor into the
horn. Spin by hand. It must run true.

**Check:** hold the rotor, turn the servo body. It must not unscrew.

### 3 — Outer rotor magnets (part 05)

Flip 05. The six magnet holes sit **under** the disk. Glue six 8 × 3 mm
magnets, **inverse** of 04. Glue both 5 × 2 mm magnets in the two small
edge pockets (Hall pips). Same way for both; polarity does not matter.

Test **before** the CA dies: hold 04 and 05 face to face with 3 mm
cardboard. They must attract and self-align.

**This rotor lives in water.** Varnish or thin-epoxy every magnet.

**Check:** turn one rotor; the other follows through the card. That is the
coupling through the capsule wall.

### 4 — Axle on the capsule (01 + 03)

Stand the capsule, top toward you. Three drilled bosses. Axle flange
matches. Three **M3 × 10**. Snug, do not strip. Silicone grease on the
whole axle stem and the flat thrust ring.

**Check:** the axle is vertical. It does not wiggle.

### 5 — Stator frame (08)

The stator **only goes on from the top**. It will not pass the fuselage
end. Slide until the split collar sits **10 mm below** the capsule
shoulder. Two **M3 × 16** in the collar ears. Cinch. The frame must not
rotate or slide by hand.

**Check:** three round columns are vertical. Three arms join the collar to
the columns (that is the v6 fix).

### 6 — Servo into the can

Lower the servo + inner rotor through the **bottom** opening, rotor **up**,
until it sits ~1 mm under the thin magnet roof.

CA the **NTC** onto the servo metal side. That side against the capsule
wall with a **thermal pad**. Foam on the other side. Heat leaves into the
water.

CA the **Hall** sensor flat under the roof, **28 mm from centre** (just
under the edge of the thin zone). Three wires drop to the ESP32. Servo
leads hang down for step 11.

**Check:** spin the outer rotor on top (not yet fitted). The inner rotor
follows through the wall.

### 7 — Outer rotor on the axle

Grease the centre hole of 05. Slide it on, **magnets down**. It will
*clack* onto the inner magnets. That is correct. Spin. It must ride the
thrust ring and **not** scrape the capsule.

**Check:** one finger turns it. You feel the inner rotor follow.

### 8 — Three-lobe cam + sliding ring

Look at the cam: three straight inner keys, a **wavy 3-lobe groove**
outside. Slide it onto the three tabs of the outer rotor, all the way
down.

Grease the wavy groove and the three stator columns.

Present the sliding ring **bosses up**: three holes on the three columns,
three pins pointing in. Lower it while turning the cam by hand so the
pins enter the groove.

Cap **07** on the axle. One **M3 × 8** in the centre.

Hard spot? A burr in the groove. Wrap 240-grit on a toothpick, then
re-grease.

**Check:** turning the cam by hand, the ring rises and falls **10 mm**,
stays flat, three times per turn, no force.

### 9 — Eight tentacles

Each tentacle = **1 TPU paddle (file 21)** + **1 PET film** + **1 PETG
barrette (20)**.

This paddle has a spine and a fishtail. It has **no Fin-Ray pads**. Do not
hunt for fourteen pads.

1. Lay the TPU paddle flat, teton up.
2. A **thin** CA line on the spine only. Not a flood.
3. Press the film on in one go, centred on the spine. B1–B6 are a
   placement guide. Palm for 10 seconds.
4. Glue the film’s 12 × 12 mm teton into the barrette **cuvette** (a blob
   of CA, 10 s).
5. Do all eight. No ribs to thread.

**Hang map (do not mix these up):**

- **Barrette teton → stator** (fixed ring, slots 8.6 × 3.0)
- **TPU teton → sliding ring**
- **Film teton → barrette cuvette**

**Check:** push the mid-span. It should curve toward your finger and
spring back. If it is a board, too much glue hit the spine. Peel the PET
with a cutter, clean, glue a thinner line.

### 10 — Hang tentacles on both rings

1. **Fixed ring** (top of the stator): barrette teton **from below** into
   each of the eight slots. A drop of CA. Films now hang from the frame.
2. Turn the cam until the sliding ring is **LOW**.
3. **Sliding ring:** TPU teton **from below** into its eight slots. A drop
   of CA (TPU holds better with it).
4. Order: eight barrettes first, ring low, then eight paddles.
5. No film rubbing a column while the CA sets.

A tentacle that beats out of time usually has its barrette and TPU swapped.

**Check:** turn the cam by hand. All eight curve **inward**, then release,
together. That is the pulse.

Root play of 2 mm eats half the stroke. Push tetons fully home.

### 11 — Wiring (leak on GPIO4)

The French notice said leak on **GPIO5**. That pin has **no ADC** on the
ESP32-C3. Kit firmware v6 reads leak on **GPIO4**. Wire it there.

```
18650  →  TP4056 B+ / B-  →  boost IN  →  boost 5 V OUT
                                              ├─ servo RED
                                              ├─ ESP32 5V pin
                                              └─ 470 µF  (long leg on +)

All blacks / browns together  =  GND

Servo yellow     →  GPIO10
Reed switch      →  GPIO3 and GND     (tap = run/stop or fault reset; 3 s = sleep)
NTC              →  GPIO0 and GND  +  10k from GPIO0 to 3.3 V
Battery divider  →  100k / 100k from pack + to GPIO1
Hall SS49E       →  3.3 V / GND / GPIO2
Leak probe       →  two bare wires at the lowest point of the capsule
                    +  470k from GPIO4 to 3.3 V     ★ GPIO4, not GPIO5
```

Set the boost to **5.0 V** (gold screw; a multimeter helps). Fixed-5 V
modules are fine.

Park the pack against the wall. CA the reed on the inner wall so you can
swipe the magnet from outside.

Leave `ENABLE_LED 0`. The LED ring would steal GPIO4 from the leak probe.

### 11b — Flash firmware

Board: **ESP32C3 Dev Module**. **USB CDC On Boot = Enabled**.

1. Install Arduino IDE from arduino.cc.
2. File → Preferences → Additional boards manager URLs:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. Boards Manager: **esp32 by Espressif Systems** (3.x is fine; the sketch
   also speaks 2.x LEDC).
4. Tools → Board → esp32 → **ESP32C3 Dev Module**.
5. Tools → **USB CDC On Boot = Enabled**.
6. USB-C data cable. Pick the port. If none: hold **BOOT** while plugging
   in, then release.
7. Open `firmware/firmware_medusa.ino` → Upload. Success looks like
   “Hash of data verified” / “Done uploading”. Failed to connect: BOOT
   trick again.

Leave flash size, frequency, partition, and upload speed on Arduino
defaults (typically 80 MHz, QIO, 4 MB, 921600). SuperMini is usually 4 MB.

No extra library for tank swim (`ENABLE_LED 0`).

### 11c — Phone remote

The jellyfish is its own Wi-Fi access point. Your phone browser is the
remote. No app. There is **no internet** on this network. That is normal.

SoftAP: **EXO-MEDUSA** / **medusa123** → **http://192.168.4.1**

**iPhone (Safari)**

1. Settings → Wi-Fi → join **EXO-MEDUSA**, password **medusa123**.
2. iOS may pop a “Log in” captive-portal page. That *is* the remote. Do
   not tap Cancel / Use without internet if you want the page to stay.
3. If nothing pops: Safari, type **http://192.168.4.1** (type it, do not
   Google it).
4. Toggle Wi-Fi if needed. Turn off VPN / iCloud Private Relay on this
   network.
5. Optional: Share → Add to Home Screen. Still just the browser.

**Android (Chrome)**

1. Join **EXO-MEDUSA**, password **medusa123**.
2. “Connected without internet” is correct. Stay. Disable auto-switch to
   mobile data if the phone hops away.
3. A “Sign in to network” banner may appear — open it. Else Chrome →
   **http://192.168.4.1**
4. If Chrome searches: type `http://` in front.

| Control | What it does |
|---|---|
| **SWIM** | Forward 55 % (remote; auto resumes after 120 s idle) |
| **STOP** | Speed 0 |
| **AUTO** | Built-in 8 s swim / 4 s glide at 42 % |
| **REV** | Reverse nudge (−35 %) |
| Slider | −100 % … +100 % |
| **RESET FAULT** | Clears a fault if the leak is gone |

Tiles (temp °C, battery V, RPM, mode, fault) poll `/status` every 1 s.

**BLE backup:** Android *Serial Bluetooth Terminal* (Bluetooth LE tab) or
iPhone *BLE Terminal*. Device `EXO-MEDUSA`. Text: `V50`, `V-40`, `S`,
`A`, `?`, `R`. Last order wins (Wi-Fi or BLE). The C3 is BLE only — it
will never appear in the phone’s headphone Bluetooth list.

If Wi-Fi + BLE together make the board flaky: `#define ENABLE_BLE 0` and
re-flash.

### 12 — O-ring and fuselage

Stretch the **53 × 3 mm** NBR O-ring into the groove at the end of the
fuselage plug. Grease it generously. Silicone grease *is* the seal.

Electronics go in through the fuselage opening: battery at the bottom,
boards along the wall.

Present fuselage under the capsule: three lugs facing three vertical
slots. Push home, then a sixth of a turn. Locked.

Never force it. Resistance = a wire on the joint.

**Check:** it does not unwind by itself. The shoulder sits flush.

### 13 — Float dome + ballast trellis

The dome is the **float**. Its chamber must be watertight (~195 cm³).

A continuous bead of **aquarium silicone (no fungicide)** on the inner
shoulder. Press disk **13f** on. Smooth with a finger. Silicone the apex
plug **13g** into the top hole. **Wait 24 hours.**

**Float test:** hold the dome alone underwater 10 minutes. **Zero
bubbles.** One bubble = redo that spot.

Sit the dome on the stator’s top ring. The lip self-centres. Three glue
dots.

Clip the ballast trellis onto the fuselage tail teton (three bosses in
the groove). About **40 g** of fishing sinkers in the bucket. Fine-tune
in step 14.

**Check:** the sealed dome floats hard on its own in a bucket. That is
what keeps the jelly head-up.

### 14 — Three tests before a tank

**Test 1 — dry pulse.** Power on. Stand the robot on a glass. All eight
tentacles must curl together about once a second (8 s swim / 4 s pause
at 42 % in AUTO).

**Test 2 — 24 h leak.** A paper towel **inside** the capsule. Close.
Weight it. Leave the capsule **24 h** at the bottom of a bucket of water.
The paper must come out **dry**. Wet paper = do not swim. Re-grease the
O-ring, twist it a quarter turn in its groove, repeat.

**Test 3 — tank trim.** Whole robot in water. Add or remove sinkers until
it sinks **very slowly**, upright, dome up. Swim will make up the rest.

Swipe the reed magnet to start/stop. Hold **3 seconds** for deep sleep.

Then film it. You earned that.

---

## Troubleshooting

**Stall / “Rotor bloque” / FAULT: rotor blocked**
The Hall no longer sees the outer rotor. Debris in the cam groove, a
follower pin jammed, or magnets too far. Firmware tries three reverse
kicks, then faults. Clean the groove. Turn by hand. **RESET FAULT** on
the phone page, or a magnet tap on the reed. If it still slips: re-glue
outer magnets 0.3 mm proud.

**Leak fault / “FUITE — ouvrir et secher la capsule”**
GPIO4 saw a wet analog reading (threshold &lt; 1200). Open. Dry. Find the
path (O-ring, bayonet, a wire in the groove). Re-grease. 24 h paper-towel
test again. RESET FAULT only after the leak is gone. Confirm the 470k
pull-up is on **GPIO4**, not GPIO5.

**Won’t join Wi-Fi / no page**
Stay on **EXO-MEDUSA**. There is no internet — phones love to hop away.
Disable “auto switch to mobile data.” Type **http://192.168.4.1**, do not
search. iPhone: use the captive-portal page; skip VPN / Private Relay.
If the SSID never appears: ESP32 has no 5 V, empty 18650, or a charge-only
USB cable during flash. TP4056 LED should show charge/idle.

**Servo twitch, will not turn = missing 470 µF**
The servo brown-outs on the 5 V rail. Fit **470 µF 10 V** across servo
5 V, long leg on +. Feed that rail from the **boost**, never through the
ESP32. Weak pack or a boost under 2 A looks the same. Set 5.0 V.

**Pulses but does not go forward**
Too heavy or too light — redo trim. Reverse the speed on the phone page.
Check tentacles curl **inward** on the down-stroke.

**One tentacle out of time**
Film unstuck, or barrette and TPU swapped on that station.

**Floats tilted or inverts**
Dome chamber leaking (bucket test: zero bubbles) or not enough tail
ballast. Watertight dome up + lead down = upright.

**Hard spot on the sliding ring**
Burr in the cam groove or on a column. 240-grit, then silicone grease.
Check the three pins are intact.

**Water in the capsule**
O-ring dry, pinched, or a print scar in the groove. Re-grease, quarter-turn
the ring, 24 h test.

**No port in Arduino IDE**
Hold **BOOT** while plugging USB, then release. Use a **data** USB-C
cable.

**Invisible on Bluetooth**
Normal in the headphone list. Use a BLE terminal app. If still nothing:
`ENABLE_BLE 1`.

**“Pause thermique” / overheat FAULT**
Firmware protects the servo: derate 52 °C, pause 58 °C, fault 65 °C.
Check the thermal pad to the wall. Let AUTO glide. Do not swim 100 %
in a hot room.

---

## What this kit is not

No steering. No depth sensor. No LED dome (leave `ENABLE_LED 0` so leak
can stay on GPIO4). No Qi lid. No Festo two-plate cam. Build the second
jelly after this one swims.

---

## First swim checklist

Tick these before the jelly goes in the tank.

1. **Print** — Magnet-test plate 01/03/04/05/07 passed through 3 mm card. Outer magnets varnished.
2. **Print** — Rest of PETG, transparent dome, TPU paddles ×8 (file 21), barrettes ×8. Stator is the only part with Tree Slim supports.
3. **Film** — `GABARIT_FLANCS_1-1.pdf` printed at 100 %. Control square is 50.0 mm. Eight films, tetons intact.
4. **Tentacles** — Barrette teton → stator. TPU teton → sliding ring. Film teton → barrette cuvette. Cam-by-hand pulse inward.
5. **Wiring** — Leak on GPIO4 (not GPIO5). Servo red from the boost. 470 µF across 5 V, long leg on +.
6. **Flash** — `firmware_medusa.ino` on ESP32C3 Dev Module. USB CDC On Boot = Enabled. AUTO 8 s / 4 s.
7. **Phone** — Wi-Fi EXO-MEDUSA / medusa123 → http://192.168.4.1. SWIM / STOP / AUTO work.
8. **Dry pulse** — On a glass, eight tentacles curl together. No stall fault. No twitch (if twitch: missing 470 µF).
9. **Dome** — Silicone, no fungicide. 24 h cure. 10 min underwater, zero bubbles.
10. **Capsule** — Paper towel inside. 24 h at the bottom of a bucket. Paper comes out dry.
11. **Trim** — Sinks very slowly, dome up, ~40 g in the tail bucket. Then swim.
12. **Kids / pets** — N52 magnets boxed. 18650 in its holder. CA capped.

---

*EXO-MEDUSA consumer kit v6 · Bambu Lab A1 · tank-swim*
