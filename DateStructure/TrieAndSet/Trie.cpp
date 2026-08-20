/*
1.Trie
2.01Trie
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;



//1.Trie
template <class F>
class Trie {
public:
    int n;
    F Path;
    vector<vector<int>> ch;
    vector<int> cnt, ed;
    Trie(int n, F Path): n(n), Path(Path) {
        newNode();//0号节点作为根
    }
private:
    //新建节点
    int newNode() {
        ch.emplace_back(vector<int>(n));
        cnt.emplace_back(0);
        ed.emplace_back(0);
        return ch.size() - 1;
    }
public:
    //插入字符串,返回终点节点
    int insert(const string& s) {
        int cur = 0;
        cnt[cur]++;
        for(const auto &c : s) {
            int path = Path(c);
            assert(0 <= path && path < n);
            if(!ch[cur][path]) {
                ch[cur][path] = newNode();
            }
            cur = ch[cur][path];
            cnt[cur]++;
        }
        ed[cur]++;
        return cur;
    }
    //查找字符串对应的终点节点,不存在返回 -1
    int find(const string& s) const {
        int cur = 0;
        for(const auto &c : s) {
            int path = Path(c);
            if(path < 0 || path >= n || !ch[cur][path]) {
                return -1;
            }
            cur = ch[cur][path];
        }
        return cur;
    }
    //返回s与Trie中任意字符串的最长公共前缀长度
    int lcp(const string& s) const {
        int cur = 0, res = 0;
        for(const auto &c : s) {
            int path = Path(c);
            if(path < 0 || path >= n || !ch[cur][path]) {
                break;
            }
            cur = ch[cur][path];
            res++;
        }
        return res;
    }
    //返回以s为前缀的字符串数量
    int prefixCnt(const string &s) const {
        int p = find(s);
        return p < 0 ? 0 : cnt[p];
    }
    //返回字符串s被完整插入的次数
    int stringCnt(const string &s) const {
        int p = find(s);
        return p < 0 ? 0 : ed[p];
    }
    // 删除字符串 s 一次
    bool erase(const string &s) {
        int cur = find(s);
        if (cur < 0 || ed[cur] == 0) {
            return false;
        }
        ed[cur]--;
        cur = 0;
        cnt[cur]--;
        for (const auto &c : s) {
            int path = Path(c);
            int q = ch[cur][path];
            //q已经没有任何字符串经过
            if(--cnt[q] == 0) {
                ch[cur][path] = 0;
                return true;
            }
            cur = q;
        }
        return true;
    }
};

//2.01Trie
template <int W = 30>
class BinaryTrie{
public:
    using Node = array<int, 3>;// Node[0],Node[1]：0/1 儿子,Node[2]：经过该节点的元素个数
    vector<Node> tr;//tr[0]:空节点,tr[1]:根节点
    //n:预计插入次数,仅用于 reserve
    BinaryTrie(const int n = 0){
        static_assert(1 <= W && W <= 64);
        if(n) {
            tr.reserve(1LL * n * (W + 1) + 2);
        }
        clear();
    }
private:
    int newNode() {
        tr.push_back({});
        return (int)tr.size() - 1;
    }
public:
    //判断x是否能用W位无符号整数表示
    bool valid(const u64& x) const{
        if constexpr (W == 64){
            return true;
        }
        else{
            return x < (1ULL << W);
        }
    }
    //当前元素总数,重复元素重复计算
    int size() const{
        return tr[1][2];
    }
    bool empty() const{
        return size() == 0;
    }
    void clear(){
        tr.clear();
        newNode(); // 0：空节点
        newNode(); // 1：根节点
    }
    //查询x出现次数
    int count(const u64& x) const{
        assert(valid(x));
        int p = 1;
        for (int i = W - 1; i >= 0; i--){
            int b = x >> i & 1;
            p = tr[p][b];
            if (!p){
                return 0;
            }
        }
        return tr[p][2];
    }
    //插入x,共插入v次
    void insert(const u64& x, const int& v = 1){
        assert(valid(x) && v > 0);
        int p = 1;
        tr[p][2] += v;
        for (int i = W - 1; i >= 0; i--){
            int b = x >> i & 1;
            if (!tr[p][b]){
                tr[p][b] = newNode();
            }

            p = tr[p][b];
            tr[p][2] += v;
        }
    }
    //返回 max(x xor y)
    u64 maxXor(const u64& x) const{
        assert(valid(x) && !empty());
        int p = 1;
        u64 ans = 0;
        for (int i = W - 1; i >= 0; i--){
            int b = x >> i & 1;
            int q = tr[p][b ^ 1];
            //优先走不同的位
            int c = (q && tr[q][2]) ? (b ^ 1) : b;
            if (c != b){
                ans |= 1ULL << i;
            }
            p = tr[p][c];
        }
        return ans;
    }
    //返回使x xor y最大的 y
    u64 maxElement(const u64& x) const{
        return x ^ maxXor(x);
    }
    // 返回 min(x xor y)
    u64 minXor(const u64& x) const{
        assert(valid(x) && !empty());
        int p = 1;
        u64 ans = 0;
        for (int i = W - 1; i >= 0; i--){
            int b = x >> i & 1;
            int q = tr[p][b];
            //优先走相同的位
            int c = (q && tr[q][2]) ? b : (b ^ 1);
            if (c != b){
                ans |= 1ULL << i;
            }
            p = tr[p][c];
        }
        return ans;
    }
    // 返回使 x xor y 最小的 y
    u64 minElement(const u64& x) const{
        return x ^ minXor(x);
    }
    //返回第k小的x xor y;k 从 0 开始
    u64 kthXor(const u64& x, int k) const{
        assert(valid(x) && 0 <= k && k < size());
        int p = 1;
        unsigned long long ans = 0;
        for (int i = W - 1; i >= 0; i--){
            int b = x >> i & 1;
            // xor 当前位为 0 的数量
            int q = tr[p][b];
            int c = q ? tr[q][2] : 0;
            if (k < c){
                p = q;
            }
            else{
                k -= c;
                p = tr[p][b ^ 1];
                ans |= 1ULL << i;
            }
        }
        return ans;
    }
    //返回使x xor y第k小的元素 y;k 从 0 开始
    u64 kthElement(const u64& x, const int& k) const{
        return x ^ kthXor(x, k);
    }
    //返回满足 (x xor y) < k 的元素y个数
    int countXorLess(const u64& x, const u64& k) const{
        assert(valid(x));
        //k超过W位的最大范围
        if constexpr (W < 64){
            if (k >= (1ULL << W)){
                return size();
            }
        }
        int p = 1;
        int ans = 0;
        for (int i = W - 1; i >= 0 && p; i--){
            int a = x >> i & 1;
            int b = k >> i & 1;
            if (b){
                // 当前 xor 位取 0，一定比 k 小
                int q = tr[p][a];
                if (q){
                    ans += tr[q][2];
                }
                //前 xor 位取 1，继续比较后面的位
                p = tr[p][a ^ 1];
            }
            else{
                // 必须让当前 xor 位为 0
                p = tr[p][a];
            }
        }
        return ans;
    }
};