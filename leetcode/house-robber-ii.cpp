class Solution {
public:
    int rob(vector<int>& nums) {
        int prev1 = 0;
        int prev2 = 0;
        int n = nums.size();

        // for (int i=0; i<2*n; i++) {
        //     int idx = i%n;
        //     if (nums[idx] == -1) break;

        //     int temp = prev1;
        //     if (prev2+nums[idx] > prev1) {
        //         prev1 = prev2+nums[idx];
        //         nums[idx] = -1;
        //     }

        //     prev2 = temp;
        // }

        // return prev1;

        if  (n==1) return nums[0];

        for (int i=0; i<n-1; i++) {
            int temp = prev1;
            prev1 = max(prev1, prev2+nums[i]);
            prev2 = temp;
        }

        int ans = prev1;
        prev1 = prev2 = 0;

        for (int i=1; i<n; i++) {
            int temp = prev1;
            prev1 = max(prev1, prev2+nums[i]);
            prev2 = temp;
        }

        return max(ans, prev1);
    }
};