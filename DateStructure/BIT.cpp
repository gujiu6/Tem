#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
using i64 = long long;





template <typename T = i64>
class BIT {
    int n;
    vector<T> tree, a;
    BIT(int n): n(n), tree(n + 1, 0) {}
    BIT(const vector<T>& a):a(a), n(a.size() - 1), tree(n + 1, 0) {
        for(int i = 1; i <= n; i++) {
            tree[i] += a[i];
            int j = i + lowbit(i);
            if(j <= n) tree[j] += tree[i];
        }
    }
    inline int lowbit(int i) {
        return i & -i;
    }
    void add(int i, T v) {
        while(i <= n){
            tree[i] += v;
            i += lowbit(i);
        }
    }
    void set(int i, T v) {
        add(i, v - a[i]);
        a[i] = v;
    }
    T sum(int i) const{
        T ans = 0;
        while(i > 0) {
            ans += tree[i];
            i -= lowbit(i);
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
            if(nxt <= n && tree[nxt] < k) {
                pos = nxt;
                k -= tree[nxt];
            }
        }
        return pos + 1;
    }
    void clear() {
        fill(tree.begin(), tree.end(), 0);
    }
};




