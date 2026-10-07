class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();


        for (int i=0; i<n; i++) {
            int curr = nums[i];
            int d_sum = 0;

            while (curr > 0) {
                d_sum += curr%10;
                curr /= 10;
            }

            if (d_sum == i) return i;
        }

        return -1;
    }
};