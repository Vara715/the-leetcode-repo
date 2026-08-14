class Solution {
public:
    void dfs(vector<vector<int>> &adj, vector<bool> &vis, int curr) {
        vis[curr] = true;

        for (int val: adj[curr]) {
            if (!vis[val]) {
                dfs(adj, vis, val);
            }
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> vis(n, false);

        dfs(rooms, vis, 0);

        for (int i=0; i<n; i++) {
            if (!vis[i]) return false;
        }

        return true;
    }
};