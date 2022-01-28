# COP4520-22-Assignment-1
Assignment 1 for COP4520-22

## Goal
Find and sum all the primes between 1 and 100,000,000 (10^8)

## Method
Uses the Sieve of Eratosthenes and multi-threading
Each thread will be given an ID (from 0 to 7), and with that ID, it will calculate the range of numbers it will sieve through <br />
Let i be the thread ID, n be the max number, and t the number of threads: <br />
The starting number is calculated with ID \* (max number / thread count) ![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bi*n%7D%7Bt%7D) <br />
The ending number is calculated with max number \* ((ID + 1) / thread count) - 1 <br />

## Test
![equation](https://latex.codecogs.com/svg.image?%5Cfrac%7Bi*n%7D%7Bt%7D)
