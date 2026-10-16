class Solution {
public:
    bool threeFibonacciSum(int n) {

        long long prev1 = 0;
        long long prev2 = 1;
        long long curr = 1;

        while (curr < n) {
            long long sum = curr+prev1+prev2;

            if (sum == n) {
                return true;
            }

            prev1 = prev2;
            long long tmp = curr;
            curr = curr+prev2;
            prev2 = tmp;
        }

        return false;
    }
};