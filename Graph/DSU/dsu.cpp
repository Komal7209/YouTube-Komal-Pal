#include<bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size, rank;
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1); // initializing with size 1 for all // SC: O(n)
        rank.assign(n, 0); // initializing with rank 0 for all // SC: O(n)
        for(int i = 0; i < n; i++) parent[i] = i; // TC: O(n), SC: O(n)
    }

    // TC: O(n), SC:O(n)
    int simpleFind(int x){
        if (x == parent[x]) 
            return x;
        else
            return simpleFind(parent[x]);
    }

    // TC: O(α(n)) 
    /*
    α(n) = inverse Ackermann function
    → grows so slowly it is practically constant, ≤ 4 even for universe size.

    So:
    O(α(n)) ≈ O(1)

    SC (amortized): O(α(n))   ~ constant
    */
    int pathCompressionFind(int x) {
        if (x == parent[x]) return x;
        return parent[x] = pathCompressionFind(parent[x]);
    }

    // TC: O(n) (because find is O(n))
    void simpleUnion(int a, int b) {
        int rootA = simpleFind(a);
        int rootB = simpleFind(b);

        if (rootA != rootB) {
            parent[rootB] = rootA;  
        }
    }

    /*
    - Find calls: O(α(n)) each → 2 * O(α(n))
    - Attach smaller tree to larger → O(1)
    Total Time Complexity: O(α(n)) ≈ O(1)
    , SC: O(α(n)) from recursion stack
    */
    void uniteBySize(int a, int b) {
        a = pathCompressionFind(a); b = pathCompressionFind(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    /*
    Same as union by size
    - 2 finds → O(α(n))
    - Constant-time union logic → O(1)
    Total Time Complexity: O(α(n)) ≈ O(1)
    , SC: O(α(n)) recursion
    */
    void uniteByRank(int a, int b) {
        a = pathCompressionFind(a); b = pathCompressionFind(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if(rank[a] == rank[b])
                rank[a]++;
        }
        
    }
};

/*
Time Complexity:

| Optimization                              | Time Complexity          |
| ----------------------------------------- | ------------------------ |
| Union by size/rank only                   | O(log n)                 |
| Path compression only                     | O(log n) (amortized)     |
| Union by size/rank + path compression     | ⭐ O(α(n)) ≈ constant    |

*/


/*

union(1,2)
union(2,3)
union(3,4)
union(4,5)



1) Naive DSU (Tall / Skewed)          2) DSU After Union by Rank/Size         3) DSU After Path Compression (Star)

1                                     1                                       Root
 └─2                                   ├─2                                      ├─2
    └─3                                └─3                                      ├─3
       └─4                                 └─4                                   ├─4
          └─5                                  └─5                                ├─5
                                                                                  └─6




- Naive:

Height = O(n)
Worst-case find(5) takes 5 recursive calls
Continuing like this gives height up to n
No rank, no size, no compression
Worst-case height = n
find() = O(n)

- After Union by Rank/Size Only — Balanced Tree:

Trees are balanced, but still have height
find() = O(log n) worst-case
No path compression yet

- After Path Compression — Star Shape

Height = O(α(n)) ≈ constant
All nodes become direct children of the root
Future find() calls take 1 or 2 steps
All nodes become direct children of the root
Depth ≈ 1
find() = O(α(n)) ≈ constant
This is the final optimized DSU structure


*/