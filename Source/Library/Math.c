#include "Library/Math.h"

int64 pow(int z, int x)
{
	int64 ans = z;
	for(int i = 1; i < x; i++) {
		ans *= z;
	}
	return ans;
}
