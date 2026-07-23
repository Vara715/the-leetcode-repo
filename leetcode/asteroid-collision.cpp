class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        for (int num : asteroids) {
            bool destroyed = false;
            while (!ans.empty() && ans.back() > 0 && num < 0) {
                if (abs(ans.back()) < abs(num)) {
                    ans.pop_back(); // previous asteroid destroyed
                    continue;       // keep checking with new top
                } else if (abs(ans.back()) == abs(num)) {
                    ans.pop_back(); // both destroyed
                    destroyed = true;
                    break;
                } else {
                    destroyed = true; // current asteroid destroyed
                    break;
                }
            }
            if (!destroyed) {
                ans.push_back(num);
            }
        }
        return ans;
    }
};