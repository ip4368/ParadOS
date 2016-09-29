#include "Library/Math.h"

int64 pow(int base, int n)
{
	// special cases
	if(n < 0)  return 0;
	if(n == 0) return 1;

	/*
	 * Iterative solution for powering
	 * Complexity is O(log x)
	 */
	int64 result = base;
	while(n > 1)
	{
		result *= result;
		if(n % 2) result *= base;
		n /= 2;
	}
	return result;
}
