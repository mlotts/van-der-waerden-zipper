#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
struct timeval secs;
struct timezone zone;

main()
{	
	FILE *source, *dest;
	double starttime, endtime, fulltime;
	long long prime, root;

	gettimeofday(&secs,&zone);
	starttime = secs.tv_sec + secs.tv_usec/(double)1000000;
	
	source = fopen("primes","r");
	dest = fopen("primesandroots","w");

	fscanf(source,"%lld",&prime);
	fprintf(dest,"%lld %d",prime,1);

	while (fscanf(source,"%lld",&prime) != EOF)
	{
		root = getFactorRoot(prime); 
		fprintf(dest,"\n%lld %lld",prime,root);
	}

	fclose(source);
	fclose(dest);

	gettimeofday(&secs,&zone);
	endtime = secs.tv_sec + secs.tv_usec/(double)1000000;
	fulltime = endtime - starttime;
	printf("Getting primitive roots... %f secs\n",fulltime);

}
