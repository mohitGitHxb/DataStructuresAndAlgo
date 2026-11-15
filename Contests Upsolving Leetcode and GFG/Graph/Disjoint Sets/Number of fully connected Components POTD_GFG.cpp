#include <bits/stdc++.h>
using namespace std;
/* 
Given an undirected graph with v vertices(numbered from 1 to v) and e edges. Find the number of good components in the graph.
A component of the graph is good if and only if the component is fully connected.
Note: A fully connected component is a subgraph of a given graph such that there's an edge between every pair of vertices in the component, the given graph can be a disconnected graph. 

Example 1:

Input: 


e=3 
v=3
edges={{1, 2},{1, 3},{3, 2}}
Output: 
1
Explanation: 
We can see that there is only one component in the graph and in this component there is a edge between any two vertces.

Example 2:

Input:

e=5 
v=7
edges={{1, 2},{7, 2},{3, 5},{3, 4},{4, 5}}
Output: 
2
Explanation: 
We can see that there are 3 components in the graph. For 1-2-7 there is no edge between 1 to 7, so it is not a fully connected component. Rest 2 are individually fully connected component.

Your Task:
You don't need to read input or print anything. Your task is to complete the function findNumberOfGoodComponent(), which takes an integer e and v and edges[][] as input parameters and returns an integer denoting the number of good components.

Expected Time Complexity: O(v+e)
Expected Auxiliary Space: O(depth of the graph)

 */
class Solution
{
public:
    void dfs(int node, vector<int> adj[], vector<bool> &visited, unordered_set<int> &st)
    {
        visited[node] = true;
        st.insert(node);
        for (int &neigh : adj[node])
        {
            if (visited[neigh] == false)
            {
                dfs(neigh, adj, visited, st);
            }
        }
    }
    int findNumberOfGoodComponent(int e, int v, vector<vector<int>> &edges)
    {
        vector<int> adj[v + 1];
        for (int i = 0; i < e; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int count = 0;
        vector<bool> visited(v + 1, false);
        for (int i = 1; i <= v; ++i)
        {
            if (visited[i] == false)
            {
                unordered_set<int> st;
                dfs(i, adj, visited, st);
                bool flag = true;
                for (int node : st)
                {
                    if (adj[node].size() != (st.size() - 1))
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    count++;
            }
        }
        return count;
    }
};
int main()
{
    return 0;
}