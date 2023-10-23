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

//^ Next greater element 2
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