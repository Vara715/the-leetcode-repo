class Solution {
public:
    string reverseString(string &s, int &i) {
        // if (idx >= s.size()) {
        //     return "";
        // }

        // string tmp = "";
        // for (int i=idx; i<s.size(); i++) {
        //     if (s[i] == '(') {
        //         tmp += reverseString(s, idx+1, curr);
        //         i = curr;
        //     } else if (s[i] == ')') {
        //         reverse(tmp.begin(), tmp.end());
        //         return tmp;
        //     } else {
        //         tmp += s[i];
        //     }

        //     curr++;
        // }

        // return tmp;

        string tmp = "";

        while (i < s.size() && s[i] != ')') {
            if (s[i] == '(') {
                i++;

                string tmp2 = reverseString(s, i);
                reverse(tmp2.begin(), tmp2.end());

                i++;
                tmp += tmp2;
            } else {
                tmp += s[i];
                i++;
            }
        }

        return tmp;
    }
    
    string reverseParentheses(string s) {
        int idx = 0;

        return reverseString(s, idx);
    }
};