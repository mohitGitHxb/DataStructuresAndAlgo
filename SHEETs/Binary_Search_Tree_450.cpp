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
/*
    Intuition:
        Since the BST is ordered in such a way that all nodes in the right subtree of a node are greater than the node, and all nodes in the left subtree are smaller than the node, we can use this property to efficiently find the smallest number greater than or equal to the input.

    Code Explanation:
        The findCeil function takes a pointer to the root of the BST and an input integer input that we want to find the ceiling of.
        The function uses a while loop to traverse the BST:
            If the current node's value matches the input value, we have found the exact match, so we return the input value itself.
            If the current node's value is less than the input value, we move to the right subtree (root = root->right), as we are looking for a greater value.
            If the current node's value is greater than or equal to the input value, we update ans to the current node's value and move to the left subtree (root = root->left).
        The ans variable will hold the smallest value greater than or equal to the input value when the loop finishes.
        If no node in the BST is greater than or equal to the input value, the ans will contain the last largest value found in the left subtree.

    Time Complexity:
        In the worst case, we visit all nodes on the path from the root to the leaf, or until we find a match.
        Since the tree is balanced in a well-formed BST, the time complexity is O(log n), where n is the number of nodes in the BST. In the worst case, it's O(n) for a skewed tree.

    Space Complexity:
        The algorithm uses a constant amount of extra space for variables, so the space complexity is O(1).

    Hints:
        Utilize the ordered property of the binary search tree to navigate the tree efficiently.
        If the current node's value is less than the input, move to the right subtree.
        If the current node's value is greater than or equal to the input, update the answer and move to the left subtree.
 */
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
/*
    Intuition:
        The code aims to insert a new node with the given value into the existing BST while maintaining the properties of a BST (nodes in the left subtree are smaller, and nodes in the right subtree are larger).
        To do this, the code traverses the BST from the root, moving left or right based on the comparison of the input value with the current node's value.

    Code Explanation:
        The insertIntoBST function takes a pointer to the root of the BST and the value val to be inserted.
        If the BST is empty (root is null), the function creates a new node with the given value and returns it.
        Otherwise, it initializes two pointers: curr and prev. They both initially point to the root node.
        The while loop continues until curr becomes null. Inside the loop:
            prev keeps track of the previous node visited.
            If the val is greater than the current node's value, curr moves to the right subtree (curr = curr->right).
            If the val is less than or equal to the current node's value, curr moves to the left subtree (curr = curr->left).
        After the loop, prev will be the parent node where the new node should be inserted.
        A new node with the given value val is created and inserted as the appropriate child of prev, based on the comparison with prev's value.
        Finally, the function returns the root of the modified BST.

    Time Complexity:
        The code traverses the tree from the root to the insertion point.
        The time complexity is O(h), where h is the height of the BST.
        In the best case (balanced BST), the height is log(n), and in the worst case (skewed BST), it's n.

    Space Complexity:
        The algorithm uses a constant amount of extra space for variables, so the space complexity is O(1).

    Hints:
        Utilize the properties of a binary search tree to navigate and insert the new node at the correct position.
        Keep track of both the current and previous nodes during traversal.
        Based on the comparison of values, move either left or right in the BST to find the correct insertion point.
 */
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
private:
    /*
        Intuition:
            The code aims to delete a node with the given value from the BST while maintaining the properties of a BST.
            There are three scenarios to consider:
                If the node to be deleted has no left child, replace it with its right child.
                If the node to be deleted has no right child, replace it with its left child.
                If the node to be deleted has both left and right children, find the in-order predecessor (the rightmost node in the left subtree), replace the node with the in-order predecessor, and update the left subtree to exclude the in-order predecessor.

        Code Explanation:
            The helper function takes a node as input and handles the three deletion scenarios. It returns the updated subtree root after deletion.
            The findLastRight function takes a node as input and returns the rightmost node in the subtree.
            The deleteNode function takes the root of the BST and the key (value) to be deleted.
            It starts by finding the node to be deleted. During this traversal, it keeps track of the current node using the curr pointer.
            After finding the node, it checks whether the node has a left or right child using the helper function.
            If the node to be deleted is the root, the curr pointer will be updated to the new root returned by the helper function.
            The function returns the updated root.

        Time Complexity:
            The time complexity is O(h), where h is the height of the BST.
            In the best case (balanced BST), the height is log(n), and in the worst case (skewed BST), it's n.

        Space Complexity:
            The algorithm uses a constant amount of extra space for variables, so the space complexity is O(1).

        Hints:
            Consider the three scenarios for deletion: node with no left child, node with no right child, and node with both left and right children.
            Utilize the helper function to handle the different deletion scenarios.
            Keep track of the current node during traversal to update the root if needed.
     */
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

