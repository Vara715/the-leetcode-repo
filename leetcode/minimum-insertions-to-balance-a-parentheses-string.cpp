class Solution {
public:
    int minInsertions(string s) {
        // int balance = 0;
        // int curr = 0;

        // for (char ch: s) {
        //     if (ch == '(') {
        //         balance += 2;
        //     } else {
        //         if (balance > 0) {
        //             balance--;
        //         } else {
        //             curr++;
        //             balance++;
        //         }
        //     } 
        // }

        // return curr+balance;

        // int open = 0, close = 0;
        // int ans = 0;

        // for (char ch: s) {
        //     if (ch == '(') {
        //         open += 2;
        //     } else {
        //         close++;

        //         if (open < 2*close) {
        //             ans+=(close-open);
        //         }
        //     }
        // }

        int inserts = 0;
        int need_close = 0;

        for (char ch: s) {
            if (ch == '(') {
                if(need_close%2 != 0) {
                    inserts++;
                    need_close--;
                }

                need_close+=2;
            } else {
                need_close--;

                if (need_close < 0) {
                    inserts++;
                    need_close = 1;
                }
            }
        }

        return inserts + need_close;
    }
};