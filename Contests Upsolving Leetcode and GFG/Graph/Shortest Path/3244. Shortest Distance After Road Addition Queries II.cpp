#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define bigInt __int128_t
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
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
You are given an integer n and a 2D integer array queries.

There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.

Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.

! In harder version constraints are 1e5 and this condition is given
! There are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
     */
public:
    const int MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    // int dijekstra(vector<vector<int>> &adj)
    // {
    //     set<pair<int, int>> s;
    //     s.insert({0, 0});
    //     vector<int> dist(adj.size(), INT_MAX);

    //     dist.at(0) = 0;
    //     while (!s.empty())
    //     {
    //         auto [d, u] = *s.begin();
    //         s.erase(s.begin());
    //         for (auto &v : adj[u])
    //         {
    //             if (dist[v] > d + 1)
    //             {
    //                 s.erase({d + 1, v});
    //                 dist[v] = d + 1;
    //                 s.insert({dist[v], v});
    //             }
    //         }
    //     }

    //     return dist.back();
    // }
    // vector<int> shortestDistanceAfterQueries_EasyVersion(int n, vector<vector<int>> &queries)
    // {
    //     vector<vector<int>> adj(n);
    //     for (int i = 0; i < n - 1; i++)
    //     {
    //         adj[i].push_back(i + 1);
    //         adj[i + 1].push_back(i);
    //     }
    //     vector<int> ans;
    //     for (auto &q : queries)
    //     {
    //         adj[q[1]].push_back(q[0]);
    //         adj[q[0]].push_back(q[1]);
    //         ans.push_back(dijekstra(adj));
    //     }
    //     return ans;
    // }
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>> &queries)
    {
        set<int> activeCities;
        for (int i = 0; i < n; i++)
            activeCities.emplace(i);
        vector<int> ans;
        /* 
        &- Just remove all the cities between u and v because it is always better to choose the shorter path(just created because of query)
        &- And it is also given that there are no two queries such that queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1] (means no overlapping)


        
        
         */
        for (auto &query : queries)
        {
            int u = query.front();
            int v = query.back();
            /* 
            % We don't want to remove the city u and v but want to remove cities between them
            % so simply remove u+1 to v-1
            & ans = activeCities.size() - 1 [-1 because city 0 cannot be removed]
             */
            auto ub = activeCities.upper_bound(v - 1);
            auto lb = activeCities.lower_bound(u + 1);
            activeCities.erase(lb, ub);
            ans.push_back(activeCities.size() - 1);
        }
        return ans;
    }
};

int main()
{
    Solution obj;
    return 0;
}