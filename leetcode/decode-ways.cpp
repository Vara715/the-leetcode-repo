class Solution {
public:
    // void ways(string &s, int i, int &ans) {
    //     if (i >= s.size()) {
    //         ans++;
    //         return;
    //     }

    //     if (s[i] == '0') return;

    //     ways(s, i+1, ans);

    //     if (s[i] != '0' && i+1 < s.size() && stoi(s.substr(i, 2)) <= 26) {
    //         ways(s, i+2, ans);
    //     }

    //     return;
    // }

    // int ways(string &s, int i, vector<int> &dp) {
    //     if (i >= s.size()) {
    //         return 1;
    //     }

    //     if (dp[i] != -1) {
    //         return dp[i];
    //     }

    //     if (s[i] == '0') return dp[i] = 0;

    //     int oneTake = ways(s, i+1, dp);
    //     int twoTake = 0;

    //     if (i+1 < s.size() && stoi(s.substr(i, 2)) <= 26) {
    //         twoTake = ways(s, i+2, dp);
    //     }

    //     return dp[i] = oneTake + twoTake;
    // }
    int numDecodings(string s) {
        int n = s.size();
        if (n==0) return 0;
        vector<int> dp(n+1, 0);
        
        // return ways(s, 0, dp);

        dp[n] = 1;
        for (int i=n-1; i>=0; i--) {
            if (s[i] == '0') continue;
            
            int oneTake = dp[i+1];
            int twoTake = 0;

            if (i+1 < n && stoi(s.substr(i, 2)) <= 26) {
                twoTake = dp[i+2];
            }

            dp[i] = oneTake + twoTake;
        }

        return dp[0];
    }
};