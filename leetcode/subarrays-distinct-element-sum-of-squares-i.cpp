class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        int res = 0;

        for (int i=0; i<n; i++) {
            unordered_set<int> Set;

            for (int j=i; j<n; j++) {
                Set.insert(nums[j]);
                int x = Set.size();

                res += x*x;
            }
        }

        return res;
    }
};