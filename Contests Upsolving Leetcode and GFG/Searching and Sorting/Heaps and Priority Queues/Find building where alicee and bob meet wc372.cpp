#include <bits/stdc++.h>
using namespace std;
/* 
You are given a 0-indexed array heights of positive integers, where heights[i] represents the height of the ith building.

If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].

You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is in building ai while Bob is in building bi.

Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.

 

Example 1:

Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
Output: [2,5,-1,5,2]
Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2]. 
In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5]. 
In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
In the fifth query, Alice and Bob are already in the same building.  
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

Example 2:

Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
Output: [7,6,-1,4,6]
Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

 

Constraints:

    1 <= heights.length <= 5 * 104
    1 <= heights[i] <= 109
    1 <= queries.length <= 5 * 104
    queries[i] = [ai, bi]
    0 <= ai, bi <= heights.length - 1



 */


/* 
^ Intuition

The goal is to determine the leftmost meeting point of two characters jumping between buildings, given their jump conditions and building heights. For simpler cases, direct comparisons suffice. However, for more complex scenarios, a priority queue helps manage unresolved cases efficiently.
Approach

The algorithm iterates through each query, categorizing them based on direct comparisons or unresolved cases. It utilizes a priority queue to manage unsolved queries. While traversing through the building heights, it resolves queries where the current height surpasses the height needed for meeting. The unresolved cases are stored in a map for future reference. As the height increases, the algorithm resolves additional queries by comparing the current height with the stored unresolved cases, effectively determining the leftmost meeting point for each query. This approach optimally handles complex scenarios while efficiently processing the simpler ones.

 */
class Solution
{
public:
    vector<int> leftmostBuildingQueries(vector<int> &heights, vector<vector<int>> &queries)
    {
        vector<int> ans(queries.size(), -1);
        unsigned n = heights.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_map<int, vector<pair<int, int>>> mp; // smaller height value idx, <max height of i,j from queries, query_idx>
        // i < j && heights[i] < heights[j] ans = j;
        // i > j && heights[i] > heights[j] ans = i;
        // i == j then ans = i or j;
        for (int i = 0; i < queries.size(); i++)
        {
            int low = queries[i].front();
            int high = queries[i].back();
            if (low < high && heights[low] < heights[high])
            {
                ans[i] = high;
            }
            else if (low > high && heights[low] > heights[high])
            {
                ans[i] = low;
            }
            else if (low == high)
            {
                ans[i] = low;
            }
            else
            {
                if (heights[low] < heights[high])
                {
                    mp[max(low, high)].push_back({heights[high], i});
                }
                else
                {
                    mp[max(low, high)].push_back({heights[low], i});
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            while (!pq.empty() && pq.top().first < heights[i])
            {
                ans[pq.top().second] = i;
                pq.pop();
            }
            if (mp.find(i) != mp.end())
            {
                for (auto p : mp[i])
                {
                    pq.push(p);
                }
            }
        }
        return ans;
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