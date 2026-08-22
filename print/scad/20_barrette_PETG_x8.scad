// 20_barrette_PETG_x8.scad
// EXO-MEDUSA v6.2 — piece 20 "barrette racine" PETG x8
//
// Hangs the PET 0.3 mm film from the FIXED stator ring (NOTICE etape 10).
// Film 12 x 12 mm root tab (GABARIT) glues into the cuvette.
// Male teton is the 8.0 x 2.8 family that fits fentes 8.6 x 3.0.
//
// Print: PETG, a plat (body on bed, teton up), x8, 1 plate. (NOTICE etape 0)
//
// openscad -o 20_barrette_PETG_x8.stl 20_barrette_PETG_x8.scad

/* [slot teton — FIXED ring 08s, ring_t=4, fentes 8.6 x 3.0] */
tab_w = 8.0;         // SOURCE medusa_v6.scad clamp tab_w / part 21
tab_t = 2.8;         // SOURCE 2.8
tab_h = 4.5;      // ring_t=4 + 0.5 mm so a glue fillet sits on the ring

/* [cuvette — GABARIT_FLANCS_1-1.pdf film teton] */
film_tet_w = 12.0; // mm  SOURCE gabarit teton width 12.00 (34.0158 pt)
film_tet_l = 12.0; // mm  SOURCE gabarit teton length 12.00
cuvette_clear = 0.4; // mm/side glue gap
cuvette_d = 0.8;     // mm  pocket depth (film is 0.3)
cuvette_w = film_tet_w + 2*cuvette_clear;  // 12.8
cuvette_l = film_tet_l + 2*cuvette_clear;

/* [body] */
body_w = 18.0;       // mm  across (12 mm teton + walls)
body_l = 20.0;       // mm  along tentacle
body_h = 3.2;       // mm  SOURCE part 21 root plate 3.2
inboard = 1.2;     // mm  plastic inboard of teton
gap_tc  = 1.2;      // mm  teton -> cuvette

$fn = 24;

module barrette() {
    cuv_y0 = inboard + tab_t + gap_tc;
    difference() {
        translate([-body_w/2, 0, 0]) cube([body_w, body_l, body_h]);
        // cuvette open to +Z, outboard of teton
        translate([-cuvette_w/2, cuv_y0, body_h-cuvette_d])
            cube([cuvette_w, cuvette_l, cuvette_d+0.1]);
    }
    // teton +Z — insert from below into anneau FIXE (stator)
    translate([-tab_w/2, inboard, body_h]) cube([tab_w, tab_t, tab_h]);
}

barrette();
