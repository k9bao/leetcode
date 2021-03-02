//给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
    TreeNode t4(4);
    TreeNode t5(5);
    TreeNode t2(2, &t4, &t5);
    TreeNode t3(3);
    TreeNode root(1, &t2, &t3);
    //          1
    //        2   3
    //      4   5
    auto ret = test.levelOrder(&root);
    cout << "ret = " << ret.size() << endl;
    for_each(ret.begin(), ret.end(), [](int &v) { cout << v << ","; });
    assert((ret == vector<int>{1, 2, 3, 4, 5}));
    cout << endl;
    TreeNode t7(7);
    TreeNode t6(6, nullptr, &t7);
    t4.left = &t6;
    TreeNode t9(9);
    TreeNode t8(8, nullptr, &t9);
    t5.right = &t8;
    //          1
    //        2   3
    //      4   5
    //    6       8
    //      7       9
    ret = test.levelOrder(&root);
    cout << "ret = " << ret.size() << endl;
    for_each(ret.begin(), ret.end(), [](int v) { cout << v << ","; });
    cout << endl;
    assert((ret == vector<int>{1, 2, 3, 4, 5, 6, 8, 7, 9}));

    return 0;
}