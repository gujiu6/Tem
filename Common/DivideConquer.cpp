/*
1.cdq分治求解三维偏序
*/
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

//1.cdq分治求解三维偏序
namespace {

class Bit {
public:
    int n;
    vector<int> bit;
    Bit(int n = 0): n(n), bit(n + 1) {}
    int lower_bit(int p) {
        return p & -p;
    }
    void add(int p, int v) {
        while(p <= n) {
            bit[p] += v;
            p += lower_bit(p);
        }
    }
    int sum(int p) {
        int ans = 0;
        while(p > 0) {
            ans += bit[p];
            p -= lower_bit(p);
        }
        return ans;
    }
};
struct Point {
    int x, y, z; 
    int id;
};
vector<int> dom3(vector<Point> points) {
    int n = points.size();
    vector<int> coord;
    for(const auto &p : points) {
        coord.push_back(p.z);
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end());
    sort(points.begin(), points.end(), [&](const Point &a, const Point &b){
        return tie(a.x, a.y, a.z) < tie(b.x, b.y, b.z);
    });
    struct Node {
        int x, y, z, cnt;
        vector<int> ids;
        i64 ans;
    };
    vector<Node> nodes;
    for(const auto &p : points) {
        int z = lower_bound(coord.begin(), coord.end(), p.z) - coord.begin() + 1;
        if(!nodes.empty() && tie(nodes.back().x, nodes.back().y, nodes.back().z) == tie(p.x, p.y, z)) {
            nodes.back().cnt++;
            nodes.back().ans++;
            nodes.back().ids.push_back(p.id);
        }
        else {
            nodes.push_back({p.x, p.y, z, 1, {p.id}, 1});
        }
    }
    vector<int> order(nodes.size()), buffer(nodes.size()), ans(n);
    Bit bit(coord.size());
    iota(order.begin(), order.end(), 0);
    auto cdq = [&](auto &&self, int l, int r) {
        if(l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        self(self, l, mid);
        self(self, mid + 1, r);
        int i = l, j = mid + 1, k = l;
        while(j <= r) {
            while(i <= mid && nodes[order[i]].y <= nodes[order[j]].y) {
                bit.add(nodes[order[i]].z, nodes[order[i]].cnt);
                buffer[k++] = order[i++];
            }
            nodes[order[j]].ans += bit.sum(nodes[order[j]].z);
            buffer[k++] = order[j++];
        }
        for(int k = l; k < i; k++) {
            bit.add(nodes[order[k]].z, -nodes[order[k]].cnt);
        }
        while(i <= mid) {
            buffer[k++] = order[i++];
        }
        copy(buffer.begin() + l, buffer.begin() + r + 1, order.begin() + l);
    };
    cdq(cdq, 0, nodes.size() - 1);
    for(const auto &node : nodes) {
        for(const auto &id : node.ids) {
            ans[id] = node.ans - 1;
        }
    }
    return ans;
}

}