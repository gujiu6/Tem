/*
1.单点修改线段树
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;


//1.单点修改线段树
struct Sum {
    i64 val = 0;
    Sum() = default;
    Sum(i64 x): val(x) {}
    friend Sum operator+ (const Sum& a, const Sum& b) {
        return Sum(a.val + b.val);
    }
};
template <class Info>
struct Seg {
    int n;
    vector<Info> tr;
    Seg(int n = 0) {init(n);}
    Seg(const vector<Info>& a){init(a);}
    void init(const int& _n) {
        n = _n;
        tr.assign((n << 1) + 2, Info{});
    }
    void init(const vector<Info>& a) {
        n = a.size() - 1;
        tr.assign((n << 1) + 2, Info{});
        for(int i = 1; i <= n; i++) {
            tr[n + i - 1] = a[i];
        }
        for(int i = n - 1; i >= 1; i--) {
            pull(i);
        }
    }
    void pull(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void set(int p, Info v) {
        p = p + n - 1;
        tr[p] = v;
        for(p >>= 1; p; p >>= 1) {
            pull(p);
        }
    }
    // 查询闭区间 [l, r]
    Info qry(int l, int r) const {
        Info x{}, y{};
        l = l + n - 1;
        r = r + n;
        while(l < r) {
            if(l & 1) {
                x = x + tr[l++];
            }
            if(r & 1) {
                y = tr[--r] + y ;
            }
            l >>= 1;
            r >>= 1;
        }
        return x + y;
    }
};