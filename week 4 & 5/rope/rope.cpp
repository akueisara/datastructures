#include <cstdio>
#include <string>
#include <iostream>
#include <stack>

struct Vertex {
    char key;
    long long size; // number of nodes below the node (include itself)
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(char key, long long size, Vertex* left, Vertex* right, Vertex* parent)
        : key(key)
        , size(size)
        , left(left)
        , right(right)
        , parent(parent)
    {
    }
};

class Rope {
    std::string s;
    Vertex* root;

public:
    Rope(const std::string& s)
        : s(s)
    {
        root = NULL;
        for (int i = 0; i < s.length(); i++) {
            Vertex* next = new Vertex(s[i], 1, NULL, NULL, NULL);
            root = merge(root, next);
        }
    }

    void update(Vertex* v)
    {
        if (v == NULL)
            return;
        v->size = 1 + (v->left != NULL ? v->left->size : 0)
            + (v->right != NULL ? v->right->size : 0);
        if (v->left != NULL) {
            v->left->parent = v;
        }
        if (v->right != NULL) {
            v->right->parent = v;
        }
    }

    void small_rotation(Vertex* v)
    {
        Vertex* parent = v->parent;
        if (parent == NULL) {
            return;
        }
        Vertex* grandparent = v->parent->parent;
        if (parent->left == v) {
            Vertex* m = v->right;
            v->right = parent;
            parent->left = m;
        }
        else {
            Vertex* m = v->left;
            v->left = parent;
            parent->right = m;
        }
        update(parent);
        update(v);
        v->parent = grandparent;
        if (grandparent != NULL) {
            if (grandparent->left == parent) {
                grandparent->left = v;
            }
            else {
                grandparent->right = v;
            }
        }
    }

    void big_rotation(Vertex* v)
    {
        if (v->parent->left == v && v->parent->parent->left == v->parent) {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        }
        else if (v->parent->right == v && v->parent->parent->right == v->parent) {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        }
        else {
            // Zig-zag
            small_rotation(v);
            small_rotation(v);
        }
    }

    void splay(Vertex*& root, Vertex* v)
    {
        if (v == NULL)
            return;
        while (v->parent != NULL) {
            if (v->parent->parent == NULL) {
                small_rotation(v);
                break;
            }
            big_rotation(v);
        }
        root = v;
    }

    Vertex* find(Vertex*& root, int leftNum)
    {
        Vertex* v = root;

        while (v != NULL) {
            long long s = (v->left != NULL) ? v->left->size : 0;
            if (leftNum == (s + 1)) {
                break;
            }
            else if (leftNum < (s + 1)) {
                v = v->left;
            }
            else if (leftNum > (s + 1)) {
                v = v->right;
                leftNum = leftNum - s - 1;
            }
        }
        splay(root, v);
        return v;
    }

    void split(Vertex* root, int key, Vertex*& left, Vertex*& right)
    {
        right = find(root, key);
        splay(root, right);
        if (right == NULL) {
            left = root;
            return;
        }
        left = right->left;
        right->left = NULL;
        if (left != NULL) {
            left->parent = NULL;
        }
        update(left);
        update(right);
    }

    Vertex* merge(Vertex* left, Vertex* right)
    {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        Vertex* min_right = right;
        while (min_right->left != NULL) {
            min_right = min_right->left;
        }
        splay(right, min_right);
        right->left = left;
        update(right);
        return right;
    }

    void insert(Vertex*& root, int k, Vertex*& subString)
    {
        Vertex* left = NULL;
        Vertex* right = NULL;
        split(root, k, left, right);
        root = merge(merge(left, subString), right);
    }

    std::string traversal_in_order(Vertex* root)
    {
        std::string printS = "";
        if (root == NULL) {
            return printS;
        }
        std::stack<Vertex*> S;
        Vertex* p = root;

        while (p != NULL) {
            S.push(p);
            p = p->left;
        }

        while (!S.empty()) {
            p = S.top();
            printS.push_back(p->key);
            S.pop();
            p = p->right;
            while (p != NULL) {
                S.push(p);
                p = p->left;
            }
        }
        return printS;
    }

    void process_naive(int i, int j, int k)
    {
        std::string t = s.substr(0, i) + s.substr(j + 1);
        s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
    }

    void process(int i, int j, int k)
    {
        Vertex* left = NULL;
        Vertex* right = NULL;
        Vertex* middle = NULL;
        split(root, i + 1, left, middle);
        split(middle, j - i + 2, middle, right);
        root = merge(left, right);
        insert(root, k + 1, middle);
    }

    std::string result()
    {
        s = traversal_in_order(root);
        return s;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    Rope rope(s);
    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index) {
        int i, j, k;
        std::cin >> i >> j >> k;
        rope.process(i, j, k);
    }
    std::cout << rope.result() << std::endl;
}
