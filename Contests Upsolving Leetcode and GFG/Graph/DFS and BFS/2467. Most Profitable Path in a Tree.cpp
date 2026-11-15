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

    There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

    At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:

        the price needed to open the gate at node i, if amount[i] is negative, or,
        the cash reward obtained on opening the gate at node i, otherwise.

    The game goes on as follows:

        Initially, Alice is at node 0 and Bob is at node bob.
        At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
        For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
            If the gate is already open, no price will be required, nor will there be any cash reward.
            If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
        If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.

    Return the maximum net income Alice can have if she travels towards the optimal leaf node.
     */
public:
    vector<vector<int>> graph;
    // to check when alice or bob will land at same node
    vector<int> parent, depth;
    void updateCostsDFS(int node, int par, int d)
    {
        depth[node] = d;
        parent[node] = par;
        for (auto &child : graph[node])
        {
            if (child == par)
                continue;
            updateCostsDFS(child, node, d + 1);
        }
    }

    int maxNetIncomeDFS(int node, int par, vector<int> &amount)
    {
        const int total = amount[node];
        int maxChildProfit = INT_MIN;
        for (auto &child : graph[node])
        {
            if (child == par)
                continue;
            maxChildProfit = max(maxChildProfit, maxNetIncomeDFS(child, node, amount));
        }
        return maxChildProfit == INT_MIN ? total : total + maxChildProfit;
    }

    int mostProfitablePath(vector<vector<int>> &edges, const int bob, vector<int> &amount)
    {
        const int n = edges.size() + 1;
        parent.resize(n);
        depth.resize(n);
        graph.resize(n);
        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        updateCostsDFS(0, -1, 0);

        int current = bob, bobDepth = 0;
        while (current != -1)
        {
            if (depth.at(current) > bobDepth)
            {
                amount[current] = 0;
            }
            else if (depth.at(current) == bobDepth)
            {
                amount[current] /= 2;
            }
            current = parent[current];
            bobDepth++;
        }

        return maxNetIncomeDFS(0, -1, amount);
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