#include <bits/stdc++.h>
using namespace std;


vector<int> nextArray(string s){
    int n=s.size();
    if(n==1) return {-1};
    vector<int>next(n);
    next[0]=-1,next[1]=0;
    int i=2,cnt=0;
    while(i<n){
        if(s[i-1]==s[cnt]){
            next[i++]=++cnt;
        }
        else if(cnt>0){
            cnt=next[cnt];
        }
        else{
            next[i++]=0;
        }
    }
    return next;
}

int KMP(string s1,string s2){
    int n1=s1.size(),n2=s2.size(),x=0,y=0;
    vector<int>next=nextArray(s2);
    while(x<n1&&y<n2){
        if(s1[x]==s2[y]){
            x++;
            y++;
        }
        else if(y==0){
            x++;
        }
        else {
            y=next[y];
        }
    }
    return y==n2?x-y:-1;
}



