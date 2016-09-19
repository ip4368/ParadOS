#include "Library/Math.h"

int64 pow(int base, int n)
{
	// base cases
	if(n == 0) return 1;
	if(n == 1) return base;

	/*
	 * Typical recursive solution for powering
	 * Complexity is O(log x)
	 */
	int64 temp = pow(base, n/2);
	if(n % 2) return temp * temp * base;
	else return temp * temp;
}
