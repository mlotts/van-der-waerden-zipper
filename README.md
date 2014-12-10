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
The third step is creating a "report" for each prime and root pair that lists characteristics about the power class progression they generate. These characteristics determine whether the progression is a viable candidate for creating long, progression-free partitions.

#### Files Involved
 - `reportgenerator.c`
 - `getpowerprogression.c`
 - `vdwheader.c`
 - `makefile`

#### Executable

`makefile` creates `generateReport.exe`

#### Notes

This `reportgenerator.c` file looks for the 'primesandroots' file that was generated in the previous step. The output from this executable is a file called 'report'. More details about the contents of 'report' can be found in our paper.

## Step 4 - Reading the Report and Identifying Candidates
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
