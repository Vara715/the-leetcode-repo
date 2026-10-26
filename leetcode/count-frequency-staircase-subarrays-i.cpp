class Solution {
public:
    int countStaircase(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i=0;i<n; i++) {
            unordered_map<int, int> freq;
            vector<int> order;

            for (int j=i; j<n; j++) {
                if (freq.find(nums[j]) == freq.end()) {
                    order.push_back(nums[j]);
                }

                freq[nums[j]]++;

                bool validOrder = true;

                for (int k=0; k<order.size(); k++) {
                    if (freq[order[k]] != k+1) {
                        validOrder = false;
                        break;
                    }
                }

                if (validOrder) ans++;
            }
        }

        return ans;
    }
};