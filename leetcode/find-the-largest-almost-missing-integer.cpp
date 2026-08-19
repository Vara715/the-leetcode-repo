class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        if (n==k) {
            int ans = -1;
            for (int val: nums) {
                ans = max(ans, val);
            }

            return ans;
        }

        unordered_map<int, int> mp;
        for (int val: nums) {
            mp[val]++;
        }

        if (k == 1) {
            int ans = -1;
            for (int val: nums) {
                if (mp[val] == 1) {
                    ans = max(ans, val);
                }
            }

            return ans;
        }

        int first = mp[nums[0]] == 1? nums[0]: -1;
        int last = mp[nums[n-1]] == 1? nums[n-1]: -1;

        return max(first, last);
    }
};