class LazySegmentTree {
private:
    vector<int> tree, lazy;
    int n;
    
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void rangeUpdate(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (r < start || l > end) return;
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
        } else {
            int mid = (start + end) / 2;
            rangeUpdate(2 * node, start, mid, l, r, val);
            rangeUpdate(2 * node + 1, mid + 1, end, l, r, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    int rangeQuery(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (r < start || l > end) return 0;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        int left_sum = rangeQuery(2 * node, start, mid, l, r);
        int right_sum = rangeQuery(2 * node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }

public:
    LazySegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }
    
    void rangeUpdate(int l, int r, int val) {
        rangeUpdate(1, 0, n - 1, l, r, val);
    }
    
    int rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
};