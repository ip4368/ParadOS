#include "Library/Math.h"

int64 pow(int z, int x)
{
	// special cases
	if(x < 0)  return 0;
	if(x == 0) return 1;

	/*
	 * Iterative solution for powering
	 * Complexity is O(log x)
	 */
	int64 result = z;
	while(x > 1)
	{
		result *= result;
		if(x % 2) result *= z;
		x /= 2;
	}
	return result;
}
