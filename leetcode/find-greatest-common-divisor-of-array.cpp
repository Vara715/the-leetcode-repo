class Solution {
public:
    int findGCD(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int small = nums[0];
        int big = nums[n-1];

        while (small != 0) {
            int tmp = small;
            small = big%small;
            big = tmp;
        }

        return big;
    }
};