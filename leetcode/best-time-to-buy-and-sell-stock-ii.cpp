// You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

// On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can sell and buy the stock multiple times on the same day, ensuring you never hold more than one share of the stock.

// Find and return the maximum profit you can achieve.

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
            profit = max(prices[i]+calculate_profit(prices, 1, i+1, n, dp), calculate_profit(prices, 0, i+1, n, dp));
        }


        return dp[i][buy] = profit;
    }
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+1, vector<int> (2, 0));
        int buy = 1;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                int profit = 0;

                if (buy == 1) {
                    profit = max(-prices[i]+dp[i+1][0], dp[i+1][1]);
                } else {
                    profit = max(prices[i]+dp[i+1][1], dp[i+1][0]);
                }


                dp[i][buy] = profit;
            } 
        }
        // return calculate_profit(prices, 1, 0, n, dp);
        return dp[0][1];
    }
};