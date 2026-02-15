#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







array<int,MAXX>fa;

void build(int n){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
}

int find(int i){
    if(i!=fa[i]){
        fa[i]=find(fa[i]);
    }
    return fa[i];
}

bool merge(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return 1;
    }
    return 0;
}



void KrusKal(){
    int n,m,cnt=0;
    cin>>n>>m;
    build(n);
    long long ans=0;
    vector<array<int,3>>edge(m);
    for(int i=0;i<m;i++){
        cin>>edge[i][1]>>edge[i][2]>>edge[i][0];
    }
    sort(edge.begin(),edge.end());
    for(int i=0;i<m;i++){
        if(merge(edge[i][1],edge[i][2])){
            ans+=edge[i][0];
            cnt++;
        }
    }
    if(cnt==n-1) cout<<ans<<endl;
    else cout<<"orz"<<endl;
    
}



