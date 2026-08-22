# EXO-MEDUSA phone remote (v6 kit)

The jellyfish is its own Wi-Fi access point. Your **phone browser is the remote**. No app to install. BLE remains a backup.

SoftAP: **EXO-MEDUSA** / **medusa123** → **http://192.168.4.1**

There is **no internet** on this network. That is normal. Stay on EXO-MEDUSA; the page is served by the ESP32.

## iPhone (Safari)

1. Settings → Wi-Fi → join **EXO-MEDUSA**, password **medusa123**.
2. iOS may pop a **“Log in”** captive-portal page. That *is* the remote — use it. Do not tap **Cancel** / **Use without internet** if you want the page to stay.
3. If nothing pops: open Safari and type **http://192.168.4.1** (type the address, do not search Google).
4. If Safari cannot open the page: toggle Wi-Fi off/on, rejoin, try the URL again. Turn off VPN / iCloud Private Relay for this network if DNS is hijacked.
5. Optional: Share → **Add to Home Screen** for a full-screen remote. Still just the browser.

## Android (Chrome)

1. Wi-Fi → join **EXO-MEDUSA**, password **medusa123**.
2. Android will often say **“Connected without internet”**. Stay on this network — tap the network → disable auto-switch to mobile data if the phone hops away.
3. A **Sign in to network** banner may appear — open it. Otherwise Chrome → **http://192.168.4.1**
4. If Chrome searches instead of loading: type `http://` in front of the address.

## Controls

| Control | Command |
|---|---|
| **SWIM** | Forward 55% (remote; auto resumes after 120 s idle) |
| **STOP** | Speed 0 |
| **AUTO** | Built-in 8 s swim / 4 s glide at 42% |
| **REV** | Reverse nudge (−35%) |
| Slider | −100% … +100% |
| **RESET FAULT** | Clears a fault if the leak is gone |

Live tiles (temp °C, battery V, RPM, mode, fault) poll `/status` every 1 s. No 4-second page refresh.

## BLE backup

If the AP is flaky: Android **Serial Bluetooth Terminal** (Bluetooth LE tab) or iPhone **BLE Terminal**. Device name `EXO-MEDUSA`. Text: `V50`, `V-40`, `S`, `A`, `?`, `R`. Last order wins (Wi-Fi or BLE).
