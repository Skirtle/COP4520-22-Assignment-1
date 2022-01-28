# COP4520-22-Assignment-1
Assignment 1 for COP4520-22 <br/>
Made by Dalton Kajander

## Goal
Find and sum all the primes between 2 and 100,000,000 (10^8, inclusive)

## Method
Sieve of Eratosthenes and multi-threading

### Sieve of Eratosthenes
The Sieve of Eratosthenes is an algorithm that finds all the prime numbers up to a certain point. In this case, up to 100,000,000. <br/>
It works by going through the list of numbers, starting at 2, and for each number, marks off each number that is a multiple of it. 
By the end, all numbers not marked off are prime numbers. <br/>
The algorithm can be made more efficient by only checking numbers that are up to the square root of the max number. This works because because after that point, any possible divisors would of been less than the square root and already checked. If one divisor is already checked, we know the other one. <br/>

### Implementation
Instead of one thread going from 2 to 10,000 (the square root of 100,000,000), 8 threads are crated, each one going through 1,250 numbers. <br/>
When each thread is created, it is given an ID that can be used to find the range it will be using. <br/>

#### Calculations
Let i be the thread ID, n be the max number, and t the number of threads: <br/>
The following images may be hard to see in dark mode <br/>
The starting number is calculated with ![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bi*n%7D%7Bt%7D) <br />
The ending number is calculated with ![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bn(i&plus;1)%7D%7Bt%7D-1) <br/>

### Why It Works
This works without issue because 100,000,000 is a perfect square, and the square root of it is divisible by 8 perfectly. <br/>
This means no threads will share any numbers in a range, and will not have the chance to try to do the same thing as another thread. <br/>
The Sieve of Eratosthenes is a tried-and-trued method of finding primes and is much faster than the naive way of searching (checking if each individual number is prime by checking all possible divisors). 

## How to Use
The file to download is ThreadedPrimes.cpp, which can be found by going into the Assignment folder. <br/>
If you want to compile this yourself: in the directory where ThreadedPrimes.cpp was downloaded, in the command prompt, type and run the following: <br/>
<code>g++ threadedPrimes.cpp -lpthread</code><br/>
<code>./a.out</code> If it creates an exe instead, replace .out with .exe, or run it by double clicking it. <br/>
This will produce a text file named primes.txt with information about the time it took, the amount of primes found, the sum of the primes found, and the 10 largest primes <br/>