#include <bits/stdc++.h>
using namespace std;
/*
Find the number of coins to place in a tree node
 */
class Solution
{
public:
// Define long long as ll for convenience
#define ll long long

    // Define three maps to store the adjacency list, subtree size and answer for each node
    unordered_map<ll, vector<ll>> mp;
    unordered_map<ll, ll> mp1;
    unordered_map<ll, ll> ans;

    // DFS function to calculate the size of the subtree for each node
    ll dfs(ll node, ll par, vector<int> &cost)
    {
        ll s = 0;
        // Iterate over all children of the current node
        for (auto it : mp[node])
        {
            if (it != par)
            {
                // Recursively calculate the size of the subtree for each child
                s += dfs(it, node, cost);
            }
        }
        s++;
        // Store the size of the subtree for the current node
        mp1[node] = s;
        return s;
    }

    // DFS function to calculate the maximum product of cost values assigned to 3 distinct nodes in the subtree of each node
    vector<ll> dfs2(ll node, ll parent, vector<int> &cost)
    {
        vector<ll> v;            // vector to store cost values
        vector<ll> k;            // temporary vector to store cost values
        v.push_back(cost[node]); // push the cost of current node to vector v
        // Iterate over all children of the current node
        for (auto it : mp[node])
        {
            if (it != parent)
            {
                // Recursively calculate the maximum product for each child
                vector<ll> x = dfs2(it, node, cost);
                // Add the cost values of the child to the temporary vector
                for (auto it : x)
                {
                    k.push_back(it);
                }
            }
        }
        // If the size of vector v is less than 3, add all cost values from vector k to vector v
        if (v.size() < 3)
        {
            for (auto it : k)
            {
                v.push_back(it);
            }
        }
        else
        {
            // Sort the cost values in vector k in descending order
            sort(k.begin(), k.end(), greater<int>());
            // Add the three largest and two smallest cost values from vector k to vector v
            v.push_back(k[0]);
            v.push_back(k[1]);
            v.push_back(k[2]);
            v.push_back(k[k.size() - 1]);
            v.push_back(k[k.size() - 2]);
        }
        // Sort the cost values in vector v in descending order
        sort(v.begin(), v.end(), greater<ll>());
        // If the size of the subtree is less than 3, the maximum product is 1
        if (mp1[node] < 3)
        {
            ans[node] = 1;
        }
        else
        {
            // Calculate the maximum product of three largest cost values and two smallest cost values
            ll p1 = v[0] * v[1] * v[2] * 1LL;
            ll p2 = v[0] * v[v.size() - 1] * v[v.size() - 2] * 1LL;
            ll p3 = max(p1, p2);
            // If the maximum product is negative, set it to 0
            if (p3 < 0)
            {
                ans[node] = 0;
            }
            else
            {
                ans[node] = p3;
            }
        }
        // If the size of vector v is more than 5, return the five largest cost values
        if (v.size() <= 5)
            return v;
        return {v[0], v[1], v[2], v[v.size() - 1], v[v.size() - 2]};
    }

    // Main function to solve the problem
    vector<long long> placedCoins(vector<vector<int>> &edges, vector<int> &cost)
    {
        // Build the adjacency list
        for (auto it : edges)
        {
            mp[it[0]].push_back(it[1]);
            mp[it[1]].push_back(it[0]);
        }
        // Call the first DFS to calculate the size of the subtree for each node
        dfs(0, -1, cost);
        // Call the second DFS to calculate the maximum product for each node
        dfs2(0, -1, cost);
        // Build the answer vector
        vector<ll> c;
        for (int i = 0; i < cost.size(); i++)
        {
            c.push_back(ans[i]);
        }
        return c;
    }
};
/* ```
This code is a solution to a problem where we need to calculate the maximum product of cost values assigned to 3 distinct nodes in the subtree of each node in a tree. The tree is represented as an adjacency list and the cost values are stored in a vector. The solution uses two depth-first search (DFS) functions to calculate the size of the subtree for each node and the maximum product for each node, respectively. */
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