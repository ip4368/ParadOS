copy ..\..\Source\ModuleLoader\ModuleLoader contents\Loader\ModuleLoader
..\windows\qemu\qemu-system-x86_64.exe  -m 4G -cpu qemu64 -bios OVMF.fd -hda fat:contents 