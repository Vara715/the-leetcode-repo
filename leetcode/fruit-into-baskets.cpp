class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        if (n <= 2) return n;
        
        int left = 0;
        int basket1 = fruits[0];
        // int freq1 = 1;
        // int freq2 = 0;

        int last1 = 0;
        int last2 = -1;

        int basket2 = -1;
        int maxLen = 0;

        for (int right=1; right<n; right++) {
            // if (basket2 == -1 && fruits[right] != basket1) {
            //     basket2 = fruits[right];
            //     freq2++;
            // }

            // if (fruits[right] != basket1 && fruits[right] != basket2) {
            //     while (freq1 > 0) {
            //         if (fruits[left] == basket1) {
            //             freq1--;
            //         }

            //         left++;
            //     }

            //     basket1 = basket2;
            //     basket2 = fruits[right];

            //     freq1 = freq2;
            //     freq2 = 0;
            // }

            // if (fruits[right] == basket1) freq1++;
            // if (fruits[right] == basket2) freq2++;

            if (fruits[right] == basket1) {
                last1 = right;
            } else if (fruits[right] == basket2) {
                last2 = right;
            } else {
                left = min(last1, last2) +1;

                if (last1 < last2) {
                    last1 = right;
                    basket1 = fruits[right];
                } else {
                    last2 = right;
                    basket2 = fruits[right];
                }
            }

            maxLen = max(maxLen, right-left+1);
        }

        return maxLen;
    }
};