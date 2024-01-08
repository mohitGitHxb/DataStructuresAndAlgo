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

/*
This class defines a set of stack operations for finding previous and next smaller or greater elements for each element in an array.

prevSmallerElement: Finds the index of the previous smaller element for each element in the array.
nextSmallerElement: Finds the index of the next smaller element for each element in the array.
prevGreaterElement: Finds the index of the previous greater element for each element in the array.
nextGreaterElement: Finds the index of the next greater element for each element in the array
 */
class StackOperations
{
public:
    // Function to find the previous smaller element for each element in the array
    std::vector<long long> prevSmallerElement(std::vector<int> &arr)
    {
        // Create a vector to store the indices of the previous smaller elements
        std::vector<long long> indices(arr.size(), -1);

        // Create a stack to store pairs of values (element, index)
        std::stack<std::pair<long long, long long>> stk;

        // Iterate through the array
        for (long long i = 0; i < arr.size(); i++)
        {
            // Keep popping elements from the stack until we find a smaller element
            while (!stk.empty() && arr.at(stk.top().second) >= arr.at(i))
                stk.pop();

            // If the stack is not empty, update the index of the previous smaller element
            if (!stk.empty())
                indices.at(i) = stk.top().second;

            // Push the current element and its index onto the stack
            stk.push({arr.at(i), i});
        }

        // Return the vector of indices of the previous smaller elements
        return indices;
    }

    // Function to find the next smaller element for each element in the array
    std::vector<long long> nextSmallerElement(std::vector<int> &arr)
    {
        // Create a vector to store the indices of the next smaller element for each element in the array
        std::vector<long long> indices(arr.size(), arr.size());

        // Create a stack to store the elements in decreasing order along with their indices
        std::stack<std::pair<long long, long long>> stk;

        // Iterate through the array from right to left
        for (long long i = arr.size() - 1; i >= 0; i--)
        {
            // Remove elements from the stack that are greater than the current element
            while (!stk.empty() && arr.at(stk.top().second) > arr.at(i))
                stk.pop();

            // If there is still an element in the stack, it is the next smaller element for the current element
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }

            // Push the current element along with its index into the stack
            stk.push({arr.at(i), i});
        }

        // Return the vector of indices
        return indices;
    }

    // Function to find the previous greater element for each element in the array
    std::vector<long long> prevGreaterElement(std::vector<int> &arr)
    {
        // Create a stack to store pairs of elements and their indices
        std::stack<std::pair<long long, long long>> stk;

        // Create a vector to store the indices of the previous greater elements
        std::vector<long long> indices(arr.size(), -1);

        // Iterate through the elements of the array
        for (long long i = 0; i < arr.size(); i++)
        {
            // Keep popping elements from the stack until the top element is greater than the current element
            while (!stk.empty() && arr.at(stk.top().second) <= arr.at(i))
                stk.pop();

            // If the stack is not empty, set the index of the previous greater element for the current element
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }

            // Push the current element and its index onto the stack
            stk.push({arr.at(i), i});
        }

        // Return the vector containing the indices of the previous greater elements
        return indices;
    }

    // Function to find the next greater element for each element in the array
    std::vector<long long> nextGreaterElement(std::vector<int> &arr)
    {
        // Create a stack to store elements along with their indices
        std::stack<std::pair<long long, long long>> stk;

        // Create a vector to store the indices of the next greater element for each element in the array
        std::vector<long long> indices(arr.size(), arr.size());

        // Iterate through the array from right to left
        for (long long i = arr.size() - 1; i >= 0; i--)
        {
            // While the stack is not empty and the element at the top of the stack is smaller than the current element,
            // pop elements from the stack
            while (!stk.empty() && arr.at(stk.top().second) < arr.at(i))
                stk.pop();

            // If the stack is not empty, store the index of the top element as the index of the next greater element for the current element
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }

            // Push the current element and its index into the stack
            stk.push({arr.at(i), i});
        }

        // Return the vector of indices of the next greater element for each element in the array
        return indices;
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

