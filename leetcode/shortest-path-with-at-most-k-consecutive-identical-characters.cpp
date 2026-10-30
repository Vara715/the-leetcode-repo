class Solution {
public:
    // void dfs(int n, int curr, int &curr_w, int weight, int k, string &labels, string s, vector<bool> &visited, vector<vector<pair<int, int>>> &adj) {

    //     //base
    //     if (curr == n-1) {
    //         int tmp = k;
    //         for (int i=1; i<s.size(); i++) {
    //             if (s[i] == s[i-1]) {
    //                 tmp--;

    //                 if (tmp == 1) break;
    //             } else {
    //                 tmp = k;
    //             }
    //         }

    //         if (tmp == 1) {
    //             curr_w = min(curr_w, weight);
    //         }

    //         return;
    //     }

    //     visited[curr] = true;
    //     for (auto [vi, w]: adj[curr]) {
    //         if (!visited[vi]) {
    //             visited[vi] = true;
    //             dfs(n, vi, curr_w, weight+w, k, labels, s+labels[vi], visited, adj);
    //             visited[vi] = false;
    //         }
    //     }
    // }
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (int i=0; i<edges.size(); i++) {
            int ui = edges[i][0];
            int vi = edges[i][1];
            int w = edges[i][2];

            adj[ui].push_back({vi, w});
        }

        // vector<bool> visited(n, false);
        // int curr_w = INT_MAX;

        // dfs(n, 0, curr_w, 0, k, labels, "", visited, adj);

        // return curr_w;

        //dijkstra
        vector<vector<int>> dist(n, vector<int> (k+1, INT_MAX));

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;


        pq.push({0, 0, 1});
        dist[0][1] = 0;

        while (!pq.empty()) {
            auto [d, u, count] = pq.top();
            pq.pop();

            if (d > dist[u][count]) continue;

            if (u == n-1) return d;

            for (auto &[v, w]: adj[u]) {
                int next_count = (labels[u] == labels[v])? count+1: 1;

                if (next_count > k) continue;

                if (d+w < dist[v][next_count]) {
                    pq.push({d+w, v, next_count});
                    dist[v][next_count] = d+w;
                }
            }
        }

        return -1;
    }
};