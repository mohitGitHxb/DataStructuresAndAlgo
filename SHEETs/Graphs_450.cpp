#include <bits/stdc++.h>
using namespace std;
/*
% Some basic theory about graphs
~ total degree of a graph = 2 x Edges (undirected graph)
~ Given N nodes and M edges
    ! M lines (represents edges)
 */
class GraphTraversals
{
public:
    //* O(V+E) T.C | O(V) space directed graph
    vector<int> BFS(int node, vector<vector<int>> adj, int vertices)
    {
        vector<bool> visited(vertices + 1);
        visited[node] = true;
        queue<int> q;
        vector<int> bfs;
        q.emplace(node);
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            bfs.emplace_back(x);
            for (auto &it : adj.at(x))
            {
                if (!visited[it])
                {
                    visited[it] = true;
                    q.emplace(it);
                }
            }
        }
        return bfs;
    }

    //* O(N) S.C | O(2E) T.C for undirected graph
    void DFS(vector<vector<int>> &adj, vector<bool> &visited, int node)
    {
        visited.at(node) = true;
        cout << node << "\n";
        for (auto &it : adj.at(node))
        {
            if (!visited[it])
            {
                DFS(adj, visited, it);
            }
        }
    }
};
int main()
{
    return 0;
}