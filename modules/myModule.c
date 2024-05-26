#include "../kernel/kernel.h"
#include "../kernel/drivers/print.h"

void module_main(){
    kPrint("Mon module est ici present", 0x0f);
}