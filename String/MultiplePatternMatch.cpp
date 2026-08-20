/*Trie与多模式匹配
1.AC自动机
2.AC自动机fail树应用
3.子序列自动机(string)
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;



//1.AC自动机
template <int Alphabet, class F>
class AhoCorasick {
public:
    struct Node {
        array<int, Alphabet> child;//Trie原始边
        array<int, Alphabet> next;//AC自动机补全后的转移
        int fail = 0;//失配指针
        bool bad = false;
        Node() {
            child.fill(-1);
            next.fill(0);
        }
    };
private:
    F Path;
    vector<Node> nodes{1};
    vector<int> endpoints;
public:
    AhoCorasick(F Path): Path(Path) {}
    //加入模式串,返回终点节点
    int insert(const string &s) {
        int cur = 0;
        for(const auto &c : s) {
            int path = Path(c);
            assert(0 <= path && path < Alphabet);
            if(nodes[cur].child[path] == -1) {
                nodes[cur].child[path] = nodes.size();
                nodes.push_back({});
            }
            cur = nodes[cur].child[path];
        }
        endpoints.push_back(cur);
        return cur;
    }
    //建立fail指针以及完整自动机转移
    void build() {
        queue<int> q;
        //根节点的真实儿子
        for(int path = 0; path < Alphabet; path++) {
            int child = nodes[0].child[path];
            if (child == -1) {
                continue;
            }
            nodes[0].next[path] = child;
            q.push(child);
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            //继承fail节点的自动机转移
            nodes[cur].bad |= nodes[nodes[cur].fail].bad;
            nodes[cur].next = nodes[nodes[cur].fail].next;
            for(int path = 0; path < Alphabet; ++path) {
                int child = nodes[cur].child[path];
                if(child == -1) {
                    continue;
                }
                // 建立 fail 指针
                nodes[child].fail = nodes[cur].next[path];
                // 真实边覆盖自动机默认转移
                nodes[cur].next[path] = child;
                q.push(child);
            }
        }
    }
    //根据字符直接进行转移
    int transition(int cur, char c) const {
        int path = Path(c);
        assert(0 <= path && path < Alphabet);
        return nodes[cur].next[path];
    }
    //获取所有节点
    const vector<Node> &getNodes() const {
        return nodes;
    }
    //获取每个模式串的终点节点
    const vector<int> &getEndpoints() const {
        return endpoints;
    }
    //2.AC自动机fail树应用,建立FailTree:fail[u]->u
    vector<vector<int>> failTree() const {
        vector<vector<int>> g(nodes.size());
        for (int u = 1; u < (int)nodes.size(); ++u) {
            g[nodes[u].fail].push_back(u);
        }
        return g;
    }
    vector<int> count(const string &text) const {
        vector<int> cnt(nodes.size());
        //扫描文本统计直接到达每个状态的次数
        int state = 0;
        for(char c : text) {
            state = transition(state, c);
            cnt[state]++;
        }
        // 建立fail树
        auto g = failTree();
        // BFS得到fail树遍历顺序
        vector<int> order;
        order.reserve(nodes.size());
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : g[u]) {
                q.push(v);
            }
        }
        //逆序把子节点贡献累加到fail父节点
        for (int i = (int)order.size() - 1; i > 0; --i) {
            int u = order[i];
            cnt[nodes[u].fail] += cnt[u];
        }
        //按模式串加入顺序返回答案
        vector<int> ans;
        ans.reserve(endpoints.size());
        for (int u : endpoints) {
            ans.push_back(cnt[u]);
        }
        return ans;
    }
    bool hit(int cur) const {
        return nodes[cur].bad;
    }
};

//3.子序列自动机(string)
class SeqAuto {
private:
    static const int SIGMA = 26;
    vector<array<int, SIGMA>> nxt;
    string s;
    int n;
public:
    SeqAuto(string str) : s(" " + str), n(str.size()){
        nxt.assign(n + 2, {});
        for(int c = 0; c < SIGMA; c++) {
            nxt[n + 1][c] = n + 1; 
        }
        for(int i = n; i >= 1; i--) {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i] - 'a'] = i;
        }
    }
    //str为s的子序列
    bool check(string str) {
        int pos = 1;
        for(char ch : str) {
            pos = nxt[pos][ch - 'a'];
            if(pos == n + 1)
                return false;
            pos++;
        }
        return true;
    }
    //str最长匹配s的前缀序列
    int match(string str) {
        int pos = 1;
        for(int i = 0; i < str.size(); i++){
            pos = nxt[pos][str[i] - 'a'];
            if(pos == n + 1)
                return i;
            pos++;
        }
        return str.size();
    }
};