#ifndef _ERRORLEVELS_H_
#define	_ERRORLEVELS_H_
// ##NO WARNING ALLOWED IN COS!### 

#define PANIC_LEVEL_ONE 0x01 //The system can't even work any more.
#define PANIC_LEVEL_TWO 0x02 //The system return an error, but it can't be fix in runtime.
#define PANIC_LEVEL_THREE 0x03 //The system return an error, but it can be fix in runtime.
#define PANIC_LEVEL_FOUR 0x04 //The system return an error, but still works fine.

#endif