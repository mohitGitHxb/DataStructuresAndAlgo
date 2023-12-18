#include <bits/stdc++.h>
using namespace std;
/*
floydWarshall: This method implements the Floyd-Warshall algorithm to find the shortest path between all pairs of vertices in a graph. It takes a graph represented as a 2D vector of integers, the number of vertices n, a bitmask mask, and a maximum distance maxDistance as input. It returns a boolean value indicating whether the maximum distance between any two vertices in the given subset of vertices is less than or equal to maxDistance.

numberOfSets: This method calculates the number of sets of vertices in a graph such that the maximum distance between any two vertices in each set is less than or equal to a given maxDistance. It takes the number of vertices n, the maximum distance maxDistance, and a vector of vectors roads representing the edges in the graph as input. It returns the number of sets that satisfy the condition.
 */
class Solution
{
public:
    bool floydWarshall(vector<vector<int>> graph, int n, int mask, int maxDistance)
    {
        int dist = 0;                   // Initialize the maximum distance
        unordered_map<int, bool> taken; // Create a map to keep track of visited nodes

        // Set the visited nodes based on the given mask
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                taken[i] = true;
            }
        }

        // Perform Floyd-Warshall algorithm to find the shortest distances between all pairs of nodes
        for (int via = 0; via < n; via++)
        {
            // Check if the current node is visited
            if (taken.count(via))
            {
                // Iterate through all nodes i
                for (int i = 0; i < n; i++)
                {
                    // Check if node i is visited
                    if (taken.count(i))
                    {
                        // Iterate through all nodes j
                        for (int j = 0; j < n; j++)
                        {
                            // Check if node j is visited
                            if (taken.count(j))
                            {
                                // Update the shortest distance between node i and node j through node via
                                graph[i][j] = min(graph[i][j], graph[i][via] + graph[via][j]);
                            }
                        }
                    }
                }
            }
        }

        // Find the maximum distance among the visited nodes
        for (int i = 0; i < n; i++)
        {
            // Check if node i is visited
            if (taken.count(i))
            {
                // Iterate through all nodes j
                for (int j = 0; j < n; j++)
                {
                    // Check if node j is visited
                    if (taken.count(j))
                    {
                        // Update the maximum distance if the distance between node i and node j is greater than the current maximum distance
                        dist = max(dist, graph[i][j]);
                    }
                }
            }
        }

        // Check if the maximum distance is less than or equal to the given maximum distance
        return dist <= maxDistance;
    }

    /**
     * Calculate the number of sets that satisfy the given conditions.
     *
     * @param n The number of vertices in the graph.
     * @param maxDistance The maximum distance allowed between two vertices in a set.
     * @param roads A vector of vectors representing the roads between vertices.
     *              Each inner vector contains three integers: the starting vertex, the ending vertex, and the weight of the road.
     *
     * @return The number of sets that satisfy the given conditions.
     *
     * @throws None.
     */
    int numberOfSets(int n, int maxDistance, vector<vector<int>> &roads)
    {
        vector<vector<int>> graph(n, vector<int>(n, 1e8));
        for (int i = 0; i < n; i++)
            graph[i][i] = 0;
        for (auto &road : roads)
        {
            int u = road.at(0), v = road.at(1), w = road.at(2);
            graph[u][v] = min(graph[u][v], w);
            graph[v][u] = min(graph[v][u], w);
        }

        int ans = 1;
        int ways = (1 << n);
        for (int mask = 1; mask < ways; ++mask)
            ans += floydWarshall(graph, n, mask, maxDistance);
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