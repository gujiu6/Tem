#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
using i64 = long long;





template <typename T = i64>
class BIT {
    int n, lg2;
    vector<T> tree;
    inline int lowbit(int i) {
        return i & -i;
    }
    BIT(int n): n(n), tree(n + 1, 0), lg2(__lg(n)) {}
    BIT(vector<T>& a): n(a.size() - 1), BIT(n) {
        for(int i = 1; i <= n; i++) {
            tree[i] += a[i];
            int j = i + lowbit(i);
            if(j <= n) tree[j] += tree[i];
        }
    }
    void add(int i, T v) {
        while(i <= n){
            tree[i] += v;
            i += lowbit(i);
        }
    }
    T qry(int i) {
        T ans = 0;
        while(i > 0) {
            ans += tree[i];
            i -= lowbit(i);
        }
        return ans;
    }
    T range_qry(int left, int right) {
        return qry(right) - qry(left - 1);
    }
    //查询第k小元素位置
    int kth(int k) {
        int pos = 0;
        int pw = 1 << lg2;
        for(int p = pw; p > 0; p >>= 1) {
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




