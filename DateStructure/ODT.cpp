//ODT珂朵莉树
#include <bits/stdc++.h>
using namespace std;
using ll = long long;


template<typename T = ll>
class ODT {
private:
    struct Node {
        int l, r;
        mutable T val;
        Node(int l, int r, T val): l(l), r(r), val(val) {}
        bool operator< (const Node& other)const {
            return l < other.l;
        }
    };
    set<Node> s;
    auto split(int pos) {
        auto it = prev(s.upper_bound(Node(pos, 0, 0)));
        if(it->l == pos)
            return it;
        int l = it->l;
        int r = it->r;
        T v = it->val;
        s.erase(it);
        s.insert(Node(l, pos - 1, v));
        return s.insert(Node(pos, r, v)).first;
    }

    auto merge(auto it) {
        if(it != s.begin()) {
            auto pre = prev(it);
            if(pre->r + 1 == it->l && pre->val == it->val){
                int l = pre->l;
                int r = it->r;
                T v = it->val;
                s.erase(pre);
                s.erase(it);
                it = s.insert(Node(l, r, v)).first;
            }
        }
        auto nxt = next(it);
        if(nxt!=s.end()) {
            if(it->r + 1 == nxt->l && it->val == nxt->val) {
                int l = it->l;
                int r = nxt->r;
                T v = it->val;
                s.erase(it);
                s.erase(nxt);
                it = s.insert(Node(l, r, v)).first;
            }
        }
        return it;
    }

    T power(T a, ll b, T mod) {
        T ans=1;
        while(b) {
            if(b & 1) ans = ans * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return ans;
    }
public:
    ODT(){}
    ODT(int n, T v) {
        s.insert(Node(1, n, v));
    }
    ODT(vector<T>& arr) {
        int n = arr.size() - 1;
        int l = 1;
        for(int i = 2; i <= n + 1; i++) {
            if(i == n + 1 || arr[i] != arr[l]) {
                s.insert(Node(l, i-1, arr[l]));
                l = i;
            }
        }
    }

    void assign(int l, int r, T v) {
        auto R = split(r + 1);
        auto L = split(l);
        s.erase(L, R);
        auto it = s.insert(Node(l , r, v)).first;
        merge(it);
    }

    void add(int l, int r, T v) {
        auto R = split(r + 1);
        auto L = split(l);
        for(auto it = L; it != R; it++) {
            it->val += v;
        }
    }
    T qry(int pos) {
        auto it = prev(s.upper_bound(Node(pos, 0, 0)));
        return it->val;
    }

    T sum(int l, int r) {
        T ans = 0;
        auto R = split(r + 1);
        auto L = split(l);
        for(auto it = L; it != R; it++){
            ans += (T)(it->r - it->l + 1) * it->val;
        }
        return ans;
    }

    T kth(int l, int r, int k) {
        vector<pair<T, int>> v;
        auto R = split(r + 1);
        auto L = split(l);
        for(auto it = L; it != R; it++){
            v.push_back({it->val, it->r - it->l + 1});
        }
        sort(v.begin(), v.end());
        for(auto [x, cnt] : v){
            if(k <= cnt)
                return x;
            k -= cnt;
        }
        return T();
    }

    T power_sum(int l, int r, ll k, ll mod) {
        T ans = 0;
        auto R = split(r + 1);
        auto L = split(l);
        for(auto it = L; it != R; it++){
            ans = (ans + (T)(it->r - it->l + 1) * power(it->val, k, mod)) % mod;
        }
        return ans;
    }

    void debug() {
        for(auto [l, r, v]:s) {
            cout << "[" << l << "," << r << "] " << v << endl;
        }
    }

};