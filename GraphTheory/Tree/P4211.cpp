#include <bits/stdc++.h>
#include <cassert>
//#include <ranges>
using namespace std;
#define ONLINE_JUDGE
#define endl '\n'
#define int long long
#define all(A,i) A.begin()+i, A.end()
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define per(i,r,l) for(int i=r;i>=l;i--)
#define dbg(x) cout<<#x<<"="<<x<<endl;
using i64 = long long;
using i128 = __int128;
using ld = long double;
using u64 = unsigned long long;
using cd = complex<double>;
using pii = array<int, 2>;
constexpr i64 INF = 1e18;
constexpr int MOD = 201314;
constexpr int MAXX = 2e5+10, LIMIT = 20;
constexpr ld eps = 1e-6;
const ld PI = acos(-1);
constexpr int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
constexpr int dx8[]={0,0,1,1,1,-1,-1,-1}, dy8[]={1,-1,-1,0,1,-1,0,1};
struct WEdge {int v;i64 w = 0;};struct DEdge {int u, v;i64 w = 0;};struct Edge {int v;};


class HLD {
public:
    int n, tim = 0;
    vector<int> fa, dep, sz, son, top, in, rev;
    HLD (const vector<vector<Edge>>& g, const int& root = 1): n(g.size() - 1), fa(n + 1), dep(n + 1), sz(n + 1, 1), son(n + 1), top(n + 1), in(n + 1), rev(n + 1) {
        sz[0] = 0;
        vector<int> ord{root};
        for(int i = 0; i < ord.size(); i++) {
            int u = ord[i];
            for(const auto &e : g[u]) {
                if(e.v == fa[u]) continue;
                fa[e.v] = u;
                dep[e.v] = dep[u] + 1;
                ord.push_back(e.v);
            }
        }
        for(int i = n - 1; i >= 0; i--) {
            int &u = ord[i], &f = fa[u];
            sz[f] += sz[u];
            if(sz[u] > sz[son[f]]) {
                son[f] = u;
            }
        }
        auto dfs = [&](auto &&self, int u, int h)->void {
            top[u] = h;
            in[u] = ++tim;
            rev[tim] = u;
            if(son[u]) {
                self(self, son[u], h);
            }
            for(const auto &e : g[u]) {
                if(e.v == fa[u] || e.v == son[u]) continue;
                self(self, e.v, e.v);
            }
        };
        if(n) dfs(dfs, root, root);
    }
    int lca(int u, int v) const {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    template <class F> void path(int u, int v, F op, bool edge = false) const {
        vector<pair<int, int>> right;
        while(top[u] != top[v]) {
            if(dep[top[u]] >= dep[top[v]]) {
                op(in[top[u]], in[u], true);
                u = fa[top[u]];
            }
            else {
                right.push_back({in[top[v]], in[v]});
                v = fa[top[v]];
            }
        }
        if(dep[u] >= dep[v]) {
            op(in[v] + edge, in[u], true);
        }
        else {
            right.push_back({in[u] + edge, in[v]});
        }
        reverse(right.begin(), right.end());
        for(const auto &[l, r] : right) {
            op(l, r, false);
        }
    }
};

struct Tag {
    bool has_set = false;
    i64 set = 0;
    i64 add = 0;
    // 先执行当前 Tag，再执行 t
    void apply(const Tag& t) {
        if(t.has_set) {
            has_set = true;
            set = t.set;
            add = t.add;
        }
        else {
            add += t.add;
        }
    }
};
struct Info {
    i64 sum = 0;
    int len = 0;
    Info() = default;
    Info(i64 x) {
        sum = x;
        len = 1;
    }
    void apply(const Tag& t) {
        if(t.has_set) {
            sum = t.set * len;
        }
        sum += t.add * len;
    }
    friend Info operator+ (const Info& a, const Info& b) {
        Info c;
        c.sum = a.sum + b.sum;
        c.len = a.len + b.len;
        return c;
    }
};
template <class Info = Info, class Tag = Tag>
class LazySeg {
public:
    int n;
    vector<Info> tr;
    vector<Tag> tag;
    LazySeg(int n = 0) {init(n);}
    LazySeg(const vector<Info>& a){init(a);}
    void init(const int& _n) {
        n = _n;
        tr.assign((n << 2) + 4, Info{});
        tag.assign((n << 2) + 4, Tag{});
        if(n) build(1, 1, n);
    }
    void init(const vector<Info>& a) {
        n = a.size() - 1;
        tr.assign((n << 2) + 4, Info{});
        tag.assign((n << 2) + 4, Tag{});
        if(n) build(1, 1, n, a);
    }
private:
    void build(int p, int l, int r) {
        tr[p].len = r - l + 1;
        tr[p].sum = 0;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
    void build(int p, int l, int r, const vector<Info>& a) {
        if(l == r) {
            tr[p] = a[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        pull(p);
    }
    void pull(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void apply(int p, const Tag& v) {
        tr[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(p << 1, tag[p]);
        apply(p << 1 | 1, tag[p]);
        tag[p] = Tag{};
    }
    void modify(int p, int l, int r, int ql, int qr, const Tag& v) {
        if(ql <= l && r <= qr) {
            apply(p, v);
            return;
        }
        push(p);
        int mid = (l + r) >> 1;
        if(ql <= mid) modify(p << 1, l, mid, ql, qr, v);
        if(qr > mid) modify(p << 1 | 1, mid + 1, r, ql, qr, v);
        pull(p);
    }
    Info qry(int p, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return tr[p];
        push(p);
        int mid = (l + r) >> 1;
        if(qr <= mid) return qry(p << 1, l, mid, ql, qr);
        if(ql > mid) return qry(p << 1 | 1, mid + 1, r, ql, qr);
        return qry(p << 1, l, mid, ql, qr) + qry(p << 1 | 1, mid + 1, r, ql, qr);
    }
public:
    // 区间加 x
    void add(int l, int r, i64 x) {
        modify(1, 1, n, l, r, Tag{.has_set = false, .set = 0, .add = x});
    }
    // 区间赋值 x
    void set(int l, int r, i64 x) {
        modify(1, 1, n, l, r, Tag{.has_set = true, .set = x, .add = 0});
    }
    // 区间信息
    Info qry(int l, int r) {
        return qry(1, 1, n, l, r);
    }
};

struct Q {
    int z;
    int id;
    int sgn;
};

inline void solve() {
    int n, m; cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    rep(i, 2, n) {
        int p; cin >> p; p++;
        g[p].push_back({i});
    }
    HLD hld(g);
    LazySeg seg(n);
    vector<i64> ans(m + 1);
    vector<vector<Q>> query(n + 1);
    rep(i, 1, m) {
        int l, r, z; cin >> l >> r >> z;
        l++;r++;z++;
        query[r].push_back({z, i, 1});
        if(l - 1 > 0) {
            query[l - 1].push_back({z, i, -1});
        }
    }
    for(int k = 1; k <= n; k++) {
        hld.path(1, k, [&](int l, int r, bool rev) {
            seg.add(l, r, 1);
        });
        for(auto &[z, id, sgn] : query[k]) {
            i64 sum = 0;
            hld.path(1, z, [&](int l, int r, int rev) {
                sum = (sum + seg.qry(l, r).sum) % MOD;
            });
            ans[id] = ((ans[id] + sum * sgn) % MOD + MOD) % MOD;
        }
    }
    for(int i = 1; i <= m; i++) cout << ans[i] << endl;
}







signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; i++){
    
        solve();
    
    }
    return 0;
}
// 难道我不配AC吗
//   ▄████  █    ██  ▄▄▄██▀▀▀██▓ █    ██
//  ██▒ ▀█▒ ██  ▓██▒   ▒██  ▓██▒ ██  ▓██▒
// ▒██░▄▄▄░▓██  ▒██░   ░██  ▒██▒▓██  ▒██░
// ░▓█  ██▓▓▓█  ░██░▓██▄██▓ ░██░▓▓█  ░██░
// ░▒▓███▀▒▒▒█████▓  ▓███▒  ░██░▒▒█████▓
//  ░▒   ▒ ░▒▓▒ ▒ ▒  ▒▓▒▒░  ░▓  ░▒▓▒ ▒ ▒
//   ░   ░ ░░▒░ ░ ░  ▒ ░▒░   ▒ ░░░▒░ ░ ░
//  ░   ░  ░░░ ░ ░  ░ ░ ░   ▒ ░ ░░░ ░ ░
//       ░    ░      ░   ░   ░     ░