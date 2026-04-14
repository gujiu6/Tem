#include <bits/stdc++.h>
using namespace std;
const int MAXX=2e5;
typedef long long ll;






int lowbit(int i){
	return i&-i;
}

//2^k
bool isPowerOfTwo(int n){
	return n>0&&!(n&(n-1));
}

int log2(int n){
	return __builtin_ctz(n);
}
//int最高位1
int highestBit32(int n){
	if(n==0) return -1;
	return 31-__builtin_clz(n);
}
//ll 最高位1
int higestBit64(ll n){
	if(n==0) return -1;
	return 63-__builtin_clzll(n);
}
//二进制位1的数量
int countBitsOne(int n){
	return __builtin_popcount(n);
}
//二进制位0的数量
int countBitsZero(int n){
	return 32-__builtin_popcount(n);
}
//[l,r] Or
ll getOr(ll l,ll r){
	if(l==r) return l;
	return l|((1LL<<(63-__builtin_clzll(l^r)+1))-1);
}
//[l,r] And
ll getAnd(ll l,ll r){
	if(l==r) return l;
	return l&(~((1LL<<(63-__builtin_clzll(l^r)+1))-1));
}
//[1,x] Xor
ll getXor(ll x){
	if(x<0) return 0;
	if(x%4==0) return x;
	if(x%4==1) return 1;
	if(x%4==2) return x+1;
	if(x%4==3) return 0;
	return -1;
}



