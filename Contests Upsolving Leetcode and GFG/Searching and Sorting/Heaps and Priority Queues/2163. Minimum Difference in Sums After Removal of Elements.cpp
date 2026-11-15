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

/*
You are given a 0-indexed integer array nums consisting of 3 * n elements.

You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:

    The first n elements belonging to the first part and their sum is sumfirst.
    The next n elements belonging to the second part and their sum is sumsecond.

The difference in sums of the two parts is denoted as sumfirst - sumsecond.

    For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
    Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.

Return the minimum difference possible between the sums of the two parts after the removal of n elements.



Example 1:

Input: nums = [3,1,2]
Output: -1
Explanation: Here, nums has 3 elements, so n = 1.
Thus we have to remove 1 element from nums and divide the array into two equal parts.
- If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
- If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
- If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
The minimum difference between sums of the two parts is min(-1,1,2) = -1.

Example 2:

Input: nums = [7,9,5,8,1,3]
Output: 1
Explanation: Here n = 2. So we must remove 2 elements and divide the remaining array into two parts containing two elements each.
If we remove nums[2] = 5 and nums[3] = 8, the resultant array will be [7,9,1,3]. The difference in sums will be (7+9) - (1+3) = 12.
To obtain the minimum difference, we should remove nums[1] = 9 and nums[4] = 1. The resultant array becomes [7,5,8,3]. The difference in sums of the two parts is (7+5) - (8+3) = 1.
It can be shown that it is not possible to obtain a difference

Hint 1
The lowest possible difference can be obtained when the sum of the first n elements in the resultant array is minimum, and the sum of the next n elements is maximum.
Hint 2
For every index i, think about how you can find the minimum possible sum of n elements with indices lesser or equal to i, if possible.
Hint 3
Similarly, for every index i, try to find the maximum possible sum of n elements with indices greater or equal to i, if possible.
Hint 4
Now for all indices, check if we can consider it as the partitioning index and hence find the answer.

*/

class Solution
{
private:
    void initializeSet(const vector<int> &nums, int start, int end,
                       multiset<int> &s, ll &sum)
    {
        sum = accumulate(nums.begin() + start, nums.begin() + end, 0LL);
        copy(nums.begin() + start, nums.begin() + end, inserter(s, s.end()));
    }

    void initializeSet(const vector<int> &nums, int start, int end,
                       multiset<int, greater<int>> &s, ll &sum)
    {
        sum = accumulate(nums.begin() + start, nums.begin() + end, 0LL);
        copy(nums.begin() + start, nums.begin() + end, inserter(s, s.end()));
    }

    template <typename SetType>
    void addAndMaintainSize(SetType &s, ll &sum, int element, size_t maxSize)
    {
        s.insert(element);
        sum += element;
        if (s.size() > maxSize)
        {
            sum -= *s.rbegin();
            s.erase(prev(s.end()));
        }
    }

    void buildLeftMinSums(const vector<int> &nums, int n, vector<ll> &leftSums)
    {
        multiset<int> leftSet;
        ll sum;

        initializeSet(nums, 0, n, leftSet, sum);
        leftSums[n] = sum;

        for (int i = n + 1; i <= 2 * n; i++)
        {
            addAndMaintainSize(leftSet, sum, nums[i - 1], n);
            leftSums[i] = sum;
        }
    }

    void buildRightMaxSums(const vector<int> &nums, int n, vector<ll> &rightSums)
    {
        multiset<int, greater<int>> rightSet;
        ll sum;

        initializeSet(nums, 2 * n, 3 * n, rightSet, sum);
        rightSums[2 * n] = sum;

        for (int i = 2 * n - 1; i >= n; i--)
        {
            addAndMaintainSize(rightSet, sum, nums[i], n);
            rightSums[i] = sum;
        }
    }

    ll computeMinDifference(const vector<ll> &leftSums, const vector<ll> &rightSums, int n)
    {
        ll result = LLONG_MAX;
        for (int i = n; i <= 2 * n; i++)
        {
            result = min(result, leftSums[i] - rightSums[i]);
        }
        return result;
    }

public:
    ll minimumDifference(vector<int> &nums)
    {
        const int n = nums.size() / 3;
        vector<ll> leftSums(3 * n + 1, 0);
        vector<ll> rightSums(3 * n + 1, 0);

        buildLeftMinSums(nums, n, leftSums);
        buildRightMaxSums(nums, n, rightSums);

        return computeMinDifference(leftSums, rightSums, n);
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    return 0;
}
#endif