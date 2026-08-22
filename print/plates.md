# Plate packing — Bambu Lab A1 (256 × 256 mm)

Origin is the front-left of the textured PEI, millimetres, part **bounding-box min-corner**.
Leave ≥ 4 mm to the bed edge. Coordinates assume each STL is dropped with **Z-min on the bed** (Bambu “Lay on Face” / auto-orient as in the table). Rotate in the slicer to match **Orientation** before trusting XY.

Usable pack window used here: **4–252 mm**.

## Plate 1 — MAGNET TEST (print this first, then stop)

Filament: **Generic PETG @BBL A1**. Process: 0.20 mm Standard. No supports.

| Part | Qty | Footprint | Place min-corner (X, Y) | Occupies to |
|---|---|---|---|---|
| 01_capsule_upper | 1 | 66 × 66 | (8, 8) | (74, 74) |
| 05_rotor_outer | 1 | 64 × 66 | (82, 8) | (148, 74) |
| 04_rotor_inner | 1 | 54 × 54 | (156, 8) | (210, 62) |
| 03_stub_axle | 1 | 26 × 26 | (8, 82) | (34, 108) |
| 07_top_cap | 1 | 30 × 30 | (42, 82) | (72, 112) |

All five sit in the front ~210 × 112 mm. Spare bed is unused on purpose — this job is the go/no-go for magnets.

After the plate: notice étapes 1–4. If the rotors do not attract through ~3 mm of plastic, **do not start plate 2**.

## Plate 2 — STRUCTURE (PETG)

Filament: **Generic PETG @BBL A1**. Stator: enable **Tree Slim** supports, upper ring only. Everyone else: supports off.

| Part | Qty | Footprint | Place min-corner (X, Y) | Occupies to |
|---|---|---|---|---|
| 08_stator | 1 | 126 × 126 | (4, 4) | (130, 130) |
| 09_slider_ring | 1 | 113 × 110 | (138, 4) | (251, 114) |
| 06_cam_3lobe | 1 | 78 × 78 | (138, 122) | (216, 200) |
| 02_fuselage | 1 | 66 × 66 | (4, 138) | (70, 204) |
| 18_ballast_trellis | 1 | 33 × 33 | (78, 138) | (111, 171) |
| 20_tentacle_bar_PETG ×8 | 8 | 18 × 20 each | see grid below | leftover bay |

Barrette grid in the leftover bay **(138, 208) – (252, 252)** — 4 × 2, 4 mm gaps, teton up:

```
(138, 208) (160, 208) (182, 208) (204, 208)
(138, 232) (160, 232) (182, 232) (204, 232)
```

Fuselage Z is **147 mm** with the collar on the bed — under the 256 mm cap. Stator standing is 99 mm.

If you prefer a safer first-layer, split: plate 2a = 08+06+18, plate 2b = 02+09+20×8. Not required.

## Plate 3 — TPU ×8

Filament: **Generic TPU @BBL A1**, external spool, **30 mm/s**, glue stick.

Each skeleton is **30 × 154 × 9.4 mm**. Eight in one row along X, long axis along Y:

| Copy | min-corner (X, Y) | Occupies to |
|---|---|---|
| 1 | (6, 51) | (36, 205) |
| 2 | (37, 51) | (67, 205) |
| 3 | (68, 51) | (98, 205) |
| 4 | (99, 51) | (129, 205) |
| 5 | (130, 51) | (160, 205) |
| 6 | (161, 51) | (191, 205) |
| 7 | (192, 51) | (222, 205) |
| 8 | (223, 51) | (253, 205) |

Gaps are **1 mm**. This is the tightest plate in the kit. If first-layer adhesion looks nervous, **split into two plates of 4** (copies 1–4 and 5–8) with 8 mm gaps — notice allows “1–2 plates”.

**Do not** try two rows of 4 with the 154 mm side along Y: 154+154+gap = 316 mm > 256.

Print **one** skeleton on a scrap corner first, overlay `docs/GABARIT_FLANCS_1-1.pdf` (50.0 mm square), then run the ×8 plate.

## Plate 4 — TRANSPARENT DOME

Filament: **Bambu PETG Translucent @BBL A1** (or Generic PETG + translucent overrides). 6 walls. No supports. Skirt on bed.

| Part | Footprint | Place |
|---|---|---|
| 13_float_dome | **160 × 160** | centred (48, 48) → (208, 208) |

The dome **cannot** share a plate with the Ø145 disk (160 + 145 + gap > 256).

## Plate 5 — TRANSPARENT DISK + PLUG

Same filament as plate 4.

| Part | Footprint | Place min-corner | Occupies to |
|---|---|---|---|
| 13_float_disk | 145 × 145 | (8, 8) | (153, 153) |
| 13_float_plug | 30 × 30 | (161, 8) | (191, 38) |

## What does **not** fit

| Combination | Why |
|---|---|
| Dome 13 + disk 13 on one plate | 160 + 145 mm > 256 |
| TPU skeletons as 2×4 with long axis along Y | 154 × 2 > 256 |
| Any single default part vs 256 mm | **none** — every default STL is inside 256 × 256 × 256 |

Optional clamp/rib/paddle (old tentacle path) are tiny and would fit on any leftover PETG plate. They are **not** on the default plates.

## 3MF

`print/EXO-MEDUSA_A1.3mf` already places objects with these XY translations (Z-min baked to the bed). Open it in Bambu Studio, assign filaments per plate, and slice **one plate at a time** starting with plate 1.
