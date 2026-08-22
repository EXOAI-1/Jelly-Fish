// 13e - dome lentille FLOTTEUR : coque + epaulement interne pour le disque de scellement
// exporter avec : -D vent_n=0 -D lobe_amp=0 -D r_max=80 -D dome_h=40 -D skirt_h=5 -D skirt_drop=8 -D r_oculus=11
include <dome_v3.scad>
// epaulement interne a z=12 (le disque O140 se colle dessus, chambre scellee ~195 cm3)
difference() {
    translate([0,0,9.5]) cylinder(h=2.5, r=76.5, $fn=160);
    translate([0,0,9.0]) cylinder(h=3.5, r=66.0, $fn=160);
}
