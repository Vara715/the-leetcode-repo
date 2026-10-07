class Solution {
public:
    int minAddToMakeValid(string s) {
        int count = 0;
        int open = 0;
        int n = s.size();

        for (char ch: s) {
            if (ch == '(') {
                open++;
            } else {
                if (open > 0) {
                    open--;
                    count++;
                }
            }
        }


        return n - 2*count;
    }
};