#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>
#include <cmath>
#include <chrono>

bool locked = true;
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
	primes[0] = false;
	primes[1] = false;

	// Create threads
	std::thread threads[threadCount];
	for (int i = 0; i < threadCount; i++) {
		threads[i] = std::thread(worker, i, primes);
	}

	locked = false;
	
	for (int i = 0; i < threadCount; i++) {
		threads[i].join();
	}

	std::cout << "Threads done\n";

	// Start timer
	auto start = std::chrono::high_resolution_clock::now();
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

	// Output
	std::cout << time << " " << numPrimes << " " << sum << std::endl;

	// Free and end
	free(primes);
	return 0;
}

void worker(int tid, bool* primes) {
	while (locked) {
		continue;
	}
	int start, stop;
	start = tid * (nSqrt / threadCount);
	stop = ((nSqrt * (tid + 1)) / threadCount) - 1;
	std::cout << "Unlocked thread " + std::to_string(tid)+ " with a range of " + std::to_string(start) + " to " + std::to_string(stop) + "\n";

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