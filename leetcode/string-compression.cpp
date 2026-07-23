class Solution {
public:
    int compress(vector<char>& chars) {
        int left = 0;
        int idx = 0;
        int n = chars.size();
        // string s = "";

        while (left < n) {
            char ch = chars[left];
            int count = 1;

            while (left+1 < n && chars[left+1] == ch) {
                left++;
                count++;
            }

            if (count == 1) {
                // s.push_back(ch);
                chars[idx++] = ch;
                left++;
                continue;
            }

            string numeration = to_string(count);
            int i=0;
            // s.push_back(ch);
            chars[idx++] = ch;
            while(i<numeration.size()) {
                // s.push_back(numeration[i]);
                chars[idx++] = numeration[i];
                i++;
            }

            left++;
        }

        // for(int i=0; i<s.size(); i++) {
        //     chars[i] = s[i];
        // }

        return idx;
    }
};