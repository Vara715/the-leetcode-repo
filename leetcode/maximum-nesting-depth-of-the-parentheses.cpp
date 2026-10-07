class Solution {
public:
    int maxDepth(string s) {
        int count = 0;
        int open = 0;

        for (char ch: s) {
            if (ch == '(') {
                open++;
            } else if (ch == ')') {
                open--;
            }

            count = max(count, open);
        }


        return count;
    }
};