#include <bits/stdc++.h>
using namespace std;
#define ll long long 
/* 
You are given a connected tree of N nodes numbered from 0 to N-1 rooted at the 0th node, where p[i] is the parent of the ith node and p[0] = -1 as the 0th node is the root.

Calculate the numbers of pairs of nodes (a,b) 0 < a < N, a < b < N such that LCA(a,b) = x , for each x where 0 < x < N.

The LCA or lowest common ancestor between two nodes a and b is defined as the lowest node in tree that has both a and b as descendants (where we allow a node to be a descendant of itself).

Example 1:

Input: 
N = 3 
p[] = [-1, 0, 0]    
Output: [4, 1 , 1]
Explanation: The structure of tree is :
   0
  / \
 1   2
For LCA = 0, we have 4 pairs (0,0), (0,1),
(0,2), (1,2)
For LCA = 1, we have only 1 pair (1,1)
For LCA = 2, we have only 1 pair (2,2)

Example 2:

Input:
N = 5
p[] = [-1, 0, 0, 1, 1]
Output: [8, 4, 1, 1, 1]
Explanation: The structure of tree is :
      0 
     / \
    1   2
   / \
  3   4
For LCA = 0, we have 8 pairs (0,0), (0,1),
(0,2),(0,3),(0,4),(1,2),(2,3),(2,4)
For LCA = 1 , we have 4 pairs (1,1), (1,3),
(1,4),(3,4)
FOR LCA = 2, we have only 1 pair (2,2),
FOR LCA = 3, we have only 1 pair (3,3)
For LCA = 4, we have only 1 pair (4,4)
 */

/* 

1. **Intuition**:
   - This code aims to calculate the number of pairs of nodes `(a, b)` such that `0 < a < N`, `a < b < N`, and their lowest common ancestor (LCA) is equal to `x` for each `x` where `0 < x < N`.
   - It employs Depth-First Search (DFS) to traverse the tree and calculate the required counts.

2. **Code Explanation**:
   - The `dfs` function takes the source node, the adjacency list, and two vectors `ans` and `subTreeSize`.
   - It calculates the subtree size rooted at the current node (`subtree`) by traversing through its children using recursion.
   - For each child node `it`, it recursively calls the `dfs` function and updates `ans[src]` using the formula: `ans[src] += subtree * subTreeSize[it]`.
   - Finally, it updates `subTreeSize[src]` with the calculated `subtree` size.
   - In the `calcPairs` function:
     - It initializes vectors `ans` and `subTreeSize` with size `N` and initializes each element of `ans` to 1, since LCA of the same node is always present.
     - It constructs the adjacency list using the given parent array `p`.
     - Calls the `dfs` function starting from the root node (0), which updates the `ans` and `subTreeSize` vectors.
     - Returns the `ans` vector containing the counts of pairs of nodes with specific LCAs.

3. **Time Complexity**:
   - The code involves a DFS traversal of the tree.
   - Each node is visited once, and each edge is explored once.
   - The time complexity is O(N), where N is the number of nodes in the tree.

4. **Space Complexity**:
   - The code uses additional memory for the `ans` and `subTreeSize` vectors, each of size N.
   - The space complexity is O(N).

5. **Hints**:
   - Construct the adjacency list representation of the tree using the given parent array.
   - Initialize the `ans` vector with 1s (LCA of the same node is always present).
   - Use DFS to traverse the tree and calculate the subtree sizes rooted at each node.
   - Update the `ans` vector according to the formula: `ans[src] += subtree * subTreeSize[it]` for each child node `it`.
   - The resulting `ans` vector will contain the counts of pairs of nodes with specific LCAs.

This code effectively calculates the desired counts of pairs of nodes with specific LCAs in a given tree by using a DFS approach to traverse the tree and update the necessary data structures.
 */
    void dfs(int src,vector<int> adj[],vector<ll> &ans,vector<ll> &subTreeSize){
        ll subtree = 1;
        for(auto it : adj[src]){
            dfs(it,adj,ans,subTreeSize);
            ans[src] += subtree * subTreeSize.at(it);
            subtree += subTreeSize.at(it);
        }
        subTreeSize.at(src) = subtree;
    }
	vector<long long>calcPairs(int N, vector<int> p)
	{
	    //? convert into graph
        vector<int> adj[N];
        for(int i = 1; i < N; i++){
            adj[p[i]].push_back(i);
        }
        
        vector<ll> ans(N,1); //? LCA of same number is always there so starting with one
        vector<ll> subTreeSize(N);
        dfs(0,adj,ans,subTreeSize);
        return ans;
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
        //write code here
    }
    return 0;
}