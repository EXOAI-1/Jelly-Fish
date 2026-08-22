# EXO-MEDUSA — consumer print kit (Bambu Lab A1)

**Aquarium jellyfish · Ø280 × 380 mm · 360° servo · phone remote over Wi-Fi AP · 2 weekends**

This folder is the printable kit for a **Bambu Lab A1** (256 × 256 × 256 mm, 0.4 mm nozzle).
It is a dry-capsule magnetic-drive jelly: a 3-lobe cam pumps a sliding ring that bends
eight Fin-Ray tentacles in unison. No electronics in the water.

| | |
|---|---|
| Size in the tank | about **Ø 280 mm** bell, **380 mm** long |
| Printer assumed | **Bambu Lab A1**, 0.4 mm nozzle, textured PEI |
| Drive | **360° continuous servo** (DS04-NFC or MG996R 360) — not a brushless motor |
| Brain | ESP32-C3 SuperMini, SoftAP **`EXO-MEDUSA`** / `medusa123` → http://192.168.4.1 |
| Time | **2 weekends** once parts are printed (print itself is several overnight jobs) |
| Default tentacles | **TPU 95A skeleton ×8 + 0.3 mm PET film + PETG barrette ×8** |

## What's in the box

```
EXO-MEDUSA-kit/
  README.md                 ← you are here
  PARTS.csv                 file / qty / material / plate / notes
  print/
    BAMBU_A1.md             exact slicer starting points (official A1 presets)
    plates.md               how to split the bed: magnet-test → structure → TPU → dome
    EXO-MEDUSA_A1.3mf       all default STLs as named objects (open in Bambu Studio)
    stl/                    one file per part (consumer names)
    stl/aliases/            original engineering filenames (hardlinks)
    stl/optional/           OLD clamp / rib / paddle tentacle system — not the default
  docs/
    BOM.md                  buy list (Thailand), servo not Furitek
    GABARIT_FLANCS_1-1.pdf  1:1 PET-film cutting template (print at 100 %)
    TENTACLES.md            why piece 19/20 were reconstructed
  scad/                     medusa_v6, dome_flotteur, tentacle skeleton + barrette
  firmware/                 flash notes + sketch (do not start here — print first)
```

**Not in this kit (on purpose):** silicone “flesh” molds (`22_moule_*`) and the Festo AquaJellies brochure.

## Two-weekend build

**Before weekend 1 — print, in this order** (see `print/plates.md`):

1. **Magnet-test plate:** parts **01, 03, 04, 05, 07**. Glue magnets, confirm the two rotors *attract* through ~3 mm of PETG. If this fails, stop — do not print the rest yet.
2. **Structure plate:** 02 fuselage, 06 cam, 08 stator (Tree Slim supports), 09 slider, 18 ballast, 20 barrettes ×8.
3. **TPU plate:** 19 skeletons ×8 at **30 mm/s**. Print **one** first, overlay the gabarit, then the other seven.
4. **Transparent plates:** 13 dome alone, then disk + apex plug.

**Weekend 1:** magnets, axle, stator, servo in the can, cam + slider, dry pulse.

**Weekend 2:** cut 8 PET films, glue tentacles (TPU + film + barrette), hang on both rings, wire + flash, O-ring the fuselage, seal the float 24 h, 24 h capsule leak test, trim ballast, tank swim.

Assembly steps live in the notice PDF (another document). This kit is the **print + buy** front door.

## Print at a glance

| Group | Material | Parts | A1 bed |
|---|---|---|---|
| 1 magnet-test | PETG | 01, 03, 04, 05, 07 | **one plate**, all fit |
| 2 structure | PETG | 02, 06, 08, 09, 18, 20×8 | **one plate**, all fit |
| 3 TPU | TPU 95A | 19 ×8 | **one tight plate** or two of 4 |
| 4 dome | Transparent PETG | 13 dome | **own plate** (Ø160 mm) |
| 5 dome seal | Transparent PETG | 13 disk + plug | **own plate** (disk Ø145 + dome Ø160 cannot share a 256 mm bed) |

No default part exceeds 256 mm in X, Y, or Z.

Filament to buy: **1 kg PETG** (structure ~300 g printed + brim/purge/failed magnet-test), **~200 g transparent PETG** (dome + solid disk), **~50–80 g TPU 95A** (8 skeletons + brim). Official notice ballpark was 450 / 95 / 60 g — the disk is a Ø145 × 3 mm plate, so transparent mass is higher than that ballpark.

## Default vs optional tentacles

- **Default (this kit):** TPU skeleton `19_tentacle_skeleton_TPU_x8.stl` + PET 0.3 mm from the gabarit + PETG barrette `20_tentacle_bar_PETG_x8.stl`.
- **Do not print** `21_flanc_superieur_TPU` as piece 19 (wrong geometry). It is parked under `print/stl/optional/`.
- **Optional / old path:** `print/stl/optional/clamp_old_x16.stl` + `rib_old_x40.stl` + `paddle_old_x8.stl` exported from `medusa_v6.scad`. Only if you abandon the notice.

## Phone remote

After flash: join Wi-Fi **EXO-MEDUSA** / **medusa123**, open **http://192.168.4.1**. BLE Nordic UART still speaks `V50`, `V-40`, `S`, `A`, `?`, `R`. Autonomous default is 8 s swim / 4 s glide at 42 %.

## Safety (short)

N52 magnets: pinch, shatter, **lethal if swallowed**. 18650: no shorts, charge only via TP4056. CA glue: seconds. Servo 5 V from the boost, **not** through the ESP32. Wet-side magnets must be varnished. Unsealed dome → the robot inverts.
