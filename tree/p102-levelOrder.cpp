//给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

#include "tree_node.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    void recursion_levelorder(queue<TreeNode *> q, vector<int> &ret) {
        if (q.empty()) {
            return;
        }

        auto p = q.front();
        ret.push_back(p->val);
        q.pop();
        if (p->left != nullptr) {
            q.push(p->left);
        }
        if (p->right != nullptr) {
            q.push(p->right);
        }
        if (q.size() > 0) {
            recursion_levelorder(q, ret);
        }
    }
    vector<int> levelOrder(TreeNode *root) {
        vector<int> ret;
        if (root != nullptr) {
            queue<TreeNode *> q;
            q.push(root);
            recursion_levelorder(q, ret);
        }
        return ret;
    }
};

int main() {
    Solution test;
    auto f = [&test](TreeNode *root) -> vector<int> { return test.levelOrder(root); };

    for (size_t i = 0; i < 4; i++) {
        checkVector(GetTree(i), GetExpect(i, 3), f);
    }
    return 0;
}