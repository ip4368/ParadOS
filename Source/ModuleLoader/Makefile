c = main.c CPU.c Terminal.c Graphics.c Drawing.c GDT.c Memory.c ../Library/String.c 
all: asm c link clean
clean: 
	rm *.o
	
asm:
	nasm -f elf64 portal.asm
	#nasm -f elf64 GDT_ASM.asm

c: #-Wno-unused-variable
	x86_64-elf-g++ -c $(c) -I ../Include -fno-stack-protector -ffreestanding -O2  -nostdlib -Wall -Wextra -fno-exceptions -fno-rtti -lgcc
link:
	x86_64-elf-ld -T Dear.Linker -nostdlib *.o -o ModuleLoader 

debug:
	x86_64-elf-objdump -D -b binary -m i386:x86-64:intel ModuleLoader > debug.txt
