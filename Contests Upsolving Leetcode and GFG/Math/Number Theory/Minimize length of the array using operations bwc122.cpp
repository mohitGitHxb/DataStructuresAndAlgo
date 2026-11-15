#include <bits/stdc++.h>
using namespace std;

// Finds the minimum length of the array without using mathematical operations
//
// nums: the input vector of integers
// returns: the minimum length of the array
int minimumArrayLength(vector<int> &nums)
{
    // Find the smallest element in the vector
    int smaller = *min_element(nums.begin(), nums.end());
    int count = 0;
    int n = nums.size();
    bool flag = false;

    // Count the occurrences of the smallest element and check if any element is not divisible by the smallest
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == smaller)
        {
            count++;
        }
        if (nums[i] % smaller != 0)
        {
            flag = true;
        }
    }

    // Determine the minimum length based on the conditions
    if (flag || count == 1)
    {
        return 1;
    }
    else
    {
        return (count + 1) / 2;
    }
}

class Solution
{
public:
    int minimumArrayLength(vector<int> &nums)
    {
        // Sort the array in ascending order
        sort(nums.begin(), nums.end());

        // Get the size of the array
        int arraySize = nums.size();

        // Initialize a counter for the number of times the smallest number appears
        int smallestNumCount = 1;

        // Initialize the greatest common divisor (gcd) to the maximum possible integer
        int gcd = INT_MAX;

        // Iterate over the array, starting from the second element
        for (int i = 1; i < arraySize; i++)
        {
            // Update the gcd to be the minimum of the current gcd and the gcd of the current and previous elements
            gcd = min(gcd, __gcd(nums[i], nums[i - 1]));

            // If the gcd is less than the smallest number in the array, return 1
            // This is because we can always reduce the array to a single element by performing the operation with the gcd and any other number
            if (gcd < nums[0])
                return 1;

            // If the current number is equal to the smallest number in the array, increment the counter
            if (nums[i] == nums[0])
                smallestNumCount++;
        }

        // Calculate the minimum length of the array after performing the operation
        // This is the ceiling of the number of times the smallest number appears divided by 2
        // This is because each operation reduces the array size by 1, and we can always perform the operation with two of the smallest numbers
        int minArrayLength = ceil(smallestNumCount / (2 * 1.0));

        // Return the minimum length of the array
        return minArrayLength;
    }
};
int main()
{
    return 0;
}