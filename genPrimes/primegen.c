#include "vdwheader.h"

/* fill an integer array with a 1 in all the indices
 * that represent prime numbers. upperBound is the
 * number up to which the primes will be found. integers
 * is the array of integers that will have its entries
 * filled with a 1 or 0 depending on whether the number
 * represented by the array index is prime or composite.
 */

//uses sieve of eratosthenes method
void getPrimes(long long upperBound, long integers[])
{
	/* i -  loop variable
	 * target - the current index of the array
	 * curPrime - the number represented by the target
	 * firstStrike - the first number that needs to be sieved
	 * 	for a given prime
	 * squareRoot - the square root of the upperBound
	 */
	long i,target,curPrime,firstStrike,squareRoot;

	//initialize integers to be unstruck
	for(i=0; i<upperBound; ++i)
	{
		integers[i] = UNSTRUCK;
	}
	
	//start at 2 and do it so that the while loop is more efficient
	target = 2;

	squareRoot = sqrt(upperBound);
	
	//only care about numbers up to the square root of the upper bound
	while (target < squareRoot)
	{
		//sieve on next unstruck number
		if (integers[target] == UNSTRUCK)
		{
			curPrime = target + 1;
			//next possible strike is at the square of the current prime
			firstStrike = curPrime * curPrime;
			//continue to strike on prime squared plus multiples of 2*prime
			while (firstStrike <= upperBound)
			{
				integers[firstStrike-1] = STRUCK;
				firstStrike += (curPrime + curPrime);
			}
		}
		target += 2;
	}
}
