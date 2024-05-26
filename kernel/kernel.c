#include "../drivers/ports.h"

void main() {
    // on envoie la position du curseur dans 
    port_byte_out(0x3d4, 14);

    int position = port_byte_in(0x3d5); // la position équivaut donc à la valeure de l'octet 0x3d5
    position = position << 8;

    port_byte_out(0x3d4,15);
    position += port_byte_in(0x3d5); // on aditionne la position avec la valeure de l'octet 0x3d5

    int offset_from_vga = position * 2;

    char *vga = 0xb8000;
    vga[offset_from_vga] = 'X';
    vga[offset_from_vga+1] = 0x0f; //couleur du charactère 0xAB (A = couleur de fond ; B = couleur de la lettre) / comme sur Windows
}
