class Solution {
public:
    // void solve(vector<vector<char>>& grid, int i, int j, int open, bool &ans) {
    //     if (i>=grid.size() && j == grid[0].size()-1) {
    //         if (open == 0) ans = true;

    //         return;  
    //     }

    //     if (i==grid.size()-1 && j >= grid[0].size()) {
    //         if (open == 0) ans = true;

    //         return;  
    //     }

    //     if (i>=grid.size() || j >= grid[0].size()) {
    //         return;
    //     }

    //     if (ans || open < 0) return;

    //     if (grid[i][j] == '(') {
    //         solve(grid, i+1, j, open+1, ans);
    //         solve(grid, i, j+1, open+1, ans);
    //     } else {
    //         solve(grid, i+1, j, open-1, ans);
    //         solve(grid, i, j+1, open-1, ans);
    //     }
    // }

    // bool solve(vector<vector<char>>& grid, int i, int j, int open, vector<vector<vector<int>>> &dp) {
    //     int n = grid.size();
    //     int m = grid[0].size();

    //     if (i >= n || j>=m) return false;

    //     if (grid[i][j] == '(') {
    //         open++;
    //     } else {
    //         open--;
    //     }

    //     if (open < 0) return false;

    //     if (dp[i][j][open] != -1) return dp[i][j][open];

    //     if (i == n-1 && j == m-1) {
    //         return dp[n-1][m-1][open] = (open == 0);
    //     }


    //     return dp[i][j][open] = solve(grid, i+1, j, open, dp) | solve(grid, i, j+1, open, dp);
    // }

    bool hasValidPath(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        if (grid[0][0] == ')' || grid[n-1][m-1] == '(') return false;

        // vector<vector<vector<int>>> dp(n, vector<vector<int>> (m, vector<int> (n*m +1, -1)));

        int maxOpen = n+m-1;

        vector<vector<char>> dp(m, vector<char> (maxOpen+1, false));

        for (int i = n - 1; i >= 0; i--) {

            for (int j = m - 1; j >= 0; j--) {

                // Stores the current cell's states
                vector<char> cur(maxOpen + 1, false);

                for (int open = 0; open <= maxOpen; open++) {

                    int newOpen = open;

                    if (grid[i][j] == '(')
                        newOpen++;
                    else
                        newOpen--;

                    if (newOpen < 0 || newOpen > maxOpen)
                        continue;

                    if (i == n - 1 && j == m - 1) {
                        cur[open] = (newOpen == 0);
                        continue;
                    }

                    bool under = false;
                    bool right = false;

                    // dp[j] is still the PREVIOUS ROW
                    if (i + 1 < n)
                        under = dp[j][newOpen];

                    // dp[j+1] is already the CURRENT ROW
                    if (j + 1 < m)
                        right = dp[j + 1][newOpen];

                    cur[open] = under || right;
                }

                // Now safely replace previous row with current row
                dp[j] = cur;
            }
        }

        return dp[0][0];
    }
};