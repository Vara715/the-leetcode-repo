class Solution {
public:
    bool checkValidString(string s) {
        int open = 0;
        int close = 0;

        for (char ch: s) {
            if (ch == '(') {
                open++;
                close++;
            } else if (ch == ')') {
                open--;
                close--;
            } else {
                open--;
                close++;
            }

            if (close<0) return false;

            open = max(open, 0);
        }

        return open == 0;
    }
};