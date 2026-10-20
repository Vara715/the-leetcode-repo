class Solution {
public:
    long long sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> divisors;
        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                divisors.push_back(i);
                if (i * i != n) {
                    divisors.push_back(n / i);
                }
            }
        }

        long long total_sum = 0;

        for (int k : divisors) {
            if (isSortable(nums, n, k)) {
                total_sum += k;
            }
        }

        return total_sum;
    }

private:
    bool isSortable(const vector<int>& nums, int n, int k) {
        int prev_max = -1;

        for (int start = 0; start < n; start += k) {
            int end = start + k - 1;

            int cur_min = nums[start];
            int cur_max = nums[start];
            int drops = 0;

            for (int i = start; i < end; ++i) {
                if (nums[i] > nums[i + 1]) {
                    drops++;
                    if (drops > 1) return false;
                }
                cur_min = min(cur_min, nums[i + 1]);
                cur_max = max(cur_max, nums[i + 1]);
            }

            if (k > 1 && nums[end] > nums[start]) {
                drops++;
                if (drops > 1) return false;
            }

            if (start > 0 && prev_max > cur_min) {
                return false;
            }

            prev_max = cur_max;
        }

        return true;
    }
};