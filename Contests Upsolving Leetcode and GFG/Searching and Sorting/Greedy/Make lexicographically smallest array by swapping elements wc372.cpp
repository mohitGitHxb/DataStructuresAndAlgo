#include <bits/stdc++.h>
using namespace std;
/*
Intuition

Main thing was abs(a[i]-a[i+1])<=limit, so to we have to minimise the difference for that we ahve to sort the array and then group the elements which obej this condition.
Approach

    make a vector of pairs and store index with their element in it.
    divide the group according to given conditiion abs(a[i]-a[i+1])<=limit and store it into map on different key values.
    sort every group indexes and put the elements accordingly.

Complexity

    Time complexity: O(nlog(n))

    Space complexity: O(n)


 */
class Solution
{
public:
    vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit)
    {
        unsigned n = nums.size();
        vector<pair<int, int>> sorted;
        vector<int> ans(n);
        unordered_map<int, vector<pair<int, int>>> groups;
        int countGroup = -1;
        for (int i = 0; i < n; i++)
        {
            sorted.push_back({nums[i], i});
        }
        sort(sorted.begin(), sorted.end());
        for (int i = 0; i < n; i++)
        {
            if (i == 0 or (sorted[i].first - sorted[i - 1].first) > limit)
            {
                countGroup++;
            }
            groups[countGroup].push_back(sorted.at(i));
        }

        for (auto p : groups)
        {
            vector<pair<int, int>> vp = p.second;
            vector<int> elements, ids;
            for (auto &q : p.second)
            {
                elements.emplace_back(q.first);
                ids.emplace_back(q.second);
            }
            sort(ids.begin(), ids.end());
            for (int i = 0; i < ids.size(); i++)
            {
                ans.at(ids.at(i)) = elements.at(i);
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