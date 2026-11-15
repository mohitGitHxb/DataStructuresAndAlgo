#include <bits/stdc++.h>
using namespace std;
/*

Expected Approach
Intuition

The Approach efficiently computes the XOR of all subarrays by taking advantage of the XOR operation's properties. It XORs alternating elements to cancel out pairs in even-length arrays, and for odd-length arrays, it considers the contribution of the unpaired element.
Example

    N=3, arr= [1,2,3]

        Iteration through Alternating Elements:
            res is initialized to 0.
            Loop iterates through the array at indices 0 and 2.
            Iteration 1: res ^= A[0] => res = 0 ^ 1 = 1
            Iteration 2: res ^= A[2] => res = 1 ^ 3 = 2
        Handling Odd-Length Array:
            N is 3, which is odd.
            The loop accumulates the XOR result in res, which is 2.
        Result:
            Since N is odd, the final result is the accumulated value of res, which is 2.

Implementation

    res = 0: Initialize a variable res to store the result, and set it to 0.
    Iterate through the array A with a step size of 2 (taking every alternate element starting from index 0).
        res ^= A[i]: Bitwise XOR (^=) the current element of A with the current value of res.
    if N % 2 == 0:: Check if the length of array A is even.
        If N is even, return 0 because the XOR of all subarrays will result in 0. This is because, for any element x in the array, there is another element at an even distance that will XOR to x, and the XOR of identical elements is always 0.
        If N is odd, return the final value of res. This is because, for odd N, there will be one element that is not XOR-ed with any other element in the array, and its value will contribute to the final result.

Complexity

Time Complexity: O(N) - The code has a linear time complexity as it iterates through the input array in a single pass.

Space Complexity: O(1) - The code has constant space complexity, using only a fixed amount of additional space regardless of the input array size.

 */


class Solution
{
public:
    // Function to find the XOR of alternating numbers
    int gameOfXor(int N, int A[])
    {

        int result = 0;

        // Xor of alternating numbers from index 0
        for (int i = 0; i < N; i++)
        {
            // If index is even, perform xor operation
            if (i % 2 == 0)
                result = result ^ A[i];
        }

        // If N is even, ans will always be 0, else return xor of alternating elements.
        if (N % 2 == 0)
            return 0;
        else
            return result;
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