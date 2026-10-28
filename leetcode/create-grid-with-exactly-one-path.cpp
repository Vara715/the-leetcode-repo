class Solution {
public:
    vector<string> createGrid(int m, int n) {
        vector<string> grid(m);

        string tmp = "";
        for (int i=0; i<n; i++) {
            tmp.push_back('#');
        }

        for (int i=0; i<m; i++) {
            grid[i] =  tmp;
        }

        for (int j=0; j<n; j++) {
            grid[0][j] = '.';
        }

        for (int i=1; i<m; i++) {
            grid[i][n-1] = '.';
        }


        return grid;
    }
};