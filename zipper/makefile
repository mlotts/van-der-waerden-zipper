#makefile

#executable that runs the zipcheckdriver program in order to check to
#see if particular W(k,l) can be improved by zipping primes
zippercheck.exe : zipcheckdriver.o getpowerprogression.o zipperFinal.o progressionchecker.o buildpartition.o
		gcc zipcheckdriver.o getpowerprogression.o zipperFinal.o progressionchecker.o buildpartition.o -lm -o zippercheck.exe

#method takes a prime, a power, a progression, and a file of candidate
#primes and then checks to see if any of the candidate primes can be
#used to create an optimal progression-free partition
zipcheckdriver.o : zipcheckdriver.c
		gcc -c zipcheckdriver.c

#has getPowerProgression() method that gets the power progression for
#each the argument prime, root, and power
getpowerprogression.o : getpowerprogression.c
		gcc -c getpowerprogression.c

#contains the zipRabungSequence() method that actually zips the sequence
#in the argument array and places the new sequence in the other argument
#array. the zip used is an arithmetic zip that takes advantage of the
#reduced residue system mod 2p
zipperFinal.o : zipperFinal.c
		gcc -c zipperFinal.c

#contains the progressionChecker() method that takes an progression in
#an argument array and checks to see if it has an arithmetic
#progression of its argument length. this file also has the method
#that checks to see if there is a progression string of residues or
#nonresidues that is in the same kth power class mod p
progressionchecker.o : progressionchecker.c
		gcc -c progressionchecker.c

#takes a sequence and then replicates it multiple times according to
#the function's parameters. the partition is stored in a separate array
#and is then checked by the progressionchecker for progressions
buildpartition.o : buildpartition.c
		gcc -c buildpartition.c
