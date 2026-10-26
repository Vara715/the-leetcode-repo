class Solution {
public:
    long long bfs(int i, int j, int n, int m, vector<vector<int>>& grid, vector<vector<bool>> &visited) {
        queue<pair<int, int>> q;
        q.push({i, j});
        visited[i][j] = true;
        long long totalCount = 0;

        vector<int> dirx = {-1, 0, 1, 0};
        vector<int> diry = {0, -1, 0, 1};

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            totalCount += grid[row][col];

            for (int k=0; k<4; k++) {
                int r = row+dirx[k];
                int c = col+diry[k];

                if (r < 0 || r >=n || c<0 || c >= m) continue;

                if (!visited[r][c] && grid[r][c] != 0) {
                    q.push({r, c});
                    visited[r][c] = true;
                }
            }
        }

        return totalCount;
    }
    int countIslands(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool> (m, false));
        int count = 0;

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (grid[i][j] != 0 && !visited[i][j]) {
                    long long totalCount = bfs(i, j, n, m, grid, visited);

                    if (totalCount %k == 0) count++;
                }
            }
        }

        return count;
    }
};