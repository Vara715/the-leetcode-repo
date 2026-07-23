class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int compute = 2*n;
        int sumOdd = 0;
        int sumEven = 0;
        for (int i=1; i<=compute; i++) {
            if (i%2 == 0) {
                sumEven+=i;
            } else {
                sumOdd+=i;
            }
        }

        while (sumOdd != 0) {
            int tmp = sumOdd;
            sumOdd = sumEven % sumOdd;
            sumEven = tmp;
        }

        return sumEven;
    }
};