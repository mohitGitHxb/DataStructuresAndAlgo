#include <bits/stdc++.h>
using namespace std;
/*

You are given a 0-indexed array nums consisting of positive integers. You can do the following operation on the array any number of times:

    Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.

Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.

The gcd of two integers is the greatest common divisor of the two integers.



Example 1:

Input: nums = [2,6,3,4]
Output: 4
Explanation: We can do the following operations:
- Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
- Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
- Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
- Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].

Example 2:

Input: nums = [2,10,6,14]
Output: -1
Explanation: It can be shown that it is impossible to make all the elements equal to 1.

*/
class Solution
{
public:
    int minOperations(vector<int> &nums)
    {
        const int n = nums.size();

        // Step 1: Count existing 1s in the array
        // If we already have 1s, we can use them to convert other elements to 1
        const int countOfOne = count(nums.begin(), nums.end(), 1);

        // If 1s already exist, we just need (n - countOfOne) operations
        // Each 1 can convert one adjacent element to 1 using gcd(1, x) = 1
        if (countOfOne)
        {
            return n - countOfOne;
        }

        // Step 2: If no 1s exist, we need to create at least one 1 first
        // Find the minimum length subarray whose gcd is 1
        // This represents the minimum operations to create the first 1
        int minLength = n + 1;

        for (int i = 0; i < n; i++)
        {
            int g = nums[i];
            // Calculate gcd of subarray starting at i
            for (int j = i + 1; j < n; j++)
            {
                g = gcd(g, nums[j]);

                // If gcd becomes 1, we found a valid subarray
                if (g == 1)
                {
                    // Length of subarray is (j - i + 1)
                    // Operations needed to reduce this subarray to 1 is (j - i)
                    minLength = min(minLength, j - i);
                    break;
                }
            }
        }

        // Step 3: Check if it's impossible to make any element 1
        // If no subarray has gcd = 1, then overall gcd > 1, making it impossible
        if (minLength == n + 1)
        {
            return -1;
        }

        // Step 4: Calculate total operations
        // minLength operations to create the first 1
        // Then (n - 1) operations to convert remaining (n-1) elements to 1
        // Total = minLength + (n - 1) = n + minLength - 1
        return n + minLength - 1;
    }
};
int main()
{
    return 0;
}