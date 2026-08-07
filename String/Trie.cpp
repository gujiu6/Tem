#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






struct Trie {
    int cnt, n;
    vector<vector<int>> tr;
    vector<int> pas, ed;
    Trie(int n): cnt(1), n(n) {
        tr.resize(MAXX, vector<int>(n));
        pas.resize(MAXX);
        ed.resize(MAXX);
    }

    int Path(char c) const {
        return c - 'a';
    }

    void insert(string& s) {
        int cur = 1;
        pas[cur]++;
        for(int i = 0; i < s.size(); i++){
            int path = Path(s[i]);
            if(tr[cur][path] == 0){
                tr[cur][path] = ++cnt;
            }
            cur = tr[cur][path];
            pas[cur]++;
        }
        ed[cur]++;
    }

    int search(string& s) const {
        int cur = 1;
        for(int i = 0; i < s.size(); i++){
            int path = Path(s[i]);
            if(tr[cur][path] == 0){
                return 0;
            }
            cur = tr[cur][path];
        }
        return ed[cur];
    }

    int prefixcount(string& pre) const {
        int cur = 1;
        for(int i = 0; i < pre.size(); i++){
            int path = Path(pre[i]);
            if(tr[cur][path] == 0){
                return 0;
            }
            cur = tr[cur][path];
        }
        return pas[cur];
    }

    void del(string& s) {
        if(search(s) > 0){
            int cur = 1;
            for(int i = 0; i < s.size(); i++){
                int path = Path(s[i]);
                if(--pas[tr[cur][path]] == 0){
                    tr[cur][path] = 0;
                    return;
                }
                cur = tr[cur][path];
            }
            ed[cur]--;
        }
    }

    void clear() {
        for(int i = 1; i <= cnt; i++){
            tr[i].assign(n, 0);
            ed[i] = 0;
            pas[i] = 0;
        }
        cnt = 1;
    }
};





