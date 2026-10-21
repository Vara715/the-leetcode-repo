class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        char min_char = 'z';
        char max_char = 'a';
        bool isSorted = true;

        for (int i=0; i<n; i++) {
            char ch = s[i];

            if (ch < min_char) {
                min_char = ch;
            }

            if (ch > max_char) {
                max_char = ch;
            }

            if (i>0) {
                if (s[i] < s[i-1]) isSorted = false;
            }
        }

        int freq_min = 0;
        int freq_max = 0;
        for (char ch: s) {
            if (ch == min_char) {
                freq_min++;
            }

            if (ch == max_char) {
                freq_max++;
            }
        }

        //case 1
        if (isSorted) return 0;

        if (n==2) return -1;

        //case 2
        if (s[0] == min_char || s[n-1] == max_char) {
            return 1;
        }

        //case 3
        if (s[0] == max_char && s[n-1] == min_char && freq_min == 1 && freq_max == 1) {
            return 3;
        }


        return 2;
    }
};