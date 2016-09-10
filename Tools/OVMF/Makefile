all: update-ML test
#update-bootloader:
	
update-ML:
	cp -R ../../Source/ModuleLoader/ModuleLoader ./contents/Loader/ModuleLoader
test:	
	sudo qemu-system-x86_64 -m 4G -enable-kvm -cpu Haswell -bios OVMF.fd -hda fat:contents
