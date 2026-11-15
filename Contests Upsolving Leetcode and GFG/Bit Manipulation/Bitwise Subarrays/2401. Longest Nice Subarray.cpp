#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
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
static int init = []()
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
    You are given an array nums consisting of positive integers.

    We call a subarray of nums nice if the bitwise AND of every pair of elements that are in different positions in the subarray is equal to 0.

    Return the length of the longest nice subarray.

    A subarray is a contiguous part of an array.

    Note that subarrays of length 1 are always considered nice.



    Example 1:

    Input: nums = [1,3,8,48,10]
    Output: 3
    Explanation: The longest nice subarray is [3,8,48]. This subarray satisfies the conditions:
    - 3 AND 8 = 0.
    - 3 AND 48 = 0.
    - 8 AND 48 = 0.
    It can be proven that no longer nice subarray can be obtained, so we return 3.

    Example 2:

    Input: nums = [3,1,5,11,13]
    Output: 1
    Explanation: The length of the longest nice subarray is 1. Any subarray of length 1 can be chosen.

    @ approach:
    &- if there are repeating bits in a subarray (bit = 1) that means the AND of elements won't be 0 (pairwise AND)
    &- Hence the necessary condition is to find the longest subarray without repeating bits

    * Time complexity: O(n)
    * Space complexity: O(31) Size of bitCount
     */
public:
    vector<int> bitCount;
    bool foundRepeatingBits(const vector<int> &nums, const int index, bool isAddMode = true)
    {
        bool result = false;
        for (int i = 0; i < 31; i++)
        {
            if (nums.at(index) & (1 << i))
            {
                bitCount.at(i) += isAddMode ? 1 : -1;
            }
            if (bitCount.at(i) > 1)
            {
                result = true;
            }
        }
        return result;
    }
    int longestNiceSubarray(vector<int> &nums)
    {
        const int n = nums.size();
        bitCount.resize(31);
        int start = 0;
        int ans = 1;
        for (int end = 0; end < n; end++)
        {
            bool isRepeating = foundRepeatingBits(nums, end, true);
            while (start < end and isRepeating)
            {
                isRepeating = foundRepeatingBits(nums, start, false);
                start++;
            }
            ans = max(ans, end - start + 1);
        }
        return ans;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif