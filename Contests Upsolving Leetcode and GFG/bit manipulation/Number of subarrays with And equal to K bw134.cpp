#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
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

class Solution
{
private:
    /*
Given an array of integers nums and an integer k, return the number of
subarrays
of nums where the bitwise AND of the elements of the subarray equals k.



Example 1:

Input: nums = [1,1,1], k = 1

Output: 6

Explanation:

All subarrays contain only 1's.

Example 2:

Input: nums = [1,1,2], k = 1

Output: 3

Explanation:

Subarrays having an AND value of 1 are: [1,1,2], [1,1,2], [1,1,2].

Example 3:

Input: nums = [1,2,3], k = 2

Output: 2

Explanation:

Subarrays having an AND value of 2 are: [1,2,3], [1,2,3].

    @ Trick:
    &- While doing And or OR operation there are only logN values possible not 2^N because
    ~ In case of AND: if bit becomes 0 it remains 0 forever
    ~ In case of OR : if bit becomes 1 it remains 1 forever

    The property of bitwise AND is it will get lower and lower every subarray, so the values will always decreasing and not generating any more distinct subarray. So the TC is at most O(32N)
     */
public:
    Solution()
    {
        fast_read();
    }

    long long countSubarrays(vector<int> &nums, int k)
    {
        int n = nums.size();
        unordered_map<int, int, custom_hash> previousAndCount;
        ll ans = 0;
        for (int &i : nums)
        {
            unordered_map<int, int, custom_hash> currentAndCount;
            for (auto &[andVal, cnt] : previousAndCount)
            {
                currentAndCount[andVal & i] += cnt;
            }
            currentAndCount[i]++;
            for (auto &[andVal, cnt] : currentAndCount)
            {
                if (andVal == k)
                    ans += cnt;
            }
            previousAndCount = currentAndCount;
        }
        return ans;
    }
};

int main()
{
    return 0;
}