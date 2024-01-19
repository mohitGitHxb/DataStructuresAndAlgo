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

//^ 8 Lemonade exchange
/*
Just maintain the counts of five and ten as you iterate through the bills.
and return false if can't give change.
* Time Complexity: O(n)
* Space Complexity: O(1)
 */

//^ 9 Valid parenthesis

class ValidParenthesis
{
public:
    /*
    Use stack to store the opening brackets and whenever you encounter a closing bracket, check if the top of the stack is matching with the current bracket. If not, return false.

    * Time Complexity: O(n)
    * Space Complexity: O(n)

     */
    bool isMatching(char a, char b)
    {
        return ((a == '(' && b == ')')) || ((a == '{' && b == '}')) || ((a == '[' && b == ']'));
    }
    bool ispar(const string &str)
    {
        if (str.empty())
            return true;
        // Your code here
        stack<char> s;
        // s.push(x[0]);
        for (int i = 0; i < str.length(); i++)
        {
            if (str.at(i) == '(' || str.at(i) == '{' || str.at(i) == '[')
            {
                s.push(str[i]);
            }
            else
            {
                if (s.empty())
                    return false;
                else if (isMatching(s.top(), str[i]) == false)
                    return false;
                else
                    s.pop();
            }
        }
        return s.empty();
    }
};

//^ 10 Check if it's possible to jump to the last index in the given array of integers
bool canJump(vector<int> &nums)
{
    // Initialize the maximum reach to the first element of the array
    int maxReach = nums[0];

    // Iterate through the array
    for (int i = 1; i < nums.size(); i++)
    {
        // If the maximum reach is less than the current index, it's not possible to jump to the last index
        if (maxReach < i)
        {
            return false;
        }
        // Update the maximum reach by taking the maximum of the current maximum reach and the combined jump length from the current index
        maxReach = max(maxReach, nums[i] + i);
    }

    // If the loop completes without returning false, it's possible to jump to the last index
    return true;
}

//^ 11 Minimum number of jumps to reach the end of the array
int jump(vector<int> &nums)
{
    // Get the size of the vector
    int n = nums.size();

    // Initialize variables to keep track of the number of jumps, the farthest we can reach, and the end of the current jump
    int jumps = 0, farthest = 0, end = 0;

    // Iterate through the vector, but stop one element before the end
    for (int i = 0; i < n - 1; i++)
    {

        // Update the farthest we can reach by comparing the current farthest with the sum of the current index and the value at that index
        farthest = max(farthest, i + nums[i]);

        // If we've reached the end of the current jump
        if (i == end)
        {

            // Increment the number of jumps
            jumps++;

            // Update the end of the current jump to be the farthest we can reach
            end = farthest;
        }
    }

    // Return the number of jumps
    return jumps;
}

//^ 12 Minimum Platforms]
/* Approach 1: Priority_queue Time Complexity - O(2NlogN) + O(N) Space Complexity - O(N)

INTUITION: Store {arr[i], dep[i]} in a vector. Sort the vector so that the train that arrives first is at the first index, the train that arrives just after the first one is at the second index and so on. We will use minHeap here (min priority_queue). Push the departure time of the first train into the heap.

Now, if arr[secondTrain] > dep[firstTrain], i.e. the first train will depart before the second train arrives. Therefore the second train can occupy the same platform. Thus we are no more concerned about the first train (as its time doesn't collapse with the next train time). Therefore we can remove the departure time of this train from the priority_queue.

Now if arr[secondTrain] <= dep[firstTrain], i.e. the first train will not depart before the second train arrives i.e. we need a separate platform for this train. And we are also concerned about the departure time of both the trains (so that if any one leaves before the next (futureTrain) arrives, we can offer the same platform to that future train). Thus push the departure time of the secondTrain in priority_queue. Now we have two items in the heap.

NOTE: We are concerned about both the departure times, but more concerned about the smaller/lesser/minimum departure i.e. the top of the minHeap.

RESULT: The number of elements in Heap will be minimum number of platforms required. Because the elements present in the Heap are nothing but the departure times which were colliding with some other trains arrival time. So we provided them a new platform. */

