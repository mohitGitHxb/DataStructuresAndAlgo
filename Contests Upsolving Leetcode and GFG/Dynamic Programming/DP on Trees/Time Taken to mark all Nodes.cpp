#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target(                                                            \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define bigInt __int128_t
#define deb(x) cout << #x << "=" << x << endl
static void fast_read() {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

class Solution {
private:
    /*
There exists an undirected tree with n nodes numbered 0 to n - 1. You are given
a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates
that there is an edge between nodes ui and vi in the tree.

Initially, all nodes are unmarked. For each node i:

    If i is odd, the node will get marked at time x if there is at least one
node adjacent to it which was marked at time x - 1. If i is even, the node will
get marked at time x if there is at least one node adjacent to it which was
marked at time x - 2.

Return an array times where times[i] is the time when all nodes get marked in
the tree, if you mark node i at time t = 0.

Note that the answer for each times[i] is independent, i.e. when you mark node i
all other nodes are unmarked.



Example 1:

Input: edges = [[0,1],[0,2]]

Output: [2,4,3]

Explanation:

    For i = 0:
        Node 1 is marked at t = 1, and Node 2 at t = 2.
    For i = 1:
        Node 0 is marked at t = 2, and Node 2 at t = 4.
    For i = 2:
        Node 0 is marked at t = 2, and Node 1 at t = 3.

Example 2:

Input: edges = [[0,1]]

Output: [1,2]

Explanation:

    For i = 0:
        Node 1 is marked at t = 1.
    For i = 1:
        Node 0 is marked at t = 2.

Example 3:

Input: edges = [[2,4],[0,1],[2,3],[0,2]]

Output: [4,6,3,5,5]

Intuition

Honestly unless you know about Tree rerooting its not natural to be able to come
up with the solution. Approach

Now whats been missing in other explanations?

Why do we need to store the farthest and the second farthest distance?

Because when you move from parent to child there are only three possible paths
that can give you the maximum value for each node:

    the one coming from parent
    the path on which the child lies if it is the longest path
    the second longest path in which the child does not belong

None of the other paths will give you the maximum value for the child and only
these three need to be compared. Think about this: You have a node, it can have
one parent and multiple children. When you move from the node to the child you
will have 2 cases:

    child lies on the path of farthest distance of the parent
    child does not lie on the path of farthest distance of the parent

Take case 1:

Child will either have max distance starting from itself to the leaf or through
the parent. Now since we are already on the maximum path of the parent, the max
distance through the parent will be either through the second largest path of
the parent or from parent of the parent. How do we take care of this in code? We
pass the maximum of the path through the parent as parentDist into the function.
We compare this with the maximum value through the child in the line
ans[node]=max(cost[node][0],parentDist);

Take case 2:
Child will either have max distance starting from itself to the leaf or through
the parent. Now since we are already on the maximum path of the parent, the max
distance through the parent will be either through the largest path of the
parent or from parent of the parent. How do we take care of this in code? Again
we do this like in case 1: We pass the maximum of the path through the parent as
parentDist into the function. We compare this with the maximum value through the
child in the line ans[node]=max(cost[node][0],parentDist);

All of these are being done in dfs2 in the below code. The farthest distance has
been stored in cost[node][0] and the second farthest distance has been stored in
cost[node][1].

Thus we only need the farthest and the second farthest distance.


     */
public:
    const int MOD = 1e9 + 7;
    Solution() { fast_read(); }
    vector<vector<int>> adj;
    vector<vector<int>> cost;
    vector<int> ans;
    void dfs1(int node, int parent) {
        for (auto& child : adj.at(node)) {
            if(child == parent) continue;
            dfs1(child,node);
            int parentChildDistance = child % 2 ? 1 : 2;
            if(parentChildDistance + cost.at(child).front() >= cost.at(node).front()){
                cost.at(node).back() = cost.at(node).front();
                cost.at(node).front() = parentChildDistance + cost.at(child).front();
            }
            else if(parentChildDistance + cost.at(child).front() > cost.at(node).back()){
                cost.at(node).back() = parentChildDistance + cost.at(child).front();
            }
        }
    }

    void dfs2(int node,int parentDist,int parent){
        ans.at(node) = max(cost.at(node).front(),parentDist);
        for(int child : adj.at(node)){
            if(child == parent) continue;
            int childNodeDistance = node % 2 ? 1 : 2;
            int nodeChildDistance = child % 2 ? 1 : 2;
            if(cost.at(child).front() + nodeChildDistance == cost.at(node).front()){
                dfs2(child,childNodeDistance + max(parentDist,cost.at(node).back()),node);
            }
            else{
                dfs2(child,childNodeDistance + max(parentDist,cost.at(node).front()),node);
            }
        }
    }

    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        adj.resize(n);
        cost.resize(n,vector<int>(2));
        ans.resize(n);
        for(auto &edge : edges){
            int u = edge.front();
            int v = edge.back();
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs1(0,-1);
        dfs2(0,0,-1);
        return ans;
    }
};
