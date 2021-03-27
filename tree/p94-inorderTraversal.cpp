//给定一个二叉树的根节点 root ，返回它的 中序 遍历。

#include "tree_node.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //保证所有结点右孩子不为空，要不就是真正的右孩子，要不就是下个要遍历的节点(最右边的叶子结点除外)
    void morris_inorder(TreeNode *root, vector<int> &ret) {
        while (root != nullptr) {
            if (root->left == nullptr) { //没有左孩子，取值，访问右孩子
                ret.push_back(root->val);
                root = root->right; //右节点不一定是右孩子，可能是某个父节点
            } else {
                auto pre = root->left;                                //pre 节点就是当前 p 节点向左走一步，然后一直向右走到最后一个孩子节点(切记是孩子节点)
                while (pre->right != nullptr && pre->right != root) { //切记 pre->right != p 用来保证只是访问孩子节点，因为pre->right 可能指向 p 本身
                    pre = pre->right;
                }
                if (pre->right == nullptr) {  //pre第一次访问必为空
                    pre->right = root;        //右子树指向它遍历的下个节点
                    root = root->left;        //访问左子树
                } else {                      //pre第二次访问必不为空，且pre->right != nullptr表明p的左子树已经遍历完成
                    ret.push_back(root->val); //访问含有左子树的父节点
                    pre->right = nullptr;     //还原访问过的右节点指针，没有这句，leetcode会陷入死循环，why？
                    root = root->right;       //左子树和父节点访问完成，开始访问右子树,right可能指向某个父节点
                }
            }
        }
    }
    void recursion_inorder(TreeNode *p, vector<int> &ret) {
        if (p->left != nullptr) {
            recursion_inorder(p->left, ret);
        }
        ret.push_back(p->val);
        if (p->right != nullptr) {
            recursion_inorder(p->right, ret);
        }
    }
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root != nullptr) {
            // recursion_inorder(root, ret);
            morris_inorder(root, ret);
        }

        return ret;
    }
};

int main() {
    Solution test;
    auto f = [&test](TreeNode *root) -> vector<int> { return test.inorderTraversal(root); };

    for (size_t i = 0; i < 4; i++) {
        checkVector(GetTree(i), GetExpect(i, 1), f);
    }

    return 0;
}