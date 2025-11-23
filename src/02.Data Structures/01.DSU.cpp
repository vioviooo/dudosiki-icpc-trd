#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using ll = long long;

struct wedge {
	int u, v;
	ll w;
};

bool operator < (wedge a, wedge b) {
	return a.w < b.w;
};

using namespace std;
using wgraph = vector<vector<wedge>>;

struct dsu {
	vector<int> leader;  // parent/representative of each element
	vector<int> size;    // size of each set (for union by size)
	int n;               // number of elements

	dsu(int _n) {
		n = _n;
		leader.resize(n);
		// Initially, each element is its own leader
		for (int i = 0; i < n; i++) {
			leader[i] = i;
		}
		size.resize(n, 1);  // All sets initially have size 1
	}

	// Find with path compression
	int find(int u) {
		if (leader[u] == u) {
			return u;
		}
		// Path compression: make nodes point directly to root
		leader[u] = find(leader[u]);
		return leader[u];
	}

	// Union by size - returns true if union was performed, false if already in same set
	bool unite(int u, int v) {
		int lu = find(u);  // Find leader of u
		int lv = find(v);  // Find leader of v
		
		// If already in same set, no union needed
		if (lu == lv) {
			return false;
		}
		
		// Union by size: attach smaller tree to larger tree
		if (size[lu] > size[lv]) {
			swap(lu, lv);
		}
		leader[lu] = lv;           // Attach lu's tree to lv
		size[lv] += size[lu];      // Update size of merged set
		return true;
	}
};

int main() {
	int n, m; 
	cin >> n >> m;
	vector<wedge> edges;
	for (int i = 0; i < m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;
		edges.push_back({ u,v,w });
	}
	sort(all(edges));  // Sort edges by weight for Kruskal's algorithm
	dsu d(n);
	ll w_total = 0;
	vector<wedge> wedges_mst;
	for (wedge elem : edges) {
		int u = elem.u;
		int v = elem.v;
		if (!d.unite(u, v)) {
			continue;  // Skip if adding this edge would create a cycle
		}
		else {
			ll w = elem.w;
			w_total += w;  // Add weight to MST total
			wedges_mst.push_back({ u,v,w });  // Add edge to MST
		}
	}
	cout << w_total << endl;
	for (int i = 0; i < n - 1; i++) {
		cout << wedges_mst[i].w << ' ';
	}
}