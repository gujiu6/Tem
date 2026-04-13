#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7,MAXX=100;




vector<vector<int>>dis(MAXX,vector<int>(MAXX,INF));


void floyd(int n){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dis[i][k]!=INF&&dis[k][j]!=INF&&dis[i][j]>dis[i][k]+dis[k][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
            }
        }
    }
}