/**
 * The code is designed to solve a problem involving asteroids represented as an array of integers. Each asteroid is moving in a certain direction (positive meaning right, negative meaning left) at the same speed. When two asteroids collide, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

The asteroidCollision function processes the array of asteroids. It uses a stack (stk) to keep track of the asteroids that have not yet collided.

Here’s a step-by-step explanation:

The function iterates over each asteroid in the input array.
If the asteroid is moving to the right (positive), it’s pushed onto the stack because it can’t collide with any asteroid to its right.
If the asteroid is moving to the left (negative), it may collide with some asteroids in the stack. A while loop is used to process these potential collisions:
If the top asteroid in the stack is moving to the right and its size is less than the current asteroid, it’s removed from the stack because it would explode upon collision.
If the top asteroid in the stack is moving to the right and its size is equal to the current asteroid, both asteroids would explode, so both are removed.
If the top asteroid in the stack is moving to the right and its size is greater than the current asteroid, or if it’s moving to the left, the loop breaks because the current asteroid can’t collide with it.
If the current asteroid hasn’t exploded, it’s pushed onto the stack.
After all asteroids have been processed, the function returns the stack, which represents the state of the asteroids after all collisions.
 * Solves the asteroid collision problem.
 *
 * @param asteroids The array of asteroids represented as integers.
 * @return The array of asteroids after all collisions.
 */
std::vector<int> asteroidCollision(const std::vector<int> &asteroids)
{
    std::vector<int> stk;
    for (int asteroid : asteroids)
    {
        bool isPushed = false;
        while (!stk.empty() && asteroid < 0 && stk.back() > 0)
        {
            if (stk.back() < -asteroid)
            {
                stk.pop_back();
                continue;
            }
            else if (stk.back() == -asteroid)
            {
                stk.pop_back();
            }
            isPushed = true;
            break;
        }
        if (!isPushed)
        {
            stk.push_back(asteroid);
        }
    }
    return stk;
}

//^ 9 Sum of Subarrays Ranges
class SubarrayRanges
{
public:
    // THIS QUESTION IS ABT Sum of subarray range

    // meangin that sum(max-min) kinda

    // HERE ALSO, we need to focus on each element contrib

    // We did Sum of subarray mins, say return was y

    // If we also do Sum of subarray max, say return x

    // then doing x-y, will give us ANSWER.

    // SINCE HERE, we will only do +, -....over and over

    // HERE WE ALSO USING ALL 4 variant

    // PSE, NSE, = SubArrayMIN

    // PGE, NGE. = SubArrayMAX

    vector<long long> prevSmallerElement(vector<int> &arr)
    {
        vector<long long> indices(arr.size(), -1);
        stack<pair<long long, long long>> stk;
        for (long long i = 0; i < arr.size(); i++)
        {
            while (!stk.empty() && arr.at(stk.top().second) >= arr.at(i))
                stk.pop();
            if (!stk.empty())
                indices.at(i) = stk.top().second;
            stk.push({arr.at(i), i});
        }
        return indices;
    }

