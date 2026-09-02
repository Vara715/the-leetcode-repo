class Solution {
public:
    // void helper(int &ans, int ops, int og, long long n) {
    //     if (n==1) {
    //         ans = min(ops, ans);
    //         return;
    //     }

    //     if (n < 1 || n > (long long)og+1) {
    //         return;
    //     }

    //     if (n%2 == 0) {
    //         helper(ans, ops+1, og, n/2);
    //     } else {
    //         helper(ans, ops+1, og, n-1);
    //         helper(ans, ops+1, og, n+1);
    //     }
    // }

    // int helper(long long n, vector<int> &dp) {
    //     if (n==1) return 0;
    //     if (dp[n] != -1) return dp[n];

    //     int even = 0;
    //     int odd = 0;

    //     if (n%2 == 0) {
    //         even = 1+helper(n/2, dp);
    //     } else {
    //         odd = 1+min(helper(n-1, dp), helper(n+1, dp));
    //     }

    //     return dp[n] = even+odd;
    // }
    // int integerReplacement(int n) {
    //     // int ops = INT_MAX;
    //     // helper(ops, 0, n, n);
    //     // return ops;

    //     vector<int> dp(n+2, -1);
    //     // for (int i=n; i>=1; i--) {
    //     //     if (i%2 == 0) {
    //     //         dp[]
    //     //     }
    //     // }

    //     return helper(n, dp);
    // }

    unordered_map<long long, int> dp;

    int helper(long long n) {
        if (n == 1) return 0;

        if (dp.count(n)) return dp[n];

        if (n % 2 == 0) {
            return dp[n] = 1 + helper(n / 2);
        }

        return dp[n] = 1 + min(helper(n - 1), helper(n + 1));
    }

    int integerReplacement(int n) {
        return helper((long long)n);
    }
};