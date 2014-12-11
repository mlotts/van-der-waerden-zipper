#include <stdio.h>
#include <stdlib.h>

//returns the result of a to be b power using the binary representation of b
long long fastExponent(long long a, long long b, long long prime)
{
	long long power, digit;

	power = 1;
	//for very large powers, this can be adjusted accordingly
	digit = ((long long)1 << 40);

	while((digit & b) == 0)
	{
		digit = digit >> 1;
	}

	while(digit != 1)
	{
		if(digit & b)
		{
			power = (power * a) % prime;	
		}
		power = (power * power) % prime;
		digit = digit >> 1;
	}

	if(digit & b)
	{
		power = (power * a) % prime;
	}

	return (power % prime);
}

//finds the least primitive root of parameter prime
long long getFactorRoot(long long prime)
{
	FILE *source;
	long long primefactors[prime];

	long long guess, done, curNumber, power, i, foundone;
	long long factorcount, factorpower, curPrime, factordown, failure;

	//factoring method assumes you have a list of primes to check
	source = fopen("primes","r");
	factordown = (prime-1);
	factorcount = 0;
	
	//get prime factors, store in primefactors array
	while (factordown != 1)
	{
		fscanf(source,"%lld",&curPrime);
		
		if (factordown % curPrime == 0)
		{
			primefactors[factorcount] = curPrime;
			factorcount++;
			while(factordown % curPrime == 0)
			{
				factordown = factordown / curPrime;
			}
		}
	}

	fclose(source);

	guess = 2;
	failure = 0;

	/* take powers of guesses that are equal to (prime-1) divided the
	 * prime factors. if none of the powers mod the prime  are 1, then
	 * we know that the guess is a primitive root
	 */
	while (! failure)
	{
		foundone = 0;

		for(i = 0; i < factorcount; ++i)
		{
			curNumber = fastExponent(guess,((prime-1)/primefactors[i]),prime);
			if (curNumber == 1)
			{
				foundone = 1;
				break;
			}
		}

		if (foundone == 0)
		{
			break;
		}
		
		guess++;
	}

	return guess;
}
