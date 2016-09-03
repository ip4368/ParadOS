//windows compiler sucks!
#pragma warning(disable:4152) //just make windows compiler happy
//im gonna using windows C compiler, because the output file size is much lighter.
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
#define PLADD 0x9000

typedef struct{
//GOP
UINT32 HResolution;
UINT32 VResolution;
UINT64 FrameBufferBase;
UINT64 FrameBufferSize;
UINT32 PixelPerScanLine;
UINT8 ColorFormat;
//Memory
EFI_MEMORY_DESCRIPTOR *MemMap;
UINT64 MemMapSize;
UINT64 DesSize;
UINT32 DesVersion;
//ACPI

//Partitions
UINT32 Partition_number;
UINT64 *Partition_table;
//UEFI services
EFI_RUNTIME_SERVICES *RuntimeServices;
EFI_CONFIGURATION_TABLE *ConfigurationTable;
} POS_PAYLOAD;

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

EFI_STATUS MemoryWork(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR *Memmap, UINT64 *MemmapSize);
EFI_STATUS LoadFileFromTheDrive(IN CHAR16 *FileName, OUT VOID **Data, OUT UINTN *FileSize);

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE IH, IN EFI_SYSTEM_TABLE *ST)
{
	
	EFI_STATUS status;
	VOID *Loader = (VOID*)ML_ADDR;
	UINTN LoaderSize;
	VOID *Buffer;
	EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP = NULL;
	VOID (*entry)();
	POS_PAYLOAD *pos_Payload = (POS_PAYLOAD *)PLADD;

	UINT64 MemMapSize = 0;
	EFI_MEMORY_DESCRIPTOR *MemMap = (EFI_MEMORY_DESCRIPTOR *)0x1000;
	UINT64 MapKey = 0;
	UINT64 DesSize  = 0;
	UINT32 DesVersion = 0;

	Print(L"ParadOS Bootloader ver. 1.0N\n");

	//Load Loader
	Print(L"Loading the ModuleLoader...");
	status = LoadFileFromTheDrive(L"\\Loader\\ModuleLoader", &Buffer, &LoaderSize);
	if(CheckProcess(status, 1)) {
		ST->BootServices->Exit(IH, status, 0, NULL);
	}
	Print(L"Loader Size: %d byte\n", LoaderSize);

	ST->BootServices->CopyMem(Loader, Buffer, LoaderSize);
	FreePool(Buffer);

	entry = Loader; //windows compiler care about this

	Print(L"Get GOP infomation...");
	status = ST->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (VOID **)&GOP);
	if(CheckProcess(status, 1)) {
		ST->BootServices->Exit(IH, status, 0, NULL);
	}
	pos_Payload->HResolution = GOP->Mode->Info->HorizontalResolution;
	pos_Payload->VResolution = GOP->Mode->Info->VerticalResolution;
	pos_Payload->FrameBufferBase = GOP->Mode->FrameBufferBase;
	pos_Payload->FrameBufferSize = GOP->Mode->FrameBufferSize;
	pos_Payload->PixelPerScanLine = GOP->Mode->Info->PixelsPerScanLine;
	pos_Payload->ColorFormat = GOP->Mode->Info->PixelFormat;

	Print(L"Passing control...\n");
	Print(L"If you stuck, that mean ParadOS fail to start.\n");
	
	/*
	LOGIC:
		Get memory map frist, then call the ExitBootServices.
		After that, check if everything fine, if true pass control.
		Otherwise, call it again. 
		Until its done.
	*/
	UINT8 i  = 0;
	do{
		i++;
		if(i == 3){
			Print(L"Fail to escape...");
			ST->BootServices->Exit(IH, status, 0, NULL);
		}

		//should not do anything before calling the ExitBootServices, these operation might destory the accuracy of memory map.
		MemoryWork(&MapKey, &DesVersion, &DesSize, MemMap, &MemMapSize);
		status = ST->BootServices->ExitBootServices(IH, MapKey);
	}while(status != EFI_SUCCESS);

	/*
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!FULL CONTROL AREA!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/
	pos_Payload->MemMap = MemMap;
	pos_Payload->MemMapSize = MemMapSize;
	pos_Payload->DesSize = DesSize;
	pos_Payload->DesVersion = DesVersion;

	
	//Runtime services
	pos_Payload->RuntimeServices = (ST->RuntimeServices);

	//Configuration table
	pos_Payload->ConfigurationTable = (ST->ConfigurationTable);

	entry();//Get the fuck out of here!

	return EFI_SUCCESS; //Never go here, just let the compiler happy :)
}

EFI_STATUS MemoryWork(UINT64 *Key, UINT32 *DesVersion, UINT64 *DesSize, EFI_MEMORY_DESCRIPTOR *Memmap, UINT64 *MemmapSize){

	//lazy..
	EFI_STATUS status;
	//Get Memory Map Size frist
	status = gST->BootServices->GetMemoryMap(MemmapSize, Memmap, Key, DesSize, DesVersion);
	while(1){
	status = gBS->AllocatePool(EfiLoaderData, *MemmapSize, (VOID **)&Memmap);
	if(status == EFI_SUCCESS){
		status = gST->BootServices->GetMemoryMap(MemmapSize, Memmap, Key, DesSize, DesVersion);
		if(status == EFI_BUFFER_TOO_SMALL){
			gBS->FreePool(Memmap);
			MemmapSize += sizeof(EFI_MEMORY_DESCRIPTOR);
		}else if(status == EFI_SUCCESS){
			break;
		}else{
			return status;
		}									
	}else{
		return status;
	}
	}

	return EFI_SUCCESS;
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
