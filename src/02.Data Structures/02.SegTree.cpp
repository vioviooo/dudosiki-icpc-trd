class SegmentTree {
private:
    vector<int> tree;
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
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        if (l <= start && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        int left_sum = query(2 * node, start, mid, l, r);
        int right_sum = query(2 * node + 1, mid + 1, end, l, r);
        return left_sum + right_sum;
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }
    
    void update(int idx, int val) {
        if (l > r || l < 0 || r >= n) return;
        update(1, 0, n - 1, idx, val);
    }
    
    int query(int l, int r) {
        if (l > r || l < 0 || r >= n) return;
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    // Example 1: Range Sum Query
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree st_sum(arr);
    
    cout << "Sum from index 1 to 3: " << st_sum.query(1, 3) << endl; // 15
    st_sum.update(2, 10);
    cout << "After update, sum from 1 to 3: " << st_sum.query(1, 3) << endl; // 20
    
    // Example 2: Range Minimum Query using generic template
    vector<int> arr2 = {1, 3, 2, 7, 9, 11};
    SegmentTree<int> st_min(arr2, INT_MAX, [](int a, int b) { return min(a, b); });
    
    cout << "Minimum from index 1 to 4: " << st_min.query(1, 4) << endl; // 2
    
    // Example 3: Range Maximum Query
    SegmentTree<int> st_max(arr2, INT_MIN, [](int a, int b) { return max(a, b); });
    
    cout << "Maximum from index 0 to 3: " << st_max.query(0, 3) << endl; // 7
    
    return 0;
}