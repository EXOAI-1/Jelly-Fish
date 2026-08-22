# Bambu Lab A1 — slicer settings (EXO-MEDUSA)

Printer: **Bambu Lab A1 · 0.4 mm nozzle · 256 × 256 × 256 mm**
Plate: **Textured PEI** unless noted. Glue stick as a *release agent* for PETG (it sticks too well) and for TPU 95A.

These numbers are taken from **Bambu Studio system presets** on GitHub (`resources/profiles/BBL/`, master, 2026) plus the assembly notice. Where the notice is stricter than the profile, the notice wins and is marked.

## How to set this up in Bambu Studio

1. Printer: **Bambu Lab A1 0.4 nozzle**
2. Process: **0.20mm Standard @BBL A1** (change layer height only where the table says 0.16 mm)
3. Filament:
   - Structure: **Generic PETG @BBL A1**
   - Dome: **Bambu PETG Translucent @BBL A1** (or Generic PETG @BBL A1 + the translucent overrides below)
   - Skeletons: **Generic TPU @BBL A1**, feed from the **external spool holder** (not AMS Lite)
4. Load `print/EXO-MEDUSA_A1.3mf` *or* the STLs in `print/stl/`. Follow `plates.md` — do **not** print everything in one job.

Process **0.20mm Standard @BBL A1** inherits `fdm_process_single_0.20`: outer wall 200 mm/s, inner 300, infill 270, first layer 50, travel 700 mm/s, acceleration 6000 mm/s², elephant-foot 0.075 mm. **Volumetric caps below will slow PETG/TPU well under those wall speeds.** That is expected.

---

## Filament A — Generic PETG @BBL A1 (structure)

**Official A1 preset** (`Generic PETG @BBL A1.json` → `Generic PETG @base` → `fdm_filament_pet`):

| Setting | Official value | Notes |
|---|---|---|
| Nozzle | **255 °C** (range 220–260) | `fdm_filament_pet.nozzle_temperature` |
| Nozzle first layer | **255 °C** | same |
| Textured PEI bed | **80 °C** (first layer 80 °C) | A1 override; base generic is 70 °C |
| Flow ratio | **0.95** | Bambu PETG family; do not raise if it clogs |
| Max volumetric | **8 mm³/s** | A1 override (base generic is 12) |
| Density | **1.27 g/cm³** | mass estimates below |
| Fan min / max | 40 % / 90 % | `@base` |
| Line width (0.4 nozzle) | outer 0.42 / inner 0.45 | wiki default |

**Notice overrides (apply these on top):**

- Supports: **off**, except stator **Tree Slim** under the upper ring only.
- Walls / infill: per-part table, not the profile default of 2 walls.
- Glue stick on textured PEI so PETG releases without ripping the sheet.
- Dry PETG 60–65 °C / 8 h before a long plate (wiki).

Effective extrusion speed at 0.20 × 0.42 mm and 8 mm³/s ≈ **95 mm/s**, so the 200 mm/s outer-wall process number will not be reached. Leave the volumetric cap at 8.

## Filament B — Bambu PETG Translucent @BBL A1 (dome 13)

**Official A1 preset** (`Bambu PETG Translucent @BBL A1.json` → `@base`):

| Setting | Official value |
|---|---|
| Nozzle | **245 °C** (first layer **250 °C**, range 230–270) |
| Textured PEI bed | **70 °C** |
| Flow ratio | **0.95** |
| Max volumetric | **6 mm³/s** |
| Density | **1.25 g/cm³** |
| Fan min / max | **10 % / 30 %** |
| Retraction | **0.3 mm** (A1 file) |

**Dome-specific (wiki “increase transparency” + watertight float):**

- **Extra outer walls:** 5–6 (kit table uses 6). Strength and fewer leak paths beat crystal-clear.
- **Ironing:** optional on the disk top face only (helps the silicone seal). Off on the dome.
- Slow outer wall if you want clearer parts: wiki says **20 mm/s** and fan off for show-piece transparency. For a working float, stay on the official 6 mm³/s cap (~70 mm/s) with low fan.
- No supports. Skirt / brim 5 mm if the Ø160 skirt lifts.
- Same textured PEI + glue stick.

## Filament C — Generic TPU @BBL A1 (skeletons ×8)

**Official A1 preset** (`Generic TPU @BBL A1.json` → `Generic TPU @base` → `fdm_filament_tpu`):

| Setting | Official value | Kit / notice |
|---|---|---|
| Nozzle | **240 °C** (range 200–250) | keep |
| Textured PEI bed | **45 °C** (A1 override; TPU base is 35 °C) | keep |
| Max volumetric | **3.2 mm³/s** (`Generic TPU @base`) | **notice is stricter** |
| Density | **1.24 g/cm³** | mass estimates |
| Retraction | **0.4 mm** | A1 direct drive; do not raise |
| Fan | min **100 %** | keep |
| SuperTack / Cool plate | **0 °C = incompatible** | use textured PEI |

**Notice + A1 TPU practice (these win):**

- **30 mm/s max** — outer, inner, infill. Slow the outer wall further if corners fuzz. (30 mm/s × 0.20 × 0.42 ≈ 2.5 mm³/s, under the 3.2 cap.)
- **Glue stick** on textured PEI.
- **External spool**, short PTFE path. AMS Lite is not for 95A.
- Disable flow-dynamics / pressure-advance calibration if the A1 complains on TPU.
- First layer 20–25 mm/s. Z-hop 0.2–0.4 mm if it snags pads.
- Dry 50–70 °C / 5–8 h.

Wiki hardware note: TPU 95A is compatible with the A1 0.4 mm nozzle; TPU 85A is not.

---

## Per-part table

