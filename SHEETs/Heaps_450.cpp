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

//^ 5 Kth largest sum contiguous subarray
/* Function to return the Kth largest element
The approach efficiently explores all subarrays using prefix sums and maintains a min-heap to keep track of the K largest elements encountered. This allows for a systematic approach to finding the Kth largest element without sorting the entire array. The use of a min-heap ensures that the algorithm remains efficient, particularly when K is significantly smaller than the array size.
 */
int kthLargest(vector<int> &arr, int N, int K)
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < N; i++)
    {
        int currentSum = 0;
        for (int j = i; j < N; j++)
        {
            currentSum += arr[j];
            pq.push(currentSum);
            while (!pq.empty() && pq.size() > K)
            {
                pq.pop();
            }
        }
    }
    return pq.top();
}

//^ 6 Merge k Sorted Arrays
class MergeKArrays
{
public:
    /*
    ! Brute force approach
     */
    vector<int> mergeKArrays(vector<vector<int>> arr, int K)
    {
        vector<int> ans;
        for (int i = 0; i < K; i++)
        {
            ans.insert(ans.end(), arr[i].begin(), arr[i].end());
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
    /*
    % Better approach slightly
     */
    vector<int> mergeKArrays(vector<vector<int>> arr, int K)
    {
        // Create a min heap using a priority queue.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialize the merged array.
        vector<int> ans;

        // Push the first element of each array into the min heap.
        for (int i = 0; i < K; i++)
        {
            pq.push({arr[i].front(), i});
        }

        // Merge the arrays by repeatedly popping the smallest element from the min heap.
        while (!pq.empty())
        {
            int index = pq.top().second;
            ans.push_back(pq.top().first);
            pq.pop();
            if (arr[index].size() > 1)
            {
                arr[index].erase(arr[index].begin());
                pq.push({arr[index].front(), index});
            }
        }
        return ans;
    }
    /*
    * Time Complexity: O(K^2logK)
    * Space Complexity: O(K^2)
    & Best approach

     */
    vector<int> mergeKArrays(vector<vector<int>> arr, int K)
    {
        // Create a min heap using a priority queue.
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        // Initialize the merged array.
        vector<int> ans;
        // Push the first element of each array into the min heap.
        for (int i = 0; i < K; i++)
        {
            pq.push({arr[i][0], {i, 0}});
        }
        // Merge the arrays by repeatedly popping the smallest element from the min heap.
        while (!pq.empty())
        {
            int value = pq.top().first;
            int arrayIndex = pq.top().second.first;
            int elementIndex = pq.top().second.second;
            pq.pop();
            ans.push_back(value);
            if (elementIndex + 1 < arr[arrayIndex].size())
            {
                pq.push({arr[arrayIndex][elementIndex + 1], {arrayIndex, elementIndex + 1}});
            }
        }
        return ans;
    }
};

//^ 7 Merge K sorted linked lists
class MergeKLists
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int x)
        {
            data = x;
            next = NULL;
        }
    };

public:
    struct comp
    {
        bool operator()(Node *a, Node *b)
        {
            return a->data > b->data;
        }
    };
    /*
    Intuition:
    The idea is to use a priority queue (min-heap) to select the node with the smallest value. This node is then removed from its original list and added to the result list. This process is repeated until all nodes have been processed. The priority queue ensures that the smallest node is always selected next, which is necessary to maintain the sorted order of the result list.
    };
     */
    // This function merges K sorted linked lists using a priority queue.
    // The priority queue is used to always pick the smallest element from the heads of the linked lists.
    // The smallest element is then removed from its linked list and added to the result list.
    // This process is repeated until all elements from all lists have been processed.
    //* Time Complexity: O(NKlogK)
    Node *mergeKLists(Node *arr[], int K)
    {
        // Create a priority queue that stores Node pointers. The nodes are compared using the comp function.
        priority_queue<Node *, vector<Node *>, comp> pq;

        // If there are no lists to merge, return NULL.
        if (K == 0)
            return NULL;

        // Add the head of each list to the priority queue.
        for (int i = 0; i < K; i++)
            if (arr[i])
                pq.push(arr[i]);

        // Initialize the head and tail of the result list.
        Node *head = NULL, *tail = NULL;

        // Process all nodes.
        while (!pq.empty())
        {
            // Get the node with the smallest value.
            Node *temp = pq.top();
            pq.pop();

            // If the chosen list is not empty, add the next node to the priority queue.
            if (temp->next)
            {
                pq.push(temp->next);
            }

            // If this is the first node, initialize the head and tail of the result list.
            // Otherwise, add the node to the end of the result list.
            if (!head)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = tail->next;
            }
        }

        // Return the head of the merged list.
        return head;
    }
};

