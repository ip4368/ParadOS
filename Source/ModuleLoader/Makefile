c = CPU.c main.c Panic.c Terminal.c Graphics.c  ../Library/Texts.c 
all: asm c link clean
clean: 
	rm *.o
	
asm:
	nasm -f elf64 portal.asm
c: #-Wno-unused-variable
	x86_64-elf-g++ -c $(c) -I ../Include -fno-stack-protector -ffreestanding -O2  -nostdlib -Wall -Wextra -fno-exceptions -fno-rtti -Werror -lgcc
link:
	x86_64-elf-ld -T Dear.Linker -nostdlib *.o -o ModuleLoader 

debug:
	x86_64-elf-objdump -D -b binary -mi386 ModuleLoader > debug.txt
