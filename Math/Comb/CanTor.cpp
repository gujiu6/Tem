#include <bits/stdc++.h>
using namespace std;


class CanTor{
private:
    vector<int> fac;
public:
    int CanTorRK(vector<int>& a) {
        int n = a.size();
        vector<int> fac(n + 1, 1);
        for(int i = 1; i <= n; i++){
            fac[i] = fac[i - 1] * i;
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            int cnt = 0;
            for(int j = i + 1; j < n; j++){
                if(a[j] < a[i]) 
                    cnt++;
            }
            ans += cnt * fac[n - i - 1];
        }
        return ans;
    }
    vector<int> deCanTor(int n, int k){
        vector<int> fac(n + 1, 1);
        for(int i = 1; i <= n; i++){
            fac[i] = fac[i - 1] * i;
        }
        vector<int> num;
        for(int i = 1; i <= n; i++)
            num.push_back(i);
        vector<int> ans;
        for(int i = n; i > 0; i--){
            int idx = k / fac[i - 1];
            k %= fac[i-1];
            ans.push_back(num[idx]);
            num.erase(num.begin() + idx);
        }
        return ans;
    }
};