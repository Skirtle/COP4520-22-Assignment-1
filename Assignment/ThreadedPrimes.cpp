#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>

// Constants
int n = 1e8;
int nSqrt = ceil(sqrt(n));
int threadCount = 8;

void worker(int tid, bool* primes);

int main() {
	// Prime array, all set to true by default
	bool* primes = (bool*)malloc(sizeof(bool) * n);
	for (int i = 0; i < n; i++) {
		primes[i] = true;
	}
	primes[0] = false; // These two are automatically false
	primes[1] = false;

	// Start timer
	auto start = std::chrono::high_resolution_clock::now();

	// Create threads
	std::thread threads[threadCount];
	for (int i = 0; i < threadCount; i++) {
		threads[i] = std::thread(worker, i, primes);
	}
	
	// Join threads
	for (int i = 0; i < threadCount; i++) {
		threads[i].join();
	}

	// End timer
	auto stop = std::chrono::high_resolution_clock::now();
	float time = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000.0;

	// Sum primes and amount of primes
	unsigned long long sum = 0;
	int numPrimes = 0;
	for (int i = 2; i < n; i++) {
		if (primes[i]) {
			sum += i;
			numPrimes++;
		}
	}

	// Find 10 largest primes and order them
	int largestPrimes[10];
	int j = 9;
	for (int i = n - 1; j >= 0; i--) {
		if (primes[i]) {
			largestPrimes[j] = i;
			j--;
		}
	}

	// Output to file
	std::string filename = "primes.txt";
	std::ofstream file(filename);
	file << time << " " << numPrimes << " " << sum << std::endl;
	for (int i = 0; i < 10; i++) {
		file << largestPrimes[i] << " ";
	}
	file << "\n";


	// Free, close, and end
	free(primes);
	file.close();
	return 0;
}

void worker(int tid, bool* primes) {
	// Calculate range
	int start, stop;
	start = tid * (nSqrt / threadCount);
	stop = ((nSqrt * (tid + 1)) / threadCount) - 1;

	// Sieve in the given range
	for (int i = start; i <= stop; i++) {
		if (primes[i]) {
			int j = i * i, k = 0;
			while (j < n) {
				primes[j] = false;
				j = (i * i) + (k++ * i);
			}
		}
	}
}