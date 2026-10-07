class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9];
        bool cols[9][9];
        bool boxes[9][9];

        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                if (board[i][j] != '.') {
                    int idx = board[i][j] - '1';
                    int boxIdx = (i/3)*3 + (j/3);

                    if (rows[i][idx] || cols[j][idx] || boxes[boxIdx][idx]) return false;

                    rows[i][idx] = cols[j][idx] = boxes[boxIdx][idx] = true;
                }
            }
        }

        return true;
    }
};