c = main.c CPU.c Terminal.c Graphics.c Drawing.c ../Library/String.c 
all: asm c link clean
clean: 
	rm *.o
	
asm:
	nasm -f elf64 portal.asm
c: #-Wno-unused-variable
	x86_64-elf-g++ -c $(c) -I ../Include -fno-stack-protector -ffreestanding -O2  -nostdlib -Wall -Wextra -fno-exceptions -fno-rtti -lgcc
link:
	x86_64-elf-ld -T Dear.Linker -nostdlib *.o -o ModuleLoader 

debug:
	x86_64-elf-objdump -D -b binary -mi386 ModuleLoader > debug.txt
