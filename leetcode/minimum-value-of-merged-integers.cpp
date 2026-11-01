class Solution {
public:
    int minMergedInteger(vector<int>& nums) {
       int n = nums.size();
        int ans = INT_MAX;

        for (int i=1; i<n; i+=2) {
            string num = to_string(nums[i-1]);
            num += to_string(nums[i]);

            ans = min(ans, stoi(num));
        }

        return ans;
    }
};