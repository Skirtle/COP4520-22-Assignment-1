#include <iostream>
#include <thread>
#include <pthread.h>
#include <functional>
#include <vector>

bool* sieve(int max);
void workerSieve(bool* prime, int num, int low, int high);

int main() {
    int n = 100000000;
    bool* prime = sieve(n);

    for (int i = 0; i < 8; i++) {
        std::cout << i * n / 8 << "-" << i * n / 8 + (n / 8 - 1) << ", "; 
    }
    std::cout << std::endl;

    unsigned long long sum = 0;
    for (int i = 0; i < n; i++) {
        if (prime[i]) sum += prime[i];
    }
    std::cout << std::endl;

    free(prime);
    return 1;
}

bool* sieve(int max) {
    if (max < 0) return NULL;
    bool* prime = (bool*)malloc(sizeof(bool) * max);
    if (prime == NULL) return NULL;

    for (int i = 0; i < max; i++) {
        prime[i] = true;
    }

    prime[0] = false;
    prime[1] = false;

    // std::thread* workers = (std::thread*)malloc(sizeof(std::thread) * 8);
    std::vector<std::thread*> threadArr;

    int iter = max / 8;
    for (int i = 0; i < max; i++) {
        if (!prime[i]) continue;
        else {
            // workerSieve(prime, i, i, max);
            for (int w = 0; w < 8; w++) {
                // workers[w] = std::thread(workerSieve, prime, i, w * iter, w * iter + (iter - 1));
                std::thread* newThread = new std::thread(workerSieve, prime, i, w * iter, w * iter + (iter - 1));
                threadArr.push_back(newThread);
            }
        }
    }
    
    return prime;
}

void workerSieve(bool* prime, int num, int low, int high) {
    // std::cout << "Thread " << std::this_thread::get_id() << " started\n";
    for (int i = low; i < high; i++) {
        if (i == 0 || i == num) continue;
        if (i % num == 0) {
            prime[i] = false;
        }
    }
}