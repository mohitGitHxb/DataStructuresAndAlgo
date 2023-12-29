#include <bits/stdc++.h>
using namespace std;

/*
Sure! Here is a list of crucial information regarding greedy approaches and how they differ from dynamic programming:

Greedy approach:

Greedy algorithms make locally optimal choices at each step with the hope of finding a global optimum.
They are simple and efficient.
They do not always guarantee an optimal solution.
Dynamic programming:

Dynamic programming breaks down a problem into smaller overlapping subproblems and solves them in a bottom-up manner.
It stores the solutions to subproblems in a table to avoid redundant calculations.
It guarantees an optimal solution.
Decision-making:

Greedy approach: Makes the choice that seems best at the current moment without considering the future consequences.
Dynamic programming: Considers all possible choices and selects the one that leads to the optimal solution.
Approach:

Greedy approach: Starts with an empty solution and iteratively adds components that offer the most immediate benefit.
Dynamic programming: Solves subproblems and builds up the solution from the bottom.
Time complexity:

Greedy approach: Often has a time complexity of O(n log n) or O(n), depending on the problem.
Dynamic programming: Often has a time complexity of O(n^2) or O(n^3), depending on the problem.
Optimal substructure:

Greedy approach: Does not require the problem to have optimal substructure.
Dynamic programming: Requires the problem to have optimal substructure.
These points should give you a basic understanding of greedy approaches and how they differ from dynamic programming. Let me know if you have any further questions!

 */

//^ 1 N meetings in one room
/*
 * Time complexity: O(n log n)
 * Space complexity: O(1)
 */
int maxMeetings(int start[], int end[], int n)
{
    // Your code here
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++)
        v.emplace_back(start[i], end[i]);

    // sort according to end time
    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b)
         { return a.second < b.second; });

    // greedy approach to find max meeting in one room.
    // We can only take a meeting if it does not overlap with the previous one.
    int count = 1, endtime = v[0].second;
    for (int i = 1; i < n; i++)
    {
        if (v[i].first > endtime)
        {
            count++;
            endtime = v[i].second;
        }
    }
    return count;
}

//^ 2 Maximum Meetings in One Room (Extension of above)
// User function Template for C++

class MaximumMeetings
{
private:
    /*
    Time complexity: The time complexity of this code is O(n log n) due to the sorting operation, where n is the number of meetings.

    Space complexity: The space complexity of this code is O(n) because of the space used to store the meetings and the answer vector, where n is the number of meetings.
     */
    typedef pair<int, int> pi;
    typedef pair<pi, int> pii;

public:
    // Comparator function for sorting
    static bool comp(pii a, pii b)
    {
        // If end times are different, sort by end time
        // If end times are same, sort by meeting number
        return (a.first.second != b.first.second) ? a.first.second < b.first.second : a.second < b.second;
    }

    vector<int> maxMeetings(int N, vector<int> &S, vector<int> &F)
    {
        vector<pii> v;   // Vector to store start and end times along with meeting number
        vector<int> ans; // Vector to store the meeting numbers that can be held

        // Store start and end times along with meeting number in vector v
        for (int i = 0; i < N; i++)
        {
            v.push_back({{S[i], F[i]}, i + 1});
        }

        // Sort the vector v based on end times and meeting number
        sort(v.begin(), v.end(), comp);

        // Add the first meeting to the answer vector
        ans.push_back(v[0].second);

        // Keep track of the end time of the last added meeting
        int prev = v[0].first.second;

        // Iterate over the rest of the meetings
        for (int i = 1; i < v.size(); i++)
        {
            // If the start time of the current meeting is greater than the end time of the last added meeting
            if (v[i].first.first > prev)
            {
                // Add the current meeting to the answer vector
                ans.push_back(v[i].second);
                // Update the end time of the last added meeting
                prev = v[i].first.second;
            }
        }

        // Sort the answer vector
        sort(ans.begin(), ans.end());

        // Return the answer vector
        return ans;
    }
};

/*

^ 3 Candy store
The problem is about buying candies from a candy store where the price of each candy is given in an array. The store has a special offer: for every candy bought, K candies can be bought for free. The goal is to find the minimum and maximum amount that can be spent to buy all the candies.

The minimum amount is found by always buying the cheapest candy available and taking the most expensive candies for free. This is done by iterating from the start of the sorted array and skipping K candies from the end for each candy bought.

The maximum amount is found by always buying the most expensive candy available and taking the cheapest candies for free. This is done by iterating from the end of the sorted array and skipping K candies from the start for each candy bought.


 */
