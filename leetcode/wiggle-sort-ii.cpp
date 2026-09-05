class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();

        vector<int> increase = nums;

        sort(increase.begin(), increase.end());

        int right = n-1;
        int left = (n-1)/2;
        int i=0;

        for (int i=0; i<n; i++) {
            if (i%2==0) {
                nums[i] = increase[left--];
            } else {
                nums[i] = increase[right--];
            }
        }
    }
};