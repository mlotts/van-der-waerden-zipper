#include "vdwheader.h"

/* 
 * this program examines the report and produces a list of zip candidates
 * that might be able to improve the bounds listed in the table
 */
main()
{
	FILE *report, *table;
	double starttime, lasttime, fulltime;
	char *line, *filler;
	int i, j, counter, power, prog; 
	long long prime, root, target, targetprime;
	
	//holds all data for each line (prime)
	int ends[5];
	int init[5];
	int max[5];

	//size doesn't need to be bigger than number of total prims being tested
	long long primes[148934];
	long long roots[148934];

	//where each line of the report is stored
	line = (char *)malloc(128);
	//place where non-integer parts of lines are stored
	filler = (char *)malloc(2);

	//open report for reading
	report = fopen("report","r");
	//open the file that will contain the results of the zip analysis
	table = fopen("W6-5","w");
	
	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	/*
	 * this should be the prime that is listed in the table as being the best
	 * for a given progression length and number of partitions
	 */
	targetprime = 14173;

	//for zipping, divide by two; for double-zipping, divide by 4
	target = 14173/2;

	//num partitions and progression length
	power = 6;
	prog = 5;
	
	//skip over the first two lines of the report since they are just headers
	fgets(line,128,report);
	fgets(line,128,report);

	fgets(line,128,report);
	sscanf(line,"%lld%lld%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d",&prime,&root,filler,&ends[0],&init[0],
		&max[0],filler,&ends[1],&init[1],&max[1],filler,&ends[2],&init[2],&max[2],filler,&ends[3],
		&init[3],&max[3],filler,&ends[4],&init[4],&max[4]);

	counter = 3;

	while(prime < target)
	{
		fgets(line,128,report);
		sscanf(line,"%lld%lld%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d",&prime,&root,filler,&ends[0],&init[0],
			&max[0],filler,&ends[1],&init[1],&max[1],filler,&ends[2],&init[2],&max[2],filler,&ends[3],
			&init[3],&max[3],filler,&ends[4],&init[4],&max[4]);

		counter++;
	}
	
	i = 0;
	
	//go through all the other lines of the report that have the
	//primes, roots, and statistics about them
	while(prime <= targetprime)
	{
		//if the maximum is between 2 and 11 (inclusive) then we are good and they will be used to
		//avoid 3-progressions through 12-progressions
		if (max[power-2] == (prog-1))
		{
			//if (prime-1) is a residue, then init must be less than
			//half of the max in order for it to remain valid. also,
			//init has to be less than max (this would always be true
			//unless there was weird behavior in one of the primes)
			if (((ends[power-2] == 1) && ((init[power-2]*2) >= max[power-2])) || (init[power-2] >= max[power-2]))
			{
			}
			//it is valid prime and the statistics are valid, since
			//the primes are in ascending order, each new valid item
			//is obviously a new maximum prime and progression, so it
			//is stored in the two-dimensional arrays
			else
			{
				primes[i] = prime;
				roots[i] = root;
				i++;
			}	
		}
		
		//get the next line of the report
		if(fgets(line,128,report) == NULL)
		{
			break;
		}
		
		//scan the line, always is of same form with prime and root,
		//followed by asterisk, and then each set of statistics for each
		//coloring that are separated by asterisks
	   sscanf(line,"%lld%lld%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d",&prime,&root,filler,&ends[0],&init[0],
				&max[0],filler,&ends[1],&init[1],&max[1],filler,&ends[2],&init[2],&max[2],filler,&ends[3],
				&init[3],&max[3],filler, &ends[4],&init[4],&max[4]);
	}

	for(j = (i-1); j >= 0; j--)
	{
		fprintf(table,"%lld %lld\n",primes[j],roots[j]);
	}

	gettimeofday(&secs,&zone);
	lasttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = lasttime - starttime;
	printf("Generating zip candidates... %f secs\n",fulltime);	
}
