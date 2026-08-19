/*
1.快读快写
2.i128转十进制字符串
3.手写Hash函数
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXX = 2e5, MOD = 1e9+7;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

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

//3.手写Hash函数
namespace {
//重量Hash(防Hack)
class Hash{
private:
    static u64 mix(u64 x){
        // SplitMix64 finalizer：雪崩扰动
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }
    static u64 seed(){
        static const u64 s = chrono::steady_clock::now().time_since_epoch().count();
        return s;
    }
public:
    //整数
    template <class T> requires is_integral_v<T>
    size_t operator()(T x) const{
        return mix(static_cast<u64>(x) + seed());
    }
    //pair
    template <class A, class B>
    size_t operator()(const pair<A, B>& x) const{
        u64 h1 = (*this)(x.first);
        u64 h2 = (*this)(x.second);
        return mix(h1 ^ (h2 << 1));
    }
    //tuple<A, B, C>
    template <class A, class B, class C>
    size_t operator()(const tuple<A, B, C>& x) const{
        u64 h1 = (*this)(get<0>(x));
        u64 h2 = (*this)(get<1>(x));
        u64 h3 = (*this)(get<2>(x));
        return mix(h1 ^ (h2 << 1) ^ (h3 << 2));
    }
    //array
    template <class T, size_t N>
    size_t operator()(const array<T, N>& x) const{
        u64 h = seed();
        for (const auto& v : x) {
            h = mix(h ^ (*this)(v));
        }
        return h;
    }
};
//快速hash(防超时)
struct Key {
    int pos;
    i64 mask;
    int rem;
    bool operator==(const Key& other) const {
        return pos == other.pos && mask == other.mask && rem == other.rem;
    }
};
class Hash2 {
public:
    size_t operator()(const Key& x) const {
        size_t h1 = hash<int>{}(x.pos);
        size_t h2 = hash<i64>{}(x.mask);
        size_t h3 = hash<int>{}(x.rem);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
}


