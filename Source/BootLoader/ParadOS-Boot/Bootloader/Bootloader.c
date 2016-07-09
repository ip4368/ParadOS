//AH! AH! AH! windows compiler sucks!
#pragma warning(disable:4152) //just make windows compiler happy
//im gonna using windows C compiler, because the efi file size is much lighter.
#pragma warning(disable:4702)

#include <Uefi.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/SimpleFileSystem.h>
#include <Library/DevicePathLib.h>
#include <Guid/FileInfo.h>

#define ML_ADDR 0x100000
#define HDR_ADDR 0x8000

typedef struct {
	UINT32 HResolution; 
	UINT32 VResolution; 
	UINTN FrameBufferBase; 
	UINTN FrameBufferSize; 
	UINT32 PixelsPerScanLine; 
	UINT8 PixelFormat; 
} POS_GRAPHICS_INFO; 

typedef struct 
{
	UINT64 TotalPages;
	POS_GRAPHICS_INFO *GraphicsInfo; 
	
}POS_BOOTLOADER_HEADER; 

UINT8 CheckProcess(EFI_STATUS status, UINT8 PrintError)
{
	UINTN index;
	if(status == EFI_SUCCESS) {
		if(PrintError){
		Print(L"Succeed!\n");
	}
		return 0;
	} else {
		if(PrintError){
		Print(L"Fail!\n");
		Print(L"--Error Code: %r\n", status);
		Print(L"Press any key to kill yourself.\n");
		gST->BootServices->WaitForEvent(1, &(gST->ConIn->WaitForKey), &index);
		}
		
		return 1;
	}
}


EFI_STATUS MemoryWork(UINT64 *TotalPages);
EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *FileSize);
EFI_STATUS GetMapKey(OUT UINTN *key);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST)
{
	
	EFI_STATUS status;
	VOID *Loader = (VOID*)ML_ADDR;
	UINTN LoaderSize;
	VOID *Buffer;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP = NULL;
	UINTN MapKey;
	VOID (*entry)();
	POS_BOOTLOADER_HEADER *pos_Payload = (POS_BOOTLOADER_HEADER *)HDR_ADDR;

	Print(L"ParadOS Bootloader ver. 1.0N\n");

	//Load Loader
	Print(L"Loading the ModuleLoader...");
	status = LoadFileFromTheDrive(L"\\Loader\\ModuleLoader", &Buffer, &LoaderSize);
	if(CheckProcess(status, 1)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);
	}
	Print(L"Loader Size: %d byte\n", LoaderSize);

	ST->BootServices->CopyMem(Loader, Buffer, LoaderSize);
	FreePool(Buffer);

	entry = Loader; //windows compiler care about this

	Print(L"Get GOP infomation...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	if(CheckProcess(status, 1)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);
	}
	pos_Payload->GraphicsInfo->HResolution = GOP->Mode->Info->HorizontalResolution;
	pos_Payload->GraphicsInfo->VResolution = GOP->Mode->Info->VerticalResolution;
	pos_Payload->GraphicsInfo->FrameBufferBase = GOP->Mode->FrameBufferBase;
	pos_Payload->GraphicsInfo->FrameBufferSize = GOP->Mode->FrameBufferSize;
	pos_Payload->GraphicsInfo->PixelsPerScanLine = GOP->Mode->Info->PixelsPerScanLine;
	pos_Payload->GraphicsInfo->PixelFormat = GOP->Mode->Info->PixelFormat;

	Print(L"Get memory infomation...");
	status = MemoryWork(&pos_Payload->TotalPages);
	if(CheckProcess(status, 1)){
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);
	}

	Print(L"Passing control...\n");
	Print(L"If you stuck, that mean ParadOS fail to start.");
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
			ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);
		}
		GetMapKey(&MapKey);//should not do anything before calling the ExitBootServices, these operation might destory the accuracy of memory map.
		status = ST->BootServices->ExitBootServices(IH, MapKey);
	}while(status != EFI_SUCCESS);

	entry();//WHISPER: Get the fuck out of here pls.

	return EFI_SUCCESS; //Never go here, just let the compiler happy :)
}

