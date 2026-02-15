//扫描线(矩阵面积并)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXX=2e5+10;






array<int,MAXX<<2>len,cover,times;
array<array<int,4>,MAXX<<1>rec,line;
array<int,MAXX<<1>arr;


int prepare(int n){
    sort(arr.begin()+1,arr.begin()+n+1);
    int m=1;
    for(int i=2;i<=n;i++){
        if(arr[m]!=arr[i]){
            arr[++m]=arr[i];
        }
    }
    arr[m+1]=arr[m];
    return m;
}

int find(int x,int n){
    return lower_bound(arr.begin()+1,arr.begin()+n+1,x)-arr.begin();
}

void up(int l,int r,int i){
    if(times[i]>0){
        cover[i]=len[i];
    }
    else if(l==r){
        cover[i]=0;
    }
    else {
        cover[i]=cover[i<<1]+cover[i<<1|1];
    }
}

void build(int l,int r,int i){
    if(l<r){
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
    }
    len[i]=arr[r+1]-arr[l];
    times[i]=cover[i]=0;
}

void adds(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        times[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid) adds(jobl,jobr,jobv,l,mid,i<<1);
        if(jobr>mid) adds(jobl,jobr,jobv,mid+1,r,i<<1|1);
    }
    up(l,r,i);
}

//示例
int calc(int n){
    for(int i=1,j=n+1,x1,x2,y1,y2;i<=n;i++,j++){
        x1=rec[i][0],y1=rec[i][1],x2=rec[i][2],y2=rec[i][3];
        arr[i]=y1,arr[j]=y2;
        line[i][0]=x1,line[i][1]=y1,line[i][2]=y2,line[i][3]=1;
        line[j][0]=x2,line[j][1]=y1,line[j][2]=y2,line[j][3]=-1;
    }
    n<<=1;
    int m=prepare(n);
    build(1,m,1);
    sort(line.begin()+1,line.begin()+n+1);
    int ans=0;
    for(int i=1,pre=0;i<=n;i++){
        ans+=cover[1]*(line[i][0]-pre);
        pre=line[i][0];
        adds(find(line[i][1],m),find(line[i][2],m)-1,line[i][3],1,m,1);
    }
    return ans;
}





