#include <bits/stdc++.h>
using namespace std;






template <typename T = int>
class DSU{
private:
    int n;
    vector<T>fa,sz;
public:
    DSU(int n):n(n),fa(n+1),sz(n+1){
        iota(fa.begin(),fa.end(),0);
    }

    T find(T i){
        if(fa[i]!=i){
            fa[i]=find(fa[i]);
        }
        return fa[i];
    }

    bool issame(T x,T y){
        return find(x)==find(y);
    }

    void merge(T x,T y){
        int fx=find(x);
        int fy=find(y);
        if(fx!=fy){
            if(sz[fx]>=sz[fy]){
                sz[fx]+=sz[fy];
                fa[fy]=fx;
            }
            else{
                sz[fy]+=sz[fx];
                fa[fx]=fy;
            }
        }
    }

    T size(T x){
        return sz[find(x)];
    }
};




