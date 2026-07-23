class Solution {
public:
    int minimumCost(vector<int>& nums, int k) {
        const long long MOD = 1000000007LL;
        // int n = nums.size();
        sort(nums.begin(), nums.end());

        long long cost = 0;
        long long costCounter = 1;
        long long resources = k;
        for (int need: nums) {
            // while (need > resources) {
            //     resources+=k;
            //     cost= (cost + costCounter)%MOD;
            //     costCounter++;
            // }

            if (need > resources) {
                long long diff = need - resources;
                long long expansions = (diff + k - 1) / k; // ceil division
    
                // Compute arithmetic series sum safely under modulo
                long long first = costCounter % MOD;
                long long last = (costCounter + expansions - 1) % MOD;
                long long addCost = ((first + last) % MOD) * (expansions % MOD) % MOD * ((MOD + 1) / 2) % MOD; 
                // (MOD+1)/2 is modular inverse of 2 under MOD
    
                cost = (cost + addCost) % MOD;
                costCounter += expansions;
                resources += expansions * k;
            }
            resources -= need;
        }

        return (int)(cost%MOD);
    }
};