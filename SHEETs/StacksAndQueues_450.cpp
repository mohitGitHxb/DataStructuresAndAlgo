#include <bits/stdc++.h>
using namespace std;

//^ 1 Valid parenthesis

class ValidParenthesis
{
public:
    // Function to check if brackets are balanced or not.
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

//^ 2 Implementation of min stack
class MinStack
{
    int minEle;
    stack<pair<int, int>> s;

public:
    /*returns min element from stack*/
    int getMin()
    {

        // Write your code here
        if (s.empty())
            return -1;
        minEle = s.top().second;
        return minEle;
    }

    /*returns poped element from stack*/
    int pop()
    {
        if (s.empty())
            return -1;
        int element = s.top().first;
        s.pop();
        return element;
    }

    /*push element x into the stack*/
    void push(int x)
    {

        if (s.empty())
        {
            s.push({x, x});
        }
        else
        {
            s.push({x, min(s.top().second, x)});
        }
    }
};

//^ 3 Next greater element in a stack
/*

Intuition:

    This code utilizes a stack data structure to efficiently find the next greater element for each element in the array.
    The idea is to traverse the array from right to left, using a stack to keep track of elements seen so far.
    While iterating through the array, if an element is greater than the top of the stack, it means that the element at the top of the stack is the next greater element for the current element.
    Store this information in two separate arrays: ans to store the next greater element and indices to store the indices of these elements.

Code:

    Initialize two vectors: ans and indices, both of size N. Set all elements to -1. These vectors will be used to store the results.

    Initialize an empty stack. The stack will store pairs of elements and their indices.

    Start iterating through the array from right to left (i.e., from N-1 to 0).

    While iterating, check if the stack is not empty and the top element of the stack (in the pair) is less than or equal to the current array element. If this condition is met, it means we've found the next greater element.

    If the condition is met, update the ans vector at the current index with the element from the stack and the indices vector with the index from the stack. This information represents the next greater element for the current element.

    Push the current array element and its index onto the stack (to potentially help find the next greater element for future elements).

    After the loop, the ans vector contains the next greater element for each element in the original array.

    Return the ans vector as the result.

Time Complexity:

    The code iterates through the array once from right to left. Therefore, the time complexity is O(N), where N is the size of the input array.

Space Complexity:

    The space complexity is O(N) because we use two additional vectors (ans and indices) to store the results.

Hint:

    The stack is used to efficiently track elements and their indices for finding the next greater element.
    Pay attention to the order of the elements in the stack and the condition for updating the result vectors.
    The algorithm works by looking at elements to the right of the current element and finding the next greater one.

 */
vector<long long> nextLargerElement(vector<long long> arr, int n)
{
    // Your code here
    vector<long long> ans(n, -1);
    vector<long long> indices(n, -1);
    stack<pair<long long, long long>> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && s.top().first <= arr[i])
            s.pop();
        if (!s.empty())
        {
            ans.at(i) = s.top().first;
            indices.at(i) = s.top().second;
        }
        s.push({arr[i], i});
    }
    return ans;
}

//^ 4 Next smaller element [help classmate]
/*
 * O(N) T.C + S.C
 */
vector<int> help_classmate(vector<int> arr, int n)
{
    // Your code goes here
    vector<int> ans(n, -1), indices(n, -1);
    stack<pair<int, int>> s;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && s.top().first >= arr[i])
            s.pop();
        if (!s.empty())
        {
            ans.at(i) = s.top().first;
            indices.at(i) = s.top().second;
        }
        s.push({arr[i], i});
    }
    return ans;
}

//^ 5 Next greater element 2
/*

Intuition:

    The code uses a stack to find the next greater number for each element in the array.
    It first identifies the index of the maximum element in the array to optimize the stack usage.
    Then, it performs two iterations: one from 0 to the maximum element index and another from the maximum element index to the end of the array.
    The idea is to find the next greater element for elements in both directions (left and right of the maximum element).

Code:

    Find the index of the maximum element in the array using the max_element function. Let's call this index maxElement.

    Create a stack of pairs. Each pair stores an element value and its index.

    Initialize a vector ans of the same size as the input array and fill it with -1. This vector will store the next greater elements.

    Push the maximum element and its index onto the stack.

    Start the first iteration from maxElement - 1 and continue until index 0 (wrapping around to the end of the array).

    In this iteration, while the stack is not empty and the element at the top of the stack is less than or equal to the current element, pop elements from the stack. If the stack is not empty, update the ans vector with the next greater element from the stack.

    Push the current element and its index onto the stack.

    Start the second iteration from n - 1 (end of the array) and continue until maxElement (the maximum element index).

    Follow the same procedure as in the first iteration to find the next greater elements for the remaining elements in the array.

    Return the ans vector, which contains the next greater elements for each element in the circular array.

Time Complexity:

    The code performs two iterations, each of which goes through the entire array. Therefore, the time complexity is O(N), where N is the size of the input array.

Space Complexity:

    The space complexity is O(N) because of the ans vector and the stack, which can potentially store all elements of the input array.

Hint:

    The key to this code is to perform two iterations from the maximum element index in both directions, using a stack to efficiently find the next greater elements.
    You need to handle the circular nature of the array when looping from the end to the maximum element index.
    Remember to update the ans vector with the next greater element when found in both iterations.
 */
