#include <bits/stdc++.h>
using namespace std;

/*
Intuition

By reading the problem statement we can see it is written 'Choose longest prefix with at most K distinct characters'.
So by 'at most', question wants to say we can have 0, 1, ..., K distinct characters but it should be longest prefix for that K.

So, basically we need to check all possibilities and this leads to using Recursion.

Recursion + DP will help us to avoid Time Limit Exceeded Error.
Approach

We need three variables i, option, mask !!

i: index used for traversing
option: It denotes whether we changed a character or not
mask: It basically acts as a 26 length long integer where ith bit represents whether we encountered ith character of alphabet or not. Just like a visited array of size 26.
NOTE: we cannot use 3D DP because it will give Memory Limit Exceeded because we need to use 'mask' as one of index with is of length 26 i.e. 2^26, so we will make a 'long long' number where

{...}{..26..}{.1.}, here
first bit is for the 'option' variable.
then next 26 bits represents our mask or simple terms visited array.
next bits represents our i i.e. index on which we are currently at.

Now, we will check if number of set bits in our mask is greater than K then we will increase our partition by 1 and update our mask to contain only current character as visited.
Else, we will just include our current character in our mask as visited and we will move on.

We also need to consider separate cases for the 'option' variables as 1.
When option is 1, then we can replace our current ith character with any of the 0...25 th character of alphabets. And then we will update our mask and again check conditions of number of set bits greater than K.

finally we will store our answer in 'DP' map, like dp[key]= ans and we can use this as our memoization dp array. And to reduce Time complexity, we do
long long key= (i<<27) | (mask<<1) | (option);
if(dp.count(key))
{
    return dp[key];
}

 */
class Solution
{
public:
    // MEMOIZATION
    unordered_map<long long, int> dp;
    /*
    i: index used for traversing
    option: It denotes whether we changed a character or not
    mask: It basically acts as a 26 length long integer where ith bit represents whether we encountered ith character of alphabet or not. Just like a visited array of size 26
    */
    int solve(string &s, int &k, vector<int> &A, long long i, bool option, long long mask)
    {
        // base case
        if (i == s.length())
            return 0;

        // we cannot use 3D DP because it will give MLE, so we will make a 'long long' number where
        //{...}{..26..}{.1.}, here first bit is for the 'option' variable
        long long key = (i << 27) | (mask << 1) | (option);
        if (dp.count(key))
        {
            return dp[key];
        }

        // included the current character in our visited array i.e. denoted by mask
        int mask2 = mask | A[i];
        int ans = 0;

        // if number of set bits in mask2 is greater than k then it means we encountered k distinct characters
        if (__builtin_popcount(mask2) > k)
        {
            // our new mask will have only the ith character as visited in it
            ans = 1 + solve(s, k, A, i + 1, option, A[i]);
        }
        else
        {
            // if count of set bits is <k then go on including characters
            ans = solve(s, k, A, i + 1, option, mask2);
        }

        if (option) // if we have the option of changing one character then,
        {
            for (int j = 0; j < 26; j++)
            {
                // if we changed the current ith character with char('a' + j) then mask will become
                mask2 = mask | (1 << j);
                if (__builtin_popcount(mask2) > k)
                {
                    // if number of set bits in mask2 is greater than k then it means we encountered k distinct characters
                    ans = max(ans, 1 + solve(s, k, A, i + 1, 0, 1 << j));
                }
                else
                {
                    // if count of set bits is <k then go on including characters
                    ans = max(ans, solve(s, k, A, i + 1, 0, mask2));
                }
            }
        }
        return dp[key] = ans;
    }
    int maxPartitionsAfterOperations(string s, int k)
    {
        int n = s.length();
        vector<int> A(n); // helpful for doing || operation with mask
        for (int i = 0; i < n; ++i)
        {
            // if we include the ith character of string s then we need to do || operation of mask with A[i]
            A[i] = 1 << (s[i] - 'a');
        }

        return solve(s, k, A, 0, 1, 0) + 1;
    }
};
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