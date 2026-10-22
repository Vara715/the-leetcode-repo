class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if (n<=0) return 0;

        vector<int> drops;
        vector<int> climb;

        for (int i=0; i<n; i++) {
            int next = (i+1)%n;

            if (nums[i] > nums[next]) {
                drops.push_back(i);
            } else if (nums[i] < nums[next]) {
                climb.push_back(i);
            }
        }

        vector<int> ans;

        if (drops.size() == 0) {
            return 0; //array sorted
        } else if (drops.size() == 1) {
            int k = (drops[0]+1)%n;
            ans.push_back(k); //left

            ans.push_back(n-k+2); //rev+left+rev = right #857
        }

        //for climbs
        if (climb.size() == 0) {
            ans.push_back(1); //sorted in desc
        } else if (climb.size() == 1) {
            int k = climb[0];

            ans.push_back(k+1+1); //left rotate then rev

            ans.push_back(1 + (n-k-1)); //rev then left
        }

        int mini = INT_MAX;
        for (int val: ans) {
            mini = min(mini, val);
        }

        return mini == INT_MAX? -1: mini;
    }
};