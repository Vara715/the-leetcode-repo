class Solution {
public:
    // bool patternMatching(string &s, string &p, int i, int j, vector<vector<int>> &dp) {
    //     //base case
    //     if (j<0) {
    //         if (i<0) {
    //             return true;
    //         } else {
    //             return false;
    //         }
    //     }

    //     if (i<0) {
    //         for (int idx=0; idx <= j; idx++) {
    //             if (p[idx] != '*') return false;
    //         }

    //         return true;
    //     }

    //     if (dp[i][j] != -1) return dp[i][j];

    //     //other cases
    //     if (p[j] == '*') {
    //         // bool ans = false;

    //         // for (int idx = i; idx>=0; idx--) {
    //         //     ans = ans | patternMatching(s, p, idx, j-1);

    //         //     if (ans) {
    //         //         return true;
    //         //     }
    //         // }

    //         return dp[i][j] = patternMatching(s, p, i, j-1, dp) | patternMatching(s, p, i-1, j, dp);
    //     }

    //     //explore all possibilities
    //     if (s[i] == p[j] || p[j] == '?') {
    //         return dp[i][j] = patternMatching(s, p, i-1, j-1, dp);
    //     }

    //     // bool ans = patternMatching(s, p, i, j-1);

    //     return dp[i][j] = false;
    // }
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

        //base cases
        dp[0][0] = 1;

        for (int j=1; j<=m; j++) {
            if (p[j-1] == '*') {
                dp[0][j] = dp[0][j-1];
            }
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (s[i-1] == p[j-1] || p[j-1] == '?') {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] == '*') {
                    dp[i][j] = dp[i-1][j] | dp[i][j-1];
                }
            }
        }


        // return patternMatching(s, p, n-1, m-1, dp);
        return dp[n][m];
    }
};