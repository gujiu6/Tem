//摩尔投票问题(线段树hard版)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXX=2e5+10;


array<array<int,2>,MAXX>nums;
array<int,MAXX>arr;
array<int,MAXX<<2>hp,val;
int n;






void up(int i){
    int lval=val[i<<1],lhp=hp[i<<1];
    int rval=val[i<<1|1],rhp=hp[i<<1|1];
    val[i]=lval==rval||lhp>=rhp?lval:rval;
    hp[i]=lval==rval?lhp+rhp:abs(lhp-rhp);
}

void build(int l,int r,int i){
    if(l==r){
        val[i]=arr[l];
    }
    else {
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

vector<int> qry(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return {val[i],hp[i]};
    }
    int mid=(l+r)>>1;
    if(jobr<=mid) return qry(jobl,jobr,l,mid,i<<1);
    if(jobl>mid) return qry(jobl,jobr,mid+1,r,i<<1|1);
    auto linf=qry(jobl,jobr,l,mid,i<<1);
    auto rinf=qry(jobl,jobr,mid+1,r,i<<1|1);
    int lval=linf[0],lhp=linf[1];
    int rval=rinf[0],rhp=rinf[1];
    int curval=lval==rval||lhp>=rhp?lval:rval;
    int curhp=lval==rval?lhp+rhp:abs(lhp-rhp);
    return {curval,curhp};
}

void buildCnt(){
    for(int i=1;i<=n;i++){
        nums[i][0]=arr[i];
        nums[i][1]=i;
    }
    sort(nums.begin()+1,nums.begin()+n+1);
}

int find(int x,int i){
    return lower_bound(nums.begin()+1,nums.begin()+n+1,array<int,2>{x,i})-nums.begin();
}





