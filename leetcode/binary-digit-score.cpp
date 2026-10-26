class Solution {
public:
    int calculateScore(int a, int b) {
        int s1 = 0;
        int s2 = 0;

        while (a>0) {
            if (a&1 == 1) {
                s1++;
            }

            a >>= 1;
        }

        while (b > 0) {
            if (b&1 == 1) {
                s2++;
            }

            b >>= 1;
        }

        if (s1 >= s2) {
            return s1*s2;
        }

        return s2/s1;
    }
};