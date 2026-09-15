/*
1.单点修改/赋值,区间/前缀和
2.区间修改, 区间和
3.二维树状数组
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
const int MAXX=2e5;
using i64 = long long;




// 1.单点修改/赋值,区间/前缀和
template <typename T = i64>
class Bit1 {
public:
    int n;
    vector<T> bit, a;
    Bit1(int n): n(n), a(n + 1), bit(n + 1) {}
    Bit1(const vector<T>& a):a(a), n(a.size() - 1), bit(n + 1) {
        for(int i = 1; i <= n; i++) {
            bit[i] += a[i];
            int j = i + lowbit(i);
            if(j <= n) bit[j] += bit[i];
        }
    }
    inline int lowbit(int p) {
        return p & -p;
    }
    void add(int p, T v) {
        while(p <= n){
            bit[p] += v;
            p += lowbit(p);
        }
    }
    void set(int p, T v) {
        add(p, v - a[p]);
        a[p] = v;
    }
    T sum(int p) const{
        T ans = 0;
        while(p > 0) {
            ans += bit[p];
            p -= lowbit(p);
        }
        return ans;
    }
    T sum(int l, int r) const{
        return sum(r) - sum(l - 1);
    }
    //查询第k小元素位置(权值BIT)
    int kth(int k) const{
        int pos = 0;
        for(int p = bit_floor(unsigned(n)); p > 0; p >>= 1) {
            int nxt = pos + p;
            if(nxt <= n && bit[nxt] < k) {
                pos = nxt;
                k -= bit[nxt];
            }
        }
        return pos + 1;
    }
};

// 2.区间修改, 区间和
template <class T = i64>
class Bit2 {
public:
    int n;
    vector<T> bit1, bit2;
    Bit2(int n): n(n), bit1(n + 2), bit2(n + 2) {}
    Bit2(const vector<T>& a): n(a.size() - 1), bit1(n + 2), bit2(n + 2) {
        for(int i = 1; i <= n; i++) {
            range_add(i, i, a[i]);
        }
    }
    inline int lowbit(int p) {
        return p & -p;
    }
    void add(vector<T>& bit, int p, T v) {
        while(p <= n){
            bit[p] += v;
            p += lowbit(p);
        }
    }
    T sum(const vector<T>& bit, int p) const {
        T ans = 0;
        while(p > 0) {
            ans += bit[p];
            p -= lowbit(p);
        }
        return ans;
    }
    void range_add(int l, int r, T v) {
        add(bit1, l, v);
        add(bit1, r + 1, -v);
        add(bit2, l, v * (l - 1));
        add(bit2, r + 1, -v * r);
    }
    T sum(int p) const {
        return sum(bit1, p) * p - sum(bit2, p);
    }
    T sum(int l, int r) const{
        return sum(r) - sum(l - 1);
    }
};

// 3.二维树状数组
template <typename T = i64>
class Bit3 {
public:
    vector<int> xs;
    vector<vector<int>> ys;
    vector<vector<T>> bit;
    int n;
    Bit3(const vector<pair<int, int>> &pts = {}) {
        for(const auto &[x, y] : pts) {
            xs.emplace_back(x);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        ys.assign(n + 1, {});
        for(const auto &[x, y] : pts) {
            int px = lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
            while(px <= n) {
                ys[px].emplace_back(y);
                px += lower_bit(px);
            }
        }
        bit.resize(n + 1);
        for(int px = 1; px <= n; px++) {
            auto &v = ys[px];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            bit[px].assign(v.size() + 1, 0);
        }
    }
    int lower_bit(int p) {
        return p & -p;
    }
    void add(int x, int y, T v) {
        auto it = lower_bound(xs.begin(), xs.end(), v);
        assert(it != xs.end() && *it == x);
        int px = it - xs.begin() + 1;
        while(px <= n) {
            it = lower_bound(ys[px].begin(), ys[px].end(), y);
            assert(it != ys[px].end() && *it == y);
            int py = it - ys[px].begin() + 1;
            while(py < bit[px].size()) {
                bit[px][py] += v;
                py += lower_bit(py);
            }
            px += lower_bit(px);
        }
    }
    void add(int x1, int y1, int x2, int y2, T v) {
        assert(x1 <= x2 && y1 <= y2);
        add(x1, y1, v);
        add(x1, y2 + 1, -v);
        add(x2 + 1, y1, -v);
        add(x2 + 1, y2 + 1, v);
    }
    T sum(int x, int y) const{
        T ans = 0;
        int px = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        while(px > 0) {
            int py = lower_bound(ys[px].begin(), ys[px].end(), y) - ys[px].begin();
            while(py > 0) {
                ans += bit[px][py];
                py -= lower_bit(py);
            }
            px -= lower_bit(px);
        }
        return ans;
    }
    T qry(int x, int y) const {
        return sum(x + 1, y + 1);
    }
};