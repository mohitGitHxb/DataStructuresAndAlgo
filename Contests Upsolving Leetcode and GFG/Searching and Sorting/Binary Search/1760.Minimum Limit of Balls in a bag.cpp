#include<bits/stdc++.h>
using namespace std;
// helper function to check if the middle pointer value of the range is a valid value to be divided or not
bool valid(int mid, vector<int> &nums, int maxOperations)
{

    // initialize a counter
    int counter = 0;

    // loop over the whole array elements
    for (int num : nums)
    {
        // check if the current element is greater than the mid
        if (num > mid)
        {
            // initialize a temp variable
            int temp = num;
            // check again if the current element is divisible by the mid
            if (temp % mid == 0)
                // if yes-> add the following value to the counter
                // ex: 8 ->(4),(4)-> (2,2),(2,2)-> 3 operations
                counter += (temp / mid) - 1;
            else
                // if no...
                counter += (temp / mid);
        }
    }

    // check if the counted balls is valid or not compared to the allowed ones
    return counter <= maxOperations;
}

int minimumSize(vector<int> &nums, int maxOperations)
{

    // handle invalid cases
    if (maxOperations < 1)
        return 0;

    // initialize mainly two pointers-> one on the minimum possible value in the array & one on the maximum one
    int left = 1, right = *max_element(nums.begin(), nums.end());

    // loop while the left pointer is before the right one
    while (left < right)
    {

        // the third pointer mid-> is exactly the middle element between the main two ones
        int mid = left + (right - left) / 2;

        // call the helper function
        if (valid(mid, nums, maxOperations))
            // case 1: if yes, valid-> move the right pointer to the mid position
            right = mid;
        else
            // case 2: if not-> move the left pointer to the position after the mid one
            left = mid + 1;
    }

    // return the right position
    return right;
}