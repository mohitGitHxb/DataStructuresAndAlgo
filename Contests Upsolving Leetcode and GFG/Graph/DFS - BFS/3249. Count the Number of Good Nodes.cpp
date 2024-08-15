#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // Adjacency list to represent the tree
    unordered_map<int, vector<int>> adjList;

    // Variable to store the count of good nodes
    int goodNodeCount = 0;

    // Depth-First Search (DFS) function to traverse the tree and count good nodes
    int dfs(int currentNode, vector<int> &visited)
    {
        // If the node is already visited, return 0 (no contribution to subtree size)
        if (visited[currentNode] == 1)
            return 0;

        // Mark the current node as visited
        visited[currentNode] = 1;

        int subtreeSize = 0;
        unordered_map<int, int> subtreeSizeFrequency; // Map to count the frequency of subtree sizes

        // Explore all adjacent nodes (child nodes)
        for (auto neighbor : adjList[currentNode])
        {
            if (visited[neighbor] == 0)
            {
                int childSubtreeSize = dfs(neighbor, visited); // Recursively calculate the size of the subtree
                subtreeSizeFrequency[childSubtreeSize]++;
                subtreeSize += childSubtreeSize;
            }
        }

        // If the current node has 1 or fewer unique subtree sizes, it's a good node
        if (subtreeSizeFrequency.size() <= 1)
            goodNodeCount++;

        return subtreeSize + 1; // Return the size of the subtree rooted at this node
    }

    // Function to count the number of good nodes in the tree
    int countGoodNodes(vector<vector<int>> &edges)
    {
        int n = edges.size();

        // Build the adjacency list from the edge list
        for (int i = 0; i < n; i++)
        {
            adjList[edges[i][0]].push_back(edges[i][1]);
            adjList[edges[i][1]].push_back(edges[i][0]);
        }

        vector<int> visited(n + 1, 0); // Vector to keep track of visited nodes
        dfs(0, visited);               // Start DFS from node 0

        return goodNodeCount; // Return the total number of good nodes
    }
};

int main()
{
    return 0;
}