    vector<long long> nextSmallerElement(vector<int> &arr)
    {
        vector<long long> indices(arr.size(), arr.size());
        stack<pair<long long, long long>> stk;
        for (long long i = arr.size() - 1; i >= 0; i--)
        {
            while (!stk.empty() && arr.at(stk.top().second) > arr.at(i))
                stk.pop();
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }
            stk.push({arr.at(i), i});
        }
        return indices;
    }

    vector<long long> prevGreaterElement(vector<int> &arr)
    {
        stack<pair<long long, long long>> stk;
        vector<long long> indices(arr.size(), -1);
        for (long long i = 0; i < arr.size(); i++)
        {
            while (!stk.empty() && arr.at(stk.top().second) <= arr.at(i))
                stk.pop();
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }
            stk.push({arr.at(i), i});
        }
        return indices;
    }

    vector<long long> nextGreaterElement(vector<int> &arr)
    {
        stack<pair<long long, long long>> stk;
        vector<long long> indices(arr.size(), arr.size());
        for (long long i = arr.size() - 1; i >= 0; i--)
        {
            while (!stk.empty() && arr.at(stk.top().second) < arr.at(i))
                stk.pop();
            if (!stk.empty())
            {
                indices.at(i) = stk.top().second;
            }
            stk.push({arr.at(i), i});
        }
        return indices;
    }

    long long sumSubarrayMaxs(vector<int> &arr)
    {
        vector<long long> prevG = prevGreaterElement(arr);
        vector<long long> nextG = nextGreaterElement(arr);
        long long n = arr.size();
        long long contribution = 0;
        for (long long i = 0; i < n; i++)
        {
            long long l = prevG[i];
            long long r = nextG[i];
            contribution += (i - l) * (r - i) * arr[i];
        }
        return contribution;
    }

    long long sumSubarrayMins(vector<int> &arr)
    {
        vector<long long> prevS = prevSmallerElement(arr);
        vector<long long> nextS = nextSmallerElement(arr);
        long long n = arr.size();
        long long contribution = 0;
        for (long long i = 0; i < n; i++)
        {
            long long to_add;
            long long l = prevS[i];
            long long r = nextS[i];
            contribution += (i - l) * (r - i) * arr[i];
        }
        return contribution;
    }

    long long subArrayRanges(vector<int> &nums)
    {
        long long totalMaxs = sumSubarrayMaxs(nums);
        long long totalMins = sumSubarrayMins(nums);
        return totalMaxs - totalMins;
    }
};

//^ 10 Largest Area in a histogram

class largestAreaHistogram
{
public:
    /*
    ### Intuition:

    The problem involves finding the largest rectangle area in a histogram. The idea is to use two arrays (`left` and `right`) to store the left and right boundaries for each bar, and then calculate the area for each bar by considering its width and height.

    ### Algorithm:

    1. Initialize two arrays `left` and `right` with the same size as the input array `heights`.
       - `left[i]` represents the index of the left boundary of the rectangle containing the bar at index `i`.
       - `right[i]` represents the index of the right boundary of the rectangle containing the bar at index `i`.
    2. Use a stack to keep track of indices while iterating through the array from left to right.
       - For each bar at index `i`, pop elements from the stack until finding a bar whose height is less than the height of the current bar.
       - The left boundary for the current bar is the index of the element at the top of the stack plus 1 (or 0 if the stack is empty).
       - Push the current index onto the stack.
    3. Clear the stack and repeat the process from right to left to fill the `right` array.
    4. Iterate through each bar in the array and calculate the area for each rectangle.
       - The width of the rectangle is `(right[i] - left[i] + 1)`.
       - The height is the height of the bar at index `i`.
       - Update the maximum area as needed.
    5. Return the maximum area.

    ### Time Complexity:

    The time complexity is O(n), where n is the size of the input array. Each element is processed once during the stack-based traversal.

    ### Space Complexity:

    The space complexity is O(n) for the left and right arrays and the stack.

    ### Summary:

    The code efficiently uses a stack to find the left and right boundaries for each bar in the histogram, allowing for the calculation of the area of the largest rectangle. The time and space complexities are reasonable for the given problem size.
     */
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        vector<int> left(n, 0), right(n, n);
        stack<int> s;
        for (int i = 0; i < n; i++)
        {
            while (!s.empty() && heights[i] <= heights[s.top()])
                s.pop();
            if (s.empty())
                left[i] = 0; // minimum element
            else
                left[i] = s.top() + 1;
            s.push(i);
        }
        while (!s.empty())
            s.pop();
        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && heights[i] <= heights[s.top()])
                s.pop();
            if (s.empty())
                right[i] = n - 1; // minimum element
            else
                right[i] = s.top() - 1;
            s.push(i);
        }
        int area = 0;
        for (int i = 0; i < n; i++)
        {
            int width = (right[i] - left[i] + 1);
            area = max(area, width * heights.at(i));
        }
        return area;
    }
};

