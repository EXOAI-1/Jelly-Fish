# EXO-MEDUSA tentacles — TPU + PET film path (v6.2 / gabarit v6.3)

Status after this pass: **CONDITIONAL GO**. The original zip could not print notice
tentacles. This folder now has a reconstructed piece 19 + piece 20. Print **one**
TPU skeleton first, overlay the 1:1 gabarit, then print the remaining seven.

Do **not** use `21_flanc_superieur_TPU_x8.stl` as piece 19. Do **not** pour the
`22_moule_chair_silicone*.stl` trays. Do **not** print `medusa_v6.scad` clamp/rib/paddle
unless you abandon the notice path.

---

## 1. Notice quotes (étapes 0, 0b, 9, 10)

**Étape 0 — print table**

| Pièce | Orientation | Réglages |
|---|---|---|
| 19 Squelettes TPU ×8 | à plat | TPU 95A, 30 mm/s maxi, 1-2 plateaux |
| 20 Barrettes ×8 | à plat | PETG, 1 plateau |

**Étape 0b — film** (page 3): *« Chaque tentacule n'a besoin que d'UNE pièce de
film PET 0,3 mm, d'une forme simple (long trapèze + queue de poisson) : 8
découpes identiques avec le gabarit fourni (GABARIT_FLANCS_1-1.pdf). »*
Print gabarit at 100 %, control square **50,0 mm**. *« Le petit téton du bas
sera collé sur la barrette imprimée. »* Mark dashed **B1–B6** before peeling.
Qty: **8 identical films** (title says “16 flancs”; body text and gabarit
v6.3 say one film per tentacle).

**Étape 9**: *« Chaque tentacule = 1 squelette TPU imprimé (pièce 19) + 1 film
(étape 0b) + 1 barrette (pièce 20). »* Glue **14 pads** only, not spine, not
bars. Film marks B1–B6 facing the bars. Film teton into barrette **cuvette**.
*« zéro nervure à enfiler. »* Finger-press test: must curve **toward** the
finger (Fin-Ray).

**Étape 10 — hang on both rings**

1. **Anneau FIXE** (stator top): barrette teton from **below** into 8 slots + cyano.
   Films now hang from the frame.
2. **Anneau COULISSANT**: TPU skeleton teton from **below** into its 8 slots + cyano.
3. Order: 8 barrettes first → cam to sliding ring **LOW** → then skeletons.
4. Ring down → tentacles curve **inward** (power stroke), all eight together.

Curvature tweak (missing file): `tentacule_v62.scad` `sp_t = 2.6` (too soft) /
`sp_t = 1.8` (too stiff). *« 2 mm de jeu à la racine mangent la moitié de la
course. »*

---

## 2. Gabarit film — measured from PDF vectors (1 pt = 25.4/72 mm)

`GABARIT_FLANCS_1-1.pdf` page content stream, left outline. Control rectangle
width **50.00 mm**. Two copies of the same outline on one A4.

| Feature | Size (mm) |
|---|---|
| Total length (teton bottom → fishtail tip) | **212.0** |
| Root teton (glues in barrette cuvette) | **12.0 × 12.0** |
| Shoulder above teton | **16.0 wide × 40.0** |
| Main body | **30.0 wide × 126.0** |
| Fishtail outer width / tip height | **36.0 / 34.0** |
| PET thickness | **0.3** (notice + gabarit text) |
| Qty | **8** (1 per tentacle; 2 outlines/sheet) |

**B1–B6** (from teton bottom, pitch **22.40 mm**): 60.0, 82.4, 104.8, 127.2,
149.6, 172.0. Gabarit: *« ce sont les 6 lames du squelette — le film se presse
sur leur chant encollé. »* Notice étape 9 instead glues **square pads at bar
tips**. Use the notice method (pads only).

---

## 3. Part-19 verdict: `21_flanc_superieur_TPU_x8.stl` is **NOT** pièce 19

ASCII OpenSCAD mesh, 68 triangles / 36 unique vertices. Bounding box
**22.000 × 209.000 × 7.400 mm** (`x=-11..11, y=-7..202, z=0..7.4`).

Reconstructed solids:

| Feature | Size (mm) |
|---|---|
| Root plate | 22 × 14 × 3.2 |
| Male slot tab | **8.0 × 2.8 × 4.2** (z=3.2..7.4) — same as `clamp()` in `medusa_v6.scad` |
| Spine | 4.0 wide × 175 long × 2.2 thick (y=7..182) |
| Fishtail paddle | 18 wide × 20 long × 1.6 (vertices ±9,198 / 0,202) |
| Holes / slots / crossbars / pads | **none** |

Notice pièce 19 is a Fin-Ray **ladder**: spine + 6 blades + square pads + TPU
teton into the **sliding** ring. File 21 is a one-piece TPU **upper flank**
(strip + paddle + ring tab). Same tentacle scale (~210 mm), different
mechanism. Ignore 21 for the notice path.

---

## 4. `medusa_v6.scad` vs barrette / `tentacule_v62.scad`

`medusa_v6.scad` parts: `cam3 | slider | stator | clamp | rib | paddle`.
**No barrette.** Universal slots `slot_w=8.6; slot_t=3.0`. Clamp is a 14×10×12
PET-film pincer with 0.55 mm slit + 8×2.8×4.2 tab (×16). Rib ×40 comb,
paddle ×8. That is the **older two-flank clamp/rib/paddle** path. No STLs were
exported for those three. **`tentacule_v62.scad` is not anywhere in this zip.**

