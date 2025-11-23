#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll MAX_D = 20;

struct edge {
    int u;
    int v;
};

using graph = vector<vector<edge>>;

struct LCA {
    vector<vector<int>> up;
    vector<int> d;
    int n;
    
    void dfs(int u, int p, const graph& g) {
        for (edge elem : g[u]) {
            int v = elem.v;
            if (v == p) {
                continue;
            }
            d[v] = 1 + d[u];
            up[v][0] = u;
            dfs(v, u, g);
        }
    }

    LCA(const graph& g, int root) {
        n = g.size();
        up.resize(n, vector<int>(MAX_D));
        d.resize(n, 0);
        
        if (root < 0 || root >= n) {
            throw invalid_argument("Root out of bounds");
        }
        
        up[root][0] = root;
        dfs(root, root, g);
        
        for (int j = 1; j < MAX_D; j++) {
            for (int u = 0; u < n; u++) {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }
        }
    }

    int find(int u, int v) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            throw invalid_argument("Node index out of bounds");
        }
        
        if (d[u] > d[v]) {
            swap(u, v);
        }
        int delta = d[v] - d[u];
        for (int j = MAX_D - 1; j >= 0; j--) {
            if (delta & (1 << j)) {
                v = up[v][j];
            }
        }
        if (u == v) {
            return u;
        }
        for (int j = MAX_D - 1; j >= 0; j--) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back({u, v});
        g[v].push_back({v, u});
    }

    int root;
    cin >> root;
    root--;
    LCA item(g, root);

    int Q;
    cin >> Q;
    vector<int> res;

    for (int q = 0; q < Q; q++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        res.push_back(item.find(u, v) + 1);
    }

    for (int elem : res) {
        cout << elem << '\n';
    }
}