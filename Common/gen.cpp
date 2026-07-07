/**
 * gen.cpp — 对拍随机数据生成器
 * 用法: ./gen [seed] | ./brute
 *       ./gen [seed] > in.txt
 * 编译: g++ -O2 -o gen gen.cpp
 */

#include <bits/stdc++.h>
using namespace std;

mt19937 rng;

// ───────────────────────────────────────────────
//  基础随机原语
// ───────────────────────────────────────────────

// [l, r] 闭区间随机整数
int randint(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// [l, r] 闭区间随机长整数
long long randll(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// [0, 1) 随机浮点
double randf() {
    return uniform_real_distribution<double>(0.0, 1.0)(rng);
}

// ───────────────────────────────────────────────
//  序列生成
// ───────────────────────────────────────────────

// 生成长度为 n、值域 [l,r] 的随机整数序列
vector<int> randArray(int n, int l, int r) {
    vector<int> a(n);
    for (auto &x : a) x = randint(l, r);
    return a;
}

// 生成长度为 n 的随机排列
vector<int> randPerm(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// 生成长度为 n、值域 [l,r] 的不降序列
vector<int> randSorted(int n, int l, int r) {
    auto a = randArray(n, l, r);
    sort(a.begin(), a.end());
    return a;
}

// ───────────────────────────────────────────────
//  字符串生成
// ───────────────────────────────────────────────

// 生成长度为 n 的随机字符串，字符集 charset
string randStr(int n, const string &charset = "abcdefghijklmnopqrstuvwxyz") {
    string s(n, ' ');
    for (auto &c : s) c = charset[randint(0, charset.size() - 1)];
    return s;
}

// ───────────────────────────────────────────────
//  图生成
// ───────────────────────────────────────────────

// 随机无向图，n 个点、m 条边（允许重边/自环由 allowSelf 控制）
// 返回边列表 (u, v)，点从 1 开始
vector<pair<int,int>> randGraph(int n, int m, bool allowSelf = false) {
    vector<pair<int,int>> edges;
    edges.reserve(m);
    for (int i = 0; i < m; i++) {
        int u = randint(1, n);
        int v = randint(1, n);
        if (!allowSelf) while (v == u) v = randint(1, n);
        edges.emplace_back(u, v);
    }
    return edges;
}

// 随机树（n 个点，Prüfer 序列法），点从 1 开始
// 返回 n-1 条边
vector<pair<int,int>> randTree(int n) {
    if (n == 1) return {};
    // Prüfer sequence
    vector<int> prufer(n - 2);
    for (auto &x : prufer) x = randint(1, n);
    vector<int> deg(n + 1, 1);
    for (int x : prufer) deg[x]++;
    vector<pair<int,int>> edges;
    edges.reserve(n - 1);
    for (int x : prufer) {
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 1) {
                edges.emplace_back(i, x);
                deg[i]--; deg[x]--;
                break;
            }
        }
    }
    // 最后两个度为1的节点
    vector<int> last;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) last.push_back(i);
    edges.emplace_back(last[0], last[1]);
    return edges;
}

// 随机带权树，权值范围 [wl, wr]
vector<tuple<int,int,int>> randWeightedTree(int n, int wl, int wr) {
    auto edges = randTree(n);
    vector<tuple<int,int,int>> res;
    res.reserve(edges.size());
    for (auto [u, v] : edges)
        res.emplace_back(u, v, randint(wl, wr));
    return res;
}

// ───────────────────────────────────────────────
//  区间/查询生成
// ───────────────────────────────────────────────

// q 个随机区间查询 [l, r]，保证 l <= r，范围在 [1, n]
vector<pair<int,int>> randQueries(int q, int n) {
    vector<pair<int,int>> queries(q);
    for (auto &[l, r] : queries) {
        l = randint(1, n);
        r = randint(1, n);
        if (l > r) swap(l, r);
    }
    return queries;
}

// ───────────────────────────────────────────────
//  输出辅助
// ───────────────────────────────────────────────

template<typename T>
void printVec(const vector<T> &v, const string &sep = " ") {
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << sep;
    }
    cout << "\n";
}

// ───────────────────────────────────────────────
//  ★ 在这里写你的测试数据格式 ★
// ───────────────────────────────────────────────
void generate() {
    // ── 示例：n 个点的树 + q 次区间查询 + 节点权值 ──
    // （根据题目格式修改此函数即可，其余部分无需改动）

    // int n = randint(3, 10);       // 节点数
    // int q = randint(1, 5);        // 查询数
    // int W = 100;                  // 权值上界

    // 第一行：n q
    // cout << n << " " << q << "\n";

    // 第二行：节点权值
    // auto w = randArray(n, 1, W);
    // printVec(w);

    // 接下来 n-1 行：树边
    // auto edges = randTree(n);
    // for (auto [u, v] : edges)
    //     cout << u << " " << v << "\n";

    // 接下来 q 行：区间查询
    // auto queries = randQueries(q, n);
    // for (auto [l, r] : queries)
    //     cout << l << " " << r << "\n";

    // 单纯的整数序列
    int n = randint(1, 100);
    auto a = randArray(n, 1, 10000);
    auto b = randArray(n, 1, 10000);
    auto c = randArray(n, 1, 10000);
    cout << n << "\n"; 
    printVec(a);
    printVec(b);
    printVec(c);

    // 随机排列
    // int n = randint(2, 8);
    // cout << n << "\n"; printVec(randPerm(n));

    // 随机图
    // int n = randint(3, 8), m = randint(n-1, min(n*(n-1)/2, 15));
    // auto G = randGraph(n, m);
    // cout << n << " " << m << "\n";
    // for (auto [u,v] : G) cout << u << " " << v << "\n";

    // 字符串
    // int n = randint(1, 10);
    // cout << n << "\n" << randStr(n, "abc") << "\n";

    
}

// ───────────────────────────────────────────────
//  主函数（不需要修改）
// ───────────────────────────────────────────────
int main(int argc, char *argv[]) {
    unsigned seed = (argc > 1) ? atoi(argv[1]) : random_device{}();
    rng.seed(seed);
    cerr << "[gen] seed = " << seed << "\n";   // 方便复现 bug
    generate();
    return 0;
}
