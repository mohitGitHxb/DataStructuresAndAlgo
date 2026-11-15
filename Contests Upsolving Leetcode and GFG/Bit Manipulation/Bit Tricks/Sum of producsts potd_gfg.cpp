#include <bits/stdc++.h>
using namespace std;
/* We will create an array that will contain sum of all the number of set bits at a particular position for all the data elements in the given number array.

e.g. for array

{10, 20, 30, 40}

set bits array {1,2,3,2,2,0}

** in question we will create a 32 size array (assuming 32 bit)

This approach works because, for each bit position, if there are k elements with that bit set, there are (k * (k - 1) / 2) pairs that contribute 1 << bit to the final sum.

    Here's an approach:
        Initialize a variable result to 0, which will store the sum of bitwise ANDs of all pairs.
        Iterate through each bit position from 0 to 31 (assuming a 32-bit integer).
        For each bit position bit, count the number of elements in the array where the bit is set (i.e., the AND of the element with a bitmask 1 << bit is non-zero).
        For each count of elements with the bit set, add (count * (count - 1) / 2) * (1 << bit) to result.
        Repeat steps 2-4 for all bit positions.
    Return result.
 */
long long pairAndSum(int n, long long arr[])
{
    long long result = 0;
    for (int bit = 0; bit < 32; bit++)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] & (1LL << bit)) // Check if the bit is set
                count++;
        }
        result += (count * 1LL * (count - 1) / 2) * (1LL << bit);
    }
    return result;
}
int main()
{
    return 0;
}