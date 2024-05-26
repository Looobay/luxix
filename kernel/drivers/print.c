#include "ports.h"
#include "screen.h"

int line;
// Jump one line
void kJump(){
    set_cursor_offset(get_offset(0,line++));
    line++;
}
int tab;
void kTab(){
    set_cursor_offset(get_offset(tab, line));
}

// Just a basic character printing function

/*
* Ecrit sur l'écran un caractère à la zone ou se situe le curseur.
* Writes a character on the screen in the area where the cursor is located.
*/
void kPrintC(const char *character, int color){
    // On demande au VGA la position du curseur / 14 = high / 15 = low
    port_byte_out(0x3d4, 14);

    int position = port_byte_in(0x3d5); // la position équivaut donc à la valeure de l'octet 0x3d5 (le registre de donnée du VGA)
    position = position << 8;

    port_byte_out(0x3d4,15);
    position += port_byte_in(0x3d5); // on aditionne la position avec la valeure de l'octet 0x3d5

    int offset_from_vga = position * 2; // cela permet d'avoir deux paramètres le caractère et la couleur

    char *vga = 0xb8000;
    vga[offset_from_vga] = *character;
    vga[offset_from_vga+1] = color; //couleur du charactère 0xAB (A = couleur de fond ; B = couleur de la lettre) / comme sur Windows

    /*
        La position comprend donc deux paramètres :
            - le caractère
            - la couleur en hexadécimal
        On additionne position avec 0x3d5 pour obtenir la position X & Y du curseur
    */
}

void kPrint(const char *string, int color){
    int offset_from_vga = get_offset(tab, line); // cela permet d'avoir deux paramètres le caractère et la couleur

    int i;
    char* vga = 0xb8000;
    if (stringLength(string) > 1){
        while(string[i] != '\0'){
            vga[offset_from_vga] = string[i];
            vga[offset_from_vga+1] = color;
            offset_from_vga = get_offset(tab+1+i, line);
            set_cursor_offset(offset_from_vga);
            i++;
        }
    }
    else{
        kPrintC(string, color);
    }
}

// Fonction pour calculer la longueur d'une chaîne de caractères.
// Random function inspired by the C standard library.
int stringLength(const char *string) {
    int i = 0;

    // Boucle pour parcourir la chaîne jusqu'au caractère nul
    while (string[i] != '\0') {
        i++;
    }

    // Retourne la longueur de la chaîne
    return i;
}