#include <stdlib.h>
#include <stdio.h>
#include "vdwheader.h"

/* this method examines a particular power and progression and tries
 * to find a prime that can be zipped in order to create a better
 * progression-free partition
 */
main()
{
	//file with candidate primes
	FILE *wkl;
	//line from file with candidate primes
	char *line;
	//destination is where the power progression for the prime is
	//stored
	char destination[1997911];
	//zipped is where the post-zip progression is stored
	static char zipped[2*1997911+1];
	static char zipped2[4*1997911+1];
	
	//array where the full partition is stored
	static char partition[(4*1997911)*(8-1)+1];
	//char partition[(4*320269)*(7-1)+1];
	
	//timing
	double starttime,fulltime,endtime;
	
	int power, root, prog, i, zip2, shortcut;
	//long prime;
	long long prime;

	//struct that is returned from the progression checking methods
	//that has lots of information about the progression if one is
	//found
	CHECKRETURN progret,inarowret;

	//make space for storing the information from the file of candidate
	//primes
	line = (char *)malloc(128);

	//file with candidate primes
	wkl = fopen("W6-8","r");

	//this is 0 if only one zip is to be done, 1 if two zips
	zip2 = 0;
	//this is 0 if a full partition check is to be done, 1 if only
	//string checking is going to be done on the zipped sequence
	shortcut = 1;
	
	//power and progression that is going to be checked
	power = 6;
	prog = 8;

	//while there is still another line in the file of candidate primes
	while(fgets(line,128,wkl) != NULL)
	{
		//get the line from the list of candidate primes
		sscanf(line,"%lld%d",&prime,&root);
		//print the current prime and root being checked
		printf("\nPrime: %lld Root: %d\n",prime,root);
	
		//get the power progression and store it in destination
		getPowerProgression(power,root,prime,destination);
	
		//timing
		//gettimeofday(&secs,&zone);
		//starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
		//arithmetically zip the sequence and store the result in the
		//zipped array
		zipSequence(destination,zipped,prime,power);

		if (zip2 != 0)
		{
			rezipSequence(zipped,zipped2,prime,power);
		}
		//timing
		//gettimeofday(&secs,&zone);
		//endtime = secs.tv_sec + secs.tv_usec/(double)1000000;
		//fulltime = endtime - starttime;
	
		//if the full partition is going to be checked, it has to be
		//built
		if (shortcut == 0)
		{
			//build partition twice as long as p when single zipping
			if (zip2 == 0)
			{
				buildPartition(zipped,partition,(prime*2),prog);
			}
			else
			{
				buildPartition(zipped2,partition,(prime*4),prog);
			}
		}
			
		//}
	
		/* check to see if the zipped progression has an arithmetic
	 	* progression of prog length, result is a 1 if there is a
	 	* progression, 0 if there is not a progression
	 	*/
		
		//if a full partition check is going to be done
		if (shortcut == 0)
		{
			//single zipping
			if (zip2 == 0)
			{
				//check partition for progression strings
				inarowret = inARow(partition,(prime*2)*(prog-1)+1,prog,prime);
				//print out result
				if (inarowret.foundProgression == 1)
				{
					printf("Found string\n");
				}
				else
				{
					printf("No string\n");
				}
				//check partition for any progressions
				progret = progressionChecker(partition,(prime*2)*(prog-1)+1,prog);
			}
			//double zipping
			else
			{
				inarowret = inARow(partition,(prime*4)*(prog-1)+1,prog,prime);
				if (inarowret.foundProgression == 1)
				{
					printf("Found string\n");
		 			printf("\nFailure: %d-string found in zipped sequence\n",prog);
					printf("Initial Index - %d\n",inarowret.initIndex);
					printf("Common Difference - %d\n",inarowret.difference);
				}
				else
				{
					printf("No string\n");
				}
				progret = progressionChecker(partition,(prime*4)*(prog-1)+1,prog);
			}
			
			//if string checking says a partition is valid but the full
			//check finds a progression that is not a string, string
			//checking is obviously insufficient
			if((inarowret.foundProgression == 0) && (progret.foundProgression == 1))
			{
				printf("ERROR: Checking strings was not sufficient\n");
			}
			//if no progression is found
			if(progret.foundProgression == 0)
			{
				//if a string progression is found but the full checker
				//does not find a progression, then something is wrong
				if (inarowret.foundProgression == 1)
				{
					printf("ERROR: Consecutive progression found incorrectly\n");
				}
				//break out of the loop since a progression has been found
				break;
			}
			//if a progression is found
			if(progret.foundProgression == 1)
			{
				//print out all of the diagnostic info for the progression
		 		printf("\nFailure: %d-progression found in zipped sequence\n",prog);
				printf("Initial Index - %d\n",progret.initIndex);
				printf("Common Difference - %d\n",progret.difference);
				//print out diagnostic info for a string progression if
				//one is found
				if (inarowret.foundProgression == 1)
				{
		 			printf("\nFailure: %d-string found in zipped sequence\n",prog);
					printf("Initial Index - %d\n",inarowret.initIndex);
					printf("Common Difference - %d\n",inarowret.difference);

				}
			}
		}
		//if only the zipped sequence is going to be checked for strings
		else
		{
			//single-zipping
			if(zip2 == 0)
			{
				inarowret = inARow(zipped,prime*2,prog,prime);
			}
			//string-checking not sufficient for double-zipping
			else
			{
				//inarowret = inARow(zipped2,prime*4,prog,prime);
			}
			
			//if no progression was found, exit the program
			if(inarowret.foundProgression == 0)
			{
				break;
			}
			//print out diagnostic info for a progression if one is found
			else
			{	
		 		printf("\nFailure: %d-string found in zipped sequence\n",prog);
				printf("Initial Index - %d\n",inarowret.initIndex);
				printf("Common Difference - %d\n",inarowret.difference);
			}
		}
		
		//}
	}

	//print out the results of the checker
	if((progret.foundProgression == 1) || (inarowret.foundProgression == 1))
	{
		printf("\nFailure: None of the primes were able to be zipped\n");
	}
	else
	{
		printf("\nSuccess: No %d-progression found in zipped sequence\n",prog);
		printf("\nThe prime used was %lld\n",prime);
	}
	
	//printf("\nZipping Progression... %f secs\n",fulltime);
	
	printf("\n");
}
