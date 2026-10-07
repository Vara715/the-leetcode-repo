class Solution {
public:
    void generate(int n, int open, int close, vector<string> &ans, string &curr) {
        if (open >=n && close >=n) {
            ans.push_back(curr);
            return;
        }

        if (open < n) {
            curr.push_back('(');
            open++;
            generate(n, open, close, ans, curr);

            open--;
            curr.pop_back();
        }

        if (close < n && open > close) {
            curr.push_back(')');
            close++;
            generate(n, open, close, ans, curr);

            close--;
            curr.pop_back();
        }

    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        string curr = "";

        generate(n, 0, 0, ans, curr);

        return ans;
    }
};