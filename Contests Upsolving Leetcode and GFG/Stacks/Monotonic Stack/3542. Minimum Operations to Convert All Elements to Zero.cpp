#include <bits/stdc++.h>
using namespace std;
/*
You are given an array nums of size n, consisting of non-negative integers. Your task is to apply some (possibly zero) operations on the array so that all elements become 0.

In one operation, you can select a

[i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum non-negative integer in that subarray to 0.

Return the minimum number of operations required to make all elements in the array 0.



Example 1:

Input: nums = [0,2]

Output: 1

Explanation:

    Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0].
    Thus, the minimum number of operations required is 1.

Example 2:

Input: nums = [3,1,2,1]

Output: 3

Explanation:

    Select subarray [1,3] (which is [1,2,1]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [3,0,2,0].
    Select subarray [2,2] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [3,0,0,0].
    Select subarray [0,0] (which is [3]), where the minimum non-negative integer is 3. Setting all occurrences of 3 to 0 results in [0,0,0,0].
    Thus, the minimum number of operations required is 3.

Example 3:

Input: nums = [1,2,1,2,1,2]

Output: 4

Explanation:

    Select subarray [0,5] (which is [1,2,1,2,1,2]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [0,2,0,2,0,2].
    Select subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,2,0,2].
    Select subarray [3,3] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,2].
    Select subarray [5,5] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,0].
    Thus, the minimum number of operations required is 4.



*/
class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        const int n = nums.size();
        stack<int> stk; // Monotonic stack to track active minimum values
        int operations = 0;

        /*
         * KEY INSIGHT: We use a monotonic decreasing stack approach
         *
         * Why this works:
         * - When we select a subarray and remove its minimum, all elements in that
         *   subarray >= minimum are still present
         * - If we process left to right, when we encounter a SMALLER value than
         *   what's in our stack, it means previous larger values can't be removed
         *   by this operation (they need separate operations)
         * - Each unique "increasing step" requires a new operation
         *
         * Example dry run with nums = [3,1,2,1]:
         * i=0, nums[0]=3: stack empty, push 3, operations=1, stack=[3]
         * i=1, nums[1]=1: 1 < 3, pop 3 (larger values need separate ops)
         *                 push 1, operations=2, stack=[1]
         * i=2, nums[2]=2: 2 > 1, this 2 can be in same subarray as 1 (min=1)
         *                 push 2, operations=3, stack=[1,2]
         * i=3, nums[3]=1: 1 == top, already handled by previous operation
         *                 stack=[1,2]
         * Result: 3 operations ✓
         */

        for (int i = 0; i < n; i++)
        {
            // Pop all values greater than current (they can't be in same operation)
            while (!stk.empty() && stk.top() > nums[i])
            {
                stk.pop();
            }

            // Skip zeros - already processed
            if (nums[i] == 0)
                continue;

            // If current value is new (not in stack), we need a new operation
            // This happens when we see a value larger than previous minimum
            if (stk.empty() || stk.top() < nums[i])
            {
                stk.push(nums[i]);
                operations += 1; // Each "step up" needs a new operation
            }
            // If stk.top() == nums[i], it's already handled by a previous operation
        }
        return operations;
    }
};
int main()
{
    return 0;
}