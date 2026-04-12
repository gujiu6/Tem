#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;







ll read(){
    bool flag=false;
    ll ans=0;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') flag=true;
        c=getchar();
    }
    while(isdigit(c)){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return flag?-ans:ans;
}

void write(ll x){
    if(x==0){
        putchar('0');
        return;
    }
    if(x<0){
        putchar('-');
        x=-x;
    }
    char ch[50];
    int index=0;
    while(x){
        ch[index++]=x%10+'0';
        x/=10;
    }
    for(int i=index-1;i>=0;i--){
        putchar(ch[i]);
    }
}



