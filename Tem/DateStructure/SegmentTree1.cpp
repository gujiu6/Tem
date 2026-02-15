//经典线段树
#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






array<ll,MAXX<<2>sum,change,add;
array<bool,MAXX<<2>update;
array<ll,MAXX>arr;

void updatelazy(int i,ll v,int n){
    sum[i]=v*n;
    add[i]=0;
    change[i]=v;
    update[i]=1;
}

void addlazy(int i,ll v,int n){
    sum[i]+=v*n;
    add[i]+=v;
}

void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void down(int i,int ln,int rn){
    if(update[i]){
        updatelazy(i<<1,change[i],ln);
        updatelazy(i<<1|1,change[i],rn);
        update[i]=0;
    }
    if(add[i]){
        addlazy(i<<1,add[i],ln);
        addlazy(i<<1|1,add[i],rn);
        add[i]=0;
    }
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
    add[i]=0;
    change[i]=0;
    update[i]=0;
}

void updates(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        updatelazy(i,jobv,r-l+1);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) updates(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid) updates(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

void adds(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv,r-l+1);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) adds(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid) adds(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

ll query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    ll ans=0;
    int mid=(l+r)>>1;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid) ans+=query(jobl,jobr,l,mid,i<<1);
    if(jobr>mid) ans+=query(jobl,jobr,mid+1,r,i<<1|1);
    return ans;
}








