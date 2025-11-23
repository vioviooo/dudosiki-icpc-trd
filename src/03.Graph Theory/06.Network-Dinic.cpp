using ll = long long;
const ll INF = 1e18;

double __speedstart__;
#define SPEEDTEST_START __speedstart__ = clock();
#define SPEEDTEST_STOP cout << "Process finished in: " << (double)(clock() - __speedstart__)/CLOCKS_PER_SEC << " seconds";

using namespace std;

struct network {
    struct edge {
        int u, v;
        ll f, c;
        edge(int _u, int _v, ll _c) : u(_u), v(_v), f(0), c(_c){}
    };

    int n;
    vector<edge> edges;
    vector<vector<int>> g;
    vector<int> d;
    vector<size_t> ptr;

    network(int _n) : n(_n), g(n){}

    void add_edge(int u, int v, ll c) {
        g[u].push_back(edges.size());
        edges.push_back(edge(u, v, c));
        g[v].push_back(edges.size());
        edges.push_back(edge(v, u, 0));
    }

    friend ostream& operator <<(ostream& out, const network& g) {
        int n = g.edges.size();
        for (int i = 0; i < n; i += 2) { // Only print original edges (skip reverse)
            edge elem = g.edges[i];
            if(elem.f > 0)
                out << elem.u + 1 << ' ' << elem.v + 1 << ' ' << elem.f << '\n';
        }
        return out;
    }

    bool bfs(int u, ll b) { // Return bool instead of void
        d.assign(n, -1);
        queue<int> q;
        q.push(u);
        d[u] = 0;
        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (int ind : g[u]) {
                ll c = edges[ind].c;
                ll f = edges[ind].f;
                if (c - f >= b && d[edges[ind].v] == -1) {
                    d[edges[ind].v] = d[u] + 1;
                    q.push(edges[ind].v);
                }
            }
        }
        return d[n-1] != -1; // Check if sink is reachable
    }

    ll dfs(int u, int finish, ll b, ll fp) {
        if (u == finish || fp == 0) {
            return fp;
        }
        for (; ptr[u] < g[u].size(); ptr[u]++) {
            int ind = g[u][ptr[u]];
            ll c = edges[ind].c;
            ll f = edges[ind].f;
            int v = edges[ind].v;
            
            if (d[v] != d[u] + 1 || c - f < b) {
                continue;
            }
            
            ll pushed = dfs(v, finish, b, min(c - f, fp));
            if (pushed > 0) {
                edges[ind].f += pushed;
                edges[ind ^ 1].f -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll dinic(int start, int finish, ll b) {
        ll res = 0;
        while (bfs(start, b)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(start, finish, b, INF)) {
                res += pushed;
            }
        }
        return res;
    }

    ll max_flow(int start, int finish) {
        ll res = 0;
        // Capacity scaling from 2^30 down to 2^0
        for (ll b = (1LL << 30); b > 0; b >>= 1) {
            res += dinic(start, finish, b);
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    network g(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        u--;
        v--;
        if (u == v) {
            continue; // Skip self-loops
        }
        g.add_edge(u, v, c);
    }
    
    int start = 0; // !
    int finish = n - 1; // !
    
    ll ans = g.max_flow(start, finish);
    cout << ans << endl;
    cout << g;
}