class Solution {
    static constexpr long long MOD = 1'000'000'007LL;

    struct Node {
        long long sum = 0;
        long long sumSq = 0;
        long long lazy = 0;
    };

    vector<Node> seg;
    int n;

    void apply(int node, int l, int r, long long d) {
        long long len = r - l + 1LL;

        seg[node].sumSq =
            (seg[node].sumSq
             + 2LL * d % MOD * seg[node].sum % MOD
             + d * d % MOD * len % MOD) % MOD;

        seg[node].sum =
            (seg[node].sum + d * len) % MOD;

        seg[node].lazy = (seg[node].lazy + d) % MOD;
    }

    void push(int node, int l, int r) {
        if (seg[node].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;
        long long d = seg[node].lazy;

        apply(node * 2, l, mid, d);
        apply(node * 2 + 1, mid + 1, r, d);

        seg[node].lazy = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr, long long d) {
        if (ql > r || qr < l)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, d);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr, d);
        update(node * 2 + 1, mid + 1, r, ql, qr, d);

        seg[node].sum =
            (seg[node * 2].sum +
             seg[node * 2 + 1].sum) % MOD;

        seg[node].sumSq =
            (seg[node * 2].sumSq +
             seg[node * 2 + 1].sumSq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        seg.assign(4 * n + 5, Node{});

        unordered_map<int, int> last;
        long long ans = 0;

        for (int j = 0; j < n; j++) {
            int prev = -1;

            if (last.count(nums[j]))
                prev = last[nums[j]];

            update(1, 0, n - 1, prev + 1, j, 1);

            ans = (ans + seg[1].sumSq) % MOD;

            last[nums[j]] = j;
        }

        return static_cast<int>(ans);
    }
};
