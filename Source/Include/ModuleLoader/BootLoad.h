#ifndef _MODULELOADER_BOOTLOAD_H_
#define _MODULELOADER_BOOTLOAD_H_

#include "Types.h"

#define PAYLOAD_ADDRESS 0x9000

//UEFI Service define
//Fuck! Seems UEFI want to replace or hijack the operating system.
//

typedef uint32 EFI_STATUS; //fuck!
typedef struct {
  uint16  Year;
  uint8   Month;
  uint8   Day;
  uint8   Hour;
  uint8   Minute;
  uint8   Second;
  uint8   Pad1;
  uint32  Nanosecond;
  int16   TimeZone;
  uint8   Daylight;
  uint8   Pad2;
} EFI_TIME;

typedef enum {
  EfiResetCold,
  EfiResetWarm,
  EfiResetShutdown
} EFI_RESET_TYPE;

typedef struct {
uint32 Type;
uint64 PhysicalStart;
uint64 VirtualStart;
uint64 NumberOfPages;
uint64 Attribute;
} EFI_MEMORY_DESCRIPTOR; 

typedef struct {
  ///
  /// The table header for the EFI Runtime Services Table.
  ///
  uint64 Signature;
	uint32 Revision;
	uint32 HeaderSize;
	uint32 CRC32; //checksum things
	uint32 Useless;

  //
  // Time Services
  //
  EFI_STATUS (*GetTime)(EFI_TIME *Time); //not gonna use the other parameter

  EFI_STATUS (*SetTime)(EFI_TIME *Time);
  EFI_STATUS (*GetWakeupTime)(bool *Enabled, bool *Pending, EFI_TIME *Time);
  EFI_STATUS (*SetWakeupTime)(bool Enable, EFI_TIME *Time);

  //
  // Virtual Memory Services
  //
  EFI_STATUS (*SetVirtualAddressMap)(uint64 MemoryMapSize, uint64 DesSize, uint32 DesVersion, EFI_MEMORY_DESCRIPTOR *NewMap); 
  EFI_STATUS (*ConvertPointer)(uint64 unuse, void **Address);

  //
  // Variable Services
  //
  EFI_STATUS (*GetVariable)(uint16 *VariableName, uint64 *GUID, uint32 *Attributes, uint64 *DataSize, void *Data);
  EFI_STATUS (*GetNextVariableName)(uint64 *VariableNameSize, uint16 *VariableName, uint64 *GUID);
  EFI_STATUS (*SetVariable)(uint16 *VariableName, uint64 *VendorGUID, uint32 Attributes, uint64 DataSize, void *Data);

  //
  // Miscellaneous Services
  //
  EFI_STATUS (*GetNextHighMonotonicCount)(uint64 *Count);
  void (*ResetSystem)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, uint64 size, void *data);

  //
  // UEFI 2.0 Capsule Services
  //
  EFI_STATUS (*UpdateCapsule)();
  EFI_STATUS (*QueryCapsuleCapabilities)();

  //
  // Miscellaneous UEFI 2.0 Service
  //
  EFI_STATUS (*QueryVariableInfo)(uint32 Attributes, uint64 *MVSS, uint64 *RVSS, uint64 *MVS);
} EFI_RUNTIME_SERVICES;

typedef struct {
  ///
  /// The 128-bit GUID value that uniquely identifies the system configuration table.
  ///
  uint64 VendorGuid[2];
  ///
  /// A pointer to the table associated with VendorGuid.
  ///
  void *VendorTable;
} EFI_CONFIGURATION_TABLE;
//EFI END

//
//PAYLOAD
//
typedef struct{
//GOP
uint32 HResolution;
uint32 VResolution;
uint64 FrameBufferBase;
uint64 FrameBufferSize;
uint32 PixelPerScanLine;
uint8 ColorFormat;
//Memmory
EFI_MEMORY_DESCRIPTOR *MemMap;
uint64 MemMapSize;
uint64 DesSize;
uint32 DesVersion;
//ACPI

//Partitions
uint32 Partition_number;
uint64 *Partition_table;
//UEFI services
EFI_RUNTIME_SERVICES *RuntimeServices;
EFI_CONFIGURATION_TABLE *ConfigurationTable;

} POS_PAYLOAD;

#endif
