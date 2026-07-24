// You are given an array prices where prices[i] is the price of a given stock on the ith day.

// Find the maximum profit you can achieve. You may complete at most two transactions.

// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

class Solution {
public:
    int calculate_profit(vector<int>& prices, int buy, int i, int n, vector<vector<vector<int>>> &dp, int times) {
        if (i>=n || times > 2) {
            return 0;
        }

        if (dp[i][buy][times] != -1) {
            return dp[i][buy][times];
        }

        int profit = 0;

        if (buy == 1) {
            profit = max(-prices[i]+calculate_profit(prices, 0, i+1, n, dp, times+1), calculate_profit(prices, 1, i+1, n, dp, times));
        } else {
            profit = max(prices[i]+calculate_profit(prices, 1, i+1, n, dp, times), calculate_profit(prices, 0, i+1, n, dp, times));
        }


        return dp[i][buy][times] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3, -1)));
        return calculate_profit(prices, 1, 0, n, dp, 0);
    }
};