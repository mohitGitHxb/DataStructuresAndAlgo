#include <bits/stdc++.h>
using namespace std;

/* 

This problem is solved using the Floyd-Warshall algorithm, which is an algorithm for finding the shortest paths in a weighted graph with positive or negative edge weights (but with no negative cycles). The main idea is to pre-calculate the minimum cost to convert each character to another character using the given cost array.

Time Complexity: O(n^3) due to the Floyd-Warshall algorithm, where n is the number of characters in the alphabet (26 in this case).

Space Complexity: O(n^2) for storing the graph, where n is the number of characters in the alphabet (26 in this case).

Important Segments of the Code:

1. The graph is initialized with a size of 26x26 (for each character in the alphabet) and filled with a large number (1e9). The diagonal is filled with 0s as the cost to convert a character to itself is 0.

2. The graph is then updated with the given cost to convert each character in the original array to the corresponding character in the changed array.

3. The Floyd-Warshall algorithm is applied to find the minimum cost to convert each character to another character. This is done by checking if the cost to convert character i to character j is greater than the cost to convert character i to character k plus the cost to convert character k to character j. If it is, the cost to convert character i to character j is updated.

4. Finally, the minimum cost to convert the source string to the target string is calculated by summing up the cost to convert each character in the source string to the corresponding character in the target string. If the cost to convert a character is still the large number (1e9), it means it's impossible to convert that character, so -1 is returned.
 */
class Solution
{
public:
    long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
    {
        vector<vector<int>> graph(26, vector<int>(26, 1e9));
        for (int i = 0; i < original.size(); i++)
        {
            graph[original[i] - 'a'][changed[i] - 'a'] = min(graph[original[i] - 'a'][changed[i] - 'a'], cost[i]);
            graph[original[i] - 'a'][original[i] - 'a'] = 0;
        }

        // dijekstra algorithm or Floyd-Warshall Algorithm
        // Since there is no negative edge in the graph and sources are all different
        // we can use floyd-warshall algorithm
        for (int k = 0; k < 26; k++)
        {
            for (int i = 0; i < 26; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }

        long long ans = 0;
        for (int i = 0; i < source.size(); i++)
        {
            if (source.at(i) == target.at(i))
                continue;
            if (graph[source[i] - 'a'][target[i] - 'a'] == 1e9)
                return -1;
            ans += graph[source[i] - 'a'][target[i] - 'a'];
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