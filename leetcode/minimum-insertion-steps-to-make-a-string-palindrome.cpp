class Solution {
public:
    int lcs(const string &s, const string &t) {
        int m= t.size();

        //1 . base case
        // vector<vector<int>> dp(n+1, vector<int> (m+1, -1));
        vector<int> prev(m+1, 0);
        vector<int> curr(m+1, 0);

        //2 . assigning base case

        // for (int i=0; i<=n; i++) {
        //     dp[i][0] = 0;
        // }

        // for (int j=0; j<=m; j++) {
        //     dp[0][j] = 0;
        // }

        //3 . opposite order
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=m; j++) {

                //4 . copying recurrence
                if  (s[i-1] == t[j-1]) {
                    curr[j] = 1+prev[j-1];
                } else {
                    curr[j] = max(curr[j-1], prev[j]);
                }
            }

            prev = curr;
        }

        return prev[m];
    }

    int minInsertions(string s) {
        string t = s;
        int n = s.size();
        reverse(t.begin(), t.end());
        return n - lcs(s, t);
    }
};