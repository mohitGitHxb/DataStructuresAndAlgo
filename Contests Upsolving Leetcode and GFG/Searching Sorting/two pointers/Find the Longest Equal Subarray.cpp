#include <bits/stdc++.h>
using namespace std;

/*
You are given a 0-indexed integer array nums and an integer k.

A subarray is called equal if all of its elements are equal. Note that the empty subarray is an equal subarray.

Return the length of the longest possible equal subarray after deleting at most k elements from nums.

A subarray is a contiguous, possibly empty sequence of elements within an array.



Example 1:

Input: nums = [1,3,2,3,1,3], k = 3
Output: 3
Explanation: It's optimal to delete the elements at index 2 and index 4.
After deleting them, nums becomes equal to [1, 3, 3, 3].
The longest equal subarray starts at i = 1 and ends at j = 3 with length equal to 3.
It can be proven that no longer equal subarrays can be created.

Example 2:

Input: nums = [1,1,2,2,1,1], k = 2
Output: 4
Explanation: It's optimal to delete the elements at index 2 and index 3.
After deleting them, nums becomes equal to [1, 1, 1, 1].
The array itself is an equal subarray, so the answer is 4.
It can be proven that no longer equal subarrays can be created.

 */

/*
    Intuition:
        The objective is to find the longest equal subarray by allowing deletion of at most k elements from the original array.
        The code maintains a sliding window [i, j] where i marks the starting index and j marks the ending index of the subarray.
        The frequency of each element in the current window is tracked using the freq map.
        The difference between the total number of elements in the current window (j - i + 1) and the frequency of the most frequent element in the window (maximumFreq) indicates the number of elements that need to be deleted.

    Code Explanation:
        The code uses two pointers, i and j, to mark the boundaries of the current subarray.
        A frequency map (freq) is used to keep track of the frequency of each element in the current subarray.
        The maximumFreq variable stores the frequency of the most frequent element in the current subarray.
        As the sliding window moves, the code increments the frequency of the element at index j and updates maximumFreq accordingly.
        If the difference between j - i + 1 and maximumFreq is greater than k, the code shrinks the window by decreasing the frequency of the element at index i and moving the i pointer to the right.
        The code updates the length of the longest equal subarray based on the current window size (j - i + 1).
        The j pointer is then incremented to move the window to the right.

    Time Complexity:
        The two pointers i and j each traverse the array once, resulting in linear time complexity.
        For each element, the frequency map is updated in constant time.
        The overall time complexity is O(n), where n is the length of the input array nums.

    Space Complexity:
        The main space consumption comes from the frequency map freq, which stores the frequency of elements.
        In the worst case, the frequency map could store all distinct elements in the array.
        The space complexity is O(n), where n is the length of the input array nums.

    Hint:
        Use a sliding window approach with two pointers i and j to represent the current subarray.
        Maintain a frequency map to track the frequency of elements in the current window.
        Keep track of the maximum frequency encountered (maximumFreq).
        Shrink the window when the difference between j - i + 1 and maximumFreq exceeds k.
        Update the length of the longest equal subarray based on the current window size.
        Move the j pointer to the right and repeat the process until the end of the array is reached.
 */
int longestEqualSubarray(vector<int> &nums, int k)
{
    int maximumFreq = 0;
    unordered_map<int, int> freq;
    int i = 0, j = 0;
    while (j < nums.size())
    {
        freq[nums[j]]++;
        maximumFreq = max(maximumFreq, freq[nums[j]]);
        if (j - i + 1 - maximumFreq > k)
        {
            --freq[nums[i++]];
        }
        j++;
    }
    return maximumFreq;
}
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