#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
    Problem statement:
    There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

    You are also given a 0-indexed integer array values of length n, where values[i] is the value associated with the ith node, and an integer k.

    A valid split of the tree is obtained by removing any set of edges, possibly empty, from the tree such that the resulting components all have values that are divisible by k, where the value of a connected component is the sum of the values of its nodes.

    Return the maximum number of components in any valid split.


     * PROBLEM UNDERSTANDING:
     * - Given an undirected tree with n nodes (0 to n-1)
     * - Each node has a value, and we have a divisor k
     * - Goal: Split tree into maximum components where each component's sum is divisible by k
     *
     * KEY INSIGHT:
     * Think in terms of NODES, not edges!
     * - Process tree from leaves inward (like peeling an onion)
     * - For each leaf: if its value is divisible by k, it can form its own component
     * - If not divisible, merge it with its parent (add values together)
     * - Continue until all nodes are processed
     *
     * APPROACH:
     * 1. Build adjacency list and track node degrees (number of connections)
     * 2. Use BFS starting from all leaf nodes (degree = 1)
     * 3. For each leaf:
     *    - If sum is divisible by k → it's a valid component (increment count)
     *    - If not divisible by k → merge with parent (add value to parent)
     * 4. After processing, the parent becomes a new leaf (repeat)
     *
     * TIME: O(n) - visit each node once
     * SPACE: O(n) - adjacency list and auxiliary arrays
     */

public:
    int maxKDivisibleComponents(int n,
                                const vector<vector<int>> &edges,
                                const vector<int> &values,
                                int k)
    {
        // Base case: single node is always valid
        if (n < 2)
            return 1;

        // Build adjacency list for the tree
        vector<vector<int>> adjacencyList(n);
        vector<int> degree(n, 0); // Track connections for each node
        vector<long long> nodeValues(values.begin(), values.end());

        // Build undirected graph
        for (const auto &edge : edges)
        {
            int node1 = edge[0];
            int node2 = edge[1];
            adjacencyList[node1].push_back(node2);
            adjacencyList[node2].push_back(node1);
            degree[node1]++;
            degree[node2]++;
        }

        // Initialize BFS queue with all leaf nodes (degree == 1)
        queue<int> leafQueue;
        for (int i = 0; i < n; i++)
        {
            if (degree[i] == 1)
            {
                leafQueue.push(i);
            }
        }

        int componentCount = 0;

        // Process nodes layer by layer from leaves to root
        while (!leafQueue.empty())
        {
            int currentNode = leafQueue.front();
            leafQueue.pop();

            // Mark node as processed
            degree[currentNode]--;

            // Check if current node's value is divisible by k
            long long currentValue = nodeValues[currentNode];
            bool isDivisible = (currentValue % k == 0);

            if (isDivisible)
            {
                // This node forms its own component - don't propagate value
                componentCount++;
            }

            // Propagate value to parent if not divisible
            long long valueToPropagate = isDivisible ? 0 : currentValue;

            // Find parent and merge values if needed
            for (int neighbor : adjacencyList[currentNode])
            {
                // Only process unvisited neighbors (potential parents)
                if (degree[neighbor] > 0)
                {
                    // Remove edge: reduce neighbor's degree
                    degree[neighbor]--;

                    // Merge current node's value into parent
                    nodeValues[neighbor] += valueToPropagate;

                    // If neighbor becomes a leaf, add to queue
                    if (degree[neighbor] == 1)
                    {
                        leafQueue.push(neighbor);
                    }
                }
            }
        }

        return componentCount;
    }
};

/*
 * EXAMPLE WALKTHROUGH:
 * n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
 *
 * Tree structure:
 *       0(1)
 *        |
 *       2(1)
 *      / |
 *    1(8) 4(4)
 *     |
 *    3(4)
 *
 * Initial leaves: 0, 3, 4 (degree = 1)
 *
 * Process leaf 0: value=1, not divisible by 6 → merge with parent 2
 *   nodeValues[2] = 1 + 1 = 2
 *
 * Process leaf 3: value=4, not divisible by 6 → merge with parent 1
 *   nodeValues[1] = 8 + 4 = 12 (divisible!) → component++
 *
 * Process leaf 4: value=4, not divisible by 6 → merge with parent 2
 *   nodeValues[2] = 2 + 4 = 6 (divisible!) → component++
 *
 * Result: 2 components
 */
int main()
{
    return 0;
}