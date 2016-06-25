#ifndef _CUMOD_H_
#define _CUMOD_H_

//Signiture
#define MAGIC0 0x90
#define MAGIC1 'C'
#define MAGIC2 'U'
#define MAGIC3 'M'
#define MAGIC3 'O'
#define MAGIC3 'D'
//sizes
#define MAGIC_MAX 6
#define NAME_MAX 32

typedef struct CUMOD_HDR {
	unsigned char MAGIC[MAGIC_MAX];
	unsigned char NAME[NAME_MAX];
	unsigned char PRODUCER[NAME_MAX];

}

#endif