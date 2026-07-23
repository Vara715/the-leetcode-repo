class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int n = gain.size();
        int currGain = 0;
        int maxAltitude = 0;

        for (int i=1; i<=n; i++) {
            currGain = currGain + gain[i-1];

            maxAltitude = max(maxAltitude, currGain);
        }

        return maxAltitude;
    }
};