class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();

        sort(nums.begin(), nums.end());

        // int curr = nums[0];

        int i = 1;
        for (int j=nums[0]+1; j<nums[n-1]; j++) {
            if (nums[i] == j) {
                i++;
            } else {
                ans.push_back(j);
            }
        }

        return ans;
    }
};