//^ 11 Remove K digits from number
string removeKdigits(string S, int k)
{
    string ans = "";                     // Initialize an empty string to store the result
    for (int i = 0; i < S.length(); i++) // Iterate through each character in the input string
    {
        while (!ans.empty() && ans.back() > S[i] && k > 0) // Check if the last digit in the result string is greater than the current digit and there are more digits to be removed
        {
            ans.pop_back(); // Remove the last digit from the result string
            k--;            // Decrement the count of digits to be removed
        }
        if (ans.empty() && S[i] == '0') // Skip leading zeros in the input string
            continue;
        ans.push_back(S[i]); // Append the current digit to the result string
    }

    while (!ans.empty() && k--) // Remove remaining digits if k > 0
        ans.pop_back();
    return (ans == "") ? "0" : ans; // Return "0" if the result string is empty, otherwise return the result string
}

//^ 12 Celebrity Problem
class CelebritySolution
{
public:
    /*
        Create two arrays indegree and outdegree, to store the indegree and outdegree
        Run a nested loop, the outer loop from 0 to n and inner loop from 0 to n.
        For every pair i, j check if i knows j then increase the outdegree of i and indegree of j
        For every pair i, j check if j knows i then increase the outdegree of j and indegree of i
        Run a loop from 0 to n and find the id where the indegree is n-1 and outdegree is 0.
     */
    /*     int celebrity(vector<vector<int>> &M, int n)
        {
            // code here
            vector<int> adj[n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (i != j && M[i][j] == 1)
                    {
                        adj[i].push_back(j);
                    }
                }
            }

            vector<int> indegree(n), outdegree(n);
            for (int i = 0; i < n; i++)
            {
                outdegree[i] = adj[i].size();
                for (auto node : adj[i])
                {
                    indegree[node]++;
                }
            }

            for (int i = 0; i < n; i++)
            {
                if (indegree.at(i) == n - 1 && outdegree.at(i) == 0)
                {
                    return i;
                }
            }
            return -1;
        } */
    /*
    Intuition
& TWO POINTERS APPROACH
The idea is to use two pointers, one from start and one from the end. Assume the start person is A, and the end person is B. If A knows B, then A must not be the celebrity. Else, B must not be the celebrity. At the end of the loop, only one index will be left as a celebrity. Go through each person again and check whether this is the celebrity.
The Two Pointer approach can be used where two pointers can be assigned, one at the start and the other at the end, and the elements can be compared and the search space can be reduced.
Implementation

    Create two indices i and j, where i = 0 and j = n-1
    Run a loop until i is less than j.
    Check if i knows j, then i can't be a celebrity. so increment i, i.e. i++
    Else j cannot be a celebrity, so decrement j, i.e. j--
    Assign i as the celebrity candidate
    Now at last check whether the candidate is actually a celebrity by re-running a loop from 0 to n-1  and constantly checking that if the candidate knows a person or if there is a candidate who does not know the candidate, then we should return -1. else at the end of the loop, we can be sure that the candidate is actually a celebrity.

Complexity Analysis

*   Time Complexity: O(N), As we running the loop for maximum of n times.
*   Space Complexity: O(1), As no extra space is required.

     */
    int celebrity(vector<vector<int>> &M, int n)
    {
        // initializing two pointers for two corners.
        int a = 0;
        int b = n - 1;

        // we keep moving till the a<b.
        while (a < b)
        {
            if (M[a][b])
                a++;
            else
                b--;
        }

        // checking if a is actually a celebrity or not.
        for (int i = 0; i < n; i++)
        {
            // if any person doesn't know a or a knows any person, we return -1.
            if ((i != a) && (M[a][i] || !M[i][a]))
                return -1;
        }
        // if we reach here a is celebrity so we retun a.
        return a;
    }
    /*
    & Stack approach
     */
    int celebrity(vector<vector<int>> &M, int n)
    {
        // code here
        stack<int> s;
        for (int i = 0; i < n; i++)
            s.push(i);
        while (s.size() > 1)
        {
            int A = INT_MIN, B = INT_MIN;
            A = s.top();
            s.pop();
            B = s.top();
            s.pop();
            if (M[A][B] && !M[B][A])
            {
                s.push(B);
            }
            else if (M[B][A] && !M[A][B])
            {
                s.push(A);
            }
            else
            {
                continue;
            }
        }
        if (s.empty())
            return -1;
        for (int i = 0; i < n; i++)
        {
            if (i != s.top() and (!M[i][s.top()] || M[s.top()][i]))
                return -1;
        }
        return s.top();
    }
};

