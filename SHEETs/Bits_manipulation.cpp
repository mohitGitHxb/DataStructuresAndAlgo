#include <bits/stdc++.h>
using namespace std;

void printBinaryDigits(int n)
{
    cout << "binary of " << n << ": ";
    for (int i = 10; i >= 0; i--)
    {
        cout << ((n >> i) & 1);
    }
    cout << "\n";
}

//^ 1 Odd Even check for a number
void checkNumber(int n)
{
    if (n & 1)
    {
        cout << "odd number\n";
    }
    else
    {
        cout << "even number\n";
    }
}

/*
 % Random Tricks and tips
 ?  (n >> i) is equivalent to n / 2^i
 ?  (n << i) is equivalent to n * 2^i

 ?  lower case letter -> upper case letter (unset 5th bit or take OR with " " space)
 ?  upper case letter -> lower case letter (set 5th bit or just take AND with "_")

 ? n & (n - 1) to check whether a number is a power of two (n&(n-1) == 0 means it is a power of 2 )

 ? Swap elements using XoR operations a -> a ^ b then b = b ^ a finally a -> a ^ b;

 CF blog : https://codeforces.com/blog/entry/73558
 */

//^ 2 clear bits till ith LSB
void clearTillIthLSB(int n, int i)
{
    int newNumber = (n & (~((1 << (i + 1)) - 1)));
    int setAllBitsTillMSB = (n & ((1 << (i + 1))) - 1);
    printBinaryDigits(newNumber);
}

//^ 3 Find intersection of two arrays in O(1) [0 TO 31]
//& can go upto 0 to 64
vector<int> findIntersection(vector<int> &arr1, vector<int> &arr2)
{

    // Initialize bitmasks for both arrays
    int bitmask1 = 0, bitmask2 = 0;

    // Iterate over the first array
    for (int num : arr1)
    {
        // Set the bit at the position corresponding to the current number
        bitmask1 |= (1 << num);
    }

    // Iterate over the second array
    for (int num : arr2)
    {
        // Set the bit at the position corresponding to the current number
        bitmask2 |= (1 << num);
    }

    // The intersection of the two arrays is represented by the bits that are set in both bitmasks
    // We can find this by performing a bitwise AND operation
    int intersection = bitmask1 & bitmask2;

    // Convert the intersection bitmask to a vector
    vector<int> result;
    for (int i = 0; i < 32; i++)
    {
        // If the bit at the current position is set, add the corresponding number to the result
        if (intersection & (1 << i))
        {
            result.push_back(i);
        }
    }

    return result;
}

//^ 4 Generate all subsets of an array [Power Set]
vector<vector<int>> subsets(vector<int> &nums)
{
    // Calculate the total number of subsets
    int totalSubsets = pow(2, nums.size());

    // Create a vector to store all the subsets
    vector<vector<int>> ans;

    // Iterate through all possible subsets
    for (int mask = 0; mask < totalSubsets; mask++)
    {
        // Create a temporary vector to store the current subset
        vector<int> temp;

        // Iterate through the elements of the input array
        for (int idx = 0; idx < nums.size(); idx++)
        {
            // Check if the current element is included in the subset
            if (mask & (1 << idx))
            {
                // Add the current element to the subset
                temp.emplace_back(nums.at(idx));
            }
        }

        // Add the current subset to the vector of subsets
        ans.emplace_back(temp);
    }

    // Return the vector of subsets
    return ans;
}
int main()
{
    printBinaryDigits(59);
    clearTillIthLSB(59, 4);
    return 0;
}