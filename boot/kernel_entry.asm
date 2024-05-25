[bits 32] ; IL FAUT LINK LE PROGRAMME AVEC KERNEL.C
[extern main] ; Define calling point. Must have same name as kernel.c 'main' function
call main ; Calls the C  function. The linker will know where it is placed in memory
jmp $