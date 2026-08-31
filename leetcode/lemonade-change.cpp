class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int n = bills.size();
        int dollar_5 = 0;
        int dollar_10 = 0;

        for (int i=0; i<n; i++) {
            if (bills[i] == 5) {
                dollar_5++;
            }

            if (bills[i] == 10) {
                dollar_10++;
            }

            int change = bills[i]-5;

            while (dollar_10 > 0 && change - 10 >= 0) {
                dollar_10--;
                change -= 10;
            } 

            while (dollar_5 > 0 && change - 5 >= 0) {
                dollar_5--;
                change -= 5;
            }

            if (change != 0) return false; 
        }

        return true;
    }
};