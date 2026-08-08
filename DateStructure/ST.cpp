#include <bits/stdc++.h>
#include <cassert>
#include <bit>
using namespace std;
const int INF = 1e9+7;


//普通ST
template <class T , class F>
struct ST1 {
    int n, lg2;
    vector<vector<T>> st;
    F op;
    ST1(const vector<T>& a, F f = {}): n(a.size() - 1), op(f) {
        lg2 = n ? bit_width(unsigned(n)) : 0;
        st.assign(lg2 + 1, vector<T>(n + 1));
        if(!n) return;
        st[0] = a;
        for(int p = 1; p <= lg2; p++) {
            for(int i = 1; i + (1LL << p) - 1 <= n; i++) {
                st[p][i] = op(st[p - 1][i], st[p - 1][i + (1LL << (p - 1))]);
            }
        }
    }

    T qry(int l, int r) const {
        assert(1 <= l && l <= r && r <= n);
        int p = bit_width(unsigned(r - l + 1)) - 1;
        T ans = op(st[p][l], st[p][r - (1LL << p) + 1]);
        return ans;
    }
};
