class Solution {
public:
    bool checkDivisibility(int n) {
        int prod = 1;
        int sum = 0;
        int test = n;

        while (test>0) {
            int d = test%10;
            test/=10;

            sum += d;
            prod *= d;
        }

        int divisor = sum+prod;

        if (n%divisor == 0) {
            return true;
        }

        return false;
    }
};