class Solution {
public:
    // int maxInt(int n) {
    //     vector<int> val;

    //     while (n > 0) {
    //         int d = n%10;
    //         val.push_back(d);
    //         n = n/10;
    //     }

    //     sort(val.begin(), val.end(), greater<int>());

    //     int output = 0;
    //     for (int i=0; i<val.size(); i++) {
    //         output = output*10 + val[i];
    //     }

    //     return output;
    // }
    long long maximizeSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> gains;
        
        long long sum = 0;

        for (int i=0; i<n; i++) {
            // if (k>0) {
            //     int val = maxInt(nums[i]);

            //     if (val > nums[i]) {
            //         sum += val;
            //         k--;
            //     } else {
            //         sum += nums[i];
            //     }
            // } else {
            //     sum+=nums[i];
            // }

            sum += nums[i];
            // int val = maxInt(nums[i]);

            string s = to_string(nums[i]);
            sort(s.begin(), s.end(), greater<char>());

            int val = stoi(s);
            gains.push_back(val - nums[i]);
        }

        sort(gains.begin(), gains.end(), greater<int>());

        for (int i=0; i<k; i++) {
            sum += gains[i];
        }


        return sum;
    }
};