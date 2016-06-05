cpp = Terminal.cpp Video.cpp main.cpp ../Library/Operations.cpp 
all: asm cpp link clean
clean: 
	rm *.o
	
asm:
	nasm -f elf64 entry.asm
cpp: #-Wno-unused-variable
	x86_64-elf-g++ -c $(cpp) -I ../Include -fno-stack-protector -ffreestanding -O2  -nostdlib -Wall -Wextra -fno-exceptions -fno-rtti
link:
	x86_64-elf-gcc -T Dear.Linker -ffreestanding -nostdlib *.o -o ModuleLoader -lgcc
