#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;
    vector<int> result;

public:
    void read() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    vector<int> in_order() {
        result.clear();
        in_order_traversal(0);
        return result;
    }

    void in_order_traversal(int index) {
        if (left[index] != -1)
            in_order_traversal(left[index]);
        result.push_back(key[index]);
        if (right[index] != -1)
            in_order_traversal(right[index]);
    }

    vector<int> pre_order() {
        result.clear();
        pre_order_traversal(0);
        return result;
    }

    void pre_order_traversal(int index) {
        result.push_back(key[index]);
        if (left[index] != -1)
            pre_order_traversal(left[index]);
        if (right[index] != -1)
            pre_order_traversal(right[index]);
    }

    vector<int> post_order() {
        result.clear();
        post_order_traversal(0);
        return result;
    }

    void post_order_traversal(int index) {
        if (left[index] != -1)
            post_order_traversal(left[index]);
        if (right[index] != -1)
            post_order_traversal(right[index]);
        result.push_back(key[index]);
    }
};

void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    t.read();
    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    return 0;
}
