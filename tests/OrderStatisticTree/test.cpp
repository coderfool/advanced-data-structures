#include <bits/stdc++.h>
#include "../../OrderStatisticTree.cpp"
using namespace std;

int main() {
    int tests = 3;
    fstream fin("tests/OrderStatisticTree/input", fstream::in); 
    fstream fout("tests/OrderStatisticTree/output", fstream::in);
    while (tests--) {
        int tc; fin >> tc;
        while (tc--) {
            int n; fin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; i++) fin >> a[i];
            OrderStatisticTree ost;
            int ans = 0, sz = 0;
            for (int x : a) {
                ost.insert(x);
                sz++;
                int low = ost.rank(x);
                int high = sz - low - ost.count(x);
                ans += min(low, high);
            }
            int expected; fout >> expected;
            if (ans != expected) return 1;
        }
    }
    return 0;
}