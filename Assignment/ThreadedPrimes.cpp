#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>
#include <cmath>
#include <chrono>

int main() {
	// Amount of numbers to go through
	int n;
	n = 1e8;

	// Prime array, all set to true by default
	bool* primes = (bool*)malloc(sizeof(bool) * n);
	for (int i = 0; i < n; i++) {
		primes[i] = true;
	}

	// Start timer
	auto start = std::chrono::high_resolution_clock::now();

	// Sieve through
	for (int i = 2; i <= sqrt(n); i++) {
		if (primes[i]) {
			int j = i * i, k = 0;
			while (j < n) {
				primes[j] = false;
				j = (i * i) + (k++ * i);
			}
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	float time = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000.0;

	// Sum all primes
	unsigned long long sum = 0;
	int numPrimes = 0;
	for (int i = 2; i < n; i++) {
		if (primes[i]) {
			sum += i;
			numPrimes++;
		}
	}
	std::cout << time << " " << numPrimes << " " << sum << std::endl;

	// Free and end
	free(primes);
	return 0;
}