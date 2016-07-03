 
all:
	cp -R ../../Source/ModuleLoader/ModuleLoader ./contents/Loader/ModuleLoader
	cp -R ../edk2/Build/COS-Boot/DEBUG_GCC49/X64/COS-Boot.efi ./contents/EFI/COS-Boot.efi
	sudo qemu-system-x86_64 -m 4G -enable-kvm -cpu Haswell -bios OVMF.fd -hda fat:contents -D debug.log
