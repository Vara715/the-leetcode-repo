class Solution {
public:
    // void compareStrings(string &s, string &t, string &ans, int idx, int currSize, int &count) {
    //     if (currSize == t.size()) {
    //         count++;
    //         return;
    //     }

    //     if (idx >= s.size()) {
    //         return;
    //     }

        
    //     for (int i=idx; i<s.size(); i++) {
    //         if (s[i] == t[currSize]) {
    //             ans.push_back(s[i]);
    //             compareStrings(s, t, ans, i+1, currSize+1, count);
    //             ans.pop_back();
    //         }
    //     }
    // }

    // int helper(string &s, string &t, int i, int j, vector<vector<int>> &dp) {
    //     if (j < 0) return 1;
    //     if (i < 0) return 0;

    //     if (dp[i][j] != -1) return dp[i][j];

    //     // int ways = 0;
    //     if (s[i] == t[j]) {
    //         return dp[i][j] = helper(s, t, i-1, j-1, dp) + helper(s, t, i-1, j, dp);
    //     } //hard to understand


    //     return dp[i][j] = helper(s, t, i-1, j, dp);
    // }
    int numDistinct(string s, string t) {
        // string ans = "";
        // int count = 0;
        // compareStrings(s, t, ans, 0, 0, count);

        // return count;
        int n = s.size();
        int m= t.size();

        vector<vector<long long>> dp(n+1, vector<long long> (m+1, 0));
        
        // return helper(s, t, n-1, m-1, dp);
        for (int i = 0; i <= n; i++) dp[i][0] = 1;

        // for (int j = 1; j <= m; j++) dp[0][j] = 0;

        // for (int i=1; i<=n; i++) {
        //     for (int j=1; j<=m; j++) {
        //         if (s[i-1] == t[j-1]) {
        //             dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        //         } else {
        //             dp[i][j] = dp[i-1][j];
        //         }
        //     }
        // }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = min(
                        (long long)INT_MAX,
                        dp[i - 1][j - 1] + dp[i - 1][j]
                    );
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }


        return dp[n][m];
    }
};