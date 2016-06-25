#include <Uefi.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include  <Protocol/LoadedImage.h>
#include  <Protocol/LoadFile.h>
#include  <Library/ShellLib.h>

typedef struct {
	UINT32 HResolution;
	UINT32 VResolution;
	UINTN FrameBufferBase;
	UINTN FrameBufferSize;
	UINT32 PixelsPerScanLine;
	UINT8 PixelFormat;


} COS_VIDEO_HEADER;

UINT8 CheckProcess(EFI_STATUS status)
{
	UINTN index;
	if(status == EFI_SUCCESS) {
		Print(L"Succeed!\n");
		return 1;
	} else {
		Print(L"Fail!\n");
		Print(L"--Error Code: %r\n", status);
		Print(L"Press any key to kill yourself.\n");
		gST->BootServices->WaitForEvent(1, &(gST->ConIn->WaitForKey), &index);
		return 0;
	}
}

EFI_STATUS LoadFileFromTheDrive(IN CONST CHAR16 *FileName, OUT VOID **FileData, OUT UINTN *FileSize);
EFI_STATUS GetMapKey(UINTN *key);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST)
{

	EFI_STATUS status;
	VOID *Loader = (VOID*)0x100000;
	UINTN LoaderSize;
	VOID *Buffer;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP = NULL;
	UINTN MapKey;
	VOID (*entry)();
	COS_VIDEO_HEADER *cos_video = (COS_VIDEO_HEADER *)0x8000;
	Print(L"COS Bootloader ver. 1.0S\n");
	Print(L"Firmware Vendor  :  %s \n", ST->FirmwareVendor);

	//Load Loader
	Print(L"Loading the Loader...");
	status = LoadFileFromTheDrive(L"\\Loader\\ModuleLoader", &Buffer, &LoaderSize);
	if(!CheckProcess(status)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
	}
	Print(L"Loader Size: %d byte\n", LoaderSize);
	Print(L"Loader loaded.\n");

	ST->BootServices->CopyMem(Loader, Buffer, LoaderSize);
	FreePool(Buffer);
	entry = Loader;
	Print(L"Get infomation about GOP...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	if(!CheckProcess(status)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
	}

	cos_video->HResolution = GOP->Mode->Info->HorizontalResolution;
	cos_video->VResolution = GOP->Mode->Info->VerticalResolution;
	cos_video->FrameBufferBase = GOP->Mode->FrameBufferBase;
	cos_video->FrameBufferSize = GOP->Mode->FrameBufferSize;
	cos_video->PixelsPerScanLine = GOP->Mode->Info->PixelsPerScanLine;
	cos_video->PixelFormat = GOP->Mode->Info->PixelFormat;

	Print(L"Display Resolution: %d x %d\n", cos_video->HResolution, cos_video->VResolution);

	Print(L"Passing control...");
	/*
	LOGIC:
		Get memory map frist, then call the ExitBootServices.
		After that, check if everything fine, if true pass control.
		Otherwise, call it again. 
		Until its true.
	*/
	UINT8 i = 0;//Common counter on the earth.
	do{
		i++;
		if(i == 3){
			ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
		}
		GetMapKey(&MapKey);//should not do anything before calling the ExitBootServices, these operation might destory the accuracy of memory map.
		status = ST->BootServices->ExitBootServices(IH, MapKey);
	}while(status != EFI_SUCCESS);


	entry();//WHISPER: Get the fuck out of here pls.

	return EFI_SUCCESS; //Never go here, just let the compiler happy :)
}

EFI_STATUS GetMapKey(UINTN *key)
{
	EFI_STATUS status;
	UINTN MemMapSize = sizeof(EFI_MEMORY_DESCRIPTOR) * 16;
	UINTN DescriptorSize = 0;
	UINT32 DescriptorVersion = 0;
	EFI_MEMORY_DESCRIPTOR *MemMap = NULL;
	do {
		MemMap = AllocatePool(MemMapSize);
		if(MemMap == NULL) {
			Print(L"Cant allocate Pool\n");
			status = EFI_UNSUPPORTED;
			break;
		}
		status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, key, &DescriptorSize, &DescriptorVersion);
		if(status == EFI_BUFFER_TOO_SMALL) {
			FreePool(MemMap);
			MemMapSize += sizeof(EFI_MEMORY_DESCRIPTOR);
		} else if(status == EFI_INVALID_PARAMETER) {
			break;
		}
	} while(status != EFI_SUCCESS);

	return status;
}

EFI_STATUS LoadFileFromTheDrive(IN CONST CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size)
{
	EFI_STATUS status;
	SHELL_FILE_HANDLE FileHandle;
	EFI_FILE_INFO *Info;
	UINT8 *data;
	UINTN size;

	status = ShellOpenFileByName(FileName, &FileHandle, EFI_FILE_MODE_READ, 0);
	if(status != EFI_SUCCESS) {
		return status;
	}

	Info = ShellGetFileInfo(FileHandle);
	size = (UINTN)Info->FileSize;
	data = AllocateRuntimeZeroPool(size);

	status = ShellReadFile(FileHandle, &size, data);
	if(status != EFI_SUCCESS) {
		return status;
	}

	status = ShellCloseFile(&FileHandle);
	if(status != EFI_SUCCESS) {
		return status;
	}
	*Data = data;
	*Size = size;

	FreePool(Info);
	return EFI_SUCCESS;
}
