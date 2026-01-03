/*
Problem Reminder (0/1 Knapsack)

wt[i] = weight of item i
val[i] = value of item i => item code
W = knapsack capacity

Each item can be taken once or not taken

*/

/*
Recursion Idea

At every item, choose:
- take it (if weight allows)
- don’t take it

Time: O(2^n)
Space: O(n) (recursion stack)
*/

//  n = wt.size(), idx =n 
int knapsackRec(int idx, int W, vector<int>& wt, vector<int>& val) {
    // Base case
    if (idx == 0) {
        if (wt[0] <= W)
            return val[0];
        return 0;
    }

    // Not take
    int notTake = knapsackRec(idx - 1, W, wt, val);

    // Take
    int take = 0;
    if (wt[idx] <= W)
        take = val[idx] + knapsackRec(idx - 1, W - wt[idx], wt, val);

    return max(take, notTake);
}

// call
// int n = wt.size();
// int ans = knapsackRec(n - 1, W, wt, val);

/*
Memoization (Top-Down DP) Idea:

Store results of (idx, W) so we don’t recompute.

Time: O(n * W)
Space: O(n * W) + recursion stack
*/

int knapsackMemo(int idx, int W,
                 vector<int>& wt, vector<int>& val,
                 vector<vector<int>>& dp) {
    if (idx == 0) {
        if (wt[0] <= W)
            return val[0];
        return 0;
    }

    if (dp[idx][W] != -1)
        return dp[idx][W];

    int notTake = knapsackMemo(idx - 1, W, wt, val, dp);

    int take = 0;
    if (wt[idx] <= W)
        take = val[idx] +
               knapsackMemo(idx - 1, W - wt[idx], wt, val, dp);

    return dp[idx][W] = max(take, notTake);
}

// call
// vector<vector<int>> dp(n, vector<int>(W + 1, -1));
// int ans = knapsackMemo(n - 1, W, wt, val, dp);

/*

Bottom-Up DP (Tabulation) Idea:

Build solution from smaller subproblems

dp[i][w] → max value using items 0..i with capacity w

Time: O(n * W)
Space: O(n * W)
*/

int knapsackDP(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    // Base case
    for (int w = wt[0]; w <= W; w++) // loop for initialising only first item
        dp[0][w] = val[0];

    for (int i = 1; i < n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];
            int take = 0;
            if (wt[i] <= w)
                take = val[i] + dp[i - 1][w - wt[i]];

            dp[i][w] = max(take, notTake);
        }
    }

    return dp[n - 1][W];
}