class MinimumPlatforms
{
public:
    int findPlatform(int arr[], int dep[], int n)
    {
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++)
        {
            v.push_back({arr[i], dep[i]});
        }

        sort(v.begin(), v.end());
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < n; i++)
        {
            pq.push(v[i].second);
            if (pq.top() < v[i].first)
                pq.pop();
        }
        return pq.size();
    }
    /* Approach 2: Priority_queue Time Complexity - O(2NlogN) + O(2N) Space Complexity - O(1)

INTUITION: Sort both the departure and arrival time arrays. maxi : maximum number of platforms required. platforms : number of platforms in use currently. i : index in "arr" array. j : index in "dep" array.

1. while(i < n && j < n) i.e. last trains arrives or last train depart.
2. j = 0 , i = 1; If(dep[j] >= arr[i]) platforms++ , i++; i.e. second train arrive before first train departs, we need extra platform (platform++), and move to the next trains arrival time (i++).
3. If(dep[j] < arr[i]) platforms-- , j++; i.e. first train departs first, so the platform becomes empty. Thus platforms--. Now move the next trains departure time.
4. if at any time, platforms > maxi then maxi = platforms. i.e. keep the track of max platforms used at any given time. */

    int findPlatform(int arr[], int dep[], int n)
    {
        sort(arr, arr + n);
        sort(dep, dep + n);
        int platforms = 1, maxi = 1;
        int i = 1, j = 0;
        while (i < n && j < n)
        {
            if (dep[j] >= arr[i])
            {
                platforms++;
                i++;
            }
            else if (dep[j] < arr[i])
            {
                platforms--;
                j++;
            }
            if (platforms > maxi)
            {
                maxi = platforms;
            }
        }
        return maxi;
    }
};

//^ 14 Insert Interval
class InsertInterval
{
private:
    /*
    ? NlogN sorting approach
     Add the new interval to the existing intervals
     and apply merge intervals function

     * O(N) T.C | O(N) space Approach
     while traversing the intervals and comparing the newInterval with the current interval, place the interval at its correct position since it is given that intervals are already sorted.
     */
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        int n = intervals.size(), i = 0;
        vector<vector<int>> res;
        // case 1: no overlapping case before the merge intervals
        // compare ending point of intervals to starting point of newInterval
        while (i < n && intervals[i][1] < newInterval[0])
        {
            res.push_back(intervals[i]);
            i++;
        }
        // case 2: overlapping case and merging of intervals
        while (i < n && newInterval[1] >= intervals[i][0])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.push_back(newInterval);
        // case 3: no overlapping of intervals after newinterval being merged
        while (i < n)
        {
            res.push_back(intervals[i]);
            i++;
        }
        return res;
    }
};

//^ 15 This function takes a vector of intervals as input and returns the count of non-overlapping intervals.
int eraseOverlapIntervals(vector<vector<int>> &intervals)
{
    // Sort the intervals in ascending order based on their start time.
    sort(intervals.begin(), intervals.end());

    // Initialize a variable to keep track of the count of merges.
    int countMerges = 0;

    // Initialize a variable to store the end time of the previous interval.
    int end = intervals.front().back();

    // Iterate through the intervals starting from the second interval.
    for (int i = 1; i < intervals.size(); i++)
    {
        // If the start time of the current interval is less than the end time of the previous interval,
        // it means there is an overlap.
        if (intervals.at(i).front() < end)
        {
            // Increment the count of merges.
            countMerges++;

            // Update the end time to be the minimum of the current end time and the end time of the current interval.
            end = min(end, intervals.at(i).back());
        }
        else
        {
            // If there is no overlap, update the end time to be the end time of the current interval.
            end = intervals.at(i).back();
        }
    }

    // Return the count of merges.
    return countMerges;
}