vector<int> candyStore(int candies[], int N, int K)
{
    vector<int> ans(2);         // Initialize a vector to store the minimum and maximum amount spent
    sort(candies, candies + N); // Sort the array of candies in ascending order

    int i = 0, j = N - 1; // Initialize two pointers, one at the start and one at the end of the array
    while (i <= j)
    {                           // While the start pointer is less than or equal to the end pointer
        ans[0] += candies[i++]; // Add the price of the candy at the start pointer to the minimum amount spent and increment the start pointer
        int steps = K;          // Initialize a variable to keep track of the number of candies to skip
        while (j >= i && steps--)
        {        // While the end pointer is greater than or equal to the start pointer and there are still candies to skip
            j--; // Decrement the end pointer
        }
    }

    i = N - 1; // Reset the start pointer to the end of the array
    j = 0;     // Reset the end pointer to the start of the array
    while (i >= j)
    {                           // While the start pointer is greater than or equal to the end pointer
        ans[1] += candies[i--]; // Add the price of the candy at the start pointer to the maximum amount spent and decrement the start pointer
        int steps = K;          // Initialize a variable to keep track of the number of candies to skip
        while (i >= j && steps--)
        {        // While the start pointer is greater than or equal to the end pointer and there are still candies to skip
            j++; // Increment the end pointer
        }
    }

    return ans; // Return the vector containing the minimum and maximum amount spent

    //? Replace While loops with this to make code shorter
    // for (int i = 0, j = N - 1; i <= j; i++, j -= K)
    // {
    //     ans[0] += candies[i];
    //     ans[1] += candies[j];
    // }
}

//^ 4 Huffman encoding
class HuffmanCodes
{

private:
public:
    /**
    Steps to print codes from Huffman Tree
    HuffmanCodes will be:
    f : 0
    c : 100
    d : 101
    a : 1100
    b : 1101
    e : 111
    HuffmanCodes will be:
    f : 0
    c : 100
    d : 101
    a : 1100
    b : 1101
    e : 111

    * Time Complexity: O(NlogN)
    * Space Complexity: O(N)
    */

    // Node structure for Huffman Tree
    struct Node
    {
        Node *left;
        Node *right;
        int freq;
        // Constructor for Node
        Node(int freq)
        {
            left = NULL;
            right = NULL;
            this->freq = freq;
        }
    };

    // Comparator for priority queue
    struct compare
    {
        bool operator()(Node *l, Node *r)
        {
            // Nodes with lower frequency have higher priority
            return l->freq > r->freq;
        }
    };

    vector<string> huffmanCodes(string S, vector<int> f, int N)
    {
        // Priority queue to store tree nodes
        priority_queue<Node *, vector<Node *>, compare> minHeap;
        for (int i = 0; i < N; i++)
        {
            // Create a new node and push it to the priority queue
            minHeap.push(new Node(f[i]));
        }
        while (minHeap.size() > 1)
        {
            // Remove the two nodes of highest priority (lowest frequency) from the queue
            Node *left = minHeap.top();
            minHeap.pop();
            Node *right = minHeap.top();
            minHeap.pop();

            // Create a new internal node with these two nodes as children and with frequency equal to the sum of the two nodes' frequencies.
            Node *parent = new Node(left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            // Add the new node to the queue.
            minHeap.push(parent);
        }

        // The remaining node is the root node and the tree is complete.
        Node *root = minHeap.top();

        vector<string> ans;
        // Traverse the Huffman Tree and store Huffman Codes in a map.
        preOrder(root, ans, "");
        return ans;
    }

    void preOrder(Node *root, vector<string> &ans, string str)
    {
        if (root == NULL)
        {
            return;
        }
        if (!root->left && !root->right)
        {
            // If this is a leaf node, then it contains one of the input characters, add it to Huffman Codes map.
            ans.push_back(str);
        }
        // Traverse left subtree and add '0' to the string.
        preOrder(root->left, ans, str + "0");
        // Traverse right subtree and add '1' to the string.
        preOrder(root->right, ans, str + "1");
    }
};

//^ 5 Fractional Knapsack
class Knapsack
{
private:
    struct Item
    { // Structure to hold the value and weight of each item
        int value;
        int weight;
    };

public:
    static bool cmp(pair<double, Item> a, pair<double, Item> b)
    { // Comparator function for sorting
        if (a.first == b.first)
        {
            return a.second.weight < b.second.weight;
        }
        return a.first > b.first;
    }

    // Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
        vector<pair<double, Item>> v; // Vector to hold the value/weight ratio and item
        for (int i = 0; i < n; i++)
        {
            v.emplace_back((arr[i].value * 1.0 / arr[i].weight * 1.0), arr[i]); // Calculate value/weight ratio and store it with item
        }

        sort(v.begin(), v.end(), cmp); // Sort the vector based on value/weight ratio
        double ans = 0;                // Variable to hold the maximum value
        for (auto it : v)
        { // Iterate through each item
            if (it.second.weight > W)
            {                                        // If item's weight is more than the remaining capacity of knapsack
                ans += (double)(it.first * W * 1.0); // Take fraction of item's value
                W = 0;                               // No capacity left in knapsack
            }
            else
            {                           // If item's weight is less than or equal to the remaining capacity of knapsack
                ans += it.second.value; // Take the whole item
                W -= it.second.weight;  // Decrease the remaining capacity of knapsack
            }
        }
        return ans; // Return the maximum value
    }
};

//^ 6 Job Sequencing Problem
class JobSequence
{
private:
    struct Job
    {
        int id;
        int dead;
        int profit;
    };

public:
    // Function to schedule the jobs to maximize profit
    vector<int> JobScheduling(Job arr[], int n)
    {
        // Sort the jobs in descending order of profit
        sort(arr, arr + n, [](Job a, Job b)
             { return a.profit > b.profit; });

        // Initialize the answer vector with 2 elements
        vector<int> ans(2);

        // Initialize the maximum deadline to 0
        int maxDeadline = 0;

        // Find the maximum deadline from the jobs
        for (int i = 0; i < n; i++)
        {
            maxDeadline = max(maxDeadline, arr[i].dead);
        }

        // Initialize a slot vector with size maxDeadline + 1 and fill it with -1
        vector<int> slot(maxDeadline + 1, -1);

        // Loop through the jobs
        for (int i = 0; i < n; i++)
        {
            // Store the current job's profit, id and deadline
            int currentProfit = arr[i].profit;
            int currJobId = arr[i].id;
            int currDeadline = arr[i].dead;

            // Loop from the current job's deadline to 1
            for (int j = currDeadline; j > 0; j--)
            {
                // If the slot is empty
                if (slot[j] == -1)
                {
                    // Assign the current job to the slot
                    slot[j] = currJobId;

                    // Increase the number of jobs done
                    ans.front()++;

                    // Increase the total profit
                    ans.back() += currentProfit;

                    // Break the loop as the job has been scheduled
                    break;
                }
            }
        }

        // Return the answer vector containing the number of jobs done and the maximum profit
        return ans;
    }
};

//^ 7 Minimum number of coins
/* 
This code is a solution to the problem of finding the minimum number of currency denominations that sum up to a given amount (N). The denominations used are {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1}.

The function `minPartition(int N)` takes an integer N as input and returns a vector of integers. The vector contains the denominations used to sum up to N.

The function works as follows:

1. It initializes a vector `denominations` with the available denominations in descending order. This is done to ensure that the largest denomination is used first, which helps in minimizing the number of denominations used.

2. It initializes an empty vector `result` to store the denominations used.

3. It then iterates over each denomination in the `denominations` vector. For each denomination, it checks if the current denomination is less than or equal to the remaining amount (N). If it is, it subtracts the denomination from N and adds the denomination to the `result` vector. This process is repeated until the remaining amount (N) is less than the current denomination.

4. Finally, it returns the `result` vector which contains the denominations used to sum up to N.

Time Complexity:
The time complexity of this function is O(n), where n is the number of denominations. This is because in the worst case, the function iterates over each denomination once.

Space Complexity:
The space complexity of this function is O(m), where m is the number of denominations used to sum up to N. This is because the `result` vector stores each denomination used. In the worst case, this could be equal to N (when all denominations used are 1), so the space complexity could also be considered as O(N).
 */
vector<int> minPartition(int N)
{
    vector<int> denominations = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    vector<int> result;
    for (int i = 0; i < denominations.size(); i++)
    {
        while (N >= denominations[i])
        {
            N -= denominations[i];
            result.push_back(denominations[i]);
        }
    }

    return result;
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