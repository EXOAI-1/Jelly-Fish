# Optional / old tentacle system

**Default kit path:** TPU skeleton + 0.3 mm PET film + PETG barrette.
Files in this folder are **not** on the default plates.

| File | Qty | What |
|---|---|---|
| `clamp_old_x16.stl` | 16 | PET-film pincer, 0.55 mm slot, 8.0×2.8 tab → 8.6×3.0 ring slots. Exported from `medusa_v6.scad` `clamp`. |
| `rib_old_x40.stl` | 40 | Comb rib, 0.6 mm slits at 12 mm flank gap. `rib`. |
| `paddle_old_x8.stl` | 8 | Caudal paddle. `paddle`. |
| `legacy_21_flanc_TPU_NOT_piece19.stl` | 0 | Original `21_flanc_superieur_TPU_x8.stl`. One-piece TPU flank + paddle + tab. **Not** notice pièce 19. |

Exported with OpenSCAD 2021.01 from `scad/medusa_v6.scad`:

```
openscad -D 'part="clamp"'  -o clamp_old_x16.stl  medusa_v6.scad
openscad -D 'part="rib"'    -o rib_old_x40.stl    medusa_v6.scad
openscad -D 'part="paddle"' -o paddle_old_x8.stl  medusa_v6.scad
```

Print these only if you deliberately drop the v6.2 film+skeleton notice and go back to two PET flanks pinched in clamps.
