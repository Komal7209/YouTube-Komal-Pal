/*
Problem:

You are given:
wt[i] → weight of item i
val[i] → value of item i
W → knapsack capacity

You can take unlimited copies of each item.
*/

/*
Recursive Idea:
For each item:
Take it → stay on same index (because unbounded)
Skip it → move to next item

State
solve(i, remainingWeight)

Base Cases
if (i == n || remainingWeight == 0) return 0;
*/

class Solution {
public:
    int solve(int i, int W, vector<int>& wt, vector<int>& val) {
        if (i == wt.size() || W == 0)
            return 0;

        int notTake = solve(i + 1, W, wt, val);

        int take = 0;
        if (wt[i] <= W) {
            // NOTE: i stays same → unbounded
            take = val[i] + solve(i, W - wt[i], wt, val);
        }

        return max(take, notTake);
    }

    int unboundedKnapsack(int W, vector<int>& wt, vector<int>& val) {
        return solve(0, W, wt, val);
    }
};

/*

Memoization: Same (i, W) states repeat many times.
DP State: dp[i][W] = maximum value

Time: O(n × W)
Space: O(n × W)

*/

class Solution {
public:
    int dp[101][1001];

    int solve(int i, int W, vector<int>& wt, vector<int>& val) {
        if (i == wt.size() || W == 0)
            return 0;

        if (dp[i][W] != -1)
            return dp[i][W];

        int notTake = solve(i + 1, W, wt, val);

        int take = 0;
        if (wt[i] <= W) {
            take = val[i] + solve(i, W - wt[i], wt, val);
        }

        return dp[i][W] = max(take, notTake);
    }

    int unboundedKnapsack(int W, vector<int>& wt, vector<int>& val) {
        memset(dp, -1, sizeof(dp));
        return solve(0, W, wt, val);
    }
};


// Bottom Up DP:

// Time: O(n × W)
// Space: O(W) (optimal)

/*
| Knapsack Type | Loop Direction |
| ------------- | -------------- |
| 0/1           | backward       |
| Unbounded     | forward        |

DP Definition: dp[w] = max value for capacity w
Transition: dp[w] = max(dp[w], val[i] + dp[w - wt[i]])
*/

class Solution {
public:
    int unboundedKnapsack(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        vector<int> dp(W + 1, 0);

        for (int i = 0; i < n; i++) {
            for (int w = wt[i]; w <= W; w++) {
                dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
            }
        }

        return dp[W];
    }
};
