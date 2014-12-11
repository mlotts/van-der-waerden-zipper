#include <stdlib.h>
#include <stdio.h>
#include "vdwheader.h"

//length of maximum prime, used to figure out how long
//the destination array needs to be
#define MAX_PRIME 100000

main()
{
	FILE *source, *dest;
	char destination[MAX_PRIME];
	double starttime,fulltime,endtime;
	int power, root, i,j,k,l;
	long long prime;
	int max, cur, ends, init;

	//open the file of primes and roots
	source = fopen("primesandroots","r");
	//open the file that the report will be written to
	//(in writing/creating  mode right here)
	dest = fopen("report","w");

	//originally used to skip over 2
	fscanf(source,"%lld",&prime);
	fscanf(source,"%d",&root);

	fprintf(dest,"%18s%14s%7s%14s%7s%14s%7s%14s%7s%14s%7s\n","*","Power 2","*","Power 3","*","Power 4","*","Power 5","*","Power 6","*");
	fprintf(dest,"Prime%10s%3s%6s%6s%6s%3s","Root","*","Ends","Int","Max","*");
	fprintf(dest,"%6s%6s%6s%3s","Ends","Int","Max","*");
	fprintf(dest,"%6s%6s%6s%3s","Ends","Int","Max","*");
	fprintf(dest,"%6s%6s%6s%3s","Ends","Int","Max","*");
	fprintf(dest,"%6s%6s%6s%3s\n","Ends","Int","Max","*");

	//timing
	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	//these are the primes that need to be added to the report
	for (i = 1; i <= 9591; ++i)
	{
		//check to make sure everything is working
		if (i%2000 == 0)
		{
			printf("On number %d\n",i);
		}
		//get the next prime and root from file
		fscanf(source,"%lld",&prime);
		fscanf(source,"%d",&root);

		//print out the prime and the root
		fprintf(dest,"%-7lld    %-4d%3s",prime,root,"*");
		
		//get the power progression for 2-7 colorings (kth powers of
		//roots)
		for (j=2; j < 7; ++j)
		{
			ends = 0;
			init = 1;
			cur = 1;
			max = 1;
			l = 1;
			
			//get the power progression and store it in the destination
			//array
			getPowerProgression(j,root,prime,destination);

			//if 1 is not a residue, then the prime is not of the right
			//form for the power
			if (destination[0] != 0)
			{
			   fprintf(dest,"  %-5d  %-4d  %-3d  *",0,0,0);
			}
			//valid prime
			else
			{
			
				//check to see if (prime-1) is a residue, make ends 1 if
				//it is (residue means it is in class 0)
				if ((((prime-1)%j) == 0) && ((prime-1)/j) % 2 == 0)
				{
					ends = 1;
				}
				
				//count how many elements at the beginning of the
				//progression are residues (class 0)
				while ((destination[l] == 0) && (l < ((prime/2)-1)))
				{
					init++;
					l++;
				}

				//start looking at the rest of the progression, with the
				//longest progression so far obviously being the initial
				//progression
				max = init;
				cur = 1;

				//only have to look through half the progression due to
				//symmetries in progressions
				for (l; l <= ((prime/2)-1); ++l)
				{
					//if there is a streak of consecutive elements in the
					//same class, add one to the current streak
					if (destination[l] == destination[l-1])
					{
						cur ++;
						//if we are at the halfway point
						if (l == ((prime/2)-1))
						{
							//if the element on the other side of the halfway
							//point is in the same class as the element
							//directly before it, we know that the symmetry
							//carries across the halfway mark and thus, the
							//progression needs to be doubled
							if (destination[l] == destination[l+1])
							{
								//check to see if doubling the current
								//progression is longer than the maximum
								//progression so far, if so, change it and
								//break out of the loop
								if ((cur * 2) >= max)
								{
									max = cur*2;
									break;
								}
							}
						}
						//update the maximum progression if a new maximum
						//progression is found
						if (cur >= max)
						{
							max = cur;
						}
					}
					//if a progression ends, reset the progression length
					//counter (cur) to 1
					else
					{
						cur = 1;
					}
				}

				//print out the data for the current prime and power
			   fprintf(dest,"  %-5d  %-4d  %-3d  *",ends,init,max);	
			}
		}
		//go to the next line in the report
		fprintf(dest,"\n");
	}
	
	//close the streams
	fclose(source);
	fclose(dest);

	//timing stuff
	gettimeofday(&secs,&zone);
	endtime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = endtime - starttime;
	printf("Report Generation... %f secs\n",fulltime);
}
