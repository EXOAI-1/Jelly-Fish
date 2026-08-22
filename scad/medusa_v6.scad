// EXO-MEDUSA v6 "AquaJelly-DIY" - pieces du mecanisme a plaque mobile
// Usage : openscad -D 'part="cam3"' -o out.stl medusa_v6.scad
// Parts : cam3 | slider | stator | clamp | rib | paddle
// Interfaces conservees : clavettes rotor (3x 5x4 sur O60), colonne stator O9,
// fentes universelles 8.6 x 3.0 (identiques a l'anneau tentacules v2/v4).

part = "cam3"; // [cam3, slider, stator, clamp, rib, paddle]

/* [Came 3 lobes synchrone - cartouche] */
cam_od = 78;         // diametre exterieur
cam_id = 60.6;       // glisse sur la colonne du rotor (O60)
cam_h  = 40;
stroke = 10;         // course totale de l'anneau (amplitude sinusoide = stroke/2)
lobes  = 3;          // 3 pions a 120 deg = anneau auto-plan, jamais de basculement
groove_w = 4.4;      // pion O4
groove_d = 3.0;
key_w = 5; key_h = 4; // clavettes du rotor (identiques v1)

/* [Anneau coulissant] */
sl_bore = 80.6;      // passe autour de la came O78
sl_od   = 110;
sl_t    = 6;
pin_d   = 4;
boss_d  = 16; boss_h = 14; boss_bore = 9.6;   // glisse sur colonnes O9
col_r   = 50;        // rayon des colonnes
n_anchor = 8;        // fentes d'ancrage des flancs internes
slot_w = 8.6; slot_t = 3.0; slot_r = 50;      // fente universelle (= anneau tentacules)

/* [Stator v6] */
cap_od = 66;
collar_z0 = 95; collar_h = 20;
col_d = 9; col_z0 = 105; ring_z0 = 190; ring_t = 4;
ring_ri = 44; ring_ro = 63;                    // assise dome inchangee (levre sur R63)

/* [Pince de flanc x16] */
cl_w = 14; cl_d = 10; cl_h = 12;
film_t = 0.55;       // film PET 0.3 + jeu
tab_w = 8; tab_t = 2.8; tab_h = 4.2;

/* [Nervure x40 et palette x8] */
flank_gap = 12;      // ecart entre les deux flancs
rib_slit = 0.6;

$fn = 96;

// ---------- decoupeur de rainure sinusoidale (polyedre, rapide en CGAL) ----------
module groove_cutter(rmid_in, rmid_out, zc, amp, nlobes, w, N=180) {
    pts = [for (i=[0:N-1]) let(a=360*i/N, z=zc+amp*sin(nlobes*a),
                               c=cos(a), s=sin(a))
           each [[rmid_in*c, rmid_in*s, z-w/2],[rmid_out*c, rmid_out*s, z-w/2],
                 [rmid_out*c, rmid_out*s, z+w/2],[rmid_in*c, rmid_in*s, z+w/2]]];
    fcs = [for (i=[0:N-1]) let(j=(i+1)%N)
           each [[4*i,4*j,4*j+1,4*i+1],[4*i+1,4*j+1,4*j+2,4*i+2],
                 [4*i+2,4*j+2,4*j+3,4*i+3],[4*i+3,4*j+3,4*j,4*i]]];
    polyhedron(points=pts, faces=fcs, convexity=10);
}

module cam3() {
    difference() {
        cylinder(h=cam_h, d=cam_od);
        translate([0,0,-0.5]) cylinder(h=cam_h+1, d=cam_id);
        for (k=[0:2]) rotate([0,0,k*120])                    // rainures de clavette
            translate([0, 30+key_h/2-0.5, cam_h/2]) cube([key_w+0.6,key_h+0.6,cam_h+2], center=true);
        groove_cutter(cam_od/2-groove_d, cam_od/2+1, cam_h/2, stroke/2, lobes, groove_w);
        translate([0,0,cam_h]) rotate_extrude() translate([cam_od/2,0]) circle(d=2.4); // chanfrein haut
    }
}