---

## 5. Silicone molds — ignore for tank-swim

| File | BBox (mm) |
|---|---|
| `22_moule_chair_silicone.stl` | 58 × 236 × 7.6 (cavity floor z≈2.99, rim 7.6) |
| `22_moule_chair_silicone (1).stl` | 58 × 244 × 7.6 (richer, not a byte copy) |

Notice never pours silicone on tentacles. Not pièce 19/20.

---

## 6. What to print now

| File | Qty | Material | Notes |
|---|---|---|---|
| `19_squelette_TPU_x8.stl` | 8 (print 1 first) | **TPU 95A**, 30 mm/s, à plat, pads+teton up | Reconstruction — see parameters |
| `20_barrette_PETG_x8.stl` | 8 | **PETG**, à plat, teton up | Reconstruction — cuvette 12.8×12.8×0.8 |
| PET film from gabarit | 8 | PET 0.3 mm A4 | Cut solid line; mark B1–B6 |
| `21_flanc_superieur_TPU_x8.stl` | 0 | — | **Not** piece 19 |
| `22_moule_chair_silicone*.stl` | 0 | — | Ignore |
| clamp / rib / paddle | 0 | — | Only if abandoning notice path |

### Piece 19 defaults (reconstruction)

| Param | Default | Source |
|---|---|---|
| Spine `sp_t` × `sp_w` | **2.2 × 4.0** | part 21 spine; NOTICE 1.8–2.6 band |
| Bars | **6** at pitch **22.4** | gabarit B1–B6 |
| `ring_sep` | **36** | EST from rotor z~174 / cam groove ~154 / stator ring z190 |
| `b1_y` | **24** | 60 (gabarit B1) − 36 |
| Bar span | **30** | gabarit body width |
| Pads | **3.5** sq × **1.4** rise, ×12 | EST (NOTICE says 14; gabarit has 6 blades → 12) |
| Teton | **8.0 × 2.8 × 6.2** | slot family + slider `sl_t=6` |
| Root plate | 12 × 10 × 3.2 | part 21 thickness 3.2 |
| Overall (defaults) | **30 × 154 × 9.4** | span × (root+spine) × (root 3.2+teton 6.2) |

OpenSCAD was **not** available (`apt: Unable to locate package openscad`).
The STL is a cube-union of these defaults. Edit `19_squelette_TPU_x8.scad`
and re-export on your machine after the first dry-fit.

### Piece 20 defaults

| Param | Default | Source |
|---|---|---|
| Teton | **8.0 × 2.8 × 4.5** | slot family; stator `ring_t=4` + 0.5 glue |
| Cuvette | **12.8 × 12.8 × 0.8** | gabarit 12×12 teton + 0.4/side |
| Body | **18 × 20 × 3.2** | 12 mm tab + walls; part 21 plate thickness |
| Overall | **18 × 20 × 7.7** | body 3.2 + teton 4.5 |

---

## 7. Cut-from-gabarit steps

1. Print `GABARIT_FLANCS_1-1.pdf` at **100 % / actual size**. Measure the
   control box: **50.0 mm** wide. Reprint if not.
2. Stick the sheet on 0.3 mm PET (repositionable spray or corner tape).
   One A4 = two outlines → two films.
3. Cut the **solid** line with cutter + metal rule. Keep the 12×12 mm teton
   intact.
4. Before peeling, mark **B1–B6** with a fine pen (22.4 mm pitch, first mark
   60 mm from teton bottom).
5. Repeat to **8** films. Fold test: no white crease (that would be PS, not PET).

---

## 8. Table assembly (étape 9) then hang (étape 10)

1. Skeleton flat, **pads up**. One CA drop on each pad (12 with this mesh;
   notice says 14). None on spine, none on bars.
2. Press film on in one go, B1–B6 on the bars, centred on the spine. 10 s palm.
3. Glue film 12×12 teton into barrette cuvette (blob of CA, 10 s).
4. Hang **barrettes** in the 8 stator slots from below, cyano. Cam to ring LOW.
   Then hang **skeleton tetons** in the 8 sliding-ring slots from below, cyano.
5. Dry test: turn cam by hand — eight tentacles curl inward together.

If bars miss the B marks: change `ring_sep` (hence `b1_y`) and reprint one
skeleton. If too floppy/stiff: `sp_t = 2.6` / `1.8`.

---

## 9. Go / no-go

| Question | Answer |
|---|---|
| Could they print notice tentacles **from the original zip**? | **NO-GO.** Piece 19 missing (21 is the wrong geometry). Piece 20 missing. Gabarit present. |
| Can they print tentacles **from this folder now**? | **CONDITIONAL GO.** Print 1× TPU 19 + 1× PETG 20 + 1 film, overlay gabarit, then ×8. |
| Piece 19 origin | Reconstruction (no `tentacule_v62.scad`). Parameters labeled. |
| Piece 20 origin | Reconstruction from gabarit teton + proven 8.0×2.8 slot tab. |
| Silicone / clamp-rib-paddle | Not required for first tank swim. |
