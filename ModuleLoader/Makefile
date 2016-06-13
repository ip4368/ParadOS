cpp = CPU.cpp main.cpp Panic.cpp Terminal.cpp Video.cpp  ../Library/Operations.cpp 
all: asm cpp link clean
clean: 
	rm *.o
	
asm:
	nasm -f elf64 entry.asm
	nasm -f elf64 ASM_Things.asm
cpp: #-Wno-unused-variable
	x86_64-elf-g++ -c $(cpp) -I ../Include -fno-stack-protector -ffreestanding -O2  -nostdlib -Wall -Wextra -fno-exceptions -fno-rtti -lgcc
link:
	x86_64-elf-ld -T Dear.Linker -nostdlib *.o -o ModuleLoader 