vector<int> nextGreaterElements(vector<int> &nums)
{
    int maxElement = max_element(nums.begin(), nums.end()) - nums.begin();
    int n = nums.size();
    stack<pair<int, int>> s;
    vector<int> ans(n, -1);
    s.push({nums[maxElement], maxElement});
    for (int i = maxElement - 1; i >= 0; i--)
    {
        while (!s.empty() && s.top().first <= nums.at(i % n))
            s.pop();
        if (!s.empty())
        {
            ans[i] = s.top().first;
        }
        s.push({nums[i % n], i % n});
    }
    for (int i = n - 1; i >= maxElement; i--)
    {
        while (!s.empty() && s.top().first <= nums.at(i % n))
            s.pop();
        if (!s.empty())
        {
            ans[i] = s.top().first;
        }
        s.push({nums[i % n], i % n});
    }
    return ans;
}

//^ 6 Sum of subarrays minimum

/*
    Denote by left[i] the distance between element A[i] and its PLE.
    Denote by right[i] the distance between element A[i] and its NLE.

    The final answer is,
    sum(A[i]*left[i]*right[i] )

    The last thing that needs to be mentioned for handling duplicate elements:
    Method: Set strict less and non-strict less(less than or equal to) for finding NLE and PLE respectively. The order doesn't matter.

    For example, the below code for finding NLE is strict less, while PLE is actually non-strict less.
    Remark: Although in both loop conditions the signs are set as >, for NLE, we make records inside the loop, while for PLE, records are done outside the loop.

*/

int sumSubarrayMins(vector<int> &nums)
{
    int n = nums.size();
    int MOD = 1e9 + 7;
    vector<int> left(n), right(n);

    // Calculate the distance to the next smaller element on the left
    stack<int> st;
    st.push(0);
    left[0] = 1;
    for (int i = 1; i < n; i++)
    {
        while (!st.empty() && nums[i] < nums[st.top()])
            st.pop();

        if (st.empty())
            left[i] = i + 1;
        else
            left[i] = i - st.top();

        st.push(i);
    }

    while (!st.empty())
        st.pop();

    // Calculate the distance to the next smaller element on the right
    st.push(n - 1);
    right[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
        while (!st.empty() && nums[i] <= nums[st.top()])
            st.pop();

        if (st.empty())
            right[i] = n - i;
        else
            right[i] = st.top() - i;

        st.push(i);
    }

    int res = 0;
    // Calculate the total contribution of each element to the final answer
    for (int i = 0; i < n; i++)
    {
        long long prod = (left[i] * right[i]) % MOD;
        prod = (prod * nums[i]) % MOD;
        res = (res + prod) % MOD;
    }

    return res;
}

//^ 7 Stock Span Problem
/*
Intuition

Question is very badly explained, so let me explain in simple words.

    Lets Consider [100,80,70,75,85]
    Question asks us to find the span of that stock's price for the current day.
    So starting from the 0 th index, we consider 100 as the current day price. So we need to find the previous highest price so their no previous data so it will be 1.
    On the 1st index (80) the previous highest price is 100, so span will be 1 and return 1.
    On the 2nd index (70) the previous highest price is 80, so span will be 1 and return 1.
    On the 3rd index (75) the previous highest price is 80, so span will be 2 and return 2.
    On the 2st index (85) the previous highest price is 100, so span will be 4 and return 4.
    The output will look like [1,1,1,2,4]

Input:
["StockSpanner","next","next","next","next","next"]
[ [ ],[100],[80],[70],[75],[85]]

Output:
[null,1,1,1,2,4]
Approach

    The StockSpanner class has a stack of pairs of integers, where the first integer represents the stock price, and the second integer represents the span of that price.
    The constructor of the class does not take any arguments and does not do anything.
    The next() method of the class takes an integer argument price, which represents the price of the stock for the current day, and returns an integer representing the span of that price.
    Initially, the span is set to 1.
    If the stack is not empty and the top of the stack has a price less than or equal to the current price, then the span is increased by the span of the top of the stack, and the top of the stack is popped.
    The pair of the current price and its span is pushed onto the stack.
    Finally, the span of the current price is returned.

Complexity:

    The time complexity of the next function is O(N), where N is the number of calls to next. This is because in the worst case, all the elements in the stack will be popped out before the current price is pushed onto the stack.
    The space complexity of the algorithm is O(N), as we are storing all the prices and their corresponding span values in the stack.

 */

