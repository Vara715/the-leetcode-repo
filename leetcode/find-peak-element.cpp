class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;
        int ans = INT_MIN;
        int idx = 0;

        while (left <= right) {
            int mid = (left+right)/2;

            if (mid > 0 && nums[mid-1] > nums[mid]) {
                right = mid-1;
            } else if (mid+1<nums.size() && nums[mid] < nums[mid+1]) {
                left = mid+1;
            } else {
                if (ans < nums[mid]) {
                    ans = nums[mid];
                    idx = mid;
                }
                break;
            }
        }

        return idx;
    }
};