//^ 13 Maximum Rectangle in a Binary matrix
class MaxRect10
{
public:
    void clearStack(stack<int> &s)
    {
        while (!s.empty())
            s.pop();
    }
    int largestAreaHistogram(vector<int> &arr)
    {
        stack<int> s;
        vector<int> left(arr.size()), right(arr.size(), arr.size());
        for (int i = 0; i < arr.size(); i++)
        {
            while (!s.empty() && arr.at(s.top()) >= arr.at(i))
                s.pop();
            if (s.empty())
            {
                left.at(i) = 0;
            }
            else
            {
                left.at(i) = s.top() + 1; // want boundary
            }
            s.push(i);
        }
        clearStack(s);
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            while (!s.empty() && arr.at(s.top()) >= arr.at(i))
                s.pop();
            if (s.empty())
            {
                right.at(i) = arr.size() - 1;
            }
            else
            {
                right.at(i) = s.top() - 1; // want boundary
            }
            s.push(i);
        }

        int Area = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            int width = right.at(i) - left.at(i) + 1;
            Area = max(Area, width * arr.at(i));
        }
        return Area;
    }
    int maxArea(vector<vector<int>> &M, int n, int m)
    {
        // Your code here
        vector<int> histogram(m);
        int area = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (M[i][j] == 0)
                {
                    histogram.at(j) = 0;
                }
                else
                {
                    histogram.at(j) += M[i][j];
                }
            }

            area = max(area, largestAreaHistogram(histogram));
        }
        return area;
    }
};

//^ 14 This function takes an array of integers `A`, the length of the array `N`,
// and the window size `K`. It returns a vector containing the first negative
// integer in every window of size `K`.

vector<long long> printFirstNegativeInteger(long long int A[],
                                            long long int N, long long int K)
{
    // Create a queue to store pairs of negative integers and their indices
    queue<pair<long long int, long long int>> negative;

    // Create a vector to store the results
    vector<long long int> ans;

    // Iterate over the first window of size `K`
    for (long long int i = 0; i < K; i++)
    {
        // If the current element is negative, add it to the queue
        if (A[i] < 0)
        {
            negative.push({A[i], i});
        }
    }

    // Iterate over the remaining elements of the array
    for (long long int i = K; i < N; i++)
    {
        // If the queue is not empty, add the first negative integer to the result vector
        if (!negative.empty())
        {
            ans.push_back(negative.front().first);
        }
        // Otherwise, add 0 to the result vector
        else
        {
            ans.push_back(0);
        }

        // Remove elements from the queue that are no longer in the current window
        while (!negative.empty() && negative.front().second <= i - K)
        {
            negative.pop();
        }

        // If the current element is negative, add it to the queue
        if (A[i] < 0)
        {
            negative.push({A[i], i});
        }
    }

    // If the queue is not empty after processing all elements, add the first negative integer to the result vector
    if (!negative.empty())
    {
        ans.push_back(negative.front().first);
    }
    // Otherwise, add 0 to the result vector
    else
    {
        ans.push_back(0);
    }

    // Return the result vector
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