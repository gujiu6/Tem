/*
1.数位DP
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int MAXX = 1000;


//1.数位DP
int dp[MAXX][MAXX];
i64 dfs(int pos, int status, bool free, bool zero, const string& str) {
    if(pos == str.size()) {

    }
    int rem_len = str.size() - pos;
    if(free && !zero && dp[rem_len][status] != -1) return dp[rem_len][status];
    int limit = free ? 9 : str[pos] - '0';
    int res = 0;
    for(int d = 0; d <= limit; d++) {
        bool nfree = free || d < limit;
        bool nzero = zero && d == 0;
        int nstatus = status;
        res = (res + dfs(pos + 1, nstatus, nfree, nzero, str));
    }
    if(free && !zero) dp[rem_len][status] = res;
    return res;
}
