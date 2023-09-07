#include <bits/stdc++.h>
using namespace std;
/*
**Binary Lifting** is a powerful technique in data structure and algorithms that is used to efficiently answer various types of queries on trees, particularly those involving finding ancestors or jumping to higher nodes in a tree.

The basic idea behind binary lifting is to precompute and store information about the ancestors of each node in the tree in a way that allows us to answer queries efficiently. This is achieved by creating an auxiliary data structure, often an array or a table, that stores information about each node's ancestor at different heights or levels in the tree.

Here's a high-level overview of how binary lifting works:

1. **Preprocessing**: In a preprocessing step, we traverse the tree and calculate and store information about each node's immediate ancestors (e.g., parent, grandparent, great-grandparent, etc.) at different heights. This information is stored in an array or a table.

2. **Query Answering**: When a query is given, we use the precomputed information to efficiently find the desired ancestor or jump to a higher node in the tree.

Binary lifting is particularly useful in solving problems that involve finding ancestors, lowest common ancestors (LCA), and jumping to higher nodes in trees. It's a powerful tool for reducing time complexity when dealing with trees.

Here are some common types of problems where binary lifting can be applied:

1. **LCA (Lowest Common Ancestor) Queries**: Given two nodes in a tree, find their lowest common ancestor. Binary lifting can be used to preprocess the tree and answer LCA queries in O(log N) time, where N is the number of nodes in the tree.

2. **Distance Queries**: Find the distance between two nodes in a tree. Binary lifting can be used to preprocess the tree and answer distance queries efficiently.

3. **Kth Ancestor Queries**: Given a node and an integer K, find the Kth ancestor of the node. Binary lifting can be applied to solve this problem efficiently.

4. **Jumping Queries**: Given a node and a number of jumps, find the node that results from jumping a certain number of levels up the tree. Binary lifting simplifies this task.

5. **Tree Traversal with Jumps**: Traverse a tree while making jumps between nodes at different heights. Binary lifting can be applied to optimize tree traversal algorithms.

6. **Dynamic Tree Problems**: Binary lifting can be used to efficiently solve dynamic tree problems where the tree structure changes over time, and you need to answer queries about the tree.

To identify if a problem can be solved using binary lifting, look for the following clues:

- The problem involves trees, particularly rooted trees or forests.
- The problem requires answering queries related to ancestors, LCA, distances between nodes, or jumping to higher nodes in the tree.
- The time complexity of solving the problem using standard tree traversal or brute force methods is not efficient enough, suggesting the need for preprocessing and optimization.

Here are a few example questions where binary lifting can be applied:

1. **LCA (Lowest Common Ancestor) Problem**: Given a tree and multiple pairs of nodes, find the lowest common ancestor of each pair.

2. **Distance Queries in Trees**: Find the distance between two nodes in a tree for multiple pairs of nodes.

3. **Kth Ancestor Queries**: Given a tree and multiple nodes, find the Kth ancestor of each node.

4. **Dynamic Tree Connectivity**: Solve dynamic tree connectivity problems where edges can be added or removed from the tree, and queries involve connectivity.

5. **Tree Hopping**: Given a rooted tree, answer queries that involve making a certain number of jumps from a given node.

Binary lifting is a versatile technique that can be applied to a wide range of tree-related problems, improving their efficiency and reducing time complexity.
 */

//^ Problem 1
/*
You are given a 0-indexed integer array receiver of length n and an integer k.

There are n players having a unique id in the range [0, n - 1] who will play a ball passing game, and receiver[i] is the id of the player who receives passes from the player with id i. Players can pass to themselves, i.e. receiver[i] may be equal to i.

You must choose one of the n players as the starting player for the game, and the ball will be passed exactly k times starting from the chosen player.

For a chosen starting player having id x, we define a function f(x) that denotes the sum of x and the ids of all players who receive the ball during the k passes, including repetitions. In other words, f(x) = x + receiver[x] + receiver[receiver[x]] + ... + receiver(k)[x].

Your task is to choose a starting player having id x that maximizes the value of f(x).

Return an integer denoting the maximum value of the function.

Note: receiver may contain duplicates.



Example 1:
Pass Number	Sender ID	Receiver ID	x + Receiver IDs
                        2
            1	2	1	3
            2	1	0	3
            3	0	2	5
            4	2	1	6

Input: receiver = [2,0,1], k = 4
Output: 6
Explanation: The table above shows a simulation of the game starting with the player having id x = 2.
From the table, f(2) is equal to 6.
It can be shown that 6 is the maximum achievable value of the function.
Hence, the output is 6.

 */


/* 

    Function solve:
        This function calculates the value of f(node) starting from a given node and parent node.
        If parent is -1, it means the end of the pass sequence, and it returns 0.
        It checks if the k-th bit of parent is not set (i.e., (k & (1LL << parent)) == 0). If true, it means that this player does not receive the ball in the pass sequence, so it recursively moves to the previous player.
        Otherwise, it adds the profit (dp[parent][node].second) of the current player to the result and continues to the previous player.
        The function essentially traverses the pass sequence to calculate the total profit starting from a given player.

    Function getMaxFunctionValue:
        It initializes variables m and n representing the maximum number of passes and the number of players, respectively.
        It creates a 2D vector dp of pairs, where dp[i][j] represents the player to whom player j passes the ball after 2^i passes and the profit earned by player j during that time.
        It initializes dp[0][j] based on the receiver array, assuming one pass.
        It then iteratively calculates dp[i][j] for each player j and for increasing numbers of passes i using the previous results.

    Finding the Maximum:
        After building the dp table, the code iterates through all players (i) and calculates the maximum value of solve(i, m - 1, k, dp) + i, which represents the total profit starting from player i plus i itself.
        It keeps track of the maximum value encountered (res) and returns it as the result.

    Time Complexity:
        Constructing the dp table takes O(n * log2(max(k))) time because it iterates through players and passes.
        Calculating the maximum value takes O(n * log2(max(k))) time as well because it iterates through players.
        Overall, the time complexity of the code is O(n * log2(max(k))).

    Space Complexity:
        The space complexity is O(n * log2(max(k))) due to the dp table, which has dimensions based on the number of players and passes.

    Hint:
        The code builds a dynamic programming table dp to efficiently compute the profit earned by each player after different numbers of passes.
        The solve function recursively traverses the passes and calculates the total profit, considering the value of k to decide whether a player should be included in the calculation.
 */
long long solve(int node, int parent, long long k, vector<vector<pair<int, long long>>> &dp)
{
    if (parent == -1)
        return 0;
    if ((k & (1LL << parent)) == 0)
    {
        return solve(node, parent - 1, k, dp);
    }
    return dp[parent][node].second + solve(dp[parent][node].first, parent - 1, k, dp);
}
long long getMaxFunctionValue(vector<int> &receiver, long long k)
{
    int m = 40, n = receiver.size(); //? m is takes as greater than log2(10^10) according to constraints
    //? dp[i][j] means from j move 2^i steps , (end point , profit)
    vector<vector<pair<int, long long>>> dp(m, vector<pair<int, long long>>(n));

    for (int j = 0; j < n; j++)
    {
        dp[0][j] = make_pair(receiver[j], receiver[j]); //? immediately pareent , score
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int x = dp[i - 1][j].first;
            dp[i][j] = make_pair(dp[i - 1][x].first, dp[i - 1][j].second + dp[i - 1][x].second);
        }
    }
    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        res = max(solve(i, m - 1, k, dp) + i, res);
    }
    return res;
}
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