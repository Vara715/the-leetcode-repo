class Solution {
public:
    int minRotations(string s) {
        // int n = s.size();
        // int rotate = min(s[0] - '0', 10 - (s[0] - '0'));

        // for (int i=1; i<n; i++) {
        //     rotate += min(abs(s[i] - '0' - (s[i-1] - '0')), abs(10 - (s[i] - '0' - (s[i-1] - '0'))));
        // }

        // return rotate;

        int curr = 0;
        int ans = 0;

        for (char ch: s) {
            int next = ch - '0';

            int forward = abs(next - curr);
            int backward = 10-forward;

            ans += min(forward, backward);
            curr = next;
        }

        return ans;
    }
};