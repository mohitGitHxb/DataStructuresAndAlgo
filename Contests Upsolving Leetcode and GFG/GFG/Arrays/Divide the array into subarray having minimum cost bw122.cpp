#include <bits/stdc++.h>
using namespace std;

/* 

Intuition

    My code maintains two sets (smallSet and bigSet) to efficiently manage the elements based on their size.
    I use multisets to easily access the smallest and largest elements in each set.
    As the goal is to minimize the cost by efficiently swapping elements between sets while considering the conditions mentioned in the code.

Approach
Initialization

    The initial expense is the first element of the array, so Istored in the variable initialExpense.
    The first element is removed from the array.

Data Structures

    I used Two multisets (bigSet and smallSet) to maintain a sorted order of elements with efficient insertion and removal.
    bigSet represents the set of larger elements.
    smallSet represents the set of smaller elements.

Initialization of Sets and Sums

    The first dist elements of the array are added to smallSet, and their sum is calculated in currentSum.
    The variable dist is incremented to ensure flexibility in later operations.

Balancing Sets

    Moved elements from smallSet to bigSet to ensure that smallSet has at most k elements.
    This is done by comparing the sizes of smallSet and bigSet.

Initial Output

    The initial value of currentSum is printed.

Iterating Through the Remaining Elements

    I iterated a loop through the remaining elements of the array.
    For each iteration, I checked whether the previous element to be removed is in smallSet.
    If yes, it is removed, and adjustments are made between smallSet and bigSet.
    The largest element in smallSet is identified (lastElement).
    The new element to be added is obtained (newElement).

Updated the Sets and Sums

    The code checks if smallSet has fewer than k elements. If true, the new element is added to smallSet.
    If smallSet already has k elements, the code compares the new element with the largest element in smallSet.
    If the new element is smaller, the largest element is moved to bigSet, and the new element is added to smallSet.
    Otherwise, the new element is directly added to bigSet.

Updated the Minimal Sum

    The minimal sum (minimalSum) is updated with the minimum of the current sum and the minimal sum from previous iterations.

Final Output

    The final result is the sum of the minimal sum and the initial expense.

Have a look at the code , still have any confusion then please let me know in the comments
Keep Solving.:)
Complexity

    Time complexity : O(NlogN)O(NlogN)O(NlogN)

NNN : size of the input array

    Space complexity : O(k)O(k)O(k)

kkk : maximum size of the multisets

 */
class Solution
{
public:
    long long minimumCost(std::vector<int> &nums, int k, int dist)
    {
        // Initializing variables
        long long int initialExpense = nums[0];
        nums.erase(nums.begin());
        int size = nums.size();
        k--;
        dist++;
        std::multiset<long long int> bigSet, smallSet;
        long long int currentSum = 0, minimalSum;

        // Adding the first 'dist' elements to the 'smallSet' and calculate their sum
        for (int i = 0; i < dist; i++)
        {
            smallSet.insert(nums[i]);
            currentSum += nums[i];
        }

        // Ensuring that 'smallSet' has 'k' elements by moving the largest elements to 'bigSet'
        int difference = dist - k;
        while (difference--)
        {
            int maximumElement = *smallSet.rbegin();
            currentSum -= maximumElement;
            bigSet.insert(maximumElement);
            smallSet.erase(smallSet.find(maximumElement));
        }

        minimalSum = currentSum;
        std::cout << minimalSum << std::endl; // Output the initial sum

        // Iterating through the remaining elements
        for (int i = 1; i <= size - dist; i++)
        {
            // Checking if the element to be removed is in 'smallSet'
            if (smallSet.find(nums[i - 1]) != smallSet.end())
            {
                currentSum -= nums[i - 1];
                smallSet.erase(smallSet.find(nums[i - 1]));

                // If 'bigSet' is not empty, move the smallest element from 'bigSet' to 'smallSet'
                if (bigSet.size() != 0)
                {
                    int minimumElement = *bigSet.begin();
                    currentSum += minimumElement;
                    smallSet.insert(minimumElement);
                    bigSet.erase(bigSet.find(minimumElement));
                }
            }
            else
            {
                // If the element to be removed is in 'bigSet', simply remove it
                bigSet.erase(bigSet.find(nums[i - 1]));
            }

            // Getting the largest element in 'smallSet'
            int lastElement = *smallSet.rbegin();

            // Getting the new element to be added
            int newElement = nums[i + dist - 1];

            // Checking if 'smallSet' has less than 'k' elements
            if (smallSet.size() < k)
            {
                currentSum += newElement;
                smallSet.insert(newElement);
            }
            else
            {
                // If 'newElement' is smaller than the largest element in 'smallSet'
                if (newElement < lastElement)
                {
                    currentSum -= lastElement;
                    currentSum += newElement;
                    bigSet.insert(lastElement);
                    smallSet.erase(smallSet.find(lastElement));
                    smallSet.insert(newElement);
                }
                else
                {
                    // If 'newElement' is not smaller, adding it to 'bigSet'
                    bigSet.insert(newElement);
                }
            }

            // Updating the minimal sum
            minimalSum = std::min(minimalSum, currentSum);
        }

        // Returning the final result
        return minimalSum + initialExpense;
    }
};

int main()
{
    return 0;
}