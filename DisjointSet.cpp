#include <vector>
using namespace std;

class DisjointSet {
    vector<int> parent, size;

    public:

    int set_count;
    
    DisjointSet (int max_value) {
        parent = vector<int>(max_value, -1);
        size = vector<int>(max_value);
        set_count = 0;
    }

    int root (int u) {
        if (parent[u] == -1) return -1;
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
        if (size[u] < size[v]) {
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        }
        else {
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        }
        set_count--;
    }

    bool find (int u, int v) {
        return root(u) == root(v);
    }

    int get_size(int u) {
        return size[root(u)];
    }
    
    void insert(int u) {
        if (u >= parent.size() || parent[u] != -1) return;
        parent[u] = u;
        size[u] = 1;
        set_count++;
    }
};
