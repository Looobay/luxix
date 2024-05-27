#include "drivers/ports.h"
#include "drivers/screen.h"
#include "drivers/print.h"

void main(){
    clear_screen();
    kPrint("Luxix 1.0 x86_64\nThanks ChatGPT!", 0x0f);
}
