#include <stdlib.h>
#include <stdio.h>
#include "vdwheader.h"

//take the zipped sequence, the length of the zipped sequence, and the
//progression length, and then build the entire partition and store it
//in the partition[] array
void buildPartition(char zipped[], char partition[], long long length, int prog)
{
	//loop counter
	int i;

	//build the partition composed of (prog-1) multiples of the zipped
	//progression (that has length length)
	for(i = 0; i < (length*(prog-1)); ++i)
	{
		partition[i] = zipped[(i%length)];
	}

	//put the last number in the partition
	partition[i] = 0;

	printf("\nPartition of Length %lld\n",(length * (prog-1))+1);

	/*for(i = 0; i < (length*(prog-1)+1); ++i)
	{
		if ((i%(length/2)) == 0)
			printf("\n");
		printf("%d ",partition[i]);
	}
	printf("\n");*/
}
