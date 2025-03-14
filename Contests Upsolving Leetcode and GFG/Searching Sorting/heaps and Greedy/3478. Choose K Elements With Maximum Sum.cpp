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
You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.

For each index i from 0 to n - 1, perform the following:

    Find all indices j where nums1[j] is less than nums1[i].
    Choose at most k values of nums2[j] at these indices to maximize the total sum.

Return an array answer of size n, where answer[i] represents the result for the corresponding index i.



Example 1:

Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2

Output: [80,30,0,80,50]

Explanation:

    For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
    For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
    For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
    For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
    For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.


    @ approach:
    Sort nums1 and its corresponding nums2 values together based on nums1.
    Use a max heap to track the top k values of nums2 as you process each element in the sorted order.
     */
public:
    vector<ll> findMaxSum(vector<int> &nums1, vector<int> &nums2, int k)
    {
        const int n = nums1.size();
        vector<tuple<int, int, int>> elements(n);
        for (int i = 0; i < n; i++)
        {
            elements.at(i) = {nums1.at(i), nums2.at(i), i};
        }
        sort(elements.begin(), elements.end());
        vector<ll> ans(n);
        multiset<int> minSt;
        ll sum = 0;
        for (int i = 0; i < n; i++)
        {
            auto [num1, num2, index] = elements.at(i);
            if (i > 0 && get<0>(elements.at(i - 1)) == num1)
            {
                ans.at(index) = ans.at(get<2>(elements.at(i - 1)));
            }
            else
            {
                ans.at(index) = sum;
            }
            minSt.insert(num2);
            sum += num2;

            if (minSt.size() > k)
            {
                sum -= *minSt.begin();
                minSt.erase(minSt.begin());
            }
        };
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