//开点线段树
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;






template <typename T=ll>
class SegmentTree3{
private:
    int cnt;
    int n;
    int max_nodes;
    vector<int> lf,rt;
    vector<T> sum,add;

    void check_left(int& i){if(!i) i=++cnt;}
    void check_right(int& i){if(!i) i=++cnt;}

    void lazy(int i,T v,int len){
        sum[i]+=v*len;
        add[i]+=v;
    }

    void up(int h,int l,int r){
        sum[h]=sum[l]+sum[r];
    }

    void down(int i,int ln,int rn){
        if(add[i]!=0){
            check_left(lf[i]);
            check_right(rt[i]);
            lazy(lf[i],add[i],ln);
            lazy(rt[i],add[i],rn);
            add[i]=0;
        }
    }

    void range_add(int jobl,int jobr,T jobv,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            lazy(i,jobv,r-l+1);
        }
        else{
            int mid=(l+r)>>1;
            down(i,mid-l+1,r-mid);
            if(jobl<=mid){
                check_left(lf[i]);
                range_add(jobl,jobr,jobv,l,mid,lf[i]);
            }
            if(jobr>mid){
                check_right(rt[i]);
                range_add(jobl,jobr,jobv,mid+1,r,rt[i]);
            }
            up(i,lf[i],rt[i]);
        }
    }

    T range_qry(int jobl,int jobr,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            return sum[i];
        }
        int mid=(l+r)>>1;
        T ans=0;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid){
            if(lf[i]!=0) ans+=range_qry(jobl,jobr,l,mid,lf[i]);
        }
        if(jobr>mid){
            if(rt[i]!=0) ans+=range_qry(jobl,jobr,mid+1,r,rt[i]);
        }
        return ans;
    }
public:
    SegmentTree3(int n,int estimate_nodes=200000):n(n),max_nodes(estimate_nodes),cnt(1){
        lf.assign(max_nodes,0);
        rt.assign(max_nodes,0);
        sum.assign(max_nodes,0);
        add.assign(max_nodes,0);
    }
    void adds(int l,int r,T v) {range_add(l,r,v,1,n,1);}
    T qry(int l,int r) {return range_qry(l,r,1,n,1);}
    void clear(){
        fill(lf.begin(),lf.end(),0);
        fill(rt.begin(),rt.end(),0);
        fill(sum.begin(),sum.end(),0);
        fill(add.begin(),add.end(),0);
        cnt=1;
    }
};




