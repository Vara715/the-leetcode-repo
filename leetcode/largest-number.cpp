class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> arr;

        for (int num: nums) {
            arr.push_back(to_string(num));
        }

        sort(arr.begin(), arr.end(), [](string &a, string&b) {
            return a+b > b+a;
        });

        string res ="";

        for (string s: arr) {
            res +=s;
        }

        if (res[0] == '0') {
            return "0";
        }

        return res;
    }
};