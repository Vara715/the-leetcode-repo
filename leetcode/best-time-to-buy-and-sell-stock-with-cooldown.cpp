class Solution {
public:
    int calculate_profit(vector<int>& prices, int buy, int i, int n, vector<vector<int>> &dp) {
        if (i>=n) {
            return 0;
        }

        if (dp[i][buy] != -1) {
            return dp[i][buy];
        }

        int profit = 0;

        if (buy == 1) {
            profit = max(-prices[i]+calculate_profit(prices, 0, i+1, n, dp), calculate_profit(prices, 1, i+1, n, dp));
        } else {
            profit = max(prices[i]+calculate_profit(prices, 1, i+2, n, dp), calculate_profit(prices, 0, i+1, n, dp));
        }


        return dp[i][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int> (2, -1));

        return calculate_profit(prices, 1, 0, n, dp);
    }
};