//^ 8 Maximum number of events attended
int maxEvents(int start[], int end[], int N)
{
    // Initialize the answer to 0
    int ans = 0;

    // Create a vector of pairs where each pair is a start and end day of an event
    vector<pair<int, int>> events;
    for (int i = 0; i < N; i++)
    {
        events.push_back({start[i], end[i]});
    }

    // Sort the events by their start days
    sort(events.begin(), events.end());

    // Initialize a priority queue to keep track of the end days of the events
    priority_queue<int, vector<int>, greater<int>> pq;

    // Initialize the current day and the index of the current event
    int day = 0, i = 0;

    // Process the events
    while (!pq.empty() || i < N)
    {
        // If the queue is empty, move to the start day of the next event
        if (pq.empty())
        {
            day = events[i].first;
        }

        // Add all events that can be attended on the current day to the queue
        while (i < N && events[i].first <= day)
        {
            pq.push(events[i++].second);
        }

        // Attend the event that ends first (it is at the top of the queue)
        pq.pop();

        // Move to the next day
        day++;

        // Increase the count of attended events
        ans++;

        // Remove all events from the queue that have already ended
        while (!pq.empty() && pq.top() < day)
        {
            pq.pop();
        }
    }

    // Return the maximum number of events that can be attended
    return ans;
}

//^ 9 Rank Transform of an Array
vector<int> arrayRankTransform(vector<int> &arr)
{
    if (arr.size() == 0)
        return {};
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < arr.size(); i++)
    {
        pq.push({arr[i], i}); // store element and its index value
    }

    int rank = 1;              // rank for first smallest element
    int last = pq.top().first; // last element which was processed (initially pq.top.first)
    while (!pq.empty())
    {
        auto itr = pq.top();
        pq.pop();
        if (itr.first != last)
        {
            rank = rank + 1; // current element is not same as last element hence rank increases
        }
        arr[itr.second] = rank;
        last = itr.first; // update last element
    }
    return arr;
}

//^ 10 Median in a stream
class MedianStream
{
private:
    /*
    The given code is a C++ implementation of a data structure that maintains a stream of integers and allows for constant-time retrieval of the median of the stream. The data structure uses two heaps, a max heap and a min heap, to keep track of the elements in the stream. The max heap stores the smaller half of the elements, and the min heap stores the larger half. This way, the top of the max heap is always the largest of the smaller elements, and the top of the min heap is always the smallest of the larger elements. If the two heaps are the same size, the median is the average of the two tops; if they are not, the median is the top of the larger heap.

   The insertHeap function inserts a new element into the appropriate heap, and then calls balanceHeaps to ensure that the heaps remain balanced (i.e., their sizes differ by at most one). The getMedian function then retrieves the median as described above.

   * The time complexity of the insertHeap and getMedian operations is O(log n), where n is the number of elements in the stream. This is because the heap operations (insertion, deletion, retrieval of the top) all take O(log n) time.

   * The space complexity is O(n), as we need to store all n elements in the heaps.

     */
    // maxHeap stores the smaller half of the elements
    priority_queue<int> smallerHalf;
    // minHeap stores the larger half of the elements
    priority_queue<int, vector<int>, greater<int>> largerHalf;

public:
    // Function to insert an element into the appropriate heap
    void insertElement(int &element)
    {
        // If the element is smaller than the largest of the smaller elements,
        // or if the smaller half is empty, insert it into the smaller half
        if (smallerHalf.size() == 0 || smallerHalf.top() > element)
        {
            smallerHalf.push(element);
        }
        // Otherwise, insert it into the larger half
        else
        {
            largerHalf.push(element);
        }
        // Ensure that the heaps remain balanced
        balanceHeaps();
    }

    // Function to balance the heaps
    void balanceHeaps()
    {
        // If the smaller half has more than one element more than the larger half,
        // move the largest of the smaller elements to the larger half
        if (smallerHalf.size() > largerHalf.size() + 1)
        {
            largerHalf.push(smallerHalf.top());
            smallerHalf.pop();
        }
        // If the larger half has more elements than the smaller half,
        // move the smallest of the larger elements to the smaller half
        else if (smallerHalf.size() < largerHalf.size())
        {
            smallerHalf.push(largerHalf.top());
            largerHalf.pop();
        }
    }

