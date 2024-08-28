#include <bits/stdc++.h>
using namespace std;
long long kMaxSubarray(int n, int k, vector<int> &arr)
{
    long long ans = -1e10;          // Initialize the answer with a very small value
    vector<long long> prefix(n, 0); // Create a vector to store the prefix sums of the array
    prefix[0] = arr[0];             // Set the first element of the prefix sums vector to be the same as the first element of the array
    for (int i = 1; i < n; i++)     // Loop through the array to calculate the prefix sums
    {
        prefix[i] = prefix[i - 1] + arr[i]; // Calculate the prefix sum at index i
    }
    while (k >= 1) // Loop k times
    {
        int i = 0, j = k - 1;  // Initialize two pointers, i and j
        while (j < n && i < n) // Loop through the array using the two pointers
        {
            if (i > 0) // If i is greater than 0, meaning it's not the first subarray
            {
                long long sum = prefix[j] - prefix[i - 1]; // Calculate the sum of the subarray using the prefix sums
                ans = max(ans, sum);                       // Update the answer with the maximum of the current sum and the previous answer
            }
            else // If i is 0, meaning it's the first subarray
            {
                ans = max(ans, prefix[j]); // Update the answer with the maximum of the current prefix sum and the previous answer
            }
            i++; // Move the i pointer forward
            j++; // Move the j pointer forward
        }
        k--; // Decrement k
    }
    return ans; // Return the maximum subarray sum found
}
int main()
{
    return 0;
}