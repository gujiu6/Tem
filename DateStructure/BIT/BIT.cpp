/*
1.单点修改/赋值,区间/前缀和
2.区间修改, 区间和
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
using i64 = long long;




//1.单点修改/赋值,区间/前缀和
template <typename T = i64>
class BIT1 {
public:
    int n;
    vector<T> bit, a;
    BIT1(int n) {init(n);}
    BIT1(const vector<T>& a) {init(a);}
    void init(const int& _n) {
        n = _n;
        a.assign(n + 1, 0);
        bit.assign(n + 1, 0);
    }
    void init(const vector<T>& _a) {
        a = _a;
        n = (a.size() - 1);
        bit.assign(n + 1, 0);
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

//2.区间修改, 区间和
template <class T = i64>
class BIT2 {
public:
    int n;
    vector<T> bit1, bit2;
    BIT2(int n) {init(n);}
    BIT2(const vector<T>& a){init(a);}
    void init(const int& _n) {
        n = _n;
        bit1.assign(n + 2, 0);
        bit2.assign(n + 2, 0);
    }
    void init(const vector<T>& a) {
        n = a.size() - 1;
        bit1.assign(n + 2, 0);
        bit2.assign(n + 2, 0);
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

