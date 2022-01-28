# COP4520-22-Assignment-1
Assignment 1 for COP4520-22

## Goal
Find and sum all the primes between 2 and 100,000,000 (10^8) (inclusive)

## Method
Uses the Sieve of Eratosthenes and multi-threading

### Sieve of Eratosthenes
The Sieve of Eratosthenes is an algorithm that finds all the prime numbers up to a certain point. In this case, up to 100,000,000. <br/>
It works by going through the list of numbers, starting at 2, and for each number, marks off each number that is a multiple of it. 
By the end, all numbers not marked off are prime numbers. <br/>
The algorithm can be made more efficient by only checking numbers that are up to the square root of the max number. 

### Implementation
Instead of one thread going from 2 to 10,000 (the square root of 100,000,000), 8 threads are crated, each one going through 1,250 numbers. <br/>
When each thread is created, it is given an ID that can be used to find the range it will be using. <br/>

#### Calculations
Let i be the thread ID, n be the max number, and t the number of threads: <br/>
The starting number is calculated with ![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bi*n%7D%7Bt%7D) <br />
The ending number is calculated with ![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bn(i&plus;1)%7D%7Bt%7D-1) <br/>

