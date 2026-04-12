//区间合并
#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






array<int,MAXX>arr;
array<ll,MAXX<<2>sum,len0,pre0,sur0,len1,pre1,sur1,change;
array<bool,MAXX>update,rev;


void updatelazy(int i,ll v,int n){
    sum[i]=v*n;
    len0[i]=pre0[i]=sur0[i]=v==0?n:0;
    len1[i]=pre1[i]=sur1[i]=v==1?n:0;
    change[i]=v;
    update[i]=1;
    rev[i]=0;
}

void reverselazy(int i,int n){
    sum[i]=n-sum[i];
    swap(len0[i],len1[i]);
    swap(pre0[i],pre1[i]);
    swap(sur0[i],sur1[i]);
    rev[i]^=1;
}


void up(int i,int ln,int rn){
    int l=i<<1;
    int r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    len0[i]=max({len0[l],len0[r],sur0[l]+pre0[r]});
    pre0[i]=len0[l]<ln?pre0[l]:(pre0[l]+pre0[r]);
    sur0[i]=len0[r]<rn?sur0[r]:(sur0[l]+sur0[r]); 
    len1[i]=max({len1[l],len1[r],sur1[l]+pre1[r]});
    pre1[i]=len1[l]<ln?pre1[l]:(pre1[l]+pre1[r]);
    sur1[i]=len1[r]<rn?sur1[r]:(sur1[l]+sur1[r]);
}

void down(int i,int ln,int rn){
    if(update[i]){
        updatelazy(i<<1,change[i],ln);
        updatelazy(i<<1|1,change[i],rn);
        update[i]=0;
    }
    if(rev[i]){
        reverselazy(i<<1,ln);
        reverselazy(i<<1|1,rn);
        rev[i]=0;
    }
}

void build(int l,int r,int i){
    if(l==r){
        sum[i]=arr[l];
        len0[i]=pre0[i]=sur0[i]=arr[l]==0;
        len1[i]=pre1[i]=sur1[i]=arr[l]==1;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
    update[i]=0;
    rev[i]=0;
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
        up(i,mid-l+1,r-mid);
    }
}

void reverses(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        reverselazy(i,r-l+1);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) reverses(jobl,jobr,l,mid,i<<1);
        if(jobr>mid) reverses(jobl,jobr,mid+1,r,i<<1|1);
        up(i,mid-l+1,r-mid);
    }
}

ll qrysum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    int mid=(l+r)>>1;
    ll ans=0;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid) ans+=qrysum(jobl,jobr,l,mid,i<<1);
    if(jobr>mid) ans+=qrysum(jobl,jobr,mid+1,r,i<<1|1);
    return ans;
}

vector<ll> qrylongest(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {len1[i],pre1[i],sur1[i]};
    }
    int mid=(l+r)>>1;
    int ln=mid-l+1,rn=r-mid;
    down(i,ln,rn);
    if(jobr<=mid) return qrylongest(jobl,jobr,l,mid,i<<1);
    if(jobl>mid) return qrylongest(jobl,jobr,mid+1,r,i<<1|1);
    vector<ll> l3=qrylongest(jobl,jobr,l,mid,i<<1);
    vector<ll> r3=qrylongest(jobl,jobr,mid+1,r,i<<1|1);
    ll llen=l3[0],lpre=l3[1],lsur=l3[2];
    ll rlen=r3[0],rpre=r3[1],rsur=r3[2];
    ll len=max({llen,rlen,lsur+rpre});
    ll pre=llen<mid-max(jobl,l)+1?lpre:(lpre+rpre);
    ll sur=rlen<min(r,jobr)-mid?rsur:(lsur+rsur);
    return {len,pre,sur};
}

void clear(){

}

