/*
1.字符串哈希
*/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = long long;


//1.字符串哈希(1-based)
class StrHash {
    static constexpr i64 p1 = 1000000007;
    static constexpr i64 p2 = 1000000009;
    i64 base;
    vector<i64> h1, h2, pw1, pw2;
    StrHash(const string& s, i64 base = 911382323): base(base), h1(s.size() + 1), h2(s.size() + 1), pw1(s.size() + 1, 1), pw2(s.size() + 1, 1) {
        int n = s.size() - 1;
        for(int i = 1; i <= n; i++) {
            int c = (unsigned char)s[i] + 1;
            h1[i] = (h1[i - 1] * base + c) % p1;
            h2[i] = (h2[i - 1] * base + c) % p2;
            pw1[i] = pw1[i - 1] * base % p1;
            pw2[i] = pw2[i - 1] * base % p2;
        }
    }
    //s[l,r]的哈希
    pair<i64, i64> get(int l, int r) const {
        assert(1 <= l && l <= r && r < h1.size());
        i64 x = (h1[r] - h1[l - 1] * pw1[r - l + 1] % p1 + p1) % p1;
        i64 y = (h2[r] - h2[l - 1] * pw2[r - l + 1] % p2 + p2) % p2;
        return {x, y};
    }
    //在s中寻找t的所有出现位置
    static vector<int> math(const string& s, const string& t) {
        int n = s.size() - 1, m = t.size() - 1;
        if(m > n) return {};
        StrHash a(s), b(t);
        vector<int> ans;
        for(int i = 1; i + m - 1 <= n; i++) {
            if(a.get(i, i + m - 1) == b.get(1, m)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};



//2.KMP
namespace KMP {

vector<int> prefix(const string& s) {
    int n = s.size() - 1;
    vector<int> p(n + 1);
    for(int i = 2; i <= n; i++) {
        int j = p[i - 1];
        while(j && s[i] != s[j + 1]) {
            j = p[j];
        }
        if(s[i] == s[j + 1]) {
            j++;
        }
        p[i] = j;
    }
    return p;
}

vector<int> KMP(const string &s, const string &t) {
    int n = s.size() - 1, m = t.size() - 1;
    if(m == 0) {
        vector<int> ans(n);
        iota(ans.begin(), ans.end(), 1);
        return ans;
    }
    auto p = prefix(t);
    vector<int> ans;
    int j = 0;
    for(int i = 1; i <= n; i++) {
        while(j && s[i] != t[j + 1]) {
            j = p[j];
        }
        if(s[i] == t[j + 1]) {
            j++;
        }
        if(j == m) {
            ans.push_back(i - m + 1);
            j = p[j];
        }
    }
    return ans;
}

//最小循环元
string minPeriod(const string& s) {
    int n = s.size() - 1;
    if(n == 0) return "";
    auto p = prefix(s);
    int len = n - p[n];
    if(n % len == 0) return s.substr(1, len);
    else return s;
}
//返回所有非空真Border长度,递增
vector<int> borders(const string &s) {
    int n = s.size() - 1;
    if (n == 0) return {};
    auto p = prefix(s);
    vector<int> ans;
    //n本身不是真Border,从最长真Border开始
    for (int x = p[n]; x; x = p[x]) {
        ans.push_back(x);
    }
    reverse(ans.begin(), ans.end());
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





//Manacher
namespace Manacher {

string manacherss(string str) {
    int n = str.size() * 2 + 1;
    string s(n, ' ');    for(int i = 0, j = 0; i < n; i++) {
        s[i] = (i & 1) == 0 ? '#' : str[j++];
    }
    return s;
}

string Manacher(string str) {
    string s = manacherss(str);
    int mx = 0, n = s.size(), bestLen = 0, bestCenter = 0;
    vector<int> p(n + 1);
    for(int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while(i + len < n && i - len >= 0 && s[i + len] == s[i - len]) {
            len++;
        }
        if(i + len > r) {
            r = i + len;
            c = i;
        }
        p[i] = len;
        if(len > bestLen) {
            bestLen = len;
            bestCenter = i;
        }    
    }
    int start = (bestCenter - bestLen + 1) / 2;
    return str.substr(start, bestLen - 1);
}

}
