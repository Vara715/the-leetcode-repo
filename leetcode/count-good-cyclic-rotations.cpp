class Solution {
public:
    int countGoodRotations(vector<int>& nums) {
        int n = nums.size();
        int half = n/2;

        long long totalSum = 0, firstSum = 0;

        for (int i=0; i<n; i++) {
            totalSum += nums[i];

            if (i < half) {
                firstSum += nums[i];
            }
        }

        int count = 0;
        for (int i=0; i<n; i++) {
            long long secondSum = totalSum - firstSum;

            if (firstSum > secondSum) count++;

            firstSum -= nums[i];
            firstSum += nums[(i+half)%n];
        }

        return count;
    }
};