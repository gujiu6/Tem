#include <bits/stdc++.h>
using namespace std;
using ll = long long;

//KMP
namespace KMP {

vector<int> nextArray(string s){
    int n = s.size();
    if(n == 1) return {-1};
    vector<int> nxt(n);
    nxt[0] = -1,nxt[1] = 0;
    int i = 2, cnt = 0;
    while(i < n){
        if(s[i-1] == s[cnt]){
            nxt[i++] = ++cnt;
        }
        else if(cnt > 0){
            cnt = nxt[cnt];
        }
        else{
            nxt[i++] = 0;
        }
    }
    return nxt;
}

int KMP(string s1, string s2){
    int n1 = s1.size(), n2 = s2.size(), x = 0, y = 0;
    vector<int> nxt = nextArray(s2);
    while(x < n1 && y < n2){
        if(s1[x] == s2[y]){
            x++;
            y++;
        }
        else if(y > 0){
            y = nxt[y];
        }
        else {
            x++;
        }
    }
    return y == n2 ? x - y : -1;
}

vector<int> KMP(string &s1, string &s2) {
    int n1 = s1.size(), n2 = s2.size();
    vector<int> nxt = nextArray(s2);
    vector<int> ans;
    int x = 0, y = 0;
    while(x < n1) {
        if(s1[x] == s2[y]) {
            x++;
            y++;
        }
        else if(y > 0) {
            y = nxt[y];
        }
        else {
            x++;
        }
        if(y == n2) {
            ans.push_back(x - y);
            y = nxt[y];
        }
    }
    return ans;
}

}

//序列自动机(string)
class SeqAuto {
private:
    static const int SIGMA = 26;
    vector<array<int, SIGMA>> nxt;
    string s;
    int n;
public:
    SeqAuto(string str) : s(" " + str), n(str.size()){
        nxt.assign(n + 2, {});
        for(int c = 0; c < SIGMA; c++) {
            nxt[n + 1][c] = n + 1; 
        }
        for(int i = n; i >= 1; i--) {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i] - 'a'] = i;
        }
    }
    //str为s的子序列
    bool check(string str) {
        int pos = 1;
        for(char ch : str) {
            pos = nxt[pos][ch - 'a'];
            if(pos == n + 1)
                return false;
            pos++;
        }
        return true;
    }
    //str最长匹配s的前缀序列
    int match(string str) {
        int pos = 1;
        for(int i = 0; i < str.size(); i++){
            pos = nxt[pos][str[i] - 'a'];
            if(pos == n + 1)
                return i;
            pos++;
        }
        return str.size();
    }
};


//字符串哈希
namespace Hash {

class Hash{
private:
    vector<ll>h, p;
    const ll B = 131, MOD = 1e9+7;//433
public:
    Hash(const string& s, ll B = 131, ll MOD = 1e9+7):B(B), MOD(MOD){
        int n = s.size();
        h.resize(n + 1, 0);
        p.resize(n + 1, 1);
        for(int i = 0; i < n; i++){
            p[i + 1] = p[i] * B % MOD;
            h[i + 1] = (h[i] * B + s[i]) % MOD;
        }
    }
    ll get(int l, int r){
        return (h[r + 1] - h[l] * p[r - l + 1] % MOD + MOD) % MOD;
    }
    ll merge(ll ha, ll hb, int lenB){
        return (ha * p[lenB] % MOD + hb) % MOD;
    }
};


}


