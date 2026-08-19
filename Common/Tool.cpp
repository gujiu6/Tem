/*
1.快读快写
2.i128转十进制字符串
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXX = 2e5, MOD = 1e9+7;
using i64 = long long;

//1.快读快写
namespace fast {

i64 read(){
    bool flag = false;
    i64 ans = 0;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-') flag = true;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return flag ? -ans : ans;
}
void write(i64 x){
    if(x == 0){
        putchar('0');
        return;
    }
    if(x < 0){
        putchar('-');
        x = -x;
    }
    char ch[50];
    int index = 0;
    while(x){
        ch[index++] = x % 10 + '0';
        x /= 10;
    }
    for(int i = index - 1; i >= 0; i--) {
        putchar(ch[i]);
    }
}

}

//2.i128转十进制字符串
string toString(__int128 x){
    if (!x){
        return "0";
    }
    auto neg = x < 0;
    auto y = neg ? 0 - (unsigned __int128)x : (unsigned __int128)x;
    string s;
    while (y){
        s.push_back(char('0' + y % 10));
        y /= 10;
    }
    if (neg){
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return s;
}