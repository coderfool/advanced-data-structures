#include <vector>
using namespace std;

class DisjointSet {
    vector<int> parent, sz;

    public:

    DisjointSet (int size) {
        parent = vector<int>(size);
        sz = vector<int>(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    int root (int u) {
        while (u != parent[u]) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    }

    void join (int u, int v) {
        int root_u = root(u);
        int root_v = root(v);
        if (root_u == root_v) return;
        if (sz[u] < sz[v]) {
            parent[root_u] = root_v;
            sz[root_v] += sz[root_u];
        }
        else {
            parent[root_v] = root_u;
            sz[root_u] += sz[root_v];
        }
    }

    bool find (int u, int v) {
        return root(u) == root(v);
    }

    int size(int u) {
        return sz[root(u)];
    }
};