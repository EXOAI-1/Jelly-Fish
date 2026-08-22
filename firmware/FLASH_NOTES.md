# EXO-MEDUSA v5 — flash notes (tank swim)

Board in Arduino IDE: **ESP32C3 Dev Module** (ESP32-C3 SuperMini).
Notice étape 11b: **USB CDC On Boot = Enabled**.

## Install (notice étape 11b)

1. Arduino IDE from arduino.cc
2. File → Preferences → Additional boards manager URLs:
   `https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. Boards Manager: install **esp32 by Espressif Systems** (current 3.x is fine; sketch also falls back to 2.x LEDC)
4. Tools → Board → esp32 → **ESP32C3 Dev Module**
5. Tools → **USB CDC On Boot = Enabled**
6. USB-C data cable, pick the port. If none: hold **BOOT** while plugging in, then release.
7. Open `firmware_medusa.ino` → Upload. Success looks like “Hash of data verified” / “Done uploading”.
   Failed to connect: BOOT trick again.

The notice does **not** specify flash size, frequency, partition scheme, or upload speed. Leave Arduino defaults (typically 80 MHz, QIO, 4 MB, Default 4 MB with spiffs, 921600). SuperMini is usually 4 MB.

## Libraries

- **ENABLE_LED 0 (default, tank swim):** no extra library. Built-in WiFi / BLE / LEDC only.
- If you later set `ENABLE_LED 1`: install **Adafruit NeoPixel**, **and move leak off GPIO4** (WS2812 uses GPIO4).

## Pin table (v5)

| Function | GPIO | Notes |
|---|---|---|
| Servo PWM (360° continuous) | **10** | 50 Hz, 16-bit LEDC, 1500 µs stop, ±100% → ±500 µs |
| Reed / ILS | **3** | INPUT_PULLUP to GND. Tap = run/stop or fault reset; 3 s = deep sleep |
| NTC 10k B3950 | **0** | ADC1. 10k to 3.3 V, NTC to GND |
| Vbat divider | **1** | ADC1. 100k/100k from pack + |
| Hall SS49E | **2** | ADC1. 3.3 V / GND / signal |
| Leak probe | **4** | ADC1. Was GPIO5 (not ADC on C3). 2 bare wires + 470k to 3.3 V. Analog threshold `<1200` |
| WS2812 ring | 4 (ifdef) | Off by default. Do not enable while leak is on GPIO4 |

Wi-Fi AP still `EXO-MEDUSA` / `medusa123`, page `http://192.168.4.1`. BLE Nordic UART unchanged (`V50`, `V-40`, `S`, `A`, `?`, `R`).

Rewire the leak sense from GPIO5 (notice étape 11) to **GPIO4**.

## Servo rail

Keep **470 µF** across the servo 5 V rail (long leg on +), fed from the boost, **not** through the ESP32. Brown-outs make the servo twitch without turning.

## After flash

Autonomous cycle: 8 s swim / 4 s glide at 42%. Then 24 h dry capsule leak test before a tank swim.
