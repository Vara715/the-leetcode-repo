class Solution {
public:
    int strStr(string haystack, string needle) {
        // int left = 0;
        // int right = needle.size()-1;
        // int r = haystack.size()-1;
        // int l =0;
        // int ans = -1;
        // i

        // while (l <= r) {
        //     while (neddle[left] == haystack[l] && needle[right] == haystack[r]) {
        //         left++;
        //         l++;
        //         r--;
        //         right--;
        //     }

        //     if  (left > right) ans = 
        // }

        int n = haystack.size();
        int m = needle.size();

        if (n<m) return -1;

        for (int i=0; i<=n-m; i++) {
            if (haystack.substr(i, m) == needle) {
                return i;
            }
        }

        return -1;
    }
};