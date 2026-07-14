#include <bits/stdc++.h>
using namespace std;


template <typename T = int>
class Inversion {
private:
    vector<T> a, tmp;
    int ans = 0;
public:
    Inversion(const vector<T>& v): a(v) {
        tmp.resize(a.size());
        merge_sort(1, a.size() - 1);
    }
    void merge_sort(int l, int r) {
        if(l >= r) return;
        int mid = (l + r) >> 1;
        merge_sort(l, mid);
        merge_sort(mid + 1, r);
        int i = l, j = mid + 1, k = l;
        while(i <= mid && j <= r) {
            if(a[i] <= a[j]) {
                tmp[k++] = a[i++];
            }
            else {
                ans += mid - i + 1;
                tmp[k++] = a[j++];
            }
        }
        while(i <= mid) {
            tmp[k++] = a[i++];
        }
        while(j <= r) {
            tmp[k++] = a[j++];
        }
        for(int p = l; p <= r; p++) {
            a[p] = tmp[p];
        }
    }
    int get_ans() {
        return ans;
    }
};