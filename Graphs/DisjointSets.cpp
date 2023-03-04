#include <bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int> rank,parent,size;
    int n;
    public:
    DisjointSet(int n){
        this->n=n;
        rank.resize(n+1);
        parent.resize(n+1);
        size.resize(n+1,1);
        for(int i=0;i<n+1;i++){parent.at(i) = i;}
    }

    inline int accessParent(int i){return parent[i];}
    int findUltimateParent(int node){
        if(node == parent[node])return node;
        return parent[node] = findUltimateParent(parent[node]);
    }
   // O(4*alpha) ~= O(1)
    void unionByRank(int u, int v){
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);
        if(ulp_u == ulp_v){return;}
        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }
        else if(rank[ulp_u] > rank[ulp_v]){
            parent[ulp_v] = ulp_u;
        }
        else{
            parent[ulp_u] = ulp_v;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u,int v){
        int ulp_u = findUltimateParent(u);
        int ulp_v = findUltimateParent(v);
        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] = size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] = size[ulp_v];
        }
    }
};


//^ Kruskal's algorithm (Minimum spanning tree)

int kruskal(int V,vector<vector<int>> adj[]){
    vector<pair<int,pair<int,int>>> edges; //? weight,bidirectional edges
    for (int i = 0; i < V; i++)
    {
        for (auto &&it : adj[i])
        {
            int adjNode = it[0];
            int weight = it[1];
            int node = i;

            edges.push_back({weight, {node, adjNode}});
        }
        
    }
    sort(edges.begin(),edges.end()); //~ sort edges according to weight
    DisjointSet ds(V);
    int mstWt = 0;
    for (auto &&it : edges)
    {
        int wt = it.first;
        int u = it.second.first;
        int v = it.second.second;

        if (ds.findUltimateParent(u)!=ds.findUltimateParent(v)){
            mstWt+=wt;
            ds.unionBySize(u,v);
        }
    }
    return mstWt;
    
}


//^ Number of provinces in a undirected graph.
int numberOfProvinces(vector<vector<int>> adj , int V){
    DisjointSet ds(V);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
        if(adj[i][j] == 1) //? edge b/w i and j
        {
            ds.unionBySize(i,j);
        }
            
        }
        
    }
    int count=0;
    for (int i = 0; i < V; i++)
    {
        if (ds.accessParent(i) == i)  //? getting unique ultimate parents or if the node is parent of itself..
        {
            count++;
        }
        
    }

    return count;
}

int main(int argc, char const *argv[])
{
    // DisjointSet* ds = new DisjointSet(7);
    // DisjointSet* ds2 = new DisjointSet(7);
    // ds->unionByRank(1,2);
    // ds->unionByRank(2,3);
    // ds->unionByRank(4,5);
    // ds->unionByRank(6,7);
    // ds->unionByRank(5,6);
    // if(ds->findUltimateParent(3) == ds->findUltimateParent(7)){
    //     cout << " same \n";
    // }
    // else{
    //     cout << " not same \n";
    // }
    // ds->unionByRank(3,7);
    // if(ds->findUltimateParent(3) == ds->findUltimateParent(7)){
    //     cout << " same \n";
    // }
    // else{
    //     cout << " not same \n";
    // }
    // ds2->unionBySize(1,2);
    // ds2->unionBySize(2,3);
    // ds2->unionBySize(4,5);
    // ds2->unionBySize(6,7);
    // ds2->unionBySize(5,6);
    // if(ds2->findUltimateParent(3) == ds2->findUltimateParent(7)){
    //     cout << " same \n";
    // }
    // else{
    //     cout << " not same \n";
    // }
    // ds2->unionBySize(3,7);
    // if(ds2->findUltimateParent(3) == ds2->findUltimateParent(7)){
    //     cout << " same \n";
    // }
    // else{
    //     cout << " not same \n";
    // }
    // // delete ds,ds2;
    // return 0;
}
