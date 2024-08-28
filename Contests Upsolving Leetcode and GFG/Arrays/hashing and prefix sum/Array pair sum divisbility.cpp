#include <bits/stdc++.h>
using namespace std;
/*
1) If length of given array is odd, return false.
   An odd length array cannot be divided into pairs.
2) Traverse input array and count occurrences of
   all remainders (use (arr[i] % k)+k)%k for handling the case of negative integers as well).
     freq[((arr[i] % k) + k) % k]++
3) Traverse input array again.
  a) Find the remainder of the current element.
  b) If remainder divides k into two halves, then
     there must be even occurrences of it as it
     forms pair with itself only.
  c) If the remainder is 0, then there must be
     even occurrences.
  d) Else, number of occurrences of current
     the remainder must be equal to a number of
     occurrences of "k - current remainder".

 */

bool canPair(vector<int> nums, int k)
{
    // Check if the size of the vector is odd, if yes, return false
    if (nums.size() & 1)
        return false;

    // Create an unordered map to store the frequency of remainders
    unordered_map<int, int> mp;

    // Iterate through each element in the vector
    for (int i : nums)
    {
        // Increment the frequency of the remainder when divided by k
        mp[i % k]++;
    }

    // Iterate through each element in the vector
    for (int i = 0; i < nums.size(); i++)
    {
        // Calculate the complement remainder needed to pair with the current element
        int complement = (k - nums[i] % k) % k;

        // Check if the frequency of the complement remainder is not equal to the frequency of the current element remainder
        if (mp[complement] != mp[nums[i] % k])
            return false;
    }

    // If all elements can be paired, return true
    return true;
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