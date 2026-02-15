//区间最值 历史最值(jiry)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18;
const int MAXX=5e5+10;








array<ll,MAXX<<2>sum,mx,cnt,sem,maxAdd,otherAdd,maxHistory,maxAddTop,otherAddTop;
array<ll,MAXX>arr;

void lazy(int i,int n,ll maxaddv,ll otheraddv,ll maxUpv,ll otherUpv){
    maxHistory[i]=max(maxHistory[i],mx[i]+maxUpv);
    maxAddTop[i]=max(maxAddTop[i],maxAdd[i]+maxUpv);
    otherAddTop[i]=max(otherAddTop[i],otherAdd[i]+otherUpv);
    sum[i]+=maxaddv*cnt[i]+otheraddv*(n-cnt[i]);
    mx[i]+=maxaddv;
    sem[i]+=sem[i]==-INF?0:otheraddv;
    maxAdd[i]+=maxaddv;
    otherAdd[i]+=otheraddv;
}

void up(int i){
    int l=i<<1,r=i<<1|1;
    sum[i]=sum[l]+sum[r];
    mx[i]=max(mx[l],mx[r]);
    maxHistory[i]=max(maxHistory[l],maxHistory[r]);
    if(mx[l]>mx[r]){
        cnt[i]=cnt[l];
        sem[i]=max(sem[l],mx[r]);
    }
    else if(mx[r]>mx[l]){
        cnt[i]=cnt[r];
        sem[i]=max(mx[l],sem[r]);
    }
    else{
        cnt[i]=cnt[l]+cnt[r];
        sem[i]=max(sem[l],sem[r]);
    }
}

void down(int i,int ln,int rn){
    int l=i<<1,r=i<<1|1;
    ll tmp=max(mx[l],mx[r]);
    if(mx[l]==tmp){
        lazy(l,ln,maxAdd[i],otherAdd[i],maxAddTop[i],otherAddTop[i]);
    }
    else{
        lazy(l,ln,otherAdd[i],otherAdd[i],otherAddTop[i],otherAddTop[i]);
    }

    if(mx[r]==tmp){
        lazy(r,rn,maxAdd[i],otherAdd[i],maxAddTop[i],otherAddTop[i]);
    }
    else{
        lazy(r,rn,otherAdd[i],otherAdd[i],otherAddTop[i],otherAddTop[i]);
    }
    maxAdd[i]=otherAdd[i]=maxAddTop[i]=otherAddTop[i]=0;
}


void build(int l,int r,int i){
    if(l==r){
        mx[i]=sum[i]=maxHistory[i]=arr[l];
        cnt[i]=1;
        sem[i]=-INF;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void adds(int jobl,int jobr,ll jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,r-l+1,jobv,jobv,jobv,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) adds(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid) adds(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

void setmin(int jobl,int jobr,ll jobv,int l,int r,int i){
    if(jobv>=mx[i]) return;
    if(jobl<=l&&r<=jobr&&sem[i]<jobv){
        lazy(i,r-l+1,jobv-mx[i],0,jobv-mx[i],0);
    }
    else{
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) setmin(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid) setmin(jobl,jobr,jobv,mid+1,r,i<<1|1);
        up(i);
    }
}

ll querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return mx[i];
    }
    int mid=(l+r)>>1;
    ll ans=-INF;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid) ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
    if(jobr>mid) ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
    return ans;
}

ll querysum(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    int mid=(l+r)>>1;
    ll ans=0;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid) ans+=querysum(jobl,jobr,l,mid,i<<1);
    if(jobr>mid) ans+=querysum(jobl,jobr,mid+1,r,i<<1|1);
    return ans;
}


ll queryhistorymax(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return maxHistory[i];
    }
    int mid=(l+r)>>1;
    ll ans=-INF;
    down(i,mid-l+1,r-mid);
    if(jobl<=mid) ans=max(ans,queryhistorymax(jobl,jobr,l,mid,i<<1));
    if(jobr>mid) ans=max(ans,queryhistorymax(jobl,jobr,mid+1,r,i<<1|1));
    return ans;
}











