class Solution {
public:
    bool bfs(int i, int j, int n, int m, vector<vector<int>>& grid, vector<vector<bool>>& visit) {
        queue<pair<int, int>> q;
        q.push({i, j});
        visit[i][j] = true;
        bool isClosed = true;

        vector<int> dirx{0, 1, 0, -1};
        vector<int> diry{-1, 0, 1, 0};

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for (int i=0; i<4; i++) {
                int r = row+dirx[i];
                int c = col+diry[i];

                if (r < 0 || r>=n || c<0 || c>=m) {
                    isClosed = false;
                } else if (grid[r][c] == 0 && !visit[r][c]) {
                    q.push({r, c});
                    visit[r][c] = true;
                }
            }
        }

        return isClosed;
    }
    int closedIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int count = 0;

        vector<vector<bool>> visit(n, vector<bool> (m, false));

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (grid[i][j] == 0 && !visit[i][j] && bfs(i, j, n, m, grid, visit)) {
                    count++;
                }
            }
        }

        return count;
    }
};