//^ 16 Shortest Job First
/*
Sure, I'd be happy to help you understand this code!

## Intuition
The code is an implementation of the Shortest Job First (SJF) scheduling algorithm. In SJF, the process with the smallest execution time is selected for execution next. This strategy can minimize the average waiting time for a set of processes.

## Application
This algorithm is commonly used in operating systems to schedule processes. It's particularly useful when you have a good estimate of how long each process will take, as it allows you to minimize the time processes spend waiting in the queue.

## Code Explanation
The `solve` function takes a vector `bt` of burst times as input, which represents the execution time of each process. The goal is to calculate the average waiting time for these processes when scheduled according to the SJF policy.

The function first pushes each process into a priority queue `pq`, where the priority is determined by the burst time. The process with the shortest burst time is considered the highest priority.

Then, it simulates the execution of the processes. For each process, it updates the current time on the Gantt chart `ganttChartTime` by adding the burst time of the process. It also records the completion time of each process in `completionTime`.

After all processes have been executed, it calculates the waiting time for each process, which is the completion time minus the burst time. The waiting times are stored in `waitingTime`.

Finally, it calculates the average waiting time by summing up all waiting times and dividing by the number of processes. The result is returned as the output.

## Time Complexity
The time complexity of this code is O(n log n), where n is the number of processes. This is because it needs to insert each process into the priority queue, which takes O(log n) time, and it does this n times.

## Space Complexity
The space complexity is O(n), as it needs to store the burst time, completion time, and waiting time for each process.

I hope this helps! Let me know if you have any other questions. 😊
 */

class Solution
{
    typedef long long ll;

public:
    ll sumOfWaitingTime(unordered_map<ll, ll> &waitingTime)
    {
        ll sum = 0;
        for (auto it : waitingTime)
        {
            sum += it.second;
        }
        return sum;
    }

    long long solve(vector<int> &bt)
    {
        unordered_map<ll, ll> completionTime, waitingTime;
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

        for (int i = 0; i < bt.size(); i++)
        {
            pq.push({bt.at(i), i});
        }

        ll ganttChartTime = 0;

        while (!pq.empty())
        {
            ll burstTimeCurrent = pq.top().first;
            ll processId = pq.top().second;
            pq.pop();

            ganttChartTime += burstTimeCurrent;
            completionTime[processId] = ganttChartTime;
        }
        // all processes arrive at 0 hence no need to calculate turn around time
        for (auto it : completionTime)
        {
            waitingTime[it.first] = it.second - bt[it.first];
        }

        ll averageWaitingTime = sumOfWaitingTime(waitingTime) / bt.size();

        return averageWaitingTime;
    }
};

//^ 17 Water the Plants (JUMP GAME VARIATION)
class WateringPlants{
    public:
    //Function to find the minimum number of sprinklers required.
    int min_sprinklers(int gallery[], int n)
    {
        //creating a vector of pairs to store the range of each sprinkler.
        vector<pair<int,int>> sprinklers;
        
        //iterating over the gallery array.
        for(int i=0; i<n; i++)
        {
            //checking if the gallery at current index is not -1.
            if(gallery[i] > -1)
            {
                //adding the range of each sprinkler to the vector.
                sprinklers.push_back( pair<int,int> ( i-gallery[i], i+gallery[i] ) );
            }
        }
        
        //sorting the sprinklers based on their starting range.
        sort(sprinklers.begin(), sprinklers.end());
        
        //initializing target, sprinklers_on, and i.
        int target=0, sprinklers_on=0, i=0;
        
        //looping until target is less than n.
        while(target<n)
        {
            //checking if i has reached the end of the sprinklers vector
            //or the starting range of next sprinkler is greater than the target.
            if(i==sprinklers.size() || sprinklers[i].first>target)
            {
                //returning -1 if above condition is true.
                return -1;
            }
            
            //initializing max_range with the ending range of current sprinkler.
            int max_range = sprinklers[i].second;
            
            //looping until i+1 is within the range of sprinklers vector
            //and the starting range of next sprinkler is less than or equal to target.
            while( i+1<sprinklers.size() && sprinklers[i+1].first<=target )
            {
                //updating i and max_range if above condition is true.
                i++;
                max_range = max( max_range,  sprinklers[i].second );
            }
            
            //checking if the maximum range is less than target
            //which means no sprinkle can cover the current target point.
            if(max_range<target)
            {
                //returning -1 if above condition is true.
                return -1;
            }
            
            //incrementing the count of sprinklers and updating target and i.
            sprinklers_on++;
            target = max_range +1;
            i++;
        }
        
        //returning the minimum number of sprinklers required.
        return sprinklers_on;
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
