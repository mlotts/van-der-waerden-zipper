#makefile

generateReport.exe : reportgenerator.o getpowerprogression.o
		gcc reportgenerator.o getpowerprogression.o -lm -o generateReport.exe

#gets the primes and roots and prints them out nicely to a file
reportgenerator.o : reportgenerator.c
		gcc -c reportgenerator.c
		
#has the getPrimes() method that gets all the primes less than the
#argument integer
getpowerprogression.o : getpowerprogression.c
		gcc -c getpowerprogression.c
