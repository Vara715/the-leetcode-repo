class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());

        int n = spells.size();
        int m = potions.size();

        vector<int> pairs(n, 0);

        for (int i=0; i<n; i++) {
            int left = 0;
            int right = m-1;
            int idx = m;

            while (left <= right) {
                int mid = left + (right - left)/2;

                if ((long long)spells[i]*potions[mid] < success) {
                    left = mid+1;
                } else {
                    // while (mid >= 0 && spells[i]*potions[mid] >= success) {
                    //     mid--;
                    // }

                    right = mid-1;
                    idx = mid;
                }
            }

            pairs[i] = m-idx;
        }

        return pairs;
    }
};