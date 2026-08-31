class Solution {
    private boolean isPallindrome(String s, int left , int right) {
        while (left < right) {
            if (s.charAt(left++) != s.charAt(right--)) {
                return false;
            }
        }
        return true;
    }
    public boolean validPalindrome(String s) {
        int left = 0;
        int right  = s.length()-1;

        while (left < right) {
            if (s.charAt(left) == s.charAt(right)) {
                left++;
                right--;
            } else {
                return isPallindrome(s, left+1, right) || isPallindrome(s, left, right-1);
            }
        }

        return true;
    }
}