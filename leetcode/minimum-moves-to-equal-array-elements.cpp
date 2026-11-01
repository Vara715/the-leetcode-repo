class Solution {
public:
    int minMoves(vector<int>& nums) {
        int moves = 0;
        int small = INT_MAX;

        for (int x: nums) {
            small = min(small, x);
        }

        for (int x: nums) {
            moves += (x - small);
        }

        return moves;
    }
};