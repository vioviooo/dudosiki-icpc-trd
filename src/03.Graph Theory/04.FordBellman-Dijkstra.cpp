
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

using namespace std;
struct wedge {
	int u, v;
	ll w;
};

using wgraph = vector<vector<wedge>>;
using matrix = vector<vector<ll>>;
const ll INF = 1e18;
using item = pair<ll, int>;

void dijkstra_fast(wgraph& g, const int start, vector<ll>& d, vector<int>& prev) {
    int n = g.size();
    d.assign(n, INF);
    prev.assign(n, -1);
    d[start] = 0;
    prev[start] = start;
    
    priority_queue<item, vector<item>, greater<item>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        item cur = pq.top();
        pq.pop();
        int u = cur.second;
        ll dist_u = cur.first;
        
        // Skip if we have a better distance already
        if (dist_u != d[u]) continue;
        
        for (const wedge& elem : g[u]) {
            int v = elem.v;
            ll w = elem.w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                prev[v] = u;
                pq.push({d[v], v});
            }
        }
    }
}

// Corrected solve_dijkstra
void solve_dijkstra() {
    int n, m, start;
    cin >> n >> m >> start;
    start--;
    wgraph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].push_back({u, v, w});
    }
    vector<ll> distances;
    vector<int> prev;
    dijkstra_fast(g, start, distances, prev);
    
    // Output results
    for (int i = 0; i < n; i++) {
        cout << distances[i] << ' ';
    }
}

void FordBellman() {
    int n, m, start;
    cin >> n >> m >> start;
    start--;
    vector<wedge> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges.push_back({u, v, w});
    }
    
    vector<ll> dp(n, INF);
    dp[start] = 0;
    
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        bool changed = false;
        for (const wedge& elem : edges) {
            int u = elem.u;
            int v = elem.v;
            ll w = elem.w;
            if (dp[u] < INF && dp[v] > dp[u] + w) {
                dp[v] = dp[u] + w;
                changed = true;
            }
        }
        if (!changed) break;
    }
    
    // Check for negative cycles
    bool hasNegativeCycle = false;
    for (const wedge& elem : edges) {
        int u = elem.u;
        int v = elem.v;
        ll w = elem.w;
        if (dp[u] < INF && dp[v] > dp[u] + w) {
            hasNegativeCycle = true;
            break;
        }
    }
    
    if (hasNegativeCycle) {
        cout << "Negative cycle";
    } else {
        for (int i = 0; i < n; i++) {
            cout << dp[i] << ' ';
        }
    }
}
