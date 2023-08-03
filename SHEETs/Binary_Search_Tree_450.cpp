#include <bits/stdc++.h>
using namespace std;
/*
Binary Search Tree is a node-based binary tree data structure which has the following properties:

    The left subtree of a node contains only nodes with keys lesser than the node’s key.
    The right subtree of a node contains only nodes with keys greater than the node’s key.
    The left and right subtree each must also be a binary search tree.
 */

// % leetcode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//% GFG
struct Node
{
    int data;
    Node *left, *right;
    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
    Node() : data(0), left(NULL), right(NULL) {}
};

//^ 1 Search in a binary search tree
TreeNode *searchBST(TreeNode *root, int val)
{
    return ((!root || root->val == val) ? root : (root->val > val) ? searchBST(root->left, val)
                                                                   : searchBST(root->right, val));
}

//^ 2 Ceil of a binary search tree
int findCeil(Node *root, int input)
{
    if (!root)
        return -1;
    int ans = -1;
    while (root)
    {
        if (root->data == input)
        {
            return root->data;
        }
        else if (root->data < input)
        {
            root = root->right;
        }
        else
        {
            ans = root->data;
            root = root->left;
        }
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
