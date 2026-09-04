class Solution {
    public int countPrimes(int n) {
        boolean[] b = new boolean[n];
        int ans = 0;
        for (int i = 2; i * i < n; i++) 
            if (!b[i]) 
                for (int j = i * i; j < n; j += i)
                    b[j] = true;
        for (int i = 2; i < n; i++)
            if (!b[i])
                ans += 1;
        return ans;
    }
}