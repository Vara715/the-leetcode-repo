class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;

        for (int i=0; i< (1<<n); i++) {
            int k = i^(i>>1);

            res.push_back(k);
        }

        return res;
    }
};