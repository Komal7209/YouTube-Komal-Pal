class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return false;

        if (rankv[px] < rankv[py])
            parent[px] = py;
        else if (rankv[px] > rankv[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rankv[px]++;
        }

        return true;
    }
};

class Solution {
public:
    int kruskal(int n, vector<vector<int>>& edges) {

        // Sort edges by weight
        sort(edges.begin(), edges.end(),
            [](vector<int>& a, vector<int>& b){
                return a[2] < b[2];
            });

        DSU dsu(n);
        int mstWeight = 0;
        int count = 0;

        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];

            if (dsu.unite(u, v)) {   // if no cycle is formed
                mstWeight += w;
                count++;

                if (count == n - 1)
                    break;
            }
        }

        return mstWeight;
    }
};
/*

Steps:

Sort all edges in increasing order of weight.

Pick the smallest edge first.

Add it only if it does NOT create a cycle.

Use DSU (Union-Find) to quickly check cycle.

Stop after using n − 1 edges.

*/

/*
edges:

(0-1,1), (1-2,2), (0-2,3)


sorted:
(0-1,1) ✅
(1-2,2) ✅
(0-2,3) ❌ (cycle)

MST: 1 + 2 = 3

*/