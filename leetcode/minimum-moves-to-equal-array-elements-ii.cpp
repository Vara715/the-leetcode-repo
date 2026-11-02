class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        int ops = 0;
        sort(nums.begin(), nums.end());

        for (int i=0; i<n; i++) {
            ops += abs(nums[n/2] - nums[i]);
        }

        return ops;
    }
};