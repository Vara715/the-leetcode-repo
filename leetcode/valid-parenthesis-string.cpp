class Solution {
public:
    // bool helper(string &s, stack<char> &st, int idx, unordered_map<char, char> &mp) {
    //     if (idx >= s.size() && st.empty()) {
    //         return true;
    //     }

    //     if (!st.empty() && idx >= s.size()) return false;
    //     if (st.empty() && idx < s.size()) return false;

    //     for (int i=idx; i<s.size(); i++) {
    //         if (s[i] != '*' && st.top() == mp[s[i]]) {
    //             st.pop();
    //             continue;
    //         } else if (s[i] != '*' && st.top() != '*') {
    //             return false;
    //         }

    //         //empty + either '(' or ')'
    //         if (st.top() == '*') {
    //             st.pop();
    //             return helper(s, st, i, mp) | helper(s, st, i+1, mp);
    //         }

    //         if (s[i] == '*') {
    //             char star = st.top();
    //             //not empty
    //             st.pop();
    //             bool value = helper(s, st, i+1, mp);

    //             //empty;
    //             st.push(star);
    //             return value | helper(s, st, i+1, mp);
    //         }
    //     }

    //     return true;
    // }
    bool checkValidString(string s) {
        // int n = s.size();
        // stack<char> st;
        // unordered_map<char, char> mp = {
        //     {'(', ')'},
        //     {')', '('}
        // };

        // for (int i=0; i<n/2; i++) {
        //     st.push(s[i]);
        // }

        // return helper(s, st, n/2, mp);

        int left = 0;
        int right = 0;
        for (char ch: s) {
            if (ch == '(') {
                left++;
                right++;
            } else if (ch == ')') {
                left--;
                right--;
            } else {
                left--;
                right++;
            }

            if (right < 0) return false;

            left = max(left, 0);
        }

        return left == 0;
    }
};