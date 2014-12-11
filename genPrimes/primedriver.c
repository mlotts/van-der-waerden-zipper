#include "vdwheader.h"

main()
{
	//an array of integers
	long integers[100000];
	double starttime, endtime, fulltime;
	//loop counters
	long i,h;
	//buffer
	FILE* fd;
	
	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	//use the sieve method to get the primes up to 100000
	getPrimes(100000,integers);
	
	gettimeofday(&secs,&zone);
	endtime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = endtime - starttime;
	printf("Getting primes... %f secs\n",fulltime);
	
	//open/create file for writing
	fd = fopen("primes","w");

	//write 2 to file
	fprintf(fd,"%d",2);

	h = 1;
	
	for(i=2; i<100000; i+=2)
	{
		if (integers[i] == UNSTRUCK)
		{
			//write prime to file
			fprintf(fd,"\n%ld",(i+1));
			h++;
		}
	}
		
	printf("Number of primes... %ld\n",h);

	//close the file
	fclose(fd);
}
