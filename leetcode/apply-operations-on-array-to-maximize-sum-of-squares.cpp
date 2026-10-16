class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1'000'000'007;

        vector<int> bitCount(31, 0);
        for (int x: nums) {
            for (int i=0; i<30; i++) {
                if ((x>>i)&1) {
                    bitCount[i]++;
                }
            }
        }


        long long totalSum = 0;
        for (int i=0; i<k; i++) {
            long long val = 0;
            for (int i=0; i<30; i++) {
                if (bitCount[i] > 0) {
                    val |= (1LL << i);
                    bitCount[i]--;
                }
            }

            totalSum = (totalSum + (val%MOD)*(val%MOD))%MOD;
        }

        return totalSum;

    }
};