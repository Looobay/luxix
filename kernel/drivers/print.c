#include "ports.h"
#include "screen.h"

int line = 0;
int tab = 0;

// Jump one line
void kJump(){
    line++;
    tab=0;
    set_cursor_offset(get_offset(0,line));
}

// Jump a specified number of line
void kJumpAt(int num){
    while(num != 0){
        num = num - 1;
        kJump();
    }
}

// Move the cursor on the right.
void kTab(){
    tab++;
    set_cursor_offset(get_offset(tab, line));
}

void kTabAt(int num){
    while(num != 0){
        num = num - 1;
        kTab();
    }
}


/*
* Ecrit sur l'écran un caractère à la zone ou se situe le curseur.
* Writes a character on the screen in the area where the cursor is located.
*/
void kPrintC(const char *character, int color){
    int offset_from_vga = get_offset(tab,line);

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

// Print string via BIOS
void kPrint(const char *string, int color) { // Thanks a lot to ChatGPT that helped me to make this function working !
    int i = 0; // CONNARD DE i (il cassait la fonction avant que le définisse à 0)
    char *vga = 0xb8000;

    while (string[i] != '\0') {
        if (string[i] == '\n') {
            kJump();
            tab = 0;
        } else {
            int offset_from_vga = get_offset(tab, line);
            vga[offset_from_vga] = string[i];
            vga[offset_from_vga + 1] = color;
            tab++;
        }
        i++;
    }
    
    // Mise à jour de la position du curseur après avoir terminé d'imprimer la chaîne
    set_cursor_offset(get_offset(tab, line));
}

// Fonction pour calculer la longueur d'une chaîne de caractères.
// String length function inspired by the C standard library.
int stringLength(const char *string) {
    int i = 0;

    // Boucle pour parcourir la chaîne jusqu'au caractère nul
    while (string[i] != '\0') {
        i++;
    }

    // Retourne la longueur de la chaîne
    return i;
}