#include <stdlib.h>
#include <stdio.h>
#include "vdwheader.h"


void zipSequence(char prcolors[], char target[], long long prime, int power);

/*int main(){
	char target[100];
	int i;
	int prime = 19; //37;
	int power = 6;
	char prcolors[] = "011242032503515443"; //"012253234004531415514135400432352210";

	//convert ascii chars to byte-long ints
	for (i = 0; i < prime; i++)
		prcolors[i] = prcolors[i]-48;
	zipSequence(prcolors, target, prime, power);
	return 0;
}*/


/* 
 * This function takes a power-residue coloring for a given prime 
 * and power and zips it to an extended coloring.
 * Parameters:
 *    prcolors - array containing the power-residue coloring
 *    target - array to be filled with the extended coloring
 *    prime - underlying prime used in creating initial coloring
 *    power - power used in deterimining the initial coloring
 */
void zipSequence(char prcolors[], char target[], long long prime, int power)
{
	int i, j, offset;
	long m;

	//SETTING THE GLUE POINTS

	//the color of the first member of the two parts that compose the zipped
	//coloring can be arbitrary, but these should be chosen so as not to form a
	//monochromatic progression amongst themselves
	target[0] = 1;
	target[prime] = (1 + (power/2)) % power;
	
	//printf("\nOriginal Coloring:\n");
	//for(i = 0; i < prime-1; i++)
	//	printf("%d", prcolors[i]);

	//SPREADING

	//even indices of the zipped coloring are simply the numbers of
	//the original coloring
	j = 2;

	for(i = 0; i < (prime-1); ++i)
	{
		target[j] = prcolors[i];
		j += 2;
	}
	
	offset = power / 2;

	//TURNING, SHIFTING, AND MERGING

	//odd indices from 1 to the midpoint of the zipped array are the
	//first half of the original coloring in reverse order
	j = 1;
	//printf("\n\nOdd Numbered Entries:\n");
	for(i = (prime-1)/2; i < (prime-1); ++i)
	{
		target[j] = (prcolors[i] + offset) % power;
		j += 2;
	//printf("%d",((prcolors[i] + offset) % power));
	}

	//odd indices from the midpoint of the zipped array to the end are
	//the second half of the original coloring in reverse order
	j += 2;
	//printf("\n");
	for(i = 0; i < (prime-1)/2; ++i)
	{
		target[j] = (prcolors[i] + offset) % power;
		j += 2;
	//printf("%d",((prcolors[i] + offset) % power));
	}

	//printout that is not used, info is simply printed out in the
	//driver.c file after this method is called
	
	//printf("\n\nZipped Sequence:\n");
	
	//for(i = 0; i < (2*prime); ++i)
	//{
	//	printf("%d",target[i]);
	//}
	//printf("\n\n");
	
}

void rezipSequence(char prcolors[], char target[], long prime, long length, int power)
{
	int i, j;
	
	//this code just filled the zipped array with 9's in order to see
	//how the other parts of the code were working
	
	for(i = 0; i < (2*length); ++i)
	{
		target[i] = 9;
	}
	
	j = 0;

	for(i = 0; i < (2*prime); ++i)
	{
		target[j] = prcolors[i];
		j += 2;
	}

	//odd indices from 1 to the midpoint of the zipped array are the
	//first half of the original coloring in reverse order
	j = 1;
	
	//printf("\n\nOdd Numbered Entries:\n");
	for(i = prime - (prime/2); i < (2*prime); ++i)
	{
		target[j] = (prcolors[i] + (power/2)) % power;
		j += 2;
	//	printf("%d",((prcolors[i] + (power/2)) % power));
	}

	//odd indices from the midpoint of the zipped array to the end are
	//the second half of the original coloring in reverse order
	
	//printf("\n");
	for(i = 0; i < prime - (prime/2); ++i)
	{
		target[j] = (prcolors[i] + (power/2)) % power;
		j += 2;
	//	printf("%d",((prcolors[i] + (power/2)) % power));
	}
	
	/*printf("\n\nZipped Sequence: ");
	
	for(i = 0; i < (2*prime); ++i)
	{
		printf("%d",target[i]);
	}
	*/
}
