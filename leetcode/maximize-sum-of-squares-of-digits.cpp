class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string curr = "";
        int x = 9;
        int s = sum;

        while (s!=0 && curr.size() != num) {
            if (s-x < 0) {
                x--;
                continue;
            }

            curr += (x + '0');
            s -= x;     
        }

        if (curr.size() == num && s>0) return "";

        while (curr.size() < num) {
            curr += 0 + '0';
        }

        return curr;
    }
};