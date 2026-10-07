class Solution {
public:
    bool isValid(string s) {
        int n = s.size();
        if (n%2 != 0) return false;

        stack<char> st;

        unordered_map<char, char> mp = {{')', '('}, {']', '['}, {'}', '{'}};

        for (int i=0; i<n; i++) {
            if (mp.find(s[i]) == mp.end()) {
                st.push(s[i]);
            } else if (!st.empty() && mp[s[i]] == st.top()) {
                st.pop();
            } else {
                return false;
            }
        }
        return st.empty();
    }
};