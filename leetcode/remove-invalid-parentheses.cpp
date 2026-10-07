class Solution {
public:
    void solve(int i, int leftRemove, int rightRemove, int balance, string &curr, string &s, unordered_set<string> &st) {
        

        //base

        if (leftRemove + rightRemove > s.size() - i) return;

        if (i == s.size()) {
            if (leftRemove == 0 && rightRemove == 0 && balance == 0) {
                st.insert(curr);
            }

            return;
        }


        if (s[i] == '(') {
            if (leftRemove > 0) {
                solve(i+1, leftRemove-1, rightRemove, balance, curr, s, st);
            }

            curr+=s[i];
            solve(i+1, leftRemove, rightRemove, balance+1, curr, s, st);
            curr.pop_back();
        } 
        else if (s[i] == ')') {
            if (rightRemove > 0) {
                solve(i+1, leftRemove, rightRemove-1, balance, curr, s, st);
            }

            if (balance > 0) {
                curr += s[i];
                solve(i+1, leftRemove, rightRemove, balance-1, curr, s, st);
                curr.pop_back();
            }
        }
        else {
            curr += s[i];
            solve(i+1, leftRemove, rightRemove, balance, curr, s, st);
            curr.pop_back();
        }
    }


    vector<string> removeInvalidParentheses(string s) {
        int leftRemove = 0, rightRemove = 0;

        for (char ch: s) {
            if (ch == '(') {
                leftRemove++;
            } else if (ch == ')') {
                if (leftRemove > 0) {
                    leftRemove--;
                } else {
                    rightRemove++;
                }
            }
        }

        vector<string> ans;
        unordered_set<string> st;
        string curr = "";
        solve(0, leftRemove, rightRemove, 0, curr, s, st);


        for (auto &str: st) {
            ans.push_back(str);
        }


        return ans;
    }
};