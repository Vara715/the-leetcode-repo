class Solution {
public:
    int LIS(vector<int> &nums, int i, int prev, vector<vector<int>> &dp) {
        if (i < 0) {
            return 0;
        }

        if (dp[i][prev+1] != -1) {
            return dp[i][prev+1];
        }

        //take
        int take = 0;
        if (prev == -1 || nums[i] < nums[prev]) {
            take = 1+LIS(nums, i-1, i, dp);
        }

        int notTake = LIS(nums, i-1, prev, dp);

        return dp[i][prev+1] = max(take, notTake);
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
        // int ans = LIS(nums, n-1, -1, dp);

        // return ans;


        for (int i=1; i<=n; i++) {
            for (int prev=0; prev<=n; prev++) {

                int take = 0;
                if (prev == 0 || nums[i-1] < nums[prev-1]) {
                    take = 1+dp[i-1][i];
                }

                int notTake = dp[i-1][prev];

                dp[i][prev] = max(take, notTake);
            }
        }

        return dp[n][0];
    }
};