#include <bits/stdc++.h>
using namespace std;
/*
You are given a 0-indexed array of positive integers nums.

A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.

Return the total number of incremovable subarrays of nums.

Note that an empty array is considered strictly increasing.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,2,3,4]
Output: 10
Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.

Example 2:

Input: nums = [6,5,7,8]
Output: 7
Explanation: The 7 incremovable subarrays are: [5], [6], [5,7], [6,5], [5,7,8], [6,5,7] and [6,5,7,8].
It can be shown that there are only 7 incremovable subarrays in nums.

Example 3:

Input: nums = [8,7,6,6]
Output: 3
Explanation: The 3 incremovable subarrays are: [8,7,6], [7,6,6], and [8,7,6,6]. Note that [8,7] is not an incremovable subarray because after removing [8,7] nums becomes [6,6], which is sorted in ascending order but not strictly increasing.

 */
class Solution1
{
public:
    bool strictlyIncreasing(vector<int> &a)
    {
        for (int i = 1; i < a.size(); i++)
        {
            if (a[i] <= a[i - 1])
                return false;
        }
        return true;
    }
    int incremovableSubarrayCount(vector<int> &nums)
    {
        unsigned n = nums.size();
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                vector<int> excludeItoJ(nums.begin(), nums.begin() + i);
                excludeItoJ.insert(excludeItoJ.end(), nums.begin() + j + 1, nums.end());
                if (strictlyIncreasing(excludeItoJ))
                    count++;
            }
        }
        return count;
    }
    /*
    Intuition

Since the question demands O(n) or O(nlogn) solution,
we can think finding the number of incremoval subarrays with left end at index i for all 0<=i<n efficiently.

Let's find the length (l) of the longest prefix (P) such that this prefix is a increasing subarray
Similarly, find the length (rrr) of the longest suffix (S) which is a increasing subarray

Ex: [6,5,10,7,8][6, 5, 10, 7, 8][6,5,10,7,8]
P: [6][6][6]
S: [7,8][7, 8][7,8]

l=1,r=2l=1, r=2l=1,r=2
The valid incremoval subarrays are
[6,5,10][6, 5, 10][6,5,10]
[6,5,10,7][6, 5, 10, 7][6,5,10,7]
[6,5,10,7,8][6, 5, 10, 7, 8][6,5,10,7,8]

[5,10][5, 10][5,10]
[5,10,7][5, 10, 7][5,10,7]
[5,10,7,8][5, 10, 7, 8][5,10,7,8]

total=6total=6total=6

You can observe that the elements in the range [l,n−r−1][l, n-r-1][l,n−r−1] always exist in any valid incremoval subarray
Approach

For every element in the prefix a[i]a[i]a[i] find the element in the suffix a[j]a[j]a[j] just greater than a[i]a[i]a[i]

Then the number of valid incremoval subarrays with left end as i+1i+1i+1 is
[i+1..j],[i+1..j+1],.....[i+1..n−1][i+1..j], [i+1..j+1], ..... [i+1..n-1][i+1..j],[i+1..j+1],.....[i+1..n−1]

Which is n−j+1n-j+1n−j+1
We also need to calculate the number of valid incremoval subarrays with left end as i=0i=0i=0
which is r+1r+1r+1
Complexity

    Time complexity:
    O(nlogn)O(nlogn)O(nlogn)

    Space complexity:
    O(n)O(n)O(n)

     */
};

pair<int, int> getIndices(vector<int> &nums)
{
    int left = 0, right = nums.size() - 1;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums.at(i) <= nums.at(i - 1))
        {
            left = i - 1;
            break;
        }
        left = i;
    }
    for (int i = nums.size() - 2; i >= 0; i--)
    {
        if (nums.at(i) >= nums.at(i + 1))
        {
            right = i + 1;
            break;
        }
        right = i;
    }
    return {left, right};
}
long long incremovableSubarrayCount(vector<int> &nums)
{
    unsigned n = nums.size();
    pair<int, int> range = getIndices(nums);
    cout << range.first << " | " << range.second << "\n";
    if (range.first >= range.second)
        return n * (n + 1) / 2;
    long long ans = 0;
    for (int i = 0; i <= range.first; i++)
    {
        int ub = upper_bound(nums.begin() + range.second, nums.end(), nums.at(i)) - nums.begin();
        cout << "ub = " << ub << "\n";
        ans += (n - ub + 1);
    }

    // case of avoiding entire left subarray part (0 to range.first) and considering only right
    ans += (n - range.second + 1);
    return ans;
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