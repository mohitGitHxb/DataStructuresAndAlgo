#include <bits/stdc++.h>
using namespace std;

/*
Intuition

Since we need to find the maximum amount of initial currency, so in every conversion, at last we need initial currency.

If 'A' is initial currency then in conversion graph we need last converted currency as 'A' that is initial currency,

A -> B -> C -> D -> A

So we need to find these conversion path in both the days, if we have converted our initital currency to some currency X, then there should be way to convert X back to initial currency.
We need to check for every possible conversion and store the maximum of all the valid conversion path.

NOTE :

    If rate of converting from currency1​ to currency2​ is x, then rate of converting from currency2​ to currency1​ will be x1​.
    So it may be the case when we need to convert currency by reciprocal of rate.

Approach

Since we need to check for every possible path and there is connectivity in the conversion of currency. So we can convert our problem into some graph and then use BFS to explore all the conversion paths.
Algorithm :

    Constructing graph

We will make 2 graphs, adj1 is graph for day-1 and adj2 is graph for day-2. We can use map kind of data structure to construct our graph, where key will be the name of currency (i.e., string) and value will be the list of pairs, where the first member will be another string and second member will be rate of conversion. We will make undirected graph from both sides and weight will be the rate of conversion. Like, A -> B (r), r - rate. Then we'll add 2 edges:
- from A -> B with edge weight r and from B -> A with edge weight r1​

In CPP, we can declare our graph like this:

map<string, vector<pair<string, double>>> adj1, adj2;

    BFS Traversal

We'll start BFS from given initialCurrency on graph1, we'll maintain queue data structure where every element will be in pair : {currentNode, amountTillNow}. As we'll choose neighbour node (i.e., conversion), let say currentNode, we'll multiply current rate of chosen node with our previous amount.
Now if our current node is the also the node in graph2. Then we'll perform another BFS traversal on graph2 with initial node as currentNode. And here also we'll maintain queue with pairs and keep multilplying the rate. As we will find the node with currency as of initialCurrency, we'll update the answer and we'll not check any neighbour node for this node.

Basically here we are checking for each node in graph1, if there is node in graph2 then find the amount how much we can get and update our answer. If in graph2 we can't reach the initialCurrency then we'll return 0.

Complexity

V1​ and E1​ be the number of vertices and edges in adj1.
V2​ and E2​ be the number of vertices and edges in adj2.

    Time complexity:
    O(V1​∗(V2​+E2​)+E1​)

    Space complexity:
    O(E1​+E2​+V1​+V2​)


*/
class Solution
{
public:
    unordered_map<string, vector<pair<string, double>>> day1Graph, day2Graph;

    /**
     * Construct graphs for day1 and day2 based on the given pairs and rates.
     *
     * @param pairs1  Pairs of currencies for day1.
     * @param rates1  Exchange rates for day1.
     * @param pairs2  Pairs of currencies for day2.
     * @param rates2  Exchange rates for day2.
     */
    void constructGraphs(vector<vector<string>> &pairs1, vector<double> &rates1,
                         vector<vector<string>> &pairs2, vector<double> &rates2)
    {
        const int n = pairs1.size(), m = pairs2.size();

        // Construct graph1
        for (int i = 0; i < n; i++)
        {
            day1Graph[pairs1[i][0]].push_back({pairs1[i][1], rates1[i]});
            day1Graph[pairs1[i][1]].push_back({pairs1[i][0], 1 / rates1[i]});
        }

        // Construct graph2
        for (int i = 0; i < m; i++)
        {
            day2Graph[pairs2[i][0]].push_back({pairs2[i][1], rates2[i]});
            day2Graph[pairs2[i][1]].push_back({pairs2[i][0], 1 / rates2[i]});
        }
    }

    /**
     * Perform BFS on day2 graph starting from the given initial currency.
     *
     * @param start The starting currency
     * @param initialCurrency  The initial currency.
     * @return The maximum amount that can be obtained.
     */
    double bfsDay2(const string &start, const string &initialCurrency)
    {
        queue<pair<string, double>> q;
        q.emplace(start, 1.0);
        unordered_set<string> vis;
        vis.insert(start);
        double ans = 0;

        while (!q.empty())
        {
            auto [curr, amount] = q.front();
            q.pop();
            if (curr == initialCurrency)
            {
                ans = max(ans, amount);
                continue;
            }

            for (auto &node : day2Graph[curr])
            {
                if (!vis.count(node.first))
                {
                    double newAmount = amount * node.second;
                    vis.insert(node.first);
                    q.emplace(node.first, newAmount);
                }
            }
        }
        return ans;
    }

    /**
     * Calculate the maximum amount that can be obtained by performing BFS on day1 and day2 graphs.
     *
     * @param initialCurrency  The initial currency.
     * @param pairs1           Pairs of currencies for day1.
     * @param rates1           Exchange rates for day1.
     * @param pairs2           Pairs of currencies for day2.
     * @param rates2           Exchange rates for day2.
     * @return The maximum amount that can be obtained.
     */
    double maxAmount(string initialCurrency, vector<vector<string>> &pairs1,
                     vector<double> &rates1, vector<vector<string>> &pairs2,
                     vector<double> &rates2)
    {

        constructGraphs(pairs1, rates1, pairs2, rates2);
        double ans = 1.0; // Declare ans here

        // Perform BFS on day1
        queue<pair<string, double>> q;
        q.emplace(initialCurrency, 1.0);
        unordered_set<string> vis;
        vis.insert(initialCurrency);

        while (!q.empty())
        {
            auto [curr, amount] = q.front();
            q.pop();
            for (auto &neighbor : day1Graph[curr])
            { // Iterate over neighbors of curr
                if (!vis.count(neighbor.first))
                {
                    double newAmount = amount * neighbor.second;
                    vis.insert(neighbor.first);
                    if (day2Graph.count(neighbor.first))
                    {
                        double answer2 = bfsDay2(neighbor.first, initialCurrency);
                        ans = max(ans, answer2 * newAmount);
                    }
                    q.emplace(neighbor.first, newAmount);
                }
            }
        }
        return ans;
    }
};
int main()
{
    return 0;
}