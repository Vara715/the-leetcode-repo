class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        int n = s.size();
        int m = knowledge.size();

        unordered_map<string, string> mp;
        for (int i=0; i<m; i++) {
            mp[knowledge[i][0]] = knowledge[i][1];
        }

        string ans = "";
        bool bOpen = false;
        bool bClose = true;

        string tmp = "";

        for (int i=0; i<n; i++) {
            if (s[i] == '(') {
                i++;
                while (s[i] != ')') {
                    tmp.push_back(s[i++]);
                }

                if (mp.find(tmp) != mp.end()) {
                    ans += mp[tmp];
                } else {
                    ans += '?';
                }


                tmp = "";
            } else {
                ans += s[i];
            }
        }

        return ans;
    }
};