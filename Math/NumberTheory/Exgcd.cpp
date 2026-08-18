#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
using i64 = long long;




i64 exgcd(i64 a,i64 b,i64 &x,i64 &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    i64 res = exgcd(b,a%b,y,x);
    y -= a / b * x;
    return res;
}



