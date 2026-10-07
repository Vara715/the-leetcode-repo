class Solution {
public:
    // int solve(int i, string &s) {
    //     if (i+1>=s.size()) return 0;

    //     int score = 0;

    //     if (s[i] == '(') {
    //         score = 2*solve(i+1)
    //     }
    // }
    int scoreOfParentheses(string s) {
        // stack<int> st;
        // int open = 0;

        // for (char ch: s) {
        //     if (ch == '(') {
        //         st.push(open);
        //         open = 0;
        //     } else {
        //         open = max(2*open, 1) + st.top();
        //         st.pop();
        //     }
        // }

        // return open;

        int score = 0;
        int depth = 0;

        for (int i=0; i<s.size(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;

                if (s[i-1] == '(') {
                    score += (1 << depth);
                }
            }
        }

        return score;
    }
};