class Solution {
public:
    bool allEqual(vector<int> &a, vector<int> &b) {
        for (int i=0; i<26; i++) {
            if (a[i] != b[i]) return false;
        }

        return true;
    }

    bool checkInclusion(string s1, string s2) {
        int n = s1.size();
        int m = s2.size();

        vector<int> freqS1(26, 0);
        vector<int> freqS2(26, 0);

        for (char ch: s1) {
            freqS1[ch-'a']++;
        }

        int left=0, right=0;

        while (right<m) {
            freqS2[s2[right] - 'a']++;

            if (right - left +1 >= n) {
                if (allEqual(freqS1, freqS2)) return true;
            }

            if (right-left+1 < n) {
                right++;
            } else {
                freqS2[s2[left] - 'a']--;
                left++;
                right++;
            }
        }

        return false;
    }
};