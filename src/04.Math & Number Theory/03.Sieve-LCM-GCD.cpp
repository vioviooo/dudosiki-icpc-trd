const int MAX_N = 1e6 + 5;
vector<bool> isPrime(MAX_N, true);
vector<int> primes;

void sieve() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i < MAX_N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < MAX_N; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (int i = 2; i < MAX_N; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
}

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

// Prime factorization using sieve
vector<pair<int, int>> prime_factors(int n) {
    vector<pair<int, int>> factors;
    for (int p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            int count = 0;
            while (n % p == 0) {
                n /= p;
                count++;
            }
            factors.push_back({p, count});
        }
    }
    if (n > 1) {
        factors.push_back({n, 1});
    }
    return factors;
}

int main() {
    sieve(); // Precompute primes
    
    // GCD examples
    cout << "GCD(56, 98) = " << gcd(56, 98) << endl;
    cout << "GCD(17, 13) = " << gcd(17, 13) << endl;
    
    // LCM examples
    cout << "LCM(12, 18) = " << lcm(12, 18) << endl;
    cout << "LCM(7, 5) = " << lcm(7, 5) << endl;
    
    // Prime check examples
    cout << "Is 17 prime? " << isPrime[17] << endl;
    cout << "Is 100 prime? " << isPrime[100] << endl;
    
    // Prime factorization
    auto factors = prime_factors(360);
    cout << "Prime factors of 360: ";
    for (auto [p, exp] : factors) {
        cout << p << "^" << exp << " ";
    }
    cout << endl;
    
    return 0;
}