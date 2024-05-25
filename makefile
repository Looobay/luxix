# $@ = target file
# $< = first dependency
# $^ = all dependencies
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin//i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin//i386-elf-gcc
# -g: Use debugging symbols in gcc
CFLAGS = -g

default:
	make out/boot.bin
	make out/kernel_entry.o
	make out/kernel.o
	make out/kernel.bin
	make luxix.bin
	make run

# First rule is run by default
luxix.bin: out/boot.bin out/kernel.bin
	cat $^ > luxix.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
out/kernel.bin: out/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
debug/kernel.elf: out/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: luxix.bin
	qemu-system-i386 -fda luxix.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: luxix.bin debug/kernel.elf # NE MARCHE PAS
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

out/%.o: boot/%.asm
	nasm $< -f elf -o $@

out/%.bin: boot/%.asm
	nasm $< -f bin -o $@

out/kernel.o : kernel/kernel.c
	i386-elf-gcc -ffreestanding -c kernel/kernel.c -o out/kernel.o

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
	rm -rf out/*bin out/*o

reset:
	make clean
	make