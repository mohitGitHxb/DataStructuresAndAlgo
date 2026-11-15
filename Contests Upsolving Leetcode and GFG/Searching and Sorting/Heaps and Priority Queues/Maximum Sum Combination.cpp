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
        You are given two integer arrays a[] and b[] of equal size. A sum combination is formed by adding one element from a[] and one from b[], using each index pair (i, j) at most once. Return the top k maximum sum combinations, sorted in non-increasing order.

        Examples:

        Input: a[] = [3, 2], b[] = [1, 4], k = 2
        Output: [7, 6]
        Explanation: Possible sums: 3 + 1 = 4, 3 + 4 = 7, 2 + 1 = 3, 2 + 4 = 6, Top 2 sums are 7 and 6.

        Input: a[] = [1, 4, 2, 3], b[] = [2, 5, 1, 6], k = 3
        Output: [10, 9, 9]
        Explanation: The top 3 maximum possible sums are : 4 + 6 = 10, 3 + 6 = 9, and 4 + 5 = 9

        Constraints:
        1 ≤ a.size() = b.size() ≤ 105
        1 ≤ k ≤ a.size()
        1 ≤ a[i], b[i] ≤ 104

        @Approach:
        &- Sort both arrays in descending order.
        &- Use a max heap to store the sum combinations.
        &- Use a map to track visited index pairs to avoid duplicates.
        &- Push the sum of the largest elements from both arrays into the heap.
        &- Pop the top k elements from the heap to get the k maximum sums.
        &- For each popped element, push the next possible sums by incrementing the indices of the arrays.
        &- Return the results in a vector.
        &- Time Complexity: O(k log k + n log n), where n is the size of the arrays.
        &- Space Complexity: O(k + n), for the heap and the map.

     */
public:
    vector<int> topKSumPairs(vector<int> &a, vector<int> &b, int k)
    {
        int n = a.size();
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end(), greater<int>());

        priority_queue<pair<int, pair<int, int>>> pq;
        map<pair<int, int>, bool> vis;

        pq.push({a[0] + b[0], {0, 0}});
        vis[{0, 0}] = true;
        vector<int> res;

        while (res.size() < k)
        {
            int sum = pq.top().first;
            int i = pq.top().second.first;
            int j = pq.top().second.second;
            res.push_back(sum);
            pq.pop();

            if (i + 1 < n && !vis[{i + 1, j}])
            {
                vis[{i + 1, j}] = true;
                pq.push({a[i + 1] + b[j], {i + 1, j}});
            }
            if (j + 1 < n && !vis[{i, j + 1}])
            {
                vis[{i, j + 1}] = true;
                pq.push({a[i] + b[j + 1], {i, j + 1}});
            }
        }

        return res;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    vector<string> words = {"aba", "bcb", "ece", "aa", "e"};
    vector<vector<int>> queries = {{0, 2}, {1, 4}, {1, 1}};
    obj.vowelStrings(words, queries);
    // Test cases for local testing
    return 0;
}
#endif