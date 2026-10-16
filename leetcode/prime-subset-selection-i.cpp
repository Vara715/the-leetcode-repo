class Solution {
public:
    vector<int> maxPrimes(int n, int s) {
        if (n<2) return {};
        
        vector<bool> isPrime(n+1, true);
        isPrime[0] = isPrime[1] = false;

        for (int i=2; i<=sqrt(n); i++) {
            if (isPrime[i]) {
                for (int j=i*i; j<=n; j+=i) {
                    isPrime[j] = false;
                }
            }
        }

        long long sum = 0;
        vector<int> primes;
        for (int i=2; i<=n; i++) {
            if (isPrime[i] && sum+i <= s) {
                sum += i;
                primes.push_back(i);
            }
        }

        return primes;
    }
};