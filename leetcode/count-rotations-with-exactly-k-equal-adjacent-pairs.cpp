class Solution {
public:
    int countRotations(string s, int k) {
        int n = s.size();
        int count = 0;

        for (int i=0; i<n; i++) {
            if (s[i] == s[(i+1)%n]) {
                count++;
            }
        }

        if (k == count) {
            return n-count;
        } else if (k == count-1) {
            return count;
        }

        return 0;
    }
};