Mass and time are **estimates from STL mesh volume × fill factor × official volumetric cap**, plus ~30 % travel overhead. They are not Bambu Studio slice previews. Use them to plan overnight jobs.

| File | Material | Qty | Layer | Infill | Walls | Supports | Orientation | BBox mm (X×Y×Z) | Mass g/ea | Time /ea | Fits 256? |
|---|---|---|---|---|---|---|---|---|---|---|---|
| `01_capsule_upper.stl` | PETG | 1 | 0.20 | 40% | 4 | none | upside-down, roof / magnet face on bed | 66.0×66.0×66.0 | 37.7 | ~1 h 20 min | YES |
| `02_fuselage.stl` | PETG | 1 | 0.20 | 40% | 4 | none | bayonet collar on bed, tail up | 66.0×66.0×147.0 | 44.5 | ~1 h 34 min | YES |
| `03_stub_axle.stl` | PETG | 1 | 0.20 | 100% | 4 | none | flat, axis vertical | 26.0×26.0×48.5 | 8.8 | ~18 min | YES |
| `04_rotor_inner.stl` | PETG | 1 | 0.20 | 50% | 4 | none | magnet pockets toward the bed | 54.0×54.0×12.0 | 7.5 | ~15 min | YES |
| `05_rotor_outer.stl` | PETG | 1 | 0.20 | 25% | 4 | none | standing, large opening up | 64.0×65.5×48.0 | 54.4 | ~1 h 55 min | YES |
| `06_cam_3lobe.stl` | PETG | 1 | 0.20 | 25% | 4 | none | standing, bore vertical (opening up) | 78.0×78.0×40.0 | 40.0 | ~1 h 25 min | YES |
| `07_top_cap.stl` | PETG | 1 | 0.20 | 100% | 3 | none | flat | 30.0×30.0×3.0 | 2.7 | ~5 min | YES |
| `08_stator.stl` | PETG | 1 | 0.20 | 30% | 4 | tree slim under upper ring only | standing (collar down, ring up) | 126.0×126.0×99.0 | 49.9 | ~1 h 34 min | YES |
| `09_slider_ring.stl` | PETG | 1 | 0.20 | 20% | 3 | none | flat, bosses UP | 112.6×110.0×14.0 | 21.1 | ~44 min | YES |
| `13_float_dome.stl` | Transparent PETG | 1 | 0.16 | 15% | 6 | none | skirt on bed, apex up | 160.0×160.0×53.0 | 81.5 | ~3 h 55 min | YES |
| `13_float_disk.stl` | Transparent PETG | 1 | 0.20 | 20% | 6 | none | flat | 145.0×145.0×3.0 | 52.6 | ~2 h 32 min | YES |
| `13_float_plug.stl` | Transparent PETG | 1 | 0.20 | 100% | 4 | none | flat | 30.0×30.0×6.0 | 3.8 | ~10 min | YES |
| `18_ballast_trellis.stl` | PETG | 1 | 0.20 | 40% | 4 | none | bucket / godet on bed | 33.0×33.0×60.0 | 6.8 | ~14 min | YES |
| `19_tentacle_skeleton_TPU_x8.stl` | TPU 95A | 8 | 0.20 | 20% | 3 | none | flat, pads + teton UP | 30.0×154.0×9.4 | 3.3 | ~23 min | YES |
| `20_tentacle_bar_PETG_x8.stl` | PETG | 8 | 0.20 | 100% | 3 | none | flat, body on bed, teton UP | 18.0×20.0×7.7 | 1.4 | ~3 min | YES |

**Totals (all qty, estimated):** PETG **285 g / ~9 h 54 min** · Transparent PETG **138 g / ~6 h 38 min** · TPU 95A **27 g / ~3 h 04 min**.

Buy a **1 kg PETG** spool, a **small transparent PETG** spool, and **≥ 100 g TPU 95A**. Brim, purge, and a failed magnet-test eat the rest.

## Print order (matches the notice)

1. **First job — magnet-test only:** `01`, `03`, `04`, `05`, `07`. Stop and glue magnets (notice étapes 1–4). Rotors must clap together through ~3 mm card. Then print the rest.
2. Structure PETG (plate 2).
3. TPU ×8 (plate 3) — one skeleton, gabarit overlay, then the other seven if B1–B6 land on the bars.
4. Transparent dome (plate 4), then disk + plug (plate 5).

## A1 256 × 256 packing (computed from STL bounding boxes)

See `plates.md` for coordinates. Summary:

| Plate | Footprints | Fit? |
|---|---|---|
| 1 magnet-test | 66, 26, 54, 66, 30 mm | **yes**, one plate with margin |
| 2 structure | stator **126×126** + slider **113×110** + cam 78 + fuselage 66 + trellis 33 + eight 18×20 bars | **yes**, one plate, tight but ≤ 251 mm |
| 3 TPU ×8 | eight **30×154** | **yes** as one row (8×30 + gaps ≈ 247 mm). Two rows of 4 need 316 mm — **does not fit**. Optional split: two plates of 4. |
| 4 dome | **160×160** | **yes**, alone |
| 5 disk + plug | **145×145** + 30×30 | **yes** together. **Dome + disk = 160+145 > 256 — cannot share a plate.** |

**No default part is larger than the A1 bed.** Tallest Z is the fuselage at **147 mm** (collar-down). Stator standing is 99 mm.

## Starting-point label

If Bambu Studio on your computer has different profile numbers (filament lot / Studio version), **trust the named system preset** (`Generic PETG @BBL A1`, `Generic TPU @BBL A1`, `Bambu PETG Translucent @BBL A1`) over this file, then re-apply the notice overrides (30 mm/s TPU, Tree Slim on the stator only, extra walls on the dome).
