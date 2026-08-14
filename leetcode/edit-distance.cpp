class Solution {
public:
    // int distance(string &word1, string &word2, int i, int j, vector<vector<int>> &dp) {
    //     //base case
    //     if (i<0) return j+1;
    //     if (j<0) return i+1;
    //     if (dp[i][j] != -1) return dp[i][j];

    //     //explore all steps
    //     if (word1[i] == word2[j]) {
    //         return dp[i][j] = distance(word1, word2, i-1, j-1, dp);
    //     }

    //     int insert = 1+ distance(word1, word2, i, j-1, dp);
    //     int remove = 1+ distance(word1, word2, i-1, j, dp);
    //     int replace = 1+ distance(word1, word2, i-1, j-1, dp);

    //     //return the minimum
    //     return dp[i][j] = min(insert, min(remove, replace));
    // }
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n+1, vector<int> (m+1, 0)); //shifting

        //base case
        for (int j=0; j<=m; j++) {
            dp[0][j] = j;
        }

        for (int i=0; i<=n; i++) {
            dp[i][0] = i;
        }

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    int insert = 1+ dp[i][j-1];
                    int remove = 1+ dp[i-1][j];
                    int replace = 1+ dp[i-1][j-1];

                    //return the minimum
                    dp[i][j] = min(insert, min(remove, replace));
                }
            }
        }

        return dp[n][m];
    }
};