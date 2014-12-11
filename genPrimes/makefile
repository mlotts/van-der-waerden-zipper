#makefile

generatePrimes.exe : primedriver.o primegen.o 
	gcc primegen.o primedriver.o -lm -o generatePrimes.exe

primegen.o : primegen.c
	gcc -c primegen.c

primedriver.o : primedriver.c
	gcc -c primedriver.c
