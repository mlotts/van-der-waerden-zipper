#include <stdlib.h>
#include <stdio.h>
#include "vdwheader.h"

/* the destination is where the progression is passed in to the
 * function, the prime is simply the length of the array, and the
 * progression is the length of the progression that the sequence is
 * supposed to avoid
 */
CHECKRETURN progressionChecker(char destination[], long long prime, int progression)
{
	double starttime,fulltime,endtime;
	CHECKRETURN returnstruct;
	
	/* valid is 1 if the progression is not found, 0 if otherwise
	 * startscan is the index of the array where the program starts to
	 *   look for a progression for a given element in the array
	 * curdiff is the distance between elements in the array for the
	 *   current progression that is being tested
	 */
	int valid, startscan, curdiff, nextstep, i, j;

	valid = 1;

	//gettimeofday(&secs,&zone);
	//starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	/* if for some reason the user wants to look for a two or one
	 * progression, it will always exist for sequence made from a power
	 * residue coloring
	 */
	if(progression <= 2)
	{
		//printf("\nThere is a %d progression\n\n",progression);
		returnstruct.foundProgression = 1;
		return returnstruct;
		//return 1;
	}
	else
	{
		/* check each element in the array to see if it is in an invalid
		 * progression
		 */
		for (i = 0; i < (prime-1-(progression-1)); ++i)
		{
			//printf("\nLooking at index number %d, which is %d...\n",i,destination[i]);
			/* always start looking for a progression at the position
			 * directly after the current element being examined
			 */
			startscan = i+1;

			//make sure startscan stays in the bounds of the array
			while(startscan <= (prime-1))
			{
				//if the elements are equal, we have the beginning of a
				//progression
				if (destination[i] == destination[startscan])
				{
					//printf("Next possibility at %d, which is %d\n",startscan,destination[startscan]);

					//calculate the difference between the two elements
					//found so far
					curdiff = startscan-i;

					//nextstep is how far away from the intial progression
					//element the next element to check will be
					nextstep = curdiff;
					
					//printf("Looking at difference of %d\n", curdiff);
					//curdiff = startscan - i;
			
					//this loop will count if the progression is long
					//enough to be invalid
					for (j = 2; j < progression; ++j)
					{
						//if ((startscan + curdiff) < (prime-1))
						
						//just code here for the checking statement
						//if ((startscan + nextstep) <= (prime-1))
						//{
							//printf("Next number in sequence is at index %d and is %d\n", (startscan+nextstep/*curdiff*/), destination[startscan+nextstep/*curdiff*/]);
						//}
						
						//if the next element in the progression is a valid
						//progression element
						if (((startscan + nextstep) <= (prime-1)) && (destination[startscan] == destination[startscan + nextstep]))
						{
							//calculate where the next element would be
							nextstep += curdiff;
							
							/* valid is now 0 since we are in what might
							 * become an invalid progression (it will change
							 * back to 1 if the progression is short enough to
							 * remain within the given length
							 */
							valid = 0;
						}

						/* if the next element in the progression is not a
						 * valid element, then we are done checking this
						 * progression and we can break out of the for loop
						 * and make valid 1 again
						 */
						else
						{
							valid = 1;
							break;	
						}
					}

					//if the for loop ended and valid is still 0, then an
					//invalid progression was found
					if (valid == 0)
					{
						//break out of the while loop since we know that
						//this sequence has an invalid progression
						break;
					}
					//if the progression ended and was short enough
					else
					{
						//start looking for a progression and the next array
						//index
						startscan++;
					}
				}
				else
				{
					startscan++;
				}
			}
			//break out of the larger for loop when an invalid
			//progression was found
			if (valid == 0)
			{
				break;
			}
		}

		//gettimeofday(&secs,&zone);
		//endtime = secs.tv_sec + secs.tv_usec/(double)1000000;
		//fulltime = endtime - starttime;
		//printf("\nProgression checker... %f secs\n",fulltime);

		//could just write return ! valid but I like the readability of
		//this code better
		if (valid == 1)
		{
			//printf("\nNo %d-progression found\n",progression);
			returnstruct.foundProgression = 0;
			returnstruct.difference = curdiff;
			returnstruct.initIndex = i;
			return returnstruct;
		}
		else
		{
			//printf("\n%d-progression found, starts at position %d with a difference of %d\n\n",progression,i,(curdiff/*/(progression-1)*/));
			returnstruct.foundProgression = 1;
			returnstruct.difference = curdiff;
			returnstruct.initIndex = i;
			return returnstruct;
		}
	}
}


