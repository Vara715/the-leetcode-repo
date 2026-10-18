class Solution {
public:
    int findColoredRoot(vector<vector<int>>& edges, string colors) {
        int n = colors.size();

        vector<int> degree(n, 0);
        for (auto &e: edges) {
            degree[e[0]]++;
            degree[e[1]]++;

            if (degree[e[0]] >3 || degree[e[1]]>3) return -1;
        }

        auto getColorVal = [](char ch) -> int {
            if (ch == 'R') return 0;
            if (ch == 'B') return 1;

            return 2;
        };

        vector<int> col(n);
        for (int i=0; i<n; i++) {
            col[i] = getColorVal(colors[i]);
        }

        vector<vector<int>> adj(n);
        vector<int> inDegree(n, 0);

        for (auto &e: edges) {
            int u = e[0];
            int v = e[1];

            if ((col[u]+1)%3 == col[v]) {
                adj[u].push_back(v);
                inDegree[v]++;
            } else if ((col[v]+1)%3 == col[u]) {
                adj[v].push_back(u);
                inDegree[u]++;
            } else {
                return -1;
            }
        }

        int root = -1;
        for (int i=0; i<n; i++) {
            if (inDegree[i] == 0) {
                if (root != -1) return -1;
                root = i;
            } else if (inDegree[i] != 1) {
                return -1;
            }
        }

        if (root == -1) return -1;

        for (int i=0; i<n; i++) {
            if (adj[i].size()>2) return -1;
        }

        vector<int> dist(n, -1);
        queue<int> q;

        q.push(root);
        dist[root] = 0;
        int visited = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            visited++;

            if (col[u] != (col[root] + dist[u])%3) {
                return -1;
            }

            for (int v: adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u]+1;
                    q.push(v);
                }
            }
        }


        return (visited == n)? root: -1;
    }
};