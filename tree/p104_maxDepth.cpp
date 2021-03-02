//给定一个二叉树，找出其最大深度。
//二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

#include <iostream>
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
    int depth(TreeNode *root, int &maxDep) {
        if (root == nullptr) {
            return 0;
        }
        auto l = depth(root->left, maxDep);
        auto r = depth(root->right, maxDep);
        maxDep = max(maxDep, max(l, r) + 1);
        return max(l, r) + 1;
    }
    int maxDepth(TreeNode *root) {
        int maxDep = 0;
        depth(root, maxDep);
        return maxDep;
    }
};

int main() {
    Solution test;
    //           1
    //            \
    //             2
    //            /
    //           3
    {
        TreeNode t3(3);
        TreeNode t2(2, &t3, nullptr);
        TreeNode t1(1, nullptr, &t2);
        auto ret = test.maxDepth(&t1);
        cout << "ret = " << ret << endl;
        assert(ret == 3); //1,2,3
    }

    //           1
    //          / \
    //         2   3
    //       /  \
    //      4    5
    {
        TreeNode t4(4);
        TreeNode t5(5);
        TreeNode t2(2, &t4, &t5);
        TreeNode t3(3);
        TreeNode root(1, &t2, &t3);
        auto ret = test.maxDepth(&root);
        cout << "ret = " << ret << endl;
        assert(ret == 3); //4,2,1,3或5，2，1，3
    }

    //          1
    //         / \
    //        2   3
    //       / \
    //      4   5
    //     /     \
    //    6       8
    //     \       \
    //      7       9
    {
        TreeNode t7(7);
        TreeNode t6(6, nullptr, &t7);
        TreeNode t9(9);
        TreeNode t8(8, nullptr, &t9);
        TreeNode t4(4, &t6, nullptr);
        TreeNode t5(5, nullptr, &t8);
        TreeNode t2(2, &t4, &t5);
        TreeNode t3(3);
        TreeNode root(1, &t2, &t3);
        auto ret = test.maxDepth(&root);
        cout << "ret = " << ret << endl;
        assert(ret == 5); //7,6,5,4,3,8,9
    }
    {
        auto ret = test.maxDepth(nullptr);
        cout << "ret = " << ret << endl;
        assert(ret == 0);
    }

    return 0;
}