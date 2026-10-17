class Solution {
public:
    int calculateDigitSum(int a) {
        int sum = 0;

        while (a>0) {
            int d = a%10;
            a /=10;

            sum += d;
        }

        return sum;
    }
    int minSwaps(vector<int>& nums) {
        
        // sort(nums.begin(), nums.end(), [](int a, int b) {
        //     int sum1 = calculateDigitSum(a);
        //     int sum2 = calculateDigitSum(b);

        //     if (sum1 == sum2) {
        //         if (a < b) {
        //             return a;
        //         }

        //         return b;
        //     }

        //     return sum1<sum2;
        // })

        int n = nums.size();
        // int swaps = 0;

        // for (int i=0; i<n-1; i++) {
        //     for (int j=0; j<n-i-1; j++) {
        //         int sum1 = calculateDigitSum(nums[j]);
        //         int sum2 = calculateDigitSum(nums[j+1]);

        //         if (sum1 > sum2) {
        //             swap(nums[j], nums[j+1]);
        //             swaps++;
        //         }

        //         if (sum1 == sum2) {
        //             if (nums[j] > nums[j+1]) {
        //                 swap(nums[j], nums[j+1]);
        //                 swaps++;
        //             }
        //         }
        //     }
        // }

        // return swaps;

        vector<vector<int>> arr(n);
        for (int i=0; i<n; i++) {
            arr[i] = {calculateDigitSum(nums[i]), nums[i], i};
        }

        sort(arr.begin(), arr.end(), [](vector<int> &a, vector<int> &b) {
            if (a[0] != b[0]) {
                return a[0]<b[0];
            }

            return a[1]<b[1];
        });

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i=0; i<n; i++) {
            if (visited[i] || arr[i][2] == i) {
                continue;
            }

            int cycleSize = 0;
            int j=i;

            while (!visited[j]) {
                visited[j] = true;
                j=arr[j][2];

                cycleSize++;
            }

            if (cycleSize > 0) {
                swaps += (cycleSize-1);
            }
        }

        return swaps;
    }
};