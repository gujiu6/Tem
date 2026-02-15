#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
const double eps=1e-6;
typedef long long ll;









array<array<double,100>,100>mat;
//高斯消元(加法方程)
void gaussAdd(int n){
	for(int i=1;i<=n;i++){
		int mx=i;
		for(int j=1;j<=n;j++){
			if(j<i&&fabs(mat[j][j])>=eps){
				continue;
			}
			if(fabs(mat[j][i])>fabs(mat[mx][i])){
				mx=j;
			}
		}
		swap(mat[mx],mat[i]);
		if(fabs(mat[i][i])>=eps){
			double tmp=mat[i][i];
			for(int j=i;j<=n+1;j++){
				mat[i][j]/=tmp;
			}
			for(int j=1;j<=n;j++){
				if(i!=j){
					double rate=mat[j][i]/mat[i][i];
					for(int k=i;k<=n+1;k++){
						mat[j][k]-=mat[i][k]*rate;
					}
				}
			}
		}
	}
}

//判断  1:唯一解  0:多解  -1:无解
int pd(int n){
	int ans=1;
    for(int i=1;i<=n;i++){
    	if(fabs(mat[i][i])<eps&&fabs(mat[i][n+1])>=eps){
    		ans=-1;
    		break;
    	}
    	if(fabs(mat[i][i])<eps){
    		ans=0;
    	}
    }	
    return ans;
}




