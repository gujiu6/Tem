/*
1.Trie
2.01Trie
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;



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
