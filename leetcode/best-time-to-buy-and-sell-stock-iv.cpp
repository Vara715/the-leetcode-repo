class Solution {
public:
    int calculate_profit(vector<int>& prices, int buy, int i, int n, vector<vector<vector<int>>> &dp, int times) {
        if (i>=n || times < 0) {
            return 0;
        }

        if (dp[i][buy][times] != -1) {
            return dp[i][buy][times];
        }

        int profit = 0;

        if (buy == 1) {
            profit = max(-prices[i]+calculate_profit(prices, 0, i+1, n, dp, times-1), calculate_profit(prices, 1, i+1, n, dp, times));
        } else {
            profit = max(prices[i]+calculate_profit(prices, 1, i+1, n, dp, times), calculate_profit(prices, 0, i+1, n, dp, times));
        }


        return dp[i][buy][times] = profit;
    }

    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k+1, -1)));
        return calculate_profit(prices, 1, 0, n, dp, k);
    }
};