    // Function to return the median of the elements
    double getMedian()
    {
        // If the heaps are the same size, the median is the average of the two tops
        if (smallerHalf.size() == largerHalf.size())
        {
            return (smallerHalf.top() + largerHalf.top()) / 2.0;
        }
        // If they are not, the median is the top of the larger heap
        else
        {
            return smallerHalf.top();
        }
    }
};

//^ 11 Top K frequent elements

vector<int> topK(vector<int> &nums, int k)
{

    // Create an unordered map to store the frequency of each element in nums.
    unordered_map<int, int> mp;
    // Create a priority queue to store pairs of frequency and element, in descending order of frequency.
    priority_queue<pair<int, int>> pq;
    // Create a vector to store the top k frequent elements.
    vector<int> ans;

    // Iterate over each element in nums.
    for (int i = 0; i < nums.size(); i++)
    {
        // Increment the frequency of the current element in the unordered map.
        mp[nums[i]]++;
    }

    // Iterate over each pair in the unordered map.
    for (auto &x : mp)
    {
        // Push the pair into the priority queue.
        pq.push({x.second, x.first});
    }

    // Iterate k times to get the top k frequent elements.
    for (int i = 0; i < k; i++)
    {
        // Push the element with the highest frequency into the vector.
        ans.push_back(pq.top().second);
        // Remove the element with the highest frequency from the priority queue.
        pq.pop();
    }
    return ans;
}

//^ 12 Task Scheduling with waiting time n
int leastInterval(vector<char> &tasks, int n)
{
    // Priority queue to store tasks based on their counts
    priority_queue<pair<int, int>> pq;

    // Map to store the count of each task
    unordered_map<char, int> taskCount;

    // Count the frequency of each task
    for (auto &task : tasks)
    {
        taskCount[task]++;
    }

    // Push tasks and their counts into the priority queue
    for (auto &task : taskCount)
    {
        pq.push({task.second, task.first});
    }

    // Timer to keep track of the total time
    int timer = 0;

    // Process tasks until the priority queue is empty
    while (!pq.empty())
    {
        // Vector to store tasks that will be processed in the current round
        vector<pair<int, int>> v;

        // Process tasks up to 'n' times or until the priority queue is empty
        for (int i = 0; i <= n; i++)
        {
            // Check if there are tasks remaining in the priority queue
            if (!pq.empty())
            {
                // Add the top task to the vector
                v.push_back(pq.top());
                pq.pop();
            }
            else
            {
                // No more tasks remaining, break the loop
                break;
            }
        }

        // Decrease the count of each task in the vector
        for (auto &task : v)
        {
            if (--task.first > 0)
            {
                // If the count is still greater than 0, push the task back into the priority queue
                pq.push(task);
            }
        }

        // Increment the timer based on the number of tasks processed in the current round
        timer += pq.empty() ? v.size() : n + 1;
    }

    // Return the total time taken
    return timer;

    /*

    * O(N) approach
    int leastInterval(int N, int K, vector<char> &tasks) {
    // Initialize a frequency array of size 26 (for each letter of the alphabet)
    vector<int> freq(26);
    int maxFreq=0;
    // Iterate over the tasks
    for(auto &it : tasks){
        // Increment the frequency of the current task
        freq[it-'A']++;
        // Update maxFreq if the frequency of the current task is greater
        maxFreq = max(maxFreq,freq[it-'A']);
    }

    // Initialize a counter for the number of tasks with frequency equal to maxFreq
    int frequencyCounter = 0;
    // Iterate over the frequency array
    for(auto &it : freq){
        // If the frequency of the current task is equal to maxFreq, increment the counter
        if(it == maxFreq)frequencyCounter++;
    }
    // Calculate the minimum time required to complete all tasks without any idle intervals
    int time = (maxFreq-1)*(K+1) + frequencyCounter;

    // Return the maximum of time and N (the total number of tasks)
    // This is because if there are more tasks than time slots, we need to return the total number of tasks
    return max(time,N);
}


     */
}

//^ 13 Divide array in sets of K consecutive elements
class DivideArrayKconsecutiveElements
{
public:
    bool isPossibleDivide(vector<int> &nums, int k)
    {

        int n = nums.size();

        // if n is not multiple of k, then we can't divide the array

        if (n % k)
            return false;

        // sort the array

        sort(nums.begin(), nums.end());

        // store the frequency of every elements into the count map

        unordered_map<int, int> count;

        for (int i = 0; i < n; i++)
        {
            count[nums[i]]++;
        }

        // iterate over the array

        for (int i = 0; i < n; i++)
        {
            // if all the occurance of curr element is include

            if (count[nums[i]] == 0)
                continue;

            // decrement the count of occurance of curr element

            count[nums[i]]--;

            // check can we make a set of k consecutive numbers

            for (int j = 1; j < k; j++)
            {
                // if nums[i] + j is not present in count map, then we can't make a set of k consecutive numbers

                if (count[nums[i] + j] == 0)
                    return false;

                // decrement the count of occurance of nums[i] + j element

                count[nums[i] + j]--;
            }
        }

        return true;
    }

