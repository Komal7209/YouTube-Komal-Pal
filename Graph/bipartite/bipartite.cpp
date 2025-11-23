// A graph is bipartite if we can:
// Divide all nodes into two groups such that
// No two adjacent nodes belong to the same group.

/*

Steps for Bipartite:

1. Color unvisited node as 0
2. BFS/DFS & color neighbors as 1
3. If neighbor has same color → Not Bipartite
4. Repeat for all components


*/


/*

✅ Time Complexity

Let:

V = number of vertices

E = number of edges

O(V+E)
Because each node and each edge is visited once.

======================

✅ Space Complexity

Color array → O(V)

Queue → O(V)

O(V)
	
*/

// bfs version
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);   // -1 = uncolored, 0 and 1 = 2 colors
    
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {

            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbour : graph[node]) {

                    // If neighbour not colored, color it opposite
                    if (color[neighbour] == -1) {
                        color[neighbour] = 1 - color[node];
                        q.push(neighbour);
                    }

                    // If neighbour has same color => NOT Bipartite
                    else if (color[neighbour] == color[node]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}


// dfs version: 

bool dfs(int node, int c, vector<int> &color, vector<vector<int>> &graph) {
    color[node] = c;

    for (int neighbour : graph[node]) {
        if (color[neighbour] == -1) {
            if (!dfs(neighbour, 1 - c, color, graph))
                return false;
        }
        else if (color[neighbour] == c) {
            return false;
        }
    }

    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!dfs(i, 0, color, graph))
                return false;
        }
    }
    return true;
}
