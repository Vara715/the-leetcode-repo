class Solution {
public:
    // bool check(int num) {
    //     int curr = num%10;
    //     num = num/10;

    //     while (num>0) {
    //         int reminder = num%10;
    //         if (reminder!=curr-1) {
    //             return false;
    //         }

    //         curr = reminder;
    //         num = num/10;
    //     }

    //     return true;
    // }
    vector<int> sequentialDigits(int low, int high) {
        vector<int> nums;
        string digits = "123456789";

        for (int i=2; i<=9; i++) {
            for (int j=0; j+i<=9; j++) {
                int num = stoi(digits.substr(j, i));
                if (num >= low && num <= high) {
                    nums.push_back(num);
                }
            }
        }

        sort(nums.begin(), nums.end());
        return nums;
        // for (int i=low; i<=high; i++) {
        //     if (check(i)) {
        //         nums.push_back(i);
        //     }
        // }

        // return nums;
    }
};