#include <bits/stdc++.h>
using namespace std;

//^ detect cycle in a directed graph using topological sort
bool isCyclic(int V, vector<int> adj[]) {
        int inDegree[V]={0};
        
        for(int i=0; i<V; i++){
            for(int it: adj[i]){
                inDegree[it]++;
            }
        }
        
        queue<int> q;
        for(int i=0; i<V; i++){
            if(inDegree[i]==0) q.push(i);
        }
        
        int cnt=0;
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            cnt++;
            for(int it: adj[v]){
                if(--inDegree[it]==0)
                    q.push(it);
            }
        }
        
        if(cnt==V)
            return 0;
        else
            return 1;
    }
int main(int argc, char const *argv[])
{
    
    return 0;
}
