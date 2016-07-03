You can download my toolchain on:
	Windows: https://mega.nz/#!XAthHa6K!fchYHB4mJVVIxVOUp8v88skoSG0BxRwMXp_3wtvKAmw
	Unix: https://mega.nz/#!uU8yWD7A!5m6BjCpFKpRqQrJl85cVXp6kIZgvFYVDB6PkmpOUyPA (I built it on arch linux)

or..do it yourself.

##Compile ParadOS-Bootloader

1. Get edk2 by git clone https://github.com/tianocore/edk2
2. Compiler things

	Windows User:
		SETUP YOUR OWN COMPILER.
	Unix User:
		cd edk2
		make -C BaseTools
		. edksetup.sh

3. Copy target.txt from Conf-edk2 to your edk2 folder
4. Edit target.txt, change TOOL_CHAIN_TAG bah bah bah
5. build 

	Windows User:
		DIY.
	Unix User:
		source edksetup.sh
		build

##Setup the cross compiler

1.Build your own cross compiler, the target should be x86_64-elf or get one from the top links.

2. Set env. : export PATH="<FILL IT>/ParadOS/Tools/<YOUR PLATFROM (unix or windows)>/cross/bin:$PATH"

	