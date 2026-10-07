class Solution {
public:
    int dist(int a, int b) {
        int d = abs(a-b);
        return min(d, 10-d);
    }
    
    int minRotations(int n, string s) {
        int ans= 0;
        int prev = 0;

        for (char ch: s) {
            int curr = ch - '0';
            ans += dist(prev, curr);
            prev = curr;
        }

        int og = ans;
        for (int i=0; i<n; i++) {
            int prev = (i==0? 0: s[i-1] - '0');
            int first = s[i] - '0';
            int last = s[n-1] - '0';

            int newCost = og - dist(prev, first) + dist(prev, last);

            ans = min(ans, newCost);
        }

        return ans;
    }
};