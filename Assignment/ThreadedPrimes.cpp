#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>
#include <cmath>

int main() {
	int n;
	n = 1e8;
	bool* primes = (bool*)malloc(sizeof(bool) * n);
	for (int i = 0; i < n; i++) {
		primes[i] = true;
	}

	for (int i = 2; i <= sqrt(n); i++) {
		if (primes[i]) {
			int j = i * i, k = 0;
			while (j < n) {
				primes[j] = false;
				j = (i * i) + (k++ * i);
			}
		}
	}

	std::cout << "Sieve done" << std::endl;

	unsigned long long sum = 0;
	for (int i = 2; i < n; i++) {
		if (primes[i]) {
			sum += i;
		}
	}
	std::cout << sum << std::endl;

	free(primes);
	return 0;
}