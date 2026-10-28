class Solution {
public:
    // void dfs(int i, int j, int n, int m, int curr, int &ans, vector<vector<int>>& grid) {

    //     //base
    //     if (i==n-1 && j==m-1) {
    //         curr ^= grid[i][j];
    //         ans = min(ans, curr);
    //         return;
    //     }

    //     if (i>=n || j>=m) return;

    //     curr ^= grid[i][j];

    //     //right
    //     dfs(i, j+1, n, m, curr, ans, grid);

    //     //down
    //     dfs(i+1, j, n, m, curr, ans, grid);
    // }
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int ans = INT_MAX;
        // dfs(0, 0, n, m, 0, ans, grid);

        int max_xor = 1024;
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>> (m, vector<bool> (max_xor, false)));

        queue<tuple<int, int, int>> q;
        int start = grid[0][0];
        q.push({0, 0, start});
        visited[0][0][start] = true;

        while (!q.empty()) {
            auto [r, c, curr_xor] = q.front();
            q.pop();

            if (r == n-1 && c == m-1) {
                ans = min(ans, curr_xor);
                continue;
            }
            
            //down
            if (r+1 < n) {
                int next_xor = curr_xor^grid[r+1][c];
                if (!visited[r+1][c][next_xor]) {
                    visited[r+1][c][next_xor] = true;
                    q.push({r+1, c, next_xor});
                }
            }

            //right
            if (c+1 < m) {
                int next_xor = curr_xor^grid[r][c+1];
                if (!visited[r][c+1][next_xor]) {
                    visited[r][c+1][next_xor] = true;
                    q.push({r, c+1, next_xor});
                }
            }
        }
        return ans;
    }
};