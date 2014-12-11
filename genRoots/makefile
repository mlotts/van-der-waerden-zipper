#makefile

generateRoots.exe : rootdriver.o rootgen.o 
	gcc rootgen.o rootdriver.o -lm -o generateRoots.exe

rootgen.o : rootgen.c
	gcc -c rootgen.c

rootdriver.o : rootdriver.c
	gcc -c rootdriver.c