    // Refactored code to improve readability and adhere to the given rules

    bool isNStraightHand(vector<int> &hands, int k)
    {
        if (hands.size() % k)
        {
            return false;
        }

        sort(hands.begin(), hands.end());

        // Create a min heap using a priority queue to keep track of the current group of cards
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Iterate through each card in the hands vector
        for (int num : hands)
        {
            // Check if there are any incomplete groups in the priority queue
            // (groups that have a card less than num - 1 or have already k cards)
            while (!pq.empty() && (pq.top().first < num - 1 || pq.top().second == k))
            {
                // If an incomplete group is found that has less than k cards,
                // return false since it is not possible to form a complete hand
                if (pq.top().second != k)
                {
                    return false;
                }
                pq.pop();
            }

            // If the priority queue is empty or the top element has the same value as num,
            // create a new group with num as the first card and count as 1
            if (pq.empty() || pq.top().first == num)
            {
                pq.push({num, 1});
                continue;
            }

            // If the top element has a different value than num,
            // update the count of the group and push it back into the priority queue
            auto it = pq.top();
            pq.pop();
            pq.push({num, it.second + 1});
        }

        // Check if there are any remaining incomplete groups in the priority queue
        // (groups that have less than k cards)
        while (!pq.empty())
        {
            if (pq.top().second != k)
            {
                return false;
            }
            pq.pop();
        }

        // If all groups have k cards, return true
        return true;
    }
};

//^ 14 Kth largest element in a stream
vector<int> kthLargest(int k, int arr[], int n)
{
    // code here
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> v;
    for (int i = 0; i < n; i++)
    {
        pq.push(arr[i]);
        if (pq.size() == k)
            v.push_back(pq.top());
        else if (pq.size() > k)
        {
            pq.pop();
            v.push_back(pq.top());
        }
        else
            v.push_back(-1);
    }
    return v;
}

//^ 15 Design Twitter
class Twitter
{
public:
    unordered_map<int, set<int>> following;
    unordered_map<int, vector<pair<int, int>>> post;
    int time;
    Twitter()
    {
        time = 0;
    }

    void postTweet(int userId, int tweetId)
    {
        post[userId].push_back({time++, tweetId});
    }

    vector<int> getNewsFeed(int userId)
    {
        priority_queue<pair<int, int>> maxh;
        vector<int> feed;
        for (auto it : post[userId])
        {
            maxh.push(it);
        }
        for (auto iter : following[userId])
        {
            for (auto it : post[iter])
            {
                maxh.push(it);
            }
        }

        while (!maxh.empty())
        {
            feed.push_back(maxh.top().second);
            if (feed.size() == 10)
                break;
            maxh.pop();
        }

        return feed;
    }

    void follow(int followerId, int followeeId)
    {
        following[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId)
    {
        following[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

//^ 16 Maximum k sum combination from two arrays
// Given two arrays A and B, the function maxCombinations returns a vector of maximum k sum combinations from the two arrays
// * Time Complexity: O(NlogN + MlogM + KlogK)
vector<int> maxCombinations(int N, int K, vector<int> &A, vector<int> &B)
{
    // Sort arrays A and B in descending order.
    sort(A.rbegin(), A.rend());
    sort(B.rbegin(), B.rend());

    // Use a priority queue to store pairs of sums and their corresponding indices.
    // Initialize the priority queue with the K largest sum combinations from the start of arrays A and B.
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < K; i++)
    {
        pq.push({A[i] + B[0], {i, 0}});
    }

    // Initialize an empty vector to store the maximum sum combinations.
    vector<int> ans;

    // Continue the process until the priority queue is empty or K iterations have been performed.
    while (!pq.empty() && K--)
    {
        // Get the maximum sum and its corresponding indices from the top of the priority queue.
        int val = pq.top().first;
        int i = pq.top().second.first;
        int j = pq.top().second.second;
        pq.pop();

        // Add the maximum sum to the vector.
        ans.push_back(val);

        // If there are more elements in array B, add the next sum combination to the priority queue.
        if (j + 1 < N)
        {
            pq.push({A[i] + B[j + 1], {i, j + 1}});
        }
    }

    // Return the vector of maximum sum combinations.
    return ans;
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