class StockSpanner
{
public:
    stack<pair<int, int>> st;
    int next(int price)
    {
        int span = 1;
        while (!st.empty() && st.top().first <= price)
        {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }
    /*

    Actual Concept:
        vector <int> calculateSpan(int price[], int n)
    {
       vector<int> ans(n,1);
       stack<pair<int,int>> s;
       s.push({price[0],0});
       for(int i = 1; i < n; i++){
           while(!s.empty() && price[s.top().second] <= price[i]) s.pop();
           if(s.empty()){
               ans[i] = i + 1;
           }
           else{
               ans[i] = (i - s.top().second);
           }
        s.push({price[i],i});
       }
       return ans;
    }

     */
};

//^ 8 Sliding Window Maximum
class SlidingWindowMax
{
public:
    /*
    * BEST SOLUTION (O(N) T.C | O(N) S.C)
    Intuition:

The idea is to use a deque (double-ended queue) to efficiently keep track of the maximum element in the sliding window. The deque stores pairs of values where the first element is the value from the array, and the second element is its index. The deque will always be sorted in decreasing order of values.
Algorithm:

    Initialize an empty deque and an empty vector ans to store the maximum values.
    Iterate through each element in the array.
        If the deque is not empty and the front element's index is outside the current sliding window, remove it from the deque.
        While the deque is not empty and the back element's value is less than the current element, remove elements from the back of the deque.
        Push the current element along with its index to the back of the deque.
        If the index is greater than or equal to k - 1, add the front element's value to the ans vector (representing the maximum in the current sliding window).
    Return the ans vector.

Time Complexity:

The algorithm has a time complexity of O(n), where n is the size of the input array. Each element is processed once.
Space Complexity:

The space complexity is O(k), where k is the size of the sliding window. The deque stores at most k elements.
     */
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> ans;
        deque<pair<int, int>> dq;
        for (int i = 0; i < nums.size(); i++)
        {
            if (!dq.empty() && dq.front().second == i - k)
                dq.pop_front();
            while (!dq.empty() && dq.front().first < nums.at(i))
                dq.pop_back();
            dq.push_back({nums.at(i), i});
            if (i >= k - 1)
                ans.push_back(dq.front().first);
        }
        return ans;
    }

    /*
    % Alternative Solution using PQ
    Intuition

1st solution uses priority_queue (max-heap) for pair (nums[i], i)!
2nd solution uses double-ended queue.
3rd solution uses just array and is what you have never seen before with very high probabilty.
Approach

The solution using priority_queue (max-heap) might not be very fast, but more intuitive.

Second approach uses double-ended queue storing index for max. It is fast with a linear time.

If the second approach is fully understood, Why not using the easier data structure? Not just double-ended queue. Third approach uses just an array storing index for max with a pointer named left. This solution is fast and run also in a linear time.

Consider the concrete example

[1,3,1,2,0,5]
3

The states for the max_idx[left:] in 3rd approach( or max_idx in 2nd approach) and ans[i] within the loop are as follows:

[0]
[1]
[1,2]->ans[0]=3
[1,3]->ans[1]=3
[3,4]->ans[2]=2
[5]->ans[3]=5

Complexity

    Time complexity:

O(nlog⁡(n))→O(n)O(n \log(n))\to O(n)O(nlog(n))→O(n)

    Space complexity:

O(n)→O(k)O(n)\to O(k)O(n)→O(k)
Code

class Solution {
    using int2=pair<int, int>; //(nums[i], i)
public:

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n=nums.size();
        priority_queue<int2> pq;

        vector<int> ans(n-k+1);
        for (int i=0; i<k; i++)
            pq.push({nums[i], i});

        ans[0]=pq.top().first;
        for(int i=k; i<n; i++){
            while(!pq.empty() && pq.top().second<=(i-k))
                pq.pop(); //Pop up element not in the window
            pq.push({nums[i], i});
            ans[i-k+1]=pq.top().first;//Max element for this window
        }
        return ans;
    }
};
     */
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