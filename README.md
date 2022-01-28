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
On creation, each thread is given an ID, from 0 to 7. <br/>
Each thread will use it's ID as the starting number for their part of the sieve. Instead of the thread going up by one, it goes up by 8, because the other threads dealt with the ones between. For instance, the thread with ID 0 starts at 0, then 8 because thread 1 started with 1, thread 2 started on 2, and so on. <br/>


### Why It Works
This works without issue because 100,000,000 is a perfect square, and the square root of it is divisible by 8 perfectly. <br/>
This means no threads will share any numbers in a range, and will not have the chance to try to do the same thing as another thread. <br/>
The Sieve of Eratosthenes is a tried-and-trued method of finding primes and is much faster than the naive way of searching (checking if each individual number is prime by checking all possible divisors). 

## How to Use
The file to download is ThreadedPrimes.cpp, which can be found by going into the Assignment folder. <br/>
If you want to compile this yourself: in the directory where ThreadedPrimes.cpp was downloaded, in the command prompt, type and run the following: <br/>
<code>g++ threadedPrimes.cpp -lpthread</code><br/>
<code>./a.out</code> If it creates an exe instead, replace .out with .exe, or run it by double clicking it. <br/>
If you are unable to compile it yourself, you may instead just download the output file and run it. If you download a.out, run the last command above. If you download a.exe, you may simply double click the file to run it. <br/>
Running the file will produce a text file named primes.txt with information about the time it took, the amount of primes found, the sum of the primes found, and the 10 largest primes <br/>


# Testing and Evaluation
## Single-threaded
In this test, there was only one thread doing everything, the main running thread. No multi-threading was used, but the same algorithm was used. <br/>
In the single-threaded version, it took an average of 1.6534 seconds to sieve through 100,000,000. <br/>
## Partioned multi-threaded
Partioned multi-threading was when each thread would get a chunk of the primes array and sieve with those numbers. Thread 0 would go from 0 to 1249, thread 1 would use 1250 to 2499, and so on. <br/>
The partitioned multi-threaded version took, on average, 1.1904 seconds for the same test. <br/>
This was the first approach taken, but decided otherwise, explained in alternating multi-threaded
## Alternating multi-threaded
Alternating multi-threaded is when the threads alternate between numbers. Thread 0 would use numbers 0, 8, 16, and so on. Thread 1 would use 1, 9, 15, and so on. Each thread starts at it's ID and adds 8 everytime. <br/>
The alternating multi-threaded version took, on average, 0.5394 for the same test. <br/>
The reason this runs better than partioned is because of thread 0. In partioned, thread 0 had all of the smallest numbers which would go into the most amount of numbers. Because of that, it had the most amount of computations to do and took a considerable amount of time. <br/>
Alternating works because all of the threads use small numbers at the same time, and each thread speeds up at the same rate and roughly the same time. <br/>
## Visualization of these approaches
![equation](https://imgur.com/a/NggxfxY)