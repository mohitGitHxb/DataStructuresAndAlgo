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
        You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:

            Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.

        Return the total number of continuous subarrays.

        A subarray is a contiguous non-empty sequence of elements within an array.



        Example 1:

        Input: nums = [5,4,2,4]
        Output: 8
        Explanation:
        Continuous subarray of size 1: [5], [4], [2], [4].
        Continuous subarray of size 2: [5,4], [4,2], [2,4].
        Continuous subarray of size 3: [4,2,4].
        Thereare no subarrys of size 4.
        Total continuous subarrays = 4 + 3 + 1 = 8.
        It can be shown that there are no more continuous subarrays.



        Example 2:

        Input: nums = [1,2,3]
        Output: 6
        Explanation:
        Continuous subarray of size 1: [1], [2], [3].
        Continuous subarray of size 2: [1,2], [2,3].
        Continuous subarray of size 3: [1,2,3].
        Total continuous subarrays = 3 + 2 + 1 = 6.

    @ Approach
    &- Similar concept as used to find Sliding window maximum and minimum.
    &- use deque to keep track of minimums and maximums in a range (simple pointers wouldn't work)
    &- if range is not continuous then pop out the pointers that are not continuous
     */
public:
    const int mod = 1e9 + 7;
    ll continuousSubarrays(const vector<int> &nums)
    {
        const int n = nums.size();
        ll totalSubarrays = 0;
        int startIndex = 0;
        deque<int> minimums, maximums;
        for (int i = 0; i < n; i++)
        {
            while (!minimums.empty() && nums[i] <= nums[minimums.back()])
                minimums.pop_back();
            while (!maximums.empty() && nums[i] >= nums[maximums.back()])
                maximums.pop_back();
            minimums.push_back(i);
            maximums.push_back(i);
            while (!minimums.empty() && !maximums.empty() && nums[maximums.front()] - nums[minimums.front()] > 2)
            {
                if (minimums.front() == startIndex)
                    minimums.pop_front();
                if (maximums.front() == startIndex)
                    maximums.pop_front();
                startIndex++;
            }
            totalSubarrays += i - startIndex + 1;
        }
        return totalSubarrays;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
