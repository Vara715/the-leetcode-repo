// class Solution {
// public:
//     void query(int &ui, int &vi, string &q) {
//         int n = q.size();
//         int i=6;

//         while (q[i] != ' ') {
//             ui = 10*ui + (q[i] - '0');
//             i++;
//         } 

//         i++;
//         while (i < n) {
//             vi = 10*vi + (q[i] - '0');
//             i++;
//         }
//     }
//     void update(string &s, string &q) {
//         int n = q.size();
//         char ch = q[n-1];
//         int ui = 0;

//         int i = 7;
//         while (q[i] != ' ') {
//             ui = ui*10 + (q[i] - '0');
//             i++;
//         }

//         s[ui] = ch;
//     }
//     void bfs(int ui, int vi, int n, string &s, unordered_map<char, int> &freq, vector<vector<int>> &adj) {
//         queue<int> q;
//         vector<bool> visited(n, false);
//         vector<int> parent(n, -1);

//         q.push(ui);
//         visited[ui] = true;

//         while (!q.empty()) {
//             int curr = q.front();
//             q.pop();

//             if (curr == vi) break;

//             for (int val: adj[curr]) {
//                 if (!visited[val]) {
//                     q.push(val);
//                     parent[val] = curr;
//                     visited[val] = true;
//                 }
//             }
//         }

//         if (!visited[vi]) return;

//         for (int node = vi; node!=-1; node = parent[node]) {
//             freq[s[node]]++;
//         }
//     }
//     vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
//         vector<bool> ans;
//         vector<vector<int>> adj(n);
//         int m = queries.size();

//         for (int i=0; i<edges.size(); i++) {
//             int ui = edges[i][0];
//             int vi = edges[i][1];

//             adj[ui].push_back(vi);
//             adj[vi].push_back(ui);
//         }

//         for (int i=0; i<m; i++) {
//             string q = queries[i];

//             if (q[0] == 'u') {
//                 update(s, q);
//                 continue;
//             }

//             int vi = 0;
//             int ui = 0;
//             query(ui, vi, q);

//             unordered_map<char, int> freq;

//             bfs(ui, vi, n, s, freq, adj);

//             int odd = 0;
//             for (auto &[ch, f]: freq) {
//                 if (f%2 != 0) {
//                     odd++;
//                 }
//             }

//             if (odd > 1) {
//                 ans.push_back(false);
//             } else {
//                 ans.push_back(true);
//             }
//         }

//         return ans;
//     }
// };



class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy, head, pos;
    vector<int> seg;
    int timer;

    int charMask(char c) {
        return 1 << (c - 'a');
    }

    void dfs(int u, int p) {
        parent[u] = p;
        sz[u] = 1;
        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];

            if (sz[v] > maxSize) {
                maxSize = sz[v];
                heavy[u] = v;
            }
        }
    }

    void decompose(int u, int h, string& s) {
        head[u] = h;
        pos[u] = timer++;

        if (heavy[u] != -1) {
            decompose(heavy[u], h, s);
        }

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v, s);
        }
    }

    void build(int node, int l, int r, string& s) {
        if (l == r) {
            // Find the node at this HLD position.
            seg[node] = charMask(s[nodeToPos[l]]);
            return;
        }

        int mid = (l + r) / 2;
        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    vector<int> nodeToPos;

    void initSegmentTree(string& s) {
        nodeToPos.resize(s.size());

        for (int u = 0; u < (int)s.size(); u++) {
            nodeToPos[pos[u]] = u;
        }

        seg.assign(4 * s.size(), 0);
        build(1, 0, (int)s.size() - 1, s);
    }

    void pointUpdate(int node, int l, int r,
                     int idx, int value) {
        if (l == r) {
            seg[node] = value;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            pointUpdate(node * 2, l, mid, idx, value);
        } else {
            pointUpdate(node * 2 + 1, mid + 1, r, idx, value);
        }

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int rangeQuery(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;

        if (ql <= l && r <= qr) return seg[node];

        int mid = (l + r) / 2;

        return rangeQuery(node * 2, l, mid, ql, qr)
             ^ rangeQuery(node * 2 + 1, mid + 1, r, ql, qr);
    }

    int pathQuery(int u, int v) {
        int mask = 0;
        int n = (int)parent.size();

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }

            mask ^= rangeQuery(1, 0, n - 1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);

        mask ^= rangeQuery(1, 0, n - 1, pos[u], pos[v]);

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, -1);
        pos.assign(n, 0);
        timer = 0;

        dfs(0, -1);
        decompose(0, 0, s);
        initSegmentTree(s);

        vector<bool> ans;

        for (string& query : queries) {
            stringstream ss(query);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                s[u] = c;
                pointUpdate(1, 0, n - 1, pos[u], charMask(c));
            } else {
                int u, v;
                ss >> u >> v;

                int mask = pathQuery(u, v);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
