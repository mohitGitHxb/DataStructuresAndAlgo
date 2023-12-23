#include <bits/stdc++.h>
using namespace std;
/*
Properties of Heap Data Structure in C++:
1. Complete Binary Tree: A heap is a complete binary tree, which means all levels of the tree are completely filled except possibly for the last level, which is filled from left to right.

2. Heap Property: In a max heap, for any given node i, the value of node i is greater than or equal to the values of its children. In a min heap, the value of node i is less than or equal to the values of its children.

3. Heap Order: In a max heap, the parent nodes have higher values than their children nodes. In a min heap, the parent nodes have lower values than their children nodes.

4. Heapify Operation: Heapify is the process of creating a heap from an array. It rearranges the elements of the array to satisfy the heap property.

5. Heap Operations: The main operations performed on a heap are insertion, deletion, and retrieval of the maximum or minimum element.

Relation between Connected Nodes in a Heap:
In a heap, the relationship between connected nodes is determined by their indices. For any given node i, its left child is located at index 2i+1 and its right child is located at index 2i+2. Similarly, the parent of a node at index i is located at index floor((i-1)/2). This relationship ensures that the heap property is maintained and allows for efficient traversal and manipulation of the heap.
 */

//^ 1 Kth Smallest Element

/**
 * Returns the kth smallest element from a vector of integers.
 *
 * @param nums - The vector of integers.
 * @param n - The size of the vector.
 * @param k - The kth smallest element to find.
 * @return The kth smallest element.
 */
int kthSmallest(vector<int> &nums, int n, int k)
{
    // Create a max heap to store the k smallest elements
    priority_queue<int> maxHeap;

    // Iterate through the vector
    for (int i = 0; i < n; i++)
    {
        // Push the current element into the max heap
        maxHeap.push(nums[i]);

        // If the size of the max heap is greater than k, remove the largest element
        if (maxHeap.size() > k)
        {
            maxHeap.pop();
        }
    }

    // Return the top element of the max heap, which is the kth smallest element
    return maxHeap.top();
}
//^ is Binary tree a heap
class CheckIfHeap
{
private:
    struct Node
    {
        int data;
        Node *left, *right;
        Node(int data)
        {
            this->data = data;
            this->left = this->right = nullptr;
        }
    };

public:
    // properties of heaps
    // complete binary tree
    // child nodes < parent (max-heap);
    int countNodes(Node *tree)
    {
        if (!tree)
            return 0;
        return 1 + countNodes(tree->left) + countNodes(tree->right);
    }
    bool isCBT(Node *tree, int i, int nodeCount)
    {
        if (!tree)
            return true;
        if (i >= nodeCount)
            return false;
        return isCBT(tree->left, 2 * i + 1, nodeCount) && isCBT(tree->right, 2 * i + 2, nodeCount);
    }
    bool isMaxOrder(Node *tree)
    {
        if (!tree->left && !tree->right)
            return true;
        if (!tree->right)
        {
            return tree->data > tree->left->data;
        }
        return tree->data > tree->left->data && tree->data > tree->right->data && isMaxOrder(tree->left) && isMaxOrder(tree->right);
    }
    bool isHeap(struct Node *tree)
    {
        // code here
        int nodeCount = countNodes(tree);
        if (isCBT(tree, 0, nodeCount) && isMaxOrder(tree))
            return true;
        return false;
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}