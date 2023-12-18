#include <bits/stdc++.h>
using namespace std;
/*
@ problem
 You have given a binary array arr of size N consists of 0 and 1. If arr[i]=0 then there is a white stone present at the index i and if arr[i]=1 then there is a black stone present at the index i.

You have infinite no of boxes of size K and you need to separate white and black stones by putting them into different boxes. Find the minimum no of box require to separate white and black stones by putting them into different boxes.



@ Explanation

    First, the array arr is sorted in non-decreasing order using the sort() function. This is done to group the white and black stones together in the array.

    Initialize two variables box1 and box2 to keep track of the number of boxes needed for white and black stones, respectively. Also, initialize a counter variable to keep track of the number of stones placed in the current box.

    Start iterating through the sorted array using the variable i. For each element arr[i], if it is a white stone (i.e., arr[i] == 0), and the current box has reached its capacity (i.e., counter == k - 1), then place the current white stone in a new box (i.e., increment box1 by 1) and reset the counter to 0. Otherwise, if the box has not reached its capacity, place the white stone in the current box (i.e., increment counter by 1).

    After the loop ends, if there are any remaining white stones that have not been placed in a box (i.e., counter > 0), place them in a new box (i.e., increment box1 by 1).

    Reset the counter to 0 and continue the iteration from the current value of i. This time, place the black stones in the boxes following the same logic as for white stones.

    After the second loop ends, if there are any remaining black stones that have not been placed in a box (i.e., counter > 0), place them in a new box (i.e., increment box2 by 1).

    Finally, return the sum of box1 and box2, which represents the minimum number of boxes required to separate white and black stones.
 */

int separateStones(int N, int k, vector<int> &arr)
{
    // code here
    sort(arr.begin(), arr.end());
    int box1 = 0, box2 = 0, counter = 0;
    int i = 0;
    for (i = 0; i < arr.size(); i++)
    {
        if (arr[i] == 1)
            break;
        else if (counter == k - 1)
        {
            box1++;
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
    if (counter > 0)
        box1++;
    counter = 0;
    for (; i < arr.size(); i++)
    {
        if (counter == k - 1)
        {
            box2++;
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
    if (counter > 0)
        box2++;
    return box1 + box2;
}
int main()
{
    return 0;
}