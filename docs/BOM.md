# EXO-MEDUSA — bill of materials (v1 tank swim)

Drive is a **360° continuous servo**, **not** the Furitek Mini-Komodo.
Skip: LED ring, SG90 pendulum, Qi wireless, silicone “flesh” molds.

Prices in THB are from `Meca_Jellyfish_BOM_Thailand.xlsx` except the servo (that spreadsheet had the wrong motor). Search column is Lazada / Shopee TH.

## Buy (electronics)

| What | Qty | Search | ~THB |
|---|---|---|---|
| 360° continuous servo (DS04-NFC or MG996R 360) | 1 | `DS04-NFC 360` or `MG996R 360 continuous` | — (not in the old BOM) |
| ESP32-C3 SuperMini | 1 | ESP32-C3 SuperMini | 105 |
| 18650 + holder (3000 mAh) | 1 | 18650 battery holder | 140 |
| TP4056 with protection (DW01) | 1 | TP4056 protection | 35 |
| 5 V boost ≥2 A (MT3608) | 1 | MT3608 boost 5V | 35 |
| 470 µF 10 V electrolytic | 1 | 470uF electrolytic | 17.5 |
| SS49E linear Hall | 1 | SS49E hall sensor | 17.5 |
| NTC 10k B3950 | 1 | NTC 10k 3950 | 17.5 |
| Reed switch + magnet | 1 | reed switch glass | 35 |
| Resistors: 10k ×1, 100k ×2, 470k ×1 | 1 kit | resistor kit | 35 |

Servo 5 V goes through the boost, **not** through the ESP32. 470 µF sits across the servo 5 V rail.

## Buy (mechanics / consumables)

| What | Qty | Search | ~THB |
|---|---|---|---|
| N52 magnets 8×3 mm | 12 | N52 8x3 magnet | 105 |
| N52 magnets 5×2 mm | 2 | N52 5x2 magnet | 35 |
| NBR O-ring ~53×3 mm | 1 | o-ring 53x3 | 35 |
| Silicone grease | 1 | silicone grease plumbing | 70 |
| PET film 0.3 mm A4 | 10 sheets | PET sheet 0.3mm A4 | 70 |
| M3 screws: 16 mm ×2, 10 mm ×3, 8 mm ×5 | 1 kit | M3 screw kit | 70 |
| Fishing sinkers / steel balls ~40 g | 1 | fishing sinkers split shot | 70 |
| Aquarium silicone 100% clear, **no fungicide** | 1–2 | aquarium silicone sealant clear 100% | 175 |
| 5-min epoxy | 1 | epoxy glue 5 minutes | 70 |
| CA glue (cyanoacrylate) | 1 | super glue CA | — (notice uses it everywhere; not in the old BOM) |
| Thermal pad + a bit of foam | 1 | thermal pad servo | — (notice étape 6) |
| Nail varnish (wet-side magnets) | 1 | — | household |

Cut the 8 tentacle films with `docs/GABARIT_FLANCS_1-1.pdf` printed at **100 %** (50.0 mm control square).

## Print (filament)

| What | ~mass (printed) | Buy | Use |
|---|---|---|---|
| PETG | ~300 g structure + bars (buy **1 kg**) | Generic PETG | capsule, stator, cam, ring, axle, rotors, barrettes ×8 |
| Transparent PETG | ~140 g (buy a small spool) | PETG Translucent | float dome + disk + plug |
| TPU 95A | ~30 g skeletons ×8 (buy **≥ 100 g**) | TPU 95A | tentacle skeletons; 30 mm/s; external spool |

Masses are STL-volume estimates; brim / purge / a failed plate are extra. The old notice ballpark (450 / 95 / 60 g) is fine as a shopping ceiling.

## Do not buy for v1 swim

- Furitek Mini-Komodo (wrong motor for this firmware)
- WS2812 8-LED ring
- SG90 (pendulum steering — v6.1, not this kit)
- Qi wireless TX/RX
- Silicone tentacle molds (`22_moule_*`)

Priced hardware rows above ≈ **1060 THB + servo + filament + CA / thermal pad**.
