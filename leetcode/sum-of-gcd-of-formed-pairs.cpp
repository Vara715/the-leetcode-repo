class Solution {
public:
    int gcd(int a, int b) {
        while(b!=0) {
            int tmp = b;
            b = a%b;
            a = tmp;
        }

        return a;
    }


    long long gcdSum(vector<int>& nums) {
        int currMax = nums[0];
        int n = nums.size();
        vector<int> gcdStore(n, -1);
        gcdStore[0] = nums[0];

        for(int i=1; i<n; i++) {
            currMax = max(currMax, nums[i]);
            gcdStore[i] = gcd(currMax, nums[i]);
        }

        sort(gcdStore.begin(), gcdStore.end());

        int left = 0;
        int right = n-1;
        long long addition = 0;
        while (left < right) {
            addition += gcd(gcdStore[left], gcdStore[right]);
            left++;
            right--;
        }

        return addition;
    }
};