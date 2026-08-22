// 19_squelette_TPU_x8.scad
// EXO-MEDUSA v6.2 — piece 19 "squelette TPU" x8  (Fin-Ray ladder)
//
// THIS IS A RECONSTRUCTION. tentacule_v62.scad is NOT in the zip.
// 21_flanc_superieur_TPU_x8.stl is a one-piece TPU flank (strip+paddle+slot tab),
// NOT this skeleton — do not print 21 as piece 19.
//
// Print: TPU 95A, a plat, 30 mm/s max, x8, 1-2 plates. (NOTICE etape 0)
// First print ONE, overlay GABARIT_FLANCS_1-1.pdf, then tweak b1_y / sp_t.
//
// openscad -o 19_squelette_TPU_x8.stl 19_squelette_TPU_x8.scad

/* [spine — NOTICE etape 10 sp_t band; thickness from part 21] */
sp_t = 2.2;           // mm  SOURCE part 21 spine z=2.2. NOTICE: 2.6 too soft, 1.8 too stiff
sp_w = 4.0;           // mm  SOURCE part 21 spine x=-2..2

/* [bars — GABARIT_FLANCS_1-1.pdf v6.3] */
n_bars    = 6;    // gabarit "6 lames" B1-B6. NOTICE "14 patins" would be 7; keep 6.
bar_pitch = 22.4; // mm  SOURCE gabarit B spacing (63.4962 pt = 22.40 mm)
b1_film   = 60.0;   // mm  SOURCE gabarit B1 from film teton bottom
ring_sep  = 36.0;  // mm  EST vertical+radial gap barrette ring -> slider ring
                         //     (rotor cup z~174, cam groove ~z154, stator ring z190, dr=6)
b1_y      = b1_film - ring_sep;  // = 24.0 mm with defaults
bar_span  = 30.0;  // mm  SOURCE gabarit film body width 30.00
bar_w     = 2.4;     // mm  EST printable TPU rib width
bar_t     = 2.2;     // mm  same layer as spine

/* [pads — NOTICE etape 9 "patins carres", glue ONLY here] */
pad   = 3.5;           // mm  EST "petits patins carres"
pad_h = 1.4;         // mm  EST rise so film does not touch spine/bars

/* [root teton — sliding ring 09s, fentes 8.6 x 3.0 x sl_t=6] */
tab_w = 8.0;         // SOURCE medusa_v6.scad clamp tab_w / part 21
tab_t = 2.8;         // SOURCE tab_t 2.8
tab_h = 6.2;      // sl_t=6 + 0.2 glue. NOTICE: 2 mm play eats half the stroke
root_w = 12.0;
root_l = 10.0;
root_h = 3.2;       // SOURCE part 21 root plate 3.2
tail   = 8.0;         // mm  EST past B6

$fn = 24;

module squelette() {
    // root plate
    translate([-root_w/2, 0, 0]) cube([root_w, root_l, root_h]);
    // teton (+Z) — insert from below into anneau coulissant
    translate([-tab_w/2, (root_l-tab_t)/2, root_h]) cube([tab_w, tab_t, tab_h]);
    // spine
    spine_len = b1_y + (n_bars-1)*bar_pitch + tail;
    translate([-sp_w/2, root_l, 0]) cube([sp_w, spine_len, sp_t]);
    // bars + pads
    arm = (bar_span - sp_w)/2;
    for (i=[0:n_bars-1]) {
        y = root_l + b1_y + i*bar_pitch;
        translate([-bar_span/2, y-bar_w/2, 0]) cube([arm, bar_w, bar_t]);
        translate([ sp_w/2,     y-bar_w/2, 0]) cube([arm, bar_w, bar_t]);
        for (s=[-1,1])
            translate([s*(bar_span/2-pad/2)-pad/2, y-pad/2, bar_t])
                cube([pad, pad, pad_h]);
    }
}

squelette();
