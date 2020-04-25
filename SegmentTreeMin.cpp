#include <vector>
#include <climits>
using namespace std;

class SegmentTreeMin {
    
    vector<int> tree, lazy_updates;
    int size = 0;
    
    void build_tree(int pos, vector<int>& arr, int low, int high) {
        if (low == high) {
            tree[pos] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build_tree(2 * pos + 1, arr, low, mid);
        build_tree(2 * pos + 2, arr, mid + 1, high);
        tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
    }
    
    int get_min(int pos, int l, int r, int low, int high) {
        if (lazy_updates[pos] != 0) {
            tree[pos] += lazy_updates[pos];
            if (low != high) {
                lazy_updates[2 * pos + 1] += lazy_updates[pos];
                lazy_updates[2 * pos + 2] += lazy_updates[pos];
            }
            lazy_updates[pos] = 0;
        }
        if (high < l || low > r) {
            return INT_MAX;
        }
        if (l <= low && high <= r) {
            return tree[pos];
        }
        int mid = (low + high) / 2;
        int min_l = get_min(2 * pos + 1, l, r, low, mid);
        int min_r = get_min(2 * pos + 2, l, r, mid + 1, high);
        return min(min_l, min_r);
    }
    
    void set_util(int pos, int idx, int val, int low, int high) {
        if (low == high) {
            tree[pos] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (idx <= mid) {
            set_util(2 * pos + 1, idx, val, low, mid);
        }
        else {
            set_util(2 * pos + 2, idx, val, mid + 1, high);
        }
        tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
    }

    void lazy_update(int pos, int l, int r, int val, int low, int high) {
        if (lazy_updates[pos] != 0) {
            tree[pos] += lazy_updates[pos];
            if (low != high) {
                lazy_updates[2 * pos + 2] += lazy_updates[pos];
                lazy_updates[2 * pos + 1] += lazy_updates[pos];
            }
            lazy_updates[pos] = 0;
        }
        if (high < l || low > r) {
            return;
        }
        if (l <= low && high <= r) {
            tree[pos] += val;
            if (low != high) {
                lazy_updates[2 * pos + 1] += val;
                lazy_updates[2 * pos + 2] += val;
            }
            return;
        }
        int mid = (low + high) / 2;
        lazy_update(2 * pos + 1, l, r, val, low, mid);
        lazy_update(2 * pos + 2, l, r, val, mid + 1, high);
        tree[pos] = min(tree[2 * pos + 1], tree[2 * pos + 2]);
    }
    
    public:
    
    SegmentTreeMin(vector<int> arr) {
        size = arr.size();
        tree = vector<int>(4 * size);
        lazy_updates = vector<int>(4 * size);
        build_tree(0, arr, 0, size - 1);
    }
    
    int minimum(int left, int right) {
        if (left > right) {
            return INT_MAX;
        }
        return get_min(0, left, right, 0, size - 1);
    }
    
    void set(int idx, int val) {
        set_util(0, idx, val, 0, size - 1);
    }

    void increment(int left, int right, int val) {
        if (left > right) {
            return;
        }
        lazy_update(0, left, right, val, 0, size - 1);
    }
};
