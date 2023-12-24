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

class HeapFunctions
{
public:
    // Function to heapify a max heap
    void maxHeapify(std::vector<int> &heap, int n, int i)
    {
        int largest = i;       // Initialize largest as root
        int left = 2 * i + 1;  // Left child
        int right = 2 * i + 2; // Right child

        // If left child is larger than root
        if (left < n && heap[left] > heap[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && heap[right] > heap[largest])
            largest = right;

        // If largest is not root
        if (largest != i)
        {
            std::swap(heap[i], heap[largest]);

            // Recursively heapify the affected sub-tree
            maxHeapify(heap, n, largest);
        }
    }

    // Function to heapify a min heap
    void minHeapify(std::vector<int> &heap, int n, int i)
    {
        int smallest = i;      // Initialize smallest as root
        int left = 2 * i + 1;  // Left child
        int right = 2 * i + 2; // Right child

        // If left child is smaller than root
        if (left < n && heap[left] < heap[smallest])
            smallest = left;

        // If right child is smaller than smallest so far
        if (right < n && heap[right] < heap[smallest])
            smallest = right;

        // If smallest is not root
        if (smallest != i)
        {
            std::swap(heap[i], heap[smallest]);

            // Recursively heapify the affected sub-tree
            minHeapify(heap, n, smallest);
        }
    }

    // Function to build a max heap
    void buildMaxHeap(std::vector<int> &heap)
    {
        int n = heap.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            maxHeapify(heap, n, i);
    }

    // Function to build a min heap
    void buildMinHeap(std::vector<int> &heap)
    {
        int n = heap.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            minHeapify(heap, n, i);
    }

    // Function to insert an element into a max heap
    void insertMaxHeap(std::vector<int> &heap, int value)
    {
        heap.push_back(value);   // Insert the new element at the end
        int i = heap.size() - 1; // Index of the inserted element

        // Fix the max heap property by comparing with parent nodes
        while (i > 0 && heap[i] > heap[(i - 1) / 2])
        {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Function to insert an element into a min heap
    void insertMinHeap(std::vector<int> &heap, int value)
    {
        heap.push_back(value);   // Insert the new element at the end
        int i = heap.size() - 1; // Index of the inserted element

        // Fix the min heap property by comparing with parent nodes
        while (i > 0 && heap[i] < heap[(i - 1) / 2])
        {
            std::swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // Function to extract the maximum element from a max heap
    int extractMax(std::vector<int> &heap)
    {
        int n = heap.size();
        if (n == 0)
            return -1; // Heap is empty

        int maxElement = heap[0];   // Store the maximum element
        heap[0] = heap[n - 1];      // Replace the root with the last element
        heap.pop_back();            // Remove the last element
        maxHeapify(heap, n - 1, 0); // Heapify the root

        return maxElement;
    }

    // Function to extract the minimum element from a min heap
    int extractMin(std::vector<int> &heap)
    {
        int n = heap.size();
        if (n == 0)
            return -1; // Heap is empty

        int minElement = heap[0];   // Store the minimum element
        heap[0] = heap[n - 1];      // Replace the root with the last element
        heap.pop_back();            // Remove the last element
        minHeapify(heap, n - 1, 0); // Heapify the root

        return minElement;
    }
};

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
//^ 2 is Binary tree a heap
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

//^ 3 Merge two binary max heaps
class MergeHeaps
{
public:
    void heapify(vector<int> &arr, int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest])
            largest = l;
        if (r < n && arr[r] > arr[largest])
            largest = r;
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m)
    {
        // your code here
        vector<int> merged(a.begin(), a.end());
        merged.insert(merged.end(), b.begin(), b.end());
        for (int i = merged.size() / 2; i >= 0; i--)
        {
            heapify(merged, merged.size(), i);
        }
        return merged;
    }
};

//^ 4 Minimum cost to connect ropes
long long minCost(long long arr[], long long n)
{
    // Your code here
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++)
        pq.push(arr[i]);
    long long cost = 0;
    while (pq.size() > 1)
    {
        long long first = pq.top();
        pq.pop();
        long long second = pq.top();
        pq.pop();
        cost += first + second;
        pq.push(first + second);
    }
    return cost;
}
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