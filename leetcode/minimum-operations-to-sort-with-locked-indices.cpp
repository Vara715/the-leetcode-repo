class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k) {
        int n = nums.size();
        int ans = 0;

        vector<int> prefix(n);
        prefix[0] = nums[0];
        for (int i=1; i<n; i++) {
            prefix[i] = max(prefix[i-1], nums[i]);
        }
        
        int unlocks = 0;
        for (int i=0; i<n; i++) {
            if (locked[i] == 1) {
                bool place = (nums[i] == i+1);
                bool blocks = (i>0 && prefix[i-1] > i); //case 537

                if (!place || blocks) {
                    unlocks++;
                    locked[i] = 0;
                }
            }
        }

        if (k < unlocks) return -1;
        ans += unlocks;

        for (int i=0; i<n; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (nums[j] > nums[j+1] && locked[j] != 1 && locked[j+1] != 1) {
                    swap(nums[j], nums[j+1]);
                    ans++;
                }
            }
        }

        return ans;
    }
};