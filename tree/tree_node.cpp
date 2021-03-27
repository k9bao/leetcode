#include "tree_node.h"

void check(vector<int> &src) {
    cout << "src:" << endl;
    for_each(src.begin(), src.end(), [](int v) { cout << v << ","; });

    auto root = CreateTree(src);
    cout << endl
         << "PreOrder:" << endl;
    prePrint(root);
    cout << endl
         << "InOrder:" << endl;
    inPrint(root);
    cout << endl
         << "PostOrder:" << endl;
    postPrint(root);
    cout << endl
         << "dst:" << endl;
    auto dst = printSrc(root);
    for_each(dst.begin(), dst.end(), [](int v) { cout << v << ","; });
    assert(src == dst);
    delTree(root);
    cout << endl
         << "---------------------------------" << endl;
}

int main() {
    //       1
    //     /   \
    //    2      3
    //     \    / \
    //      4  5   6
    //     /
    //    7
    {
        auto src = vector<int>{1, 2, 3, null, 4, 5, 6, 7};
        check(src);
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
        auto src = vector<int>{1, 2, 3, 4, 5, null, null, 6, null, null, 8, null, 7, null, 9};
        check(src);
    }
}