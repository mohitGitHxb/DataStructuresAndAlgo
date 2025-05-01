#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
static int init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
        You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:

    Decrement the value at each index in the range [li, ri] in nums by at most vali.
    The amount by which each value is decremented can be chosen independently for each index.

A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.



Example 1:

Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]

Output: 2

Explanation:

    For i = 0 (l = 0, r = 2, val = 1):
        Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
        The array will become [1, 0, 1].
    For i = 1 (l = 0, r = 2, val = 1):
        Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
        The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.

Example 2:

Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]

Output: -1

Explanation:

    For i = 0 (l = 1, r = 3, val = 2):
        Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
        The array will become [4, 1, 0, 0].
    For i = 1 (l = 0, r = 2, val = 1):
        Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
        The array will become [3, 0, 0, 0], which is not a Zero Array.

    @ approach
    & Use partial sum technique to lazy propagate the values.
    & Use binary search to find the optimal value of K

    * Time complexity O(NlogN)
    * Space complexity O(N)
     */
public:
    const int mod = 1e9 + 7;
    bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries, int limit = 0)
    {
        int n = nums.size();
        // limit = queries.size();
        vector<ll> diff(n + 1);
        // partial sum technique to update the values in lazy manner
        for (int i = 0; i < limit; i++)
        {
            int li = queries[i][0];
            int ri = queries[i][1];
            int decrement = queries[i][2];
            diff[li] += decrement;
            diff[ri + 1] -= decrement;
        }
        for (int i = 0; i < n; i++)
        {
            diff[i + 1] += diff[i];
            if ((nums[i] - diff[i]) > 0)
            {
                return false;
            }
        }
        return true;
    }
    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int low = 0, high = queries.size();
        int ans = INT_MAX;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isZeroArray(nums, queries, mid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans == INT_MAX ? -1 : ans; // return the minimum number of queries
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