module slider() {
    difference() {
        union() {
            cylinder(h=sl_t, d=sl_od);
            for (k=[0:2]) rotate([0,0,22.5+k*120])          // bossages de guidage
                translate([0,col_r,0]) cylinder(h=boss_h, d=boss_d);
            for (k=[0:2]) rotate([0,0,60+k*120])            // porte-pions renforces
                translate([0,(sl_bore/2+38)/2,sl_t/2]) cube([10,sl_bore/2-36,sl_t],center=true);
        }
        translate([0,0,-0.5]) cylinder(h=boss_h+1, d=sl_bore);
        for (k=[0:2]) rotate([0,0,22.5+k*120])
            translate([0,col_r,-0.5]) cylinder(h=boss_h+1, d=boss_bore);
        for (k=[0:n_anchor-1]) rotate([0,0,k*360/n_anchor]) // fentes d'ancrage flancs internes
            translate([0,slot_r,sl_t/2]) cube([slot_w,slot_t,sl_t+2], center=true);
    }
    for (k=[0:2]) rotate([0,0,60+k*120])                    // 3 pions dans la rainure
        translate([0, 36.4, sl_t/2]) rotate([-90,0,0]) cylinder(h=5.4, d=pin_d, $fn=32);
}

module stator_v6() {
    difference() {                                           // collier fendu (identique v1)
        union() {
            translate([0,0,collar_z0]) difference() {
                cylinder(h=collar_h, d=cap_od+8);
                translate([0,0,-0.5]) cylinder(h=collar_h+1, d=cap_od+0.5);
            }
            for (s=[-1,1]) translate([s*7, cap_od/2+8, collar_z0+collar_h/2])
                cube([8,12,collar_h], center=true);
            // CORRECTIF v6 : 3 bras radiaux collier -> colonnes (bug v1-v4 : jamais connectes)
            for (k=[0:2]) rotate([0,0,22.5+k*120])
                translate([0,(cap_od/2+col_r+4)/2, collar_z0+collar_h/2])
                    cube([10, col_r-cap_od/2+8, collar_h], center=true);
            for (k=[0:2]) rotate([0,0,22.5+k*120])          // colonnes cylindriques = glissieres
                translate([0,col_r,col_z0]) cylinder(h=ring_z0+ring_t-col_z0, d=col_d);
            translate([0,0,ring_z0]) difference() {          // anneau superieur
                cylinder(h=ring_t, r=ring_ro);
                translate([0,0,-0.5]) cylinder(h=ring_t+1, r=ring_ri);
            }
        }
        translate([0, cap_od/2+2, collar_z0+collar_h/2]) cube([3,10,collar_h+2], center=true);
        rotate([90,0,0]) translate([0, collar_z0+collar_h/2, -(cap_od/2+22)])
            cylinder(h=14, d=3.4, $fn=32);                   // percage M3 des oreilles
        for (k=[0:n_anchor-1]) rotate([0,0,k*360/n_anchor])  // fentes flancs externes
            translate([0,56,ring_z0+ring_t/2]) cube([slot_w,slot_t,ring_t+2], center=true);
    }
}

module clamp() {                                             // pince de flanc (x16)
    difference() {
        translate([-cl_w/2,-cl_d/2,0]) cube([cl_w,cl_d,cl_h]);
        translate([-6.3,-film_t/2,-0.5]) cube([12.6,film_t,9.5]);   // fente film (par le bas)
    }
    translate([-tab_w/2,-tab_t/2,cl_h]) cube([tab_w,tab_t,tab_h]); // teton -> fente 8.6x3.0
}

module rib() {                                               // nervure peigne (x40)
    difference() {
        translate([-10,-9,0]) cube([20,18,2.5]);
        for (s=[-1,1]) translate([-8, s*flank_gap/2-rib_slit/2, -0.5]) cube([19,rib_slit,3.5]);
    }
}

module paddle() {                                            // palette caudale (x8)
    difference() {
        linear_extrude(2.2) polygon([[-7,0],[7,0],[9,14],[18,32],[6,26],[0,34],[-6,26],[-18,32],[-9,14]]);
        for (s=[-1,1]) translate([s*flank_gap/2-rib_slit/2,-0.5,-0.5]) cube([rib_slit,11,3.5]);
    }
}

if (part=="cam3") cam3();
if (part=="slider") slider();
if (part=="stator") stator_v6();
if (part=="clamp") clamp();
if (part=="rib") rib();
if (part=="paddle") paddle();
