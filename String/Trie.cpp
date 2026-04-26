#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






class Trie{
private:
    int cnt,path;
    array<array<int,26>,MAXX>tree;
    array<int,MAXX>pass1,end1;
public:
    Trie(int ):cnt(1){}

    int Path(char c){
        return c-'a';
    }

    void insert(string &word){
        int cur=1;
        pass1[cur]++;
        for(int i=0;i<word.size();i++){
            path=Path(word[i]);
            if(tree[cur][path]==0){
                tree[cur][path]=++cnt;
            }
            cur=tree[cur][path];
            pass1[cur]++;
        }
        end1[cur]++;
    }

    int search(string &word){
        int cur=1;
        for(int i=0;i<word.size();i++){
            path=Path(word[i]);
            if(tree[cur][path]==0){
                return 0;
            }
            cur=tree[cur][path];
        }
        return end1[cur];
    }

    int prefixcount(string pre){
        int cur=1;
        for(int i=0;i<pre.size();i++){
            path=Path(pre[i]);
            if(tree[cur][path]==0){
                return 0;
            }
            cur=tree[cur][path];
        }
        return pass1[cur];
    }

    void del(string &word){
        if(search(word)>0){
            int cur=1;
            for(int i=0;i<word.size();i++){
                path=Path(word[i]);
                if(--pass1[tree[cur][path]]==0){
                    tree[cur][path]=0;
                    return;
                }
                cur=tree[cur][path];
            }
            end1[cur]--;
        }
    }

    void clear(){
        for(int i=1;i<=cnt;i++){
            tree[i].fill(0);
            end1[i]=0;
            pass1[i]=0;
        }
    }
};





