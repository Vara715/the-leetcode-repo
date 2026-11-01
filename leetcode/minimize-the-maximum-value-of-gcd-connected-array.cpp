class Solution {
public:
    int smallest_prime(int num) {
        for (int i=2; 1LL*i*i <= num; i++) {
            if (num%i == 0) {
                return i;
            }
        }

        return num;
    }
    
    long long minimumMaxValue(int n, int index, int value) {
        if (value == 1) return -1;

        int f = smallest_prime(value);

        //prefix
        long long prefixMax =0;

        if (value%2 == 0) {
            prefixMax = value/2 -1;
        } else if (f == value) { //prime
            prefixMax = 0;
        } else {
            prefixMax = (value -f)/2;  //not prime
        }

        if (index > prefixMax) return -1;

        long long suffix = n-1LL-index;

        if (suffix == 0) {
            return value;
        }

        if (value %2 == 0) {
            return value + 2*suffix;
        }

        if (f == value) {
            return 2LL*value + 2*(suffix-1);
        }

        return value +f + 2*(suffix-1);
    }
};