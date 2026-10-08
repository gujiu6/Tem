/*
1.DFT/IDFT
2.FFT
3.NTT
*/
#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
using ll = long long;
using ld = long double;
const ld PI = acosl(-1);
const ll MOD = 998244353;


//1.DFT/IDFT
vector<cd> dftNaive(const vector<cd> &a, bool inv = false) {
    // a 是时域或频域序列,inv=false/true 表示 DFT/IDFT;返回变换结果,逆变换已除以长度.
    int n = a.size();
    vector<cd> A(n);
    long double pi = acosl(-1);
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            long double ang = 2 * pi * j * k / n * (inv ? -1 : 1);
            A[k] += a[j] * cd(cosl(ang), sinl(ang));
        }
        if (inv) {
            A[k] /= n;
        }
    }
    return A;
}


//2.FFT
namespace FFT{

void fft(vector<cd> &a, bool inv = false) {
    // a 是待变换序列,inv 表示是否做逆变换;原地完成 FFT,逆变换已除以长度.
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int k = n >> 1;
        while (j & k) {
            j ^= k;
            k >>= 1;
        }
        j ^= k;
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int len = 2; len <= n; len <<= 1) {
        ld ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cosl(ang), sinl(ang));
        for (int l = 0; l < n; l += len) {
            cd w{1.0L, 0.0L};
            for (int j = 0; j < len / 2; j++) {
                cd x = a[l + j];
                cd y = a[l + j + len / 2] * w;
                a[l + j] = x + y;
                a[l + j + len / 2] = x - y;
                w *= wlen;
            }
        }
    }
    if (inv) {
        for (auto &x : a) {
            x /= n;
        }
    }
}
template <class T = ld>
vector<T> mul(const vector<T> &a, const vector<T> &b) {
    // a,b 是实系数序列;返回二者的线性卷积,任一输入为空时返回空.
    if (a.empty() || b.empty()) {
        return {};
    }
    int sz = a.size() + b.size() - 1;
    int n = bit_ceil((unsigned long long)sz);
    vector<cd> x(n), y(n);
    copy(a.begin(), a.end(), x.begin());
    copy(b.begin(), b.end(), y.begin());
    fft(x, false);
    fft(y, false);
    for (int i = 0; i < n; i++) {
        x[i] *= y[i];
    }
    fft(x, true);
    vector<T> c(sz);
    for (int i = 0; i < sz; i++) {
        c[i] = llround(x[i].real());
    }
    return c;
}

}

//3.NTT
namespace NTT {

const ll G = 3;
ll power(ll a, ll b) {
    ll ans = 1;
    a %= MOD;
    while (b) {
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

void ntt(vector<ll>& a, bool inv = false) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int k = n >> 1;
        while (j & k) {
            j ^= k;
            k >>= 1;
        }
        j ^= k;
        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll wn = power(G, (MOD - 1) / len);
        if (inv) {
            wn = power(wn, MOD - 2);
        }
        for (int i = 0; i < n; i += len) {
            ll w = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wn % MOD;
            }
        }
    }
    if (inv) {
        ll inv_n = power(n, MOD - 2);
        for (auto &x : a)
            x = x * inv_n % MOD;
    }
}

vector<ll> mul(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    int sz = a.size() + b.size() - 1;
    int n = bit_ceil((unsigned long long)sz);
    vector<ll> x(n), y(n);
    copy(a.begin(), a.end(), x.begin());
    copy(b.begin(), b.end(), y.begin());
    ntt(x, false);
    ntt(y, false);
    for (int i = 0; i < n; i++) {
        x[i] = x[i] * y[i] % MOD;
    }
    ntt(x, true);
    x.resize(sz);
    return x;
}

}
