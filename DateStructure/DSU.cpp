#include <bits/stdc++.h>
using namespace std;






template <typename T = int>
class DSU{
private:
    int n;
    int row,col;
    vector<T>fa,sz;
public:
    DSU(int n):n(n),row(0),col(0),fa(n+1),sz(n+1,1){
        iota(fa.begin(),fa.end(),0);
    }
    DSU(int r,int c):n(r*c),row(r),col(c),fa(r*c+1),sz(r*c+1,1){
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
    int id(int i,int j){
        return i*col+j;
    }
};