//^ 5  Kth Smallest element in a BST
class KthSmallest
{
public:
    /*
    @ Using extra space O(K)
     */
    void inorder(TreeNode *root, int k, vector<int> &in)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, k, in);
        if (in.size() == k)
            return;
        in.emplace_back(root->val);
        inorder(root->right, k, in);
    }
    int kthSmallest(TreeNode *root, int k)
    {
        vector<int> in;
        inorder(root, k, in);
        return in.back();
    }

    /*
    @ Optimized version of above code
    ? Can also use Morris traversal to avoid extra stack space
     */
    void inorder(TreeNode *root, int &k, int &res)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, k, res);
        if (k == 1)
        {
            res = root->val;
            k--;
            return;
        }
        k--;
        inorder(root->right, k, res);
    }
    int kthSmallest_v2(TreeNode *root, int k)
    {
        int res = root->val;
        inorder(root, k, res);
        return res;
    }

    /*
    @ Morris approach
     */
    int KthSmallestElement(Node *root, int k)
    {
        if (!root)
        {
            return -1;
        }
        Node *curr = root;
        int count = 0;
        while (curr)
        {
            if (!curr->left)
            {
                if (++count == k)
                    return curr->data;
                curr = curr->right;
            }
            else
            {
                Node *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }
                if (!prev->right)
                {
                    prev->right = curr;
                    curr = curr->left;
                }
                else
                {
                    prev->right = NULL;
                    if (++count == k)
                        return curr->data;
                    curr = curr->right;
                }
            }
        }
        return -1;
    }
};

