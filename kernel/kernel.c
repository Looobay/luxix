#include "drivers/ports.h"
#include "drivers/screen.h"
#include "drivers/print.h"

void main() {
    clear_screen();
    kPrint("Luxix is online!", 0x0f);
    kJump();
    kPrint("Hello", 0x0f);
}
