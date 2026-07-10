#include <bits/stdc++.h>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a,bool invert)
{
    int n=a.size();
    for(int i=1,j=0;i<n;i++)
    {
        int bit=n>>1;
        while(j&bit)
        {
            j^=bit;
            bit>>=1;
        }
        j^=bit;
        if(i<j)
            swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1)
    {
        double ang=2*PI/len;
        if(invert)
            ang=-ang;
        cd wn(cos(ang),sin(ang));
        for(int i=0;i<n;i+=len)
        {
            cd w(1);
            for(int j=0;j<len/2;j++)
            {
                cd u=a[i+j];
                cd v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wn;
            }
        }
    }
    if(invert)
    {
        for(auto &x:a)
            x/=n;
    }
}
vector<int> mul(vector<int> A, vector<int> B) {
    int result_len = A.size() + B.size() - 1;
    int n = 1;
    while(n < result_len) n <<= 1;
    vector<complex<double>> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    fft(fa, true);
    vector<int> result(result_len);
    for(int i = 0; i < result_len; i++) {
        result[i] = round(fa[i].real());
    }
    return result;
}