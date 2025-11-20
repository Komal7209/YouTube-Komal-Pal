#include<bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n);
        size.assign(n, 1);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};
