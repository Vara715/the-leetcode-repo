class Solution {
public:
    void solve(int i, int j, char prev, vector<vector<char>>& grid, vector<int> &ans) {
        if (i >= grid.size() || j >= grid[0].size()) {
            if (prev == 'L') {
                ans.push_back(i);
                ans.push_back(j+1);
            } else if (prev == 'R') {
                ans.push_back(i);
                ans.push_back(j-1);
            } else if (prev == 'U') {
                ans.push_back(i+1);
                ans.push_back(j);
            } else {
                ans.push_back(i-1);
                ans.push_back(j);
            }

            return;
        }

        if (grid[i][j] == 'V') {
            if (prev == 'L') {
                ans.push_back(i);
                ans.push_back(j+1);
            } else if (prev == 'R') {
                ans.push_back(i);
                ans.push_back(j-1);
            } else if (prev == 'U') {
                ans.push_back(i+1);
                ans.push_back(j);
            } else {
                ans.push_back(i-1);
                ans.push_back(j);
            }

            return;
        }

        char tmp = grid[i][j];
        grid[i][j] = 'V';

        if (tmp == 'L') {
            solve(i, j-1, tmp, grid, ans);
        } else if (tmp == 'R') {
            solve(i, j+1, tmp, grid, ans);
        } else if (tmp == 'U') {
            solve(i-1, j, tmp, grid, ans);
        } else {
            solve(i+1, j, tmp, grid, ans);
        }
    }
    vector<int> lastVisitedCell(vector<vector<char>>& grid) {
        vector<int> ans;
        

        solve(0, 0, '1', grid, ans);

        return ans;
    }
};