//ASSUMES THAT ONLY SINGLE ZIPPING IS DONE (i.e. THAT ZIPPED SEQUENCE IS 2p!!!
//check for progressions with successive elements
CHECKRETURN inARow(char destination[], long long length, int progression, long long prime)
{
	//is eventually returned with results of what is found
	CHECKRETURN returnstruct;
	//congruent is 1 if the prime is congruent to 1 mod 4
	int i, cur, congruent,success;
	
	cur = 1;
	congruent = 0;
	success == 0;

	//if prime is congruent to 1 mod 4
	if (prime % 4 == 1)
	{
		congruent = 1;
	}

	//if prime is congruent to 1 mod 4
	if (congruent == 1)
	{
		//are 1,2,...(l-1)/2 in the same class?
		for (i = 1; i < ((progression-1)/2); ++i)
		{
			//if the beginning of the progression is not invalid
			if (!(destination[i] == destination[i+1]))
			{
				success = 1;
				break;
			}
		}
	}
	//if prime is not congruent to 1 mod 4
	else
	{
		//are 1,2,...(l-1) in the same class?
		for (i = 1; i < (progression-1); ++i)
		{
			if (!(destination[i] == destination[i+1]))
			{
				success = 1;
				break;
			}
		}
	}

	//THERE WAS A PROBLEM WITH THE BEGINNING OF THE ARRAY
	if (success != 1)
	{
		//set up diagnostic info and return the structure
		returnstruct.foundProgression = 1;
		returnstruct.difference = 1;
		//-1 for initIndex means there was a problem at the beginning
		returnstruct.initIndex = -1;
		return returnstruct;
	}
	
	//printf("\nCommencing string checking\n");
	//printf("Sequence Length: %d\nProgression:	%d\n",length,progression);
	//printf("%d %d\n",destination[1],destination[618]);

	//check for strings
	for(i = 0; i < (length-1); ++i)
	{
		//IS THERE SYMMETRY IN THE ZIPPED SEQUENCE???
		if (i < ((2*prime)-1))
		{
			//printf("i = %d\ni+prime = %d\n",i,(i+prime)%(2*prime));

			//IF DOUBLE ZIPPING, USE THIS IF STATEMENT instead of the below
			//if (destination[i] == destination[(i+(2*prime))%(4*prime)])

			//IF SINGLE ZIPPING, USE THIS IF STATEMENT
			if (destination[i] == destination[(i+prime)%(2*prime)])
			{
				//partition is invalid since the symmetry will create
				//progressions
				//printf("Invalid Symmetry\n");
				success = 0;
				break;
			}
		}
	
		//if there is are back-to-back numbers in the same kth power
		//class then a progression string is present
		if(destination[i] == destination[i+1])
		{
			//add 1 to cur, which represents the length of the
			//progression
			cur++;
			//if there is a progression that is equal to the progression
			//length that needs to be avoided, then the partition is
			//invalid
			if(cur == progression)
			{
				break;
			}
		}
		//otherwise, the progression length counter is reset to 1
		else
		{
			cur = 1;
		}
	}
	//printf("i = %d\n",i);

	//if success is 0 then the partition has invalid symmetry
	if (success == 0)
	{
		returnstruct.foundProgression = 1;
		returnstruct.difference = prime;
		returnstruct.initIndex = i;

		return returnstruct;
	}

	//if cur is equal to progression then there was an invalid
	//progression string found
	if(cur == progression)
	{
		//printf("String Found\n");
		returnstruct.foundProgression = 1;
		returnstruct.difference = 1;
		returnstruct.initIndex = i-(progression-1);
	}
	//otherwise the partition was valid
	else
	{
		//printf("String not found\n");
		//printf("cur = %d\nprogression = %d\n",cur,progression);
		returnstruct.foundProgression = 0;
	}

	//return the structure
	return returnstruct;
}
