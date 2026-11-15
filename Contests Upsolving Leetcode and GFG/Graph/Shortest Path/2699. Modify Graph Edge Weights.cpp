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
You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.

Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).

Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.

Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
* Time complexity : O(E^2logV)
* Space complexity : O(2V)
     */
public:
    const int MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    ll shortestPathWithoutNegativeEdge(int n, vector<vector<int>> &edges, int source, int destination)
    {

        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < n; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            if (w != -1)
            {
                graph.at(u).emplace_back(v, w);
                graph.at(v).emplace_back(u, w);
            }
        }
        vector<ll> dist(n, 1e15);
        dist.at(source) = 0;
        set<pair<ll, int>> s;
        s.insert({0, source});
        while (!s.empty())
        {

            auto it = s.begin();
            int u = it->second;
            ll w = it->first;
            s.erase(it);
            for (auto x : graph[u])
            {
                int v = x.first;
                ll weight = x.second;
                if (w + weight < dist[v])
                {
                    if (dist[v] != 1e15)
                        s.erase({dist[v], v});
                    dist[v] = w + weight;
                    s.insert({dist[v], v});
                }
            }
        }
        return dist[destination];
    }



    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> &edges, int source, int destination, int target)
    {
        ll initialShortestDistance = shortestPathWithoutNegativeEdge(n, edges, source, destination);
        //% This means that current shortest distance even without considering any negative -1 edges we still are able to make the distance equal to target
        //% So for all the -1 edges we can simply replace them with postive large values like 2e9
        if (initialShortestDistance == target)
        {
            for (auto &edge : edges)
            {
                if (edge[2] == -1)
                {
                    edge[2] = 2e9;
                }
            }
            return edges;
        }
        //& If current shortest distance without considering the -1 edges is still less than target then we can't make any path which can give SHORTEST DISTANCE equal to target
        //& Because it is clearly written that we can only increase the value of the edges not decrease it
        else if (initialShortestDistance < target)
        {
            return vector<vector<int>>();
        }
        /*
        ~ First we will now assign each -1 edge with value = 1 and will again check whether the new shortest path including all edges is equal to target or not
        ~ If it is equal then simply return the modified edges
        & Else now we will calculate the difference of current new shortest distance with the target let it be diff = target - newShortestDistance
        & Assign one of the previous -1 edge ( currently in the path ) this diff value
        & Finally return the new modified edges

         */
        else
        {
            bool found = false;
            for (auto &edge : edges)
            {
                if (edge[2] == -1)
                {
                    edge[2] = (found) ? 2e9 : 1;
                    if (!found)
                    {

                        ll newShortestDistance = shortestPathWithoutNegativeEdge(n, edges, source, destination);
                        if (newShortestDistance <= target)
                        {
                            found = true;
                            edge[2] += (target - newShortestDistance);
                        }
                    }
                }
            }
            if (!found)
            {
                return vector<vector<int>>();
            }
            return edges;
        }
        return vector<vector<int>>();
    }










    vector<vector<int>> modifiedGraphEdges2(int n, vector<vector<int>> &edges, int source, int destination, int target)
    {
        // this is a clean implementation with lesser redundancies
        ll initialShortestDistance = shortestPathWithoutNegativeEdge(n, edges, source, destination);
        if (initialShortestDistance < target)
            return vector<vector<int>>();
        bool found = (target == initialShortestDistance);
        for (auto &edge : edges)
        {
            if (edge[2] == -1)
            {
                edge[2] = (found) ? 2e9 : 1;
                if (!found)
                {
                    ll newShortestDistance = shortestPathWithoutNegativeEdge(n, edges, source, destination);
                    if (newShortestDistance <= target)
                    {
                        found = true;
                        edge[2] += (target - newShortestDistance);
                    }
                }
            }
        }
        if (!found)
            return vector<vector<int>>();
        return edges;
    }
};

int main()
{
    Solution obj;
    return 0;
}