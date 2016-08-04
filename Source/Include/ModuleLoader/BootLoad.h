#ifndef _BOOTLOAD_H_
#define _BOOTLOAD_H_

#include "Types.h"

#define PAYLOAD_ADDRESS 0x8000

typedef struct{
//GOP
uint32 HResolution;
uint32 VResolution;
uint64 FrameBufferBase;
uint64 FrameBufferSize;
uint32 PixelPerScanLine;
uint8 ColorFormat;
//Memmory
uint64 Page_Number;
//ACPI

//Partitions
uint32 Partition_number;
uint64 *Partition_table;

} POS_PAYLOAD;

#endif
