//开点线段树
#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;









int cnt;
array<int,MAXX>lf,rt;
array<ll,MAXX>sum,add;

void lazy(int i,ll v,int n){
    sum[i]+=v*n;
    add[i]+=v;
}

void up(int h,int l,int r){
    sum[h]=sum[l]+sum[r];
}

void down(int i,int ln,int rn){
    if(add[i]){
        if(lf[i]==0) lf[i]=++cnt;
        if(rt[i]==0) rt[i]=++cnt;
        lazy(lf[i],add[i],ln);
        lazy(rt[i],add[i],rn);
        add[i]=0;
    }
}

void adds(int jobl,int jobr,ll jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv,r-l+1);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid){
            if(lf[i]==0) lf[i]=++cnt;
            adds(jobl,jobr,jobv,l,mid,lf[i]);
        }
        if(jobr>mid){
            if(rt[i]==0) rt[i]=++cnt;
            adds(jobl,jobr,jobv,mid+1,r,rt[i]);
        }
        up(i,lf[i],rt[i]);
    }
}

ll query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    int mid=(l+r)>>1;
    ll ans=0;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid){
        if(lf[i]!=0) ans+=query(jobl,jobr,l,mid,lf[i]);
    }
    if(jobr>mid){
        if(rt[i]!=0) ans+=query(jobl,jobr,mid+1,r,rt[i]);
    }
    return ans;
}

void clear(){
    sum.fill(0);
    lf.fill(0);
    rt.fill(0);
    add.fill(0);
}