//^ 6 Validate a BST
class ValidateBST
{
private:
public:
    /*
    @ Using fact that inorder of a bst is a sorted array

    *O(N) T.C | O(N) S.C
     */
    bool isValidBST(TreeNode *root)
    {
        vector<int> inorder;
        if (!root)
            return true;
        TreeNode *curr = root;
        while (curr)
        {
            if (!curr->left)
            {
                inorder.emplace_back(curr->val);
                curr = curr->right;
            }
            else
            {
                TreeNode *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }
                if (!prev->right)
                {
                    prev->right = curr;
                    curr = curr->left;
                }

                else
                {
                    prev->right = nullptr;
                    inorder.emplace_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        for (int i = 0; i < inorder.size() - 1; i++)
        {
            if (inorder[i + 1] <= inorder[i])
                return false;
        }
        return true;
    }

    /*
    @ Simple recursion
    &- All the nodes will get some valid range according to their parent.
        Intuition:
        A binary search tree (BST) is a binary tree where each node has a value greater than or equal to the values in its left subtree and less than or equal to the values in its right subtree.
        The code checks whether the given binary tree satisfies the properties of a BST.

    Code Explanation:
        The isBST function takes a node as input along with optional lower and upper range limits.
        It starts by checking if the current node is null, which is considered a valid BST.
        Then it checks if the value of the current node falls within the specified lower and upper range limits. If not, it returns false.
        The function then makes a recursive call to isBST for the left and right subtrees:
            For the left subtree, the upper range limit is updated to the value of the current node, ensuring that all nodes in the left subtree are less than the current node.
            For the right subtree, the lower range limit is updated to the value of the current node, ensuring that all nodes in the right subtree are greater than the current node.
        The function returns true only if both the left and right subtrees are valid BSTs and the current node's value satisfies the range conditions.

    Time Complexity:
        The algorithm visits each node exactly once, so the time complexity is O(n), where n is the number of nodes in the binary tree.

    Space Complexity:
        The algorithm uses a constant amount of extra space for variables and the call stack during recursion, so the space complexity is O(h), where h is the height of the tree. In the worst case (skewed tree), the height can be n.

    Hints:
        Utilize the concept of range limits to validate the values of nodes in the tree.
        Use recursion to check the left and right subtrees while updating the range limits accordingly.
        Remember that a valid BST has its left subtree values less than the current node and its right subtree values greater than the current node.
     */
    bool isBST(Node *root, int lowerRange = -1e9, int upperRange = 1e9)
    {
        if (!root)
            return true;
        if (root->data <= lowerRange || root->data >= upperRange)
            return false;
        return isBST(root->left, lowerRange, root->data) && isBST(root->right, root->data, upperRange);
    }
};

//^ 7  LCA of a bst
class LCA
{
private:
public:
    /*
    @ This LCA code works for both BT and BST
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root || root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right)
            return root;
        return left ? left : right;
    }
};

//^ 8 Construct a binary SEARCH tree from preorder traversal
class PreorderTree
{
private:
    typedef vector<int> vi;
    typedef unordered_map<int, int> hmp;

public:
    /*
    @ Brute force NlogN Time
    ? This method works for binary trees as well as BST!
    */
    TreeNode *helper(vi &pre, vi &in, hmp &mp, int preStart, int preEnd, int inStart, int inEnd)
    {
        if (preStart > preEnd || inStart > inEnd)
            return nullptr;
        TreeNode *node = new TreeNode(pre[preStart]);
        int inRoot = mp[node->val];
        int numsLeft = inRoot - inStart;
        node->left = helper(pre, in, mp, preStart + 1, preStart + numsLeft, inStart, inStart + numsLeft);
        node->right = helper(pre, in, mp, preStart + numsLeft + 1, preEnd, inRoot + 1, inEnd);
        return node;
    }
    TreeNode *bstFromPreorder(vi &preorder)
    {
        vi inorder = preorder;
        sort(inorder.begin(), inorder.end());
        hmp mp;
        for (int i = 0; i < inorder.size(); i++)
        {
            mp[inorder[i]] = i;
        }
        TreeNode *root = helper(preorder, inorder, mp, 0, preorder.size() - 1, 0, inorder.size() - 1);
        return root;
    }

    /*
    @ Best approach using range method
    &- For each node in preorder we can decide the possible range of that node.
    &- This will help to decide where that node would be placed in the tree.
    &- For every node in left side the lower range will be 0 and upper range will be decided by the parent node [0,parent value)
    &- For every node in right side the lower range will be 0 and upper range will not be changed at all i.e [0,previous value);

    *O(N) T.c | O(1) S.C
     */
    int idx = 0;
    TreeNode *bstFromPreorder(vi &preorder, int upperLim = 1e9)
    {
        if (idx >= preorder.size() || preorder.at(idx) >= upperLim)
            return nullptr;
        TreeNode *node = new TreeNode(preorder.at(idx++));
        node->left = bstFromPreorder(preorder, node->val);
        node->right = bstFromPreorder(preorder, upperLim);
        return node;
    }
};

//^ 9 Find inorder successor and predecessor
void findPreSuc(Node *root, Node *&pre, Node *&suc, int val)
{
    pre = NULL, suc = NULL;
    Node *curr = root;
    while (root != NULL)
    {
        if (root->data >= val)
        {
            root = root->left;
        }
        else
        {
            pre = root;
            root = root->right;
        }
    }

    root = curr;
    while (root)
    {
        if (root->data <= val)
        {
            root = root->right;
        }
        else
        {
            suc = root;
            root = root->left;
        }
    }
}

//^ 11 Correct BST with two nodes swapped
class FixBST
{
public:
    /*
    @ Brute force / naive
    ? Take the inorder traversal of the bst and store it in an array
    &- Now sort this array and again do the same inorder traversal and this time keep a pointer in the array too
    &- Whenever there is a mismatch between the the array and the node->val change node->val = array[pointer]
    ! O(N) + O(NlogN) T.C | O(N) S.C
     */

    /*
    @ Better approach
        Intuition:
        A valid BST has its nodes ordered in such a way that the values of nodes in the left subtree are less than the value of the root node, and the values of nodes in the right subtree are greater than the value of the root node.
        When two nodes are swapped, this order is disturbed. The code aims to identify these two nodes and swap their values back to correct the BST.

    Code Explanation:
        The recoverTree function takes the root of the tree as input.
        The algorithm employs Morris Traversal, which is a way to traverse a binary tree without using recursion or extra space.
        The algorithm iterates through the tree using Morris Traversal:
            If the current node has no left child, it checks whether the current node's value violates the BST property (i.e., it's smaller than the previous node's value). If a violation is found, it identifies the first and last violation nodes.
            If the current node has a left child, it finds the in-order predecessor (the rightmost node in the left subtree) using the prev pointer.
            If the predecessor's right child is not connected, it connects it to the current node (this step creates a temporary threaded link).
            If the predecessor's right child is already connected to the current node (which means we've traversed the left subtree), it disconnects the link and checks for violations as before.
        Once the algorithm has identified the two nodes that are swapped, it swaps their values to correct the BST.

    Time Complexity:
        The algorithm uses Morris Traversal to traverse the tree in constant space, visiting each node exactly twice. So, the time complexity is O(n), where n is the number of nodes in the tree.

    Space Complexity:
        The algorithm uses a constant amount of extra space (excluding the input and output), so the space complexity is O(1).

    Hints:
        Morris Traversal is a clever technique to traverse a binary tree with O(1) space.
        Maintain a prev pointer to track the in-order predecessor while traversing.
        Pay close attention to the cases where the predecessor's right child is connected or not.
     */
    TreeNode *firstViolation, *lastViolation, *previousNode, *adjacentToFirst;
    void recoverTree(TreeNode *root)
    {
        TreeNode *curr = root;
        previousNode = new TreeNode(INT_MIN);
        while (curr)
        {
            if (!curr->left)
            {
                if (previousNode && (curr->val < previousNode->val))
                {
                    if (!firstViolation)
                    {
                        firstViolation = previousNode;
                        adjacentToFirst = curr;
                    }
                    else
                    {
                        lastViolation = curr;
                    }
                }
                previousNode = curr;
                curr = curr->right;
            }
            else
            {
                TreeNode *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }
                if (!prev->right)
                {
                    prev->right = curr;
                    curr = curr->left;
                }
                if (prev->right == curr)
                {
                    prev->right = nullptr;
                    if (previousNode && (curr->val < previousNode->val))
                    {
                        if (!firstViolation)
                        {
                            firstViolation = previousNode;
                            adjacentToFirst = curr;
                        }
                        else
                        {
                            lastViolation = curr;
                        }
                    }
                    previousNode = curr;
                    curr = curr->right;
                }
            }
        }
        if (firstViolation && lastViolation)
        {
            swap(firstViolation->val, lastViolation->val);
        }
        else
        {
            swap(firstViolation->val, adjacentToFirst->val);
        }
    }
};

//^ 12 Largest BST in a binary tree
class LargestBST
{
public:
    /*
    @ Brute force
    &- For each node in the binary tree check if it is a valid BST by using validateBST function
    &- After getting a valid BST count the number of nodes in the bst
    &- take the maximum of all the BSTs in the binary tree and return the maximum

    !O(N^2) Time and O(log N) S.C
     */

