class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp = nums;

        sort(tmp.begin(), tmp.end());
        int k = -1;

        for (int i=0; i<n; i++) {
            if (nums[i] != tmp[i]) {
                if (k == -1) {
                    k = nums[i];
                    continue;
                }
                k = k&nums[i];
            }
        }

        return k==-1? 0: k;
    }
};