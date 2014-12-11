#include "vdwheader.h"
#include <string.h>

//this program examines the report and produces a table for the
//longest l-progression-free partitions for particular colorings
main()
{
	FILE *report, *table;
	double starttime, lasttime, fulltime;
	char *line, *chartLine, *filler, *buffer;
	int i, j, curPower, root;
	long long prime;

	//holds all data for each line (prime)
	int ends[5];
	int init[5];
	int max[5];

	//primes and progressions that avoid colorings for specific numbers
	//of partitions and progressions that need to be avoided
	//these two dimensional arrays are indexed first by the powers
	//(number of partitions of the integers) and indexed second by the
	//progression-lengths that need to be avoided
	long long primes[5][10] = {0};
	long long prog[5][10] = {0};

	//where each line of the report is stored
	line = (char *)malloc(125);
	//where the prime line is stored when creating the table
	chartLine = (char *)malloc(130);
	buffer = (char *)malloc(35);
	//place where non-integer parts of lines are stored
	filler = (char *)malloc(2);

	//open report for reading
	report = fopen("report","r");
	//open table file for writing the table
	table = fopen("table","w");
	
	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	//skip over the first two lines of the report since they are just
	//headers
	fgets(line,125,report);
	fgets(line,125,report);

	//go through all the other lines of the report that have the
	//primes, roots, and statistics about them
	//for(i=3; i <= 148934; ++i)
	for(i=3; i <= 9593; ++i)
	{
		//get the next line of the report
		fgets(line,125,report);
		
		//scan the line, always is of same form with prime and root,
		//followed by asterisk, and then each set of statistics for each
		//coloring that are separated by asterisks
	   	sscanf(line,"%lld%d%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d%s%d%d%d",&prime,&root,filler,&ends[0],&init[0],
				&max[0],filler,&ends[1],&init[1],&max[1],filler,&ends[2],&init[2],&max[2],filler,&ends[3],
				&init[3],&max[3],filler, &ends[4],&init[4],&max[4]);

		//see if the statistics can be used
		for(j=2; j < 7; ++j)
		{
			//if the maximum is between 2 and 11 (inclusive) then we are good and they will be used to
			//avoid 3-progressions through 12-progressions
			if (max[j-2] > 1 && max[j-2] <= 11)
			{
				//if (prime-1) is a residue, then init must be less than
				//half of the max in order for it to remain valid. also,
				//init has to be less than max (this would always be true
				//unless there was weird behavior in one of the primes)
				if (((ends[j-2] == 1) && ((init[j-2]*2) >= max[j-2])) || (init[j-2] >= max[j-2]))
				{
				}
				//it is valid prime and the statistics are valid, since
				//the primes are in ascending order, each new valid item
				//is obviously a new maximum prime and progression, so it
				//is stored in the two-dimensional arrays
				else
				{
					prog[j-2][(max[j-2]-2)] = (prime * (max[j-2]) + 1);
					primes[j-2][(max[j-2]-2)] = prime;
				}	
			}
		}
	}

	
	gettimeofday(&secs,&zone);
	lasttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = lasttime - starttime;
	printf("Reading Report... %f secs\n",fulltime);
	
	//print out report with rows for each progression and columns for
	//each power. first item in each table element is the progression,
	//beneath the progressions will be the primes
	
	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	//print out heading and first few lines of report
	fprintf(table,"\n                             Table 1: Lower Bounds For Particular Colorings and Progression Lengths\n\n");
	for (j = 0; j < 129; ++j)
	{
		fprintf(table,"*");
	}
	fprintf(table,"\n");
	fprintf(table,"*%18s%14s%8s%14s%8s%14s%8s%14s%8s%14s%8s\n","*","Power 2","*","Power 3","*","Power 4","*","Power 5","*","Power 6","*");
	for (j = 0; j < 129; ++j)
	{
		fprintf(table,"*");
	}
	fprintf(table,"\n");
	
	//print out rows of report for each possible avoided progression (3-12)
	for (i=3; i < 13; ++i)
	{
		fprintf(table,"* %2d-progression  *",i);
		strcpy(chartLine,"");
		for (j=2; j < 7; ++j)
		{
			//if the prime and progression is reasonable (this needs to
			//be checked since not every element in the table actually
			//has a valid prime and maximum progression length)
			if (primes[j-2][i-3] > 100000 || prog[j-2][i-3] > 100000000 || primes[j-2][i-3] <= 0 || prog[j-2][i-3] <= 0) 
			{
				//simply make array element blank if it is invalid
				fprintf(table,"%22s","*");
				sprintf(buffer,"%22s","*");
				strcat(chartLine,buffer);
			}
			//otherwise print the progression length
			else
			{
				fprintf(table,"        %-8lld%6s",prog[j-2][i-3],"*");
				sprintf(buffer,"        %-8lld%6s",primes[j-2][i-3],"*");
				strcat(chartLine,buffer);
			}
		}
		
		//go to the next line and print the primes
		fprintf(table,"\n*                 *");
		fprintf(table,chartLine);

		//go to the next line and print the bottom line
		fprintf(table,"\n");
		for (j = 0; j < 129; ++j)
		{
			fprintf(table,"*");
		}
		fprintf(table,"\n");
	}
	
	gettimeofday(&secs,&zone);
	lasttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = lasttime - starttime;
	printf("Printing Report... %f secs\n",fulltime);
}
