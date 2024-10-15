#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ull unsigned long long
#define ll long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.



Example 1:

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].

Example 2:

Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]



Constraints:

    nums.length == k
    1 <= k <= 3500
    1 <= nums[i].length <= 50
    -105 <= nums[i][j] <= 105
    nums[i] is sorted in non-decreasing order.

     */
public:
    vector<int> smallestRange(vector<vector<int>> &nums)
    {
        int n = nums.size(), minLength = INT_MAX;
        //~ store the first elements of all the sorted arrays and initialize k pointers
        //~ <element,arrayIndex,elementIndex_in_the_array>
        multiset<tuple<int, int, int>> st;
        for (int i = 0; i < n; i++)
        {
            st.insert({nums[i][0], i, 0});
            minLength = min<int>(nums[i].size(), minLength);
        }
        int difference = INT_MAX;
        vector<int> ans(2, -1);
        /*
        ~ For each iteration check for minimum element and maximum element and calculate their difference
        ~ If (calculated difference < current best difference) then update the answer.
        ~ make sure to erase the minimum element and go for the next element in that particular array.
        ~ Array can be accessed via arrayIndex (minIdx) and next element via (ptrMin)
        ~ erase previous min element and insert the new element

        ~ Continue this till we actually go out of bounds for a particular array (minimum element array)

        * Time complexity : O(NlogN) + O((N+M) * log(N));
        * Space complexity : O(N)

        */
        while(!st.empty())
        {
            auto [minEle, minIdx, ptrMin] = *st.begin();
            auto [maxEle, maxIdx, ptrMax] = *st.rbegin();
            if (maxEle - minEle < difference)
            {
                difference = maxEle - minEle;
                ans.front() = minEle;
                ans.back() = maxEle;
            }
            if (ptrMin + 1 < nums[minIdx].size())
            {
                st.erase(st.begin());
                st.insert({nums[minIdx][ptrMin + 1], minIdx, ptrMin + 1});
            }
            else
            {
                break;
            }
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