EFI_STATUS MemoryWork(UINT64 *TotalPages){

	//lazy..
	EFI_STATUS status;
	EFI_MEMORY_DESCRIPTOR *MemMap = NULL; //point to nothing
	UINTN MemMapSize = sizeof(EFI_MEMORY_DESCRIPTOR) * 29;
	UINTN DesSize = 0;
	UINT32 DesVersion;
	UINTN MapKey;
	//Get Memory Map Size frist
	while(1){
	status = gBS->AllocatePool(EfiLoaderData, MemMapSize, (VOID **)&MemMap);
	if(status == EFI_SUCCESS){
		status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, &MapKey, &DesSize, &DesVersion);
		if(status == EFI_BUFFER_TOO_SMALL){
			gBS->FreePool(MemMap);
			MemMapSize += sizeof(EFI_MEMORY_DESCRIPTOR);
		}else if(status == EFI_SUCCESS){
			break;
		}else{
			return status;
		}									
	}else{
		return status;
	}
	}
	UINTN max = MemMapSize / DesSize;

	TotalPages = 0;
	for(UINTN i = 0; i < max;i++){
		EFI_MEMORY_DESCRIPTOR *temp = (EFI_MEMORY_DESCRIPTOR *)(((UINT8 *)MemMap) + (i * DesSize));
		
		TotalPages += temp->NumberOfPages;
	}
	return EFI_SUCCESS;

}

EFI_STATUS GetMapKey(UINTN *key)
{
	EFI_STATUS status = EFI_OUT_OF_RESOURCES;//init variable
	UINTN MemMapSize = 0;
	UINTN DescriptorSize = 0;
	UINT32 DescriptorVersion = 0;
	EFI_MEMORY_DESCRIPTOR *MemMap = NULL;
	do {
		//once the GetMemoryMap function return EFI_BUFFER_TOO_SMALL, it also return the buffer size it need
		if(status == EFI_BUFFER_TOO_SMALL) {
			status = gBS->AllocatePool(EfiLoaderData, MemMapSize, (VOID **)&MemMap);
			if(CheckProcess(status, 0)){
				return status;
			}
		} else if(status == EFI_INVALID_PARAMETER) {
			break;
		}
		status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, key, &DescriptorSize, &DescriptorVersion);
		
	} while(CheckProcess(status, 0));

	return status;
}

EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *Size)
{
	EFI_STATUS status;
	EFI_HANDLE *handles = NULL;
	EFI_FILE *root = NULL;
	EFI_FILE *file = NULL;
	EFI_FILE_INFO *info = NULL;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFS = NULL;
	UINTN MaxHandles;
	UINTN InfoBuffSize = 0;
	UINT8 *buffer;
	
	status = gBS->LocateHandleBuffer(ByProtocol, &gEfiSimpleFileSystemProtocolGuid, NULL, &MaxHandles, &handles);
	if(CheckProcess(status, 0)){
		Print(L"Getting SFS Protocols...");
		return status;
	}
	for(UINTN i = 0; i < MaxHandles; i++){
		status = gBS->HandleProtocol(handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
		if(CheckProcess(status, 0)){
			Print(L"Getting file system protocol...");
			return status;
		}
		status = SFS->OpenVolume(SFS, &root);
		if(CheckProcess(status, 0)){
			Print(L"Opening volume...");
			return status;
		}
		//check is needed file exist?
		status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
		if(!CheckProcess(status, 0)){
			//found!
			break;
		}
	}

	//Be a good boy.
	gBS->FreePool(handles);

	//still nothing...
	if(file == NULL){
		Print(L"File not found...");
		return status;
	}

	//Get what size of buffer it need.
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, NULL);
	if(status == EFI_BUFFER_TOO_SMALL){
		//Need more space!
		status = gBS->AllocatePool(EfiLoaderData, InfoBuffSize, (VOID **)&info);
		if(CheckProcess(status, 0)){
		return status;
	}
	}else if(CheckProcess(status, 0)){
		return status;
	}

	//if go here, mean sucess to allocate pool.
	//do the real getinfo().
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
	if(CheckProcess(status, 0)){
		return status;
	}	
	*Size = info->FileSize;
	//Not use it any more, u free!
	gBS->FreePool(info);

	status = gBS->AllocatePool(EfiLoaderData, *Size, (VOID **)&buffer);
	if(CheckProcess(status, 0)){
		return status;
	}
	
	//Read file
	status = file->Read(file, Size, buffer);
	if(CheckProcess(status, 0)){
		return status;
	}
	
	//Finish!
	status = file->Close(file);
	if(CheckProcess(status, 0)){
		return status;
	}
	root->Close(root);

	*Data = buffer;

	return EFI_SUCCESS;
}
