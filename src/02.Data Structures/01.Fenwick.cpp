// а внутри пример кода
/*
 * Соблюдайте правила наименования разделов и файлов!
 * Сначала - номер, потом точка, потом без пробела название.
 * Слова в названии разделяются минусами. Пробелы и подчеркивания в названиях файлов не поддерживаются.
 */
class FenwickTree0Based {
private:
    vector<int> tree;
    int n;
    
public:
    FenwickTree0Based(int size) : n(size), tree(size + 1, 0) {}
    
    // Update: add 'value' at index 'idx' (0-based indexing)
    void update(int idx, int value) {
        idx++;  // Convert to 1-based
        while (idx <= n) {
            tree[idx] += value;
            idx += idx & -idx;
        }
    }
    
    // Query: prefix sum from 0 to 'idx' (0-based indexing)
    int query(int idx) {
        idx++;  // Convert to 1-based
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
    
    // Range query: sum from 'l' to 'r' (0-based indexing)
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
    
    // Get value at specific index
    int get(int idx) {
        return rangeQuery(idx, idx);
    }
    
    // Set value at specific index
    void set(int idx, int value) {
        int current = get(idx);
        update(idx, value - current);
    }
};

long long countInversions(vector<int>& arr) {
    int n = arr.size();
    
    // Coordinate compression
    vector<int> sorted = arr;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    
    FenwickTree ft(sorted.size());
    long long inversions = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        int pos = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin() + 1;
        inversions += ft.query(pos - 1);  // Count elements smaller than current
        ft.update(pos, 1);
    }
    
    return inversions;
}

class FenwickTree2D {
private:
    vector<vector<int>> tree;
    int n, m;
    
public:
    FenwickTree2D(int rows, int cols) {
        n = rows;
        m = cols;
        tree.resize(n + 1, vector<int>(m + 1, 0));
    }
    
    void update(int x, int y, int value) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                tree[i][j] += value;
            }
        }
    }
    
    int query(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    
    // Query sum from (x1,y1) to (x2,y2)
    int rangeQuery(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};