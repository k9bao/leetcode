#include <iostream>
#include <queue>
#include <vector>

using namespace std;

//Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
    void SetLR(TreeNode *l, TreeNode *r = nullptr) {
        left = l;
        right = r;
    }
} TreeNode;

void recursion_levelorder(queue<TreeNode *> q, vector<TreeNode *> &ret) {
    if (q.empty()) {
        return;
    }

    auto p = q.front();
    ret.push_back(p);
    if (p != nullptr) {
        q.push(p->left);
        q.push(p->right);
    }
    q.pop();
    if (q.size() > 0) {
        recursion_levelorder(q, ret);
    }
}

vector<int> printTree(TreeNode *root) {
    vector<TreeNode *> retTemp;
    queue<TreeNode *> q;
    q.push(root);
    recursion_levelorder(q, retTemp);
    vector<int> ret;
    for (auto i = retTemp.begin(); i != retTemp.end(); i++) {
        ret.push_back((*i) != nullptr ? (*i)->val : INT_MIN);
    }

    for (size_t i = ret.size() - 1; i >= 0; i--) { //删除后边连续无效值
        if (ret[i] != INT_MIN) {
            ret.assign(ret.begin(), ret.begin() + i + 1);
            break;
        }
    }

    for_each(ret.begin(), ret.end(), [](int v) { cout << v << ","; });
    cout << endl;
    return ret;
}

vector<TreeNode> initTree(const int n) {
    vector<TreeNode> p;
    for (size_t i = 0; i < n; i++) {
        TreeNode t(i);
        p.push_back(t);
    }
    return p;
}

TreeNode *initTree(vector<int> t) {
    if (t.size() == 0) {
        return nullptr;
    }
    queue<TreeNode *> q;
    TreeNode *root = new TreeNode(t[0]);
    q.push(root);
    int levelSize = 1;
    int cur = 1;
    while (cur < t.size()) {
        for (int i = cur; i < levelSize; i += 2) {
            auto node = q.front();
            q.pop();
            if (i == t.size()) {
                return root;
            } else {
                if (t[i] != INT_MIN) {
                    auto temp = new TreeNode(t[i]);
                    node->left = temp;
                    q.push(temp);
                }
            }
            if (i + 1 == t.size()) {
                return root;
            } else {
                if (t[i] != INT_MIN) {
                    auto temp = new TreeNode(t[i]);
                    node->right = temp;
                    q.push(temp);
                }
            }
        }
        levelSize = q.size() * 2;
    }
    return root;

    // vector<TreeNode *> p;
    // p.push_back(nullptr); //方便计算下标
    // for (size_t i = 0; i < t.size(); i++) {
    //     if (t[i] != INT_MIN) {
    //         TreeNode *temp = new TreeNode(t[i]);
    //         p.push_back(temp);
    //     } else {
    //         p.push_back(nullptr);
    //     }
    // }

    // int i = 0;
    // int valid = 1;
    // while (i < p.size()) {
    //     for (size_t i = 0; i < valid; i++) {
    //         assert(p[i] != nullptr);
    //         p[i]->left = p[i + valid];
    //         if (p[i + valid] != nullptr) {
    //             /* code */
    //         }

    //         p[i]->right = p[i + valid + 1];
    //     }
    // }

    // for (size_t i = 1; i < p.size() / 2 + 1; i++) {
    //     if (p[i] != nullptr) {
    //         p[i]->left = p[i * 2 < p.size() ? i * 2 : 0];
    //         p[i]->right = p[i * 2 + 1 < p.size() ? i * 2 + 1 : 0];
    //     }
    // }

    // return p.size() > 1 ? p[1] : p[0];
}

void clearTree(TreeNode *root) {
    vector<TreeNode *> retTemp;
    queue<TreeNode *> q;
    q.push(root);
    recursion_levelorder(q, retTemp);
    vector<int> ret;
    for (auto i = retTemp.begin(); i != retTemp.end(); i++) {
        if (*i != nullptr) {
            delete *i;
            *i = nullptr;
        }
    }
}
