class Combinatorics {
private:
    vector<long long> fact, inv_fact;
    long long mod;
    
    // Modular exponentiation
    long long power(long long a, long long b) {
        long long result = 1;
        while (b > 0) {
            if (b & 1) {
                result = (result * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        return result;
    }
    
public:
    Combinatorics(int max_n, long long m) {
        mod = m;
        fact.resize(max_n + 1);
        inv_fact.resize(max_n + 1);
        precompute();
    }
    
    // Precompute factorials and inverse factorials
    void precompute() {
        fact[0] = 1;
        for (int i = 1; i < fact.size(); i++) {
            fact[i] = (fact[i-1] * i) % mod;
        }
        
        // Fermat's Little Theorem for inverse factorials
        int n = fact.size() - 1;
        inv_fact[n] = power(fact[n], mod - 2);
        for (int i = n-1; i >= 0; i--) {
            inv_fact[i] = (inv_fact[i+1] * (i+1)) % mod;
        }
    }
    
    // nCr modulo mod
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        
        long long numerator = fact[n];
        long long denominator = (inv_fact[r] * inv_fact[n-r]) % mod;
        return (numerator * denominator) % mod;
    }
    
    // nPr modulo mod
    long long nPr(int n, int r) {
        if (r < 0 || r > n) return 0;
        long long numerator = fact[n];
        long long denominator = inv_fact[n-r];
        return (numerator * denominator) % mod;
    }
    
    // Factorial modulo mod
    long long factorial(int n) {
        return fact[n];
    }
    
    // Inverse factorial modulo mod
    long long inverse_factorial(int n) {
        return inv_fact[n];
    }
    
    // Catalan number modulo mod
    long long catalan(int n) {
        if (n == 0) return 1;
        long long num = nCr(2*n, n);
        long long den = n + 1;
        return (num * power(den, mod - 2)) % mod;
    }
    
    // Stars and bars: number of non-negative integer solutions to x1 + x2 + ... + xk = n
    long long stars_and_bars(int n, int k) {
        return nCr(n + k - 1, k - 1);
    }
    
    // Stars and bars with positive integers (each xi >= 1)
    long long stars_and_bars_positive(int n, int k) {
        if (n < k) return 0;
        return nCr(n - 1, k - 1);
    }
};

// Alternative implementation for when precomputation is not possible
class CombinatoricsNoPrecompute {
private:
    long long mod;
    
    long long power(long long a, long long b) {
        long long result = 1;
        while (b > 0) {
            if (b & 1) {
                result = (result * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        return result;
    }
    
public:
    CombinatoricsNoPrecompute(long long m) {
        mod = m;
    }
    
    // nCr without precomputation (slower but useful when n is large)
    long long nCr(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        if (r == 0) return 1;
        if (r > n - r) r = n - r;
        
        long long result = 1;
        for (long long i = 1; i <= r; i++) {
            result = (result * (n - i + 1)) % mod;
            result = (result * power(i, mod - 2)) % mod;
        }
        return result;
    }
    
    // Lucas Theorem for nCr % mod when mod is prime and n, r are large
    long long nCr_lucas(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        if (r == 0) return 1;
        
        return (nCr_lucas(n / mod, r / mod) * nCr(n % mod, r % mod)) % mod;
    }
};

int main() {
    const int MOD = 1e9 + 7;
    const int MAX_N = 1000000;
    Combinatorics comb(MAX_N, MOD);
    cout << "10C5 = " << comb.nCr(10, 5) << endl;           // 252
    cout << "10P5 = " << comb.nPr(10, 5) << endl;           // 30240
    cout << "5! = " << comb.factorial(5) << endl;           // 120
    cout << "Catalan(4) = " << comb.catalan(4) << endl;     // 14
    
    cout << "Ways to distribute 10 identical items to 3 people: " 
         << comb.stars_and_bars(10, 3) << endl;             // 66
    
    cout << "Ways to distribute 10 identical items to 3 people (each gets at least 1): " 
         << comb.stars_and_bars_positive(10, 3) << endl;    // 36
    
    CombinatoricsNoPrecompute comb2(MOD);
    cout << "100C50 (no precompute) = " << comb2.nCr(100, 50) << endl;
    
    return 0;
}