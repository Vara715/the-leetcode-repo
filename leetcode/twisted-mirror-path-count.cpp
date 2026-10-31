class Solution {
public:
    const int MOD = 1000000007;

    bool step(int i, int j, int dir, int m, int n, const vector<vector<int>>& grid, int &next_i, int &next_j) {
        int r = i, c = j;
        int d = dir;

        while (true) {
            if (d == 1) {
                c++;
            } else {
                r++;
            }

            if (r >= m || c >= n) return false;

            if (grid[r][c] == 0) {
                next_i = r;
                next_j = c;
                return true;
            }

            if (d == 1) {
                d = 0;
            } else {
                d = 1;
            }
        }
    }

    int dfs(int i, int j, int m, int n, vector<vector<int>>& dp, const vector<vector<int>>& grid) {
        if (i == m - 1 && j == n - 1) return 1;
        if (dp[i][j] != -1) return dp[i][j];

        long long paths = 0;
        int next_i, next_j;

        if (step(i, j, 1, m, n, grid, next_i, next_j)) {
            paths = (paths + dfs(next_i, next_j, m, n, dp, grid)) % MOD;
        }

        if (step(i, j, 0, m, n, grid, next_i, next_j)) {
            paths = (paths + dfs(next_i, next_j, m, n, dp, grid)) % MOD;
        }

        return dp[i][j] = paths;
    }

    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        if (grid[0][0] == 1) return 0;
        if (m == 1 && n == 1) return 1;

        vector<vector<int>> dp(m, vector<int>(n, -1));
        return dfs(0, 0, m, n, dp, grid);
    }
};