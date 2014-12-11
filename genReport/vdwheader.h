#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

//used for sieve of eratosthenes
#define UNSTRUCK 0
#define STRUCK 1

//timing structures
struct timeval secs;
struct timezone zone;

//structure that is returned by progression checking methods
struct progCheckReturn
{
	//whether or not a progression is found
	int foundProgression;
	//the index where the progression starts
	int initIndex;
	//the difference between progression elements
	int difference;
};

//so the progCheckReturn structures can be called CHECKRETURN
typedef struct progCheckReturn CHECKRETURN;

/* fill an integer array with a 1 in all the 
 * indices that represent prime numbers
 */
void getPrimes(long long upperBound, long* array);

//check for all progressions
CHECKRETURN progressionChecker(char *zip, long long prime, int power);

//check for progression strings
CHECKRETURN inARow(char *destination, long long length, int progression, long long prime);
