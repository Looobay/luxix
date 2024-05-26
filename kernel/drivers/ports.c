// Permet de faire des appels Assembleur

/*
 * Lis un octet sur le port spécifié et renvoie le resultat
 * Read a byte from the specified port and return the result
 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    /* Inline assembler syntax
     * !! Notice how the source and destination registers are switched from NASM !!
     *
     * '"=a" (result)'; result = EAX ; il défini la variable result sur EAX (AL)
     * '"d" (port)': défini EDX (DX) sur la variable port
     * 
     * DONC ON DIS A L'ASSEMBLEUR QUE L'ON VEUT LIRE L'OCTET DEFINI DANS PORT ET ON RETOURNE SA VALEUR DANS RESULT
     * 
     * Les inputs et les outputs sont séparers par ":""
     */
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}
/*
* Envoie l'octet spécifié (data) dans le port spécifié (port).
* Sends the specified byte (data) to the specified port (port).
*/
void port_byte_out (unsigned short port, unsigned char data) {
    /* Notice how here both registers are mapped to C variables and
     * nothing is returned, thus, no equals '=' in the asm syntax 
     * However we see a comma since there are two variables in the input area
     * and none in the 'return' area
     */
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
/*
* Permet d'enregistrer un mot correctement dans DX et AX qui sont des registres pour les mots !
* Allows you to record a word correctly in DX and AX which are registers for words!
*/
unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}
/*
* Envoie le mot spécifié (data) dans le port spécifié (port).
* Sends the specified word (data) to the specified port (port).
*/
void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}