    /*
    @ Efficient approach
    &- Create a structure which will hold the minimum and maximum node values for the left and right subtrees and the maximum size of the BST
    &- perform a post order traversal because we will need to go to leftmost then rightmost then root
    &- For each node compare if largest number of left side < root->data < smallest value right side
    &- If the above case is true then return the structure holding minimum and maximum node value as min(left.min and root->data) and max(root->data,right.max) and size will be 1 + left.size + right.size

    &- Else return the structure holding minimum and maximum node value as INT_MIN and INT_MAX respectively with size = max(left.size,right.size)
    *O(N) Time and O(1) S.C
     */
    class Solution
    {
    private:
        struct NodeValue
        {
            int minNode, maxNode, maxSize;
            NodeValue(int mini, int maxi, int maxs)
            {
                minNode = mini;
                maxNode = maxi;
                maxSize = maxs;
            }
        };

    public:
        /*You are required to complete this method */
        // Return the size of the largest sub-tree which is also a BST
        NodeValue helper(Node *root)
        {
            if (!root)
                return NodeValue(INT_MAX, INT_MIN, 0);

            NodeValue left = helper(root->left);
            NodeValue right = helper(root->right);
            if (left.maxNode < root->data && root->data < right.minNode)
            {
                //? Valid BST
                return NodeValue(min(left.minNode, root->data), max(right.maxNode, root->data), 1 + left.maxSize + right.maxSize);
            }
            else
            {
                return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
            }
        }
        int largestBst(Node *root)
        {
            return helper(root).maxSize;
        }
    };
};

//^ Maximum sum in a binary tree which is also a BST
class MaxSumBST
{
private:
    struct NodeValue
    {
        int minNode, maxNode, maxSum;
        bool isBST;
        NodeValue(int mini, int maxi, int maxs, bool isBST = false)
        {
            minNode = mini;
            maxNode = maxi;
            maxSum = maxs;
            this->isBST = isBST;
        }
    };

public:
    NodeValue helper(TreeNode *root, int &ans)
    {
        if (!root)
            return NodeValue(INT_MAX, INT_MIN, 0, true);
        NodeValue left = helper(root->left, ans);
        NodeValue right = helper(root->right, ans);
        NodeValue curr(min(root->val, left.minNode), max(root->val, right.maxNode), left.maxSum + right.maxSum + root->val);
        if (left.isBST && right.isBST && (root->val > left.maxNode && root->val < right.minNode))
        {
            curr.isBST = true;
        }
        else
        {
            curr.isBST = false;
        }
        if (curr.isBST)
        {
            ans = max(ans, curr.maxSum);
        }

        return curr;
    }
    int maxSumBST(TreeNode *root)
    {
        int maxSum = 0;
        NodeValue temp = helper(root, maxSum);
        return maxSum;
    }
};
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
