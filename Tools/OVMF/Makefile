all: update-ML test
update-bootloader:
	cp -R ../edk2/Build/ParadOS-Boot/DEBUG_GCC5/X64/ParadOS-Boot.efi ./contents/EFI/BOOT/bootx64.efi
update-ML:
	cp -R ../../Source/ModuleLoader/ModuleLoader ./contents/Loader/ModuleLoader
test:	
	sudo qemu-system-x86_64 -m 4G -enable-kvm -cpu Haswell -bios OVMF.fd -hdb fat:contents 
