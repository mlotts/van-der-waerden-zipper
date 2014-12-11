#include <stdio.h>
#include <stdlib.h>

/* dest will contain the residue class identifiers for the numbers
 * represented by the array indices
 */
void getPowerProgression(int power, int root, long long prime, char dest[])
{
	int i;
	long long target;

	target = 1;
	
	for (i = 1; i < prime; ++i)
	{
		//get power of root
		target = ((target % prime) * root) % prime;
		dest[target-1] = i % power;
	}
}
