//AH! AH! AH! windows compiler sucks!
#pragma warning(disable:4152) //just make windows compiler happy
//im gonna using windows C compiler, because the efi file size is much lighter.


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


EFI_STATUS MemoryWork();
EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *FileSize);
EFI_STATUS GetMapKey(OUT UINTN *key);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST)
{
	UINTN Index;
	EFI_STATUS status;
	VOID *Loader = (VOID*)ML_ADDR;
	UINTN LoaderSize;
	VOID *Buffer;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP = NULL;
	UINTN MapKey;
	VOID (*entry)();
	POS_GRAPHICS_INFO *pos_video = (POS_GRAPHICS_INFO *)HDR_ADDR;


	Print(L"ParadOS Bootloader ver. 1.0N\n");
	Print(L"Firmware Vendor  :  %s \n", ST->FirmwareVendor);

	//Load Loader
	Print(L"Loading the ModuleLoader...");
	status = LoadFileFromTheDrive(L"\\Loader\\ModuleLoader", &Buffer, &LoaderSize);
	if(!CheckProcess(status)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
	}
	Print(L"Loader Size: %d byte\n", LoaderSize);

	ST->BootServices->CopyMem(Loader, Buffer, LoaderSize);
	FreePool(Buffer);

	entry = Loader; //windows compiler care about this

	Print(L"Get GOP infomation...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	if(!CheckProcess(status)) {
		ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
	}

	pos_video->HResolution = GOP->Mode->Info->HorizontalResolution;
	pos_video->VResolution = GOP->Mode->Info->VerticalResolution;
	pos_video->FrameBufferBase = GOP->Mode->FrameBufferBase;
	pos_video->FrameBufferSize = GOP->Mode->FrameBufferSize;
	pos_video->PixelsPerScanLine = GOP->Mode->Info->PixelsPerScanLine;
	pos_video->PixelFormat = GOP->Mode->Info->PixelFormat;

	Print(L"Memory Work\n");
	MemoryWork();
	ST->BootServices->WaitForEvent (
  1,
  &(ST->ConIn->WaitForKey),
  &Index);

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
			ST->BootServices->Exit(IH, EFI_SUCCESS, 0, NULL);//yup success~!
		}
		GetMapKey(&MapKey);//should not do anything before calling the ExitBootServices, these operation might destory the accuracy of memory map.
		status = ST->BootServices->ExitBootServices(IH, MapKey);
	}while(status != EFI_SUCCESS);


	entry();//WHISPER: Get the fuck out of here pls.
	

	return EFI_SUCCESS; //Never go here, just let the compiler happy :)
}

EFI_STATUS MemoryWork(){

	//lazy..
	EFI_STATUS status;
	EFI_MEMORY_DESCRIPTOR *MemMap = NULL; //point to nothing
	UINTN MemMapSize = 0;
	UINTN DesSize;
	UINT32 DesVersion;
	UINTN MapKey;
	UINT8 IsEqual = 0;

	//Get Memory Map Size frist
	status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, &MapKey, &DesSize, &DesVersion);
	if(status != EFI_BUFFER_TOO_SMALL){
		return status; 
	}else{
		status = gBS->AllocatePool(EfiRuntimeServicesData, MemMapSize, (VOID **)&MemMap);
		if(!CheckProcess(status)){//cant allocate
			return status;
		}
	}
	status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, &MapKey, &DesSize, &DesVersion);
	if(!CheckProcess(status)){
		return status;
	}
	//Check paging ratio
	if((UINT64)MemMap[0].PhysicalStart == (UINT64)MemMap[0].VirtualStart){ //if Physical address is equal Virtual address
		IsEqual = 1;//great!
		Print(L"Physical address is equal Virtual address\n"); //Physical address is equal Virtual address in my pc
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
			status = gBS->AllocatePool(EfiBootServicesData, MemMapSize, (VOID **)&MemMap);
			if(!CheckProcess(status)){
				return status;
			}
		} else if(status == EFI_INVALID_PARAMETER) {
			break;
		}
		status = gST->BootServices->GetMemoryMap(&MemMapSize, MemMap, key, &DescriptorSize, &DescriptorVersion);
		
	} while(status != EFI_SUCCESS);

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
	if(status != EFI_SUCCESS){
		Print(L"Getting SFS Protocols...");
		return status;
	}
	for(UINTN i = 0; i < MaxHandles; i++){
		status = gBS->HandleProtocol(handles[i], &gEfiSimpleFileSystemProtocolGuid, (void **)&SFS);
		if(status != EFI_SUCCESS){
			Print(L"Getting file system protocol...");
			return status;
		}
		status = SFS->OpenVolume(SFS, &root);
		if(status != EFI_SUCCESS){
			Print(L"Opening volume...");
			return status;
		}
		//check is needed file exist?
		status = root->Open(root, &file, FileName, EFI_FILE_MODE_READ, 0);
		if(status == EFI_SUCCESS){
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
		status = gBS->AllocatePool(EfiBootServicesData, InfoBuffSize, (VOID **)&info);
		if(status != EFI_SUCCESS){
		return status;
	}
	}else if(status != EFI_SUCCESS){
		return status;
	}

	//if go here, mean sucess to allocate pool.
	//do the real getinfo().
	status = file->GetInfo(file, &gEfiFileInfoGuid, &InfoBuffSize, info);
	if(status != EFI_SUCCESS){
		return status;
	}	
	*Size = info->FileSize;
	//Not use it any more, u free!
	gBS->FreePool(info);

	status = gBS->AllocatePool(EfiBootServicesData, *Size, (VOID **)&buffer);
	if(status != EFI_SUCCESS){
		return status;
	}
	
	//Read file
	status = file->Read(file, Size, buffer);
	if(status != EFI_SUCCESS){
		return status;
	}
	
	//Finish!
	status = file->Close(file);
	if(status != EFI_SUCCESS){
		return status;
	}
	root->Close(root);

	*Data = buffer;

	return EFI_SUCCESS;
}
