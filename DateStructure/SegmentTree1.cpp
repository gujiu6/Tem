//经典线段树
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;




template <typename T=ll>
class SegmentTree1{
private:
    int n;
    vector<T> sum,change,add;
    vector<bool> update;

    void updatelazy(int i,T v,int len){
        sum[i]=v*len;
        add[i]=0;
        change[i]=v;
        update[i]=1;
    }

    void addlazy(int i,T v,int len){
        sum[i]+=v*len;
        add[i]+=v;
    }

    void up(int i){
        sum[i]=sum[i<<1]+sum[i<<1|1];
    }

    void down(int i,int ln,int rn){
        if(update[i]!=0){
            updatelazy(i<<1,change[i],ln);
            updatelazy(i<<1|1,change[i],rn);
            update[i]=0;
        }
        if(add[i]!=0){
            addlazy(i<<1,add[i],ln);
            addlazy(i<<1|1,add[i],rn);
            add[i]=0;
        }
    }

    void build(const vector<T>& arr,int l,int r,int i){
        if(l==r){
            sum[i]=arr[l];
        }
        else{
            int mid=(l+r)>>1;
            build(arr,l,mid,i<<1);
            build(arr,mid+1,r,i<<1|1);
            up(i);
        }
    }
public:
    SegmentTree1(int n):n(n),sum(n<<2,0),add(n<<2,0),change(n<<2,0),update(n<<2,0){}
    SegmentTree1(const vector<T>& arr,int n):SegmentTree1(n){
        build(arr,1,n,1);
    }

    void range_update(int jobl,int jobr,T jobv,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            updatelazy(i,jobv,r-l+1);
        }
        else{
            int mid=(l+r)>>1;
            down(i,mid-l+1,r-mid);
            if(jobl<=mid) range_update(jobl,jobr,jobv,l,mid,i<<1);
            if(jobr>mid) range_update(jobl,jobr,jobv,mid+1,r,i<<1|1);
            up(i);
        }
    }

    void range_add(int jobl,int jobr,T jobv,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            addlazy(i,jobv,r-l+1);
        }
        else{
            int mid=(l+r)>>1;
            down(i,mid-l+1,r-mid);
            if(jobl<=mid) range_add(jobl,jobr,jobv,l,mid,i<<1);
            if(jobr>mid) range_add(jobl,jobr,jobv,mid+1,r,i<<1|1);
            up(i);
        }
    }

    T range_qry(int jobl,int jobr,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            return sum[i];
        }
        T ans=0;
        int mid=(l+r)>>1;
        down(i,mid-l+1,r-mid);
        if(jobl<=mid) ans+=range_qry(jobl,jobr,l,mid,i<<1);
        if(jobr>mid) ans+=range_qry(jobl,jobr,mid+1,r,i<<1|1);
        return ans;
    }
    void updates(int l,int r,T v) {range_update(l,r,v,1,n,1);}
    void adds(int l,int r,T v) {range_add(l,r,v,1,n,1);}
    T qry(int l,int r) {return range_qry(l,r,1,n,1);}
};








