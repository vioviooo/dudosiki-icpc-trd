// Space optimized - O(W) space
int knapsack_01_optimized(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        // Traverse backwards to avoid reusing items
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}


// Unbounded knapsack - items can be used multiple times
int unbounded_knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<int> dp(W + 1, 0);
    
    for (int w = 1; w <= W; w++) {
        for (int i = 0; i < n; i++) {
            if (wt[i] <= w) {
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }
    }
    return dp[W];
}

class Knapsack {
public:
    // 0/1 Knapsack with reconstruction
    static int knapsack_01(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];
                if (w >= wt[i - 1]) {
                    dp[i][w] = max(dp[i][w], 
                                  val[i - 1] + dp[i - 1][w - wt[i - 1]]);
                }
            }
        }
        return dp[n][W];
    }
    
    // Get selected items
    static vector<int> getSelectedItems(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        
        for (int i = 1; i <= n; i++) {
            for (int w = 0; w <= W; w++) {
                dp[i][w] = dp[i - 1][w];
                if (w >= wt[i - 1]) {
                    dp[i][w] = max(dp[i][w], 
                                  val[i - 1] + dp[i - 1][w - wt[i - 1]]);
                }
            }
        }
        
        vector<int> selected;
        int w = W;
        for (int i = n; i > 0 && w > 0; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                selected.push_back(i - 1);
                w -= wt[i - 1];
            }
        }
        reverse(selected.begin(), selected.end());
        return selected;
    }
    
    // Knapsack with large weight but small values
    static int knapsack_min_weight(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        int total_val = accumulate(val.begin(), val.end(), 0);
        vector<int> dp(total_val + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 0; i < n; i++) {
            for (int v = total_val; v >= val[i]; v--) {
                if (dp[v - val[i]] != INT_MAX) {
                    dp[v] = min(dp[v], dp[v - val[i]] + wt[i]);
                }
            }
        }
        
        int ans = 0;
        for (int v = total_val; v >= 0; v--) {
            if (dp[v] <= W) {
                ans = v;
                break;
            }
        }
        return ans;
    }
    
    // Count number of ways to achieve exactly weight W
    static int countWays(int W, vector<int>& wt) {
        vector<int> dp(W + 1, 0);
        dp[0] = 1;
        
        for (int weight : wt) {
            for (int w = W; w >= weight; w--) {
                dp[w] += dp[w - weight];
            }
        }
        return dp[W];
    }
};

// Example usage
int main() {
    // Example 1: Basic 0/1 Knapsack
    vector<int> wt = {1, 3, 4, 5};
    vector<int> val = {1, 4, 5, 7};
    int W = 7;
    
    cout << "0/1 Knapsack: " << Knapsack::knapsack_01(W, wt, val) << endl;
    
    // Example 2: Get selected items
    auto selected = Knapsack::getSelectedItems(W, wt, val);
    cout << "Selected items: ";
    for (int idx : selected) {
        cout << idx << " ";
    }
    cout << endl;
    
    // Example 3: Count ways
    cout << "Number of ways: " << Knapsack::countWays(W, wt) << endl;
    
    return 0;
}