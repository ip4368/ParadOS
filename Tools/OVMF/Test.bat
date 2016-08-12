copy ..\..\Source\ModuleLoader\ModuleLoader contents\Loader\ModuleLoader
..\windows\qemu\qemu-system-x86_64.exe  -m 1G -cpu qemu64 -bios OVMF.fd -hda fat:contents -vga std -S -d cpu_reset