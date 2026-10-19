class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        int n = nums.size();
        // sort(nums.begin(), nums.end());

        vector<int> ans;

        int count = 0;
        int res = 0;
        for (int i=0; i<n; i++) {
            if (nums[i] < target) {
                count++;
            }

            if (nums[i] == target) {
                res++;
            }
        }

        for (int i=count; i<res+count; i++) {
            ans.push_back(i);
        }

        // for (int i=0; i<n; i++) {
        //     if (nums[i] == target) {
        //         ans.push_back(i);
        //     }
        // }

        return ans;
    }
};