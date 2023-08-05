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

//^ 3 Insert a node in the bst
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);
    TreeNode *curr = root;
    TreeNode *prev = curr;
    while (curr)
    {
        prev = curr;
        if (val > curr->val)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    if (val > prev->val)
    {
        prev->right = new TreeNode(val);
    }
    else
    {
        prev->left = new TreeNode(val);
    }
    return root;
}

//^ 4 Delete node in a bst
class DeleteNodesBST
{
public:
    TreeNode *helper(TreeNode *root)
    {
        if (!root->left)
        {
            return root->right;
        }
        else if (!root->right)
            return root->left;
        TreeNode *rightChild = root->right;
        TreeNode *leftLastRight = findLastRight(root->left);
        leftLastRight->right = rightChild;
        return root->left;
    }
    TreeNode *findLastRight(TreeNode *root)
    {
        if (!root->right)
        {
            return root;
        }
        while (root->right)
        {
            root = root->right;
        }
        return root;
    }
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (!root)
            return root;
        if (root->val == key)
            return helper(root);
        TreeNode *curr = root;
        while (root)
        {
            if (root->val > key)
            {
                if (root->left && root->left->val == key)
                {
                    root->left = helper(root->left);
                    break;
                }
                else
                {
                    root = root->left;
                }
            }
            else
            {
                if (root->right && root->right->val == key)
                {
                    root->right = helper(root->right);
                    break;
                }
                else
                {
                    root = root->right;
                }
            }
        }
        return curr;
    }
};
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
