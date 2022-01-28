#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>


int main() {
	// Constants
	int n, nSqrt;
	n = 1e8;
	nSqrt = ceil(sqrt(n));

	// Prime array, all set to true by default
	bool* primes = (bool*)malloc(sizeof(bool) * n);
	for (int i = 0; i < n; i++) {
		primes[i] = true;
	}
	primes[0] = false; // These two are automatically false
	primes[1] = false;

	// Start timer
	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 2; i <= nSqrt; i++) {
		if (primes[i]) {
			int j = i * i, k = 0;
			while (j < n) {
				primes[j] = false;
				j = (i * i) + (k++ * i);
			}
		}
	}

	// End timer
	auto stop = std::chrono::high_resolution_clock::now();
	float time = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000.0;

	std::cout << "Single threaded took " + std::to_string(time) + " seconds" + "\n";

	// Output to file
	std::string filename = "single.txt";
	std::ofstream file(filename);
	file << time << std::endl;

	free(primes);
	file.close();
	return 0;
}