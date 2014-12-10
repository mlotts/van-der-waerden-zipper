van-der-waerden-zipper
======================

## Overview

This code was written in the summer of 2010 by Mark Lotts and Dr. John Rabung as part of a research project to find new lower for van der Waerden numbers. Its primary function is to create progression-free interger partitions, which can then be used to try and improve lower bounds for van der Waerden numbers. The result of this work was published in the Electronic Journal of Combinatorics and can be found here: [http://www.combinatorics.org/ojs/index.php/eljc/article/view/v19i2p35/pdf](http://www.combinatorics.org/ojs/index.php/eljc/article/view/v19i2p35/pdf).

We broke down the process of testing integer partitions to find new lower bounds into five distinct steps, each of which is represented by a separate subfolder in this repository, which contains a makefile that produces the necessary binary. A brief description of each step and information about the corresponding code is below.

## Step 1 - Generate Primes
The first step is generating prime numbers. The code for this step can be found in the genPrimes directory.

#### Files Involved

- `primedriver.c`
- `primegen.c`
- `vdwheader.h`
- `makefile`

#### Executable 

`makefile` creates `generatePrimes.exe`

#### Notes

To change the upper bound for the prime-finding, you'll need to modify the body of the primedriver.c file. The primegen.c file uses the Sieve of Eratosthenes to find primes. The output of the executable is a file called 'primes' that contains one prime number per line, in ascending order.

## Step 2 - Finding Primitive Roots
The second step is finding a primitive root for each prime. The code for this step can be found in the genRoots directory.

#### Files Involved

 - `rootdriver.c`
 - `rootgen.c`
 - `makefile`

#### Executable 
 
`makefile` creates `generateRoots.exe`

#### Notes

The `rootdriver.c` file looks for the 'primes' file generated in the previous step to read in a list of prime numbers. Then, `rootgen.c` finds primitive roots for these primes by calculating the prime factorization of (p-1) for each prime p, and then checking the corresponding powers of the candidate root mod p to ensure that none of them generate 1. The output of the executable is a file called 'primesandroots' that contains, in ascending order, one prime and one root per line, delimited by a space.

## Step 3 - Creating a Report
The third step is creating a "report" for each prime and root pair that lists characteristics about the power class partition they generate. These characteristics determine whether the partition is a viable candidate for creating long, progression-free partitions.

#### Files Involved
 - `reportgenerator.c`
 - `getpowerprogression.c`
 - `vdwheader.c`
 - `makefile`

#### Executable

`makefile` creates `generateReport.exe`

#### Notes

This `reportgenerator.c` file looks for the 'primesandroots' file that was generated in the previous step. The output from this executable is a file called 'report'. More details about the contents of 'report' can be found in our paper.

## Step 4 - Reading the Report and Identifying Zip Candidates
The fourth step is reading the report and determining which progressions are candidates for zipping; a process which can lead  to significantly longer progression-free partitions.

#### Files Involved

 - `reportreader.c`
 - `zippossibilityfilecreator.c`
 - `vdwheader.c`
 - `makefile`

#### Executable

`reportreader.c` and `zippossibilityfilecreator.c` compile separately

#### Notes

The `reportreader.c` file looks for the 'report' file generated in the previous step. It outputs a file called 'table' that contains the largest primes from 'report' that can be used to generate progression-free partitions with two, three, four, five, and six power classes. For each number of classes, the primes used to avoid progressions of length three through twelve are listed. After the 'table' file is created, the `zippossibilityfilecreator.c` file is used to create files of candidate primes that, after being zipped, can potentially be used to create larger progression-free partitions than those listed in the table. This file also looks for the 'report' file, and it requires editing of the code for the creation of each candidate file. For example, to generate a list of primes for zip testing for the case of six power classes and avoiding 5-progressions, you'll need to edit the following lines:

```
//open the file that will contain the results of the zip analysis
table = fopen("W6-5","w");
		
//the prime indicated in 'table' as the largest for k=6, l=5
targetprime = 14173;

//for zipping, divide by two; for double-zipping, divide by 4
target = 14173/2;

//num partitions and progression length
power = 6;
prog = 5;
```

## Step 5 - Create and Validate Zipped Partitions
The fifth and final step is using the files of zip candidates to determine whether or not any of the partitions listed in the table can be improved by zipping.

#### Files Involved
 - `zipcheckdriver.c`
 - `getpowerprogression.c`
 - `zipperFinal.c`
 - `progressionchecker.c`
 - `buildpartition.c`
 - `vdwheader.c`
 - `makefile`

#### Executable
`makefile` creates `zippercheck.exe`

#### Notes
The `zipcheckdriver.c` file looks for zip candidate files created in the previous step using `zippossibilityfilecreator.c` and then checks the primes in each file to determine if they create progression-free zipped partitions. Our research showed that, for single zipping, partitions that are free of strings of l elements can be 'glued' together to create an l-progression free partition of size (2p)*(l-1)+1, where p is the prime used to create the partition. Thus, by default, `progressionchecker.c` will only check for strings of elements in the same power class. For double-zipping, string-checking is not sufficient to determine that the partition will be free of l-progressions, so `progressionchecker.c` also contains an exhaustive progression-checking algorithm. The following lines in zipcheckdriver.c need to be changed before each usage depending on the value of k and l being tested, and whether or not zipping or double-zipping is being tested.

```
//should be the size of the prime
char destination[1997911];
//zipped is where the post-zip progression is stored
static char zipped[2*1997911+1];
static char zipped2[4*1997911+1];
    
//array where the full partition is stored
static char partition[(4*1997911)*(8-1)+1];

//file with candidate primes
wkl = fopen("W6-8","r");

//this is 0 if only one zip is to be done, 1 if two zips
zip2 = 0;
//this is 0 if a full partition check is to be done, 1 if only
//string checking is going to be done on the zipped sequence
shortcut = 1;

//power and progression that is going to be checked
power = 6;
prog = 8;
```

Furthermore, if string-checking is being used for double-zipping (which, as previously stated, is not sufficient, but can be used to narrow down the candidates before exhaustive checking is done), the following if statements in the `progressionchecker.c` file must be swapped:

```
//IF DOUBLE ZIPPING, USE THIS IF STATEMENT instead of the below
//if (destination[i] == destination[(i+(2*prime))%(4*prime)])

//IF SINGLE ZIPPING, USE THIS IF STATEMENT
if (destination[i] == destination[(i+prime)%(2*prime)])
```
