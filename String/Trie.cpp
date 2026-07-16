#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






class Trie {
private:
    int cnt, n;
    vector<vector<int>> tree;
    vector<int> pass1, end1;
public:
    Trie(int n): cnt(1), n(n) {
        tree.resize(MAXX, vector<int>(n));
        pass1.resize(MAXX);
        end1.resize(MAXX);
    }

    int Path(char c) {
        return c-'a';
    }

    void insert(string& s) {
        int cur = 1;
        pass1[cur]++;
        for(int i = 0; i < s.size(); i++){
            int path = Path(s[i]);
            if(tree[cur][path] == 0){
                tree[cur][path] = ++cnt;
            }
            cur = tree[cur][path];
            pass1[cur]++;
        }
        end1[cur]++;
    }

    int search(string& s) {
        int cur = 1;
        for(int i = 0; i < s.size(); i++){
            int path = Path(s[i]);
            if(tree[cur][path] == 0){
                return 0;
            }
            cur = tree[cur][path];
        }
        return end1[cur];
    }

    int prefixcount(string& pre){
        int cur = 1;
        for(int i = 0; i < pre.size(); i++){
            int path = Path(pre[i]);
            if(tree[cur][path] == 0){
                return 0;
            }
            cur = tree[cur][path];
        }
        return pass1[cur];
    }

    void del(string& s){
        if(search(s) > 0){
            int cur = 1;
            for(int i = 0; i < s.size(); i++){
                int path = Path(s[i]);
                if(--pass1[tree[cur][path]] == 0){
                    tree[cur][path] = 0;
                    return;
                }
                cur = tree[cur][path];
            }
            end1[cur]--;
        }
    }

    void clear(){
        for(int i = 1; i <= cnt; i++){
            tree[i].assign(n, 0);
            end1[i] = 0;
            pass1[i] = 0;
        }
    }
};





