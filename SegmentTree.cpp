#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
    vector<int> seg;
public:
    SegmentTree(int n) {
        seg.resize(4 * n + 1);
    }

    void build(int index, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[index] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        seg[index] = min(seg[2 * index + 1], seg[2 * index + 2]);
    }

    int query(int index, int low, int high, int left, int right) {
        // No Overlapping [left, right] < [low, high] OR [low, high] < [left, right] 
        if (right < low || high < left) {
            return INT_MAX;
        }
        // Complete Overlapping [left [low, high] right]
        if (left <= low && high <= right) {
            return seg[index];
        }
        int mid = (low + high) / 2;
        int l = query(2 * index + 1, low, mid, left, right);
        int r = query(2 * index + 2, mid + 1, high, left, right);
        // cout << "[" << low << "," << high << "]: " << min(l, r) << " left: " << l << " right: " << r << endl;
        return min(l, r);
    }

    void update(int index, int low, int high, int i, int val) {
        if (low == high) {
            seg[index] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid) {
            update(2 * index + 1, low, mid, i, val);
        }
        else {
            update(2 * index + 2, mid + 1, high, i, val);
        }
        seg[index] = min(seg[2 * index + 1], seg[2 * index + 2]);
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
#endif

    vector<int> arr{ 2,1,0,3,5,4 };

    int n = arr.size();
    SegmentTree seg(n);
    seg.build(0, 0, n - 1, arr);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int left, right;
            cin >> left >> right;
            cout << seg.query(0, 0, n - 1, left, right) << endl;
        }
        else {
            int i, val;
            cin >> i >> val;
            seg.update(0, 0, n - 1, i, val);
        }
    }
    return 0;
}