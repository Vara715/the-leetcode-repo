class Solution {
public:
    bool divides(string &a, string &b) {
        int n= b.size();
        for (int i=0; i<a.size(); i+=n) {
            if (a.substr(i, n) != b) {
                return false;
            } 
        }

        return true;
    }
    string gcdOfStrings(string str1, string str2) {
        // int n = str2.size();
        // string res = str2;
        // while (n>0) {
        //     if (divides(str1, res) && divides(str2, res)) {
        //         return res;
        //     }
        //     res.pop_back();
        //     n--;
        // }
        // return res;

        int len = gcd(str1.size(), str2.size());
        string res = str2.substr(0, len);

        if (divides(str1, res) && divides(str2, res)) {
            return res;
        }

        return "";
    }
};