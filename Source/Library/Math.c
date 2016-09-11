#include "Library/Math.h"
/*
int64 pow(int z, int x)
{
	// base cases
	if(x == 0) return 1;
	if(x == 1) return z;

	/*
	 * Typical recursive solution for powering
	 * Complexity is O(log x)
	 */
	int64 temp = pow(z, x/2);
	if(x % 2) return temp * temp * z;
	else return temp * temp;
}

*/