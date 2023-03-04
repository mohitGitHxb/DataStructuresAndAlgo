#include <bits/stdc++.h>
using namespace std;

void printGraph(vector<int> adj[], int vertex)
{
    for (int i = 0; i < vertex; i++)
    {
        for (auto &&c : adj[i])
        {
            cout << c << " ";
        }
        cout << "\n ----------------------- \n";
    }
}

//^ Adjacency list...
void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

//^ BFS of a undirected and connected graph
void BFS(vector<int> adj[], int vertex, int src)
{
    deque<int> dq;
    vector<bool> visited(vertex + 1);
    dq.push_back(src);
    visited[src] = true;

    /* 
    ?pop out elements from the queue and print them out.
     */
    while (!dq.empty())
    {
        int u = dq.front();
        dq.pop_front();
        cout << u << " ";
        for (auto &&i : adj[u])
        {
            if (!visited[i]) //?we are checking if the element is already visited if it isn't then push the same element in the queue.
            {
                visited[i] = true;
                dq.push_back(i);
            }
        }
    }
}

//^ BFS of a disconnected graph O(V+E) time
void BFS(vector<int> adj[], int s, bool visited[])
{
    queue<int> q;

    visited[s] = true;
    q.push(s);

    while (q.empty() == false)
    {
        int u = q.front();
        q.pop();
        cout << u << " ";

        for (int v : adj[u])
        {
            if (visited[v] == false)
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void BFSDin(vector<int> adj[], int V)
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
            BFS(adj, i, visited);
    }
}

//^ NO. OF Islands in a graph
int getIslands(vector<int> adj[], int V)
{
    bool visited[V];
    fill(visited, visited + V, false);
    int count = 0;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            BFS(adj, i, visited);
            count++;
        }
    }
    return count;
}

//^ depth first search O(V+E) time
void DFSutil(vector<int> adj[], int s, bool visited[])
{
    visited[s] = true;
    cout << s << " ";
    for (auto &&i : adj[s])
    {
        if (!visited[i])
            DFSutil(adj, i, visited);
    }
}

void /* int */ DFS(vector<int> adj[], int V, int s)
{
    bool visited[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
    }
    // DFSutil(adj,s,visited);

    //^DFS of a undirected graph(disconnected)
    // int count = 0;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            DFSutil(adj, s, visited);
            // count++;
        }
    }
    // return count;
}



//^ topological sortings for graph using the BFS O(V+E) time (Kahn's algorithm)
/* 
?method:1 store the indegree of every vertex in the graph
?       create a queue q
?        add the 0 indegree vertices to the queue q
?        while the queue is not empty
?            reduce the degree of the vertices by 1
 */
void topological(vector<int> adj[], int V){
    vector<int> indegree(V);
    for (int i = 0; i < V; i++)
    {
        for (auto &x : adj[i])
        {
            indegree[x]++;  //? storing indegrees of the graph
        }
    }

    queue<int> q; //? queue to store the neighboring elements of the graph
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
        
    }
    /* 
    todo : decrease the indegree of the neighboring elements by 1
    todo : if indegree reaches 0, push into the queue
     */
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        cout << u << " ";
        for (auto &x : adj[u])
        {
            if (--indegree[x] == 0)
            {
                q.push(x);
            }   
        }   
    }
}


//^Detect cycles in an undirected graph O(V+E) time complexity
/* bool detectCyclesUtil(vector<int> adj[], int src, vector<bool> &visited, int parent)
{
    visited[src] = true;
    for (auto &i : adj[src])
    {
        if (!visited[i])
        {
            if (detectCyclesUtil(adj, i, visited, src))
            {
                return true;
            }
        }
        else if (i!=parent)return true;
    }
    return false;   // not founded cycle
}

bool detectCycles(vector<int> adj[], int V)
{
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            if(detectCyclesUtil(adj, i, visited,-1))
                return true;
    return false;
}
 */


//^ Detect Cycles in a directed graph (works for both undirected and directed graphs).

/* 
& Method:
* To detect a back edge, we can keep track of vertices currently in recursion stack of function for DFS traversal. If we reach a vertex that is already in the recursion stack, 
* then there is a cycle in the tree. The edge that connects current vertex to the vertex in the recursion stack is a back edge.
* We can use an auxiliary array say, recStack[] to keep track of vertices in the recursion stack.

* Therefore, for every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already visited and u is not a parent of v, then there is a cycle in the graph. If we don’t find such an adjacent for any vertex, we say that there is no cycle.
 */

bool detectCyclesUtil(vector<int> adj[],int s,vector<bool> &visited,vector<bool> &recursionStack){
    visited.at(s) = true;
    recursionStack.at(s) = true;
    for (auto &&i : adj[s])
    {
    if(visited[i]==false && detectCyclesUtil(adj,i,visited,recursionStack)){
        return true;
    }
    else if (recursionStack.at(i) == true)
    {
        return true;
    }
    
    }
    recursionStack.at(s) = false;
    return false;
    
}

bool detectCycles(vector<int> adj[], int V)
{   
    vector<bool> visited(V, false);
    vector<bool> recursionStack(V, false);
    for (int i = 0; i < V; i++)
        if(!visited[i])
        {
            if(detectCyclesUtil(adj, i, visited, recursionStack))
                return true;
        return false;
        }
}


//^ Shortest path in DAG
//^ url ('https://ide.geeksforgeeks.org/gzWf6QCSxm');


void topoSort(int node,vector<pair<int,int>> adj[],vector<bool> &visited,stack<int> &st){
    visited[node] = true;
        for (auto &&i : adj[node])
        {
            int v = i.first;
            if(!visited[v])
                topoSort(v,adj,visited,st);
        }
        st.push(node);
        
        
}
vector<int> shortestPath(int N,int M,vector<int> edges[]){
    vector<pair<int,int> > adj[N];
    for(int i=0;i<M;i++){
        int u = edges[i][0];
        int v = edges[i][1];
        int weight = edges[i][2];
        adj[u].push_back(make_pair(v,weight));
    }

    //& topological sort
    vector<bool> visited(N, false);
    stack<int> st;
    for(int i=0;i<N;i++){
        if(!visited[i]){
            topoSort(i,adj,visited,st);
        }
    }

    vector<int> path(N,INT_MAX);
    path[0] = 0;
    while (!st.empty())
    {
        int node = st.top();
        st.pop();
        for (auto &&i : adj[node])
        {
            int v = i.first;
            int weight = i.second;
            if(path[node] + weight < path[v]){
                path[v] = path[node] + weight;
            }
        }
        

    }
    return path;


}


//^ Prim's Algorithm for minimum spanning tree

//! O(V^2) time
int primAlgorithm(vector<int> graph[],int V){
    vector<bool> mSET(V, false);
    vector<int> key(V,INT_MAX);
    int res = 0;
    key[0]=0;
    for (int count = 0; count < V; count++)
    {
        int u = -1;
        for (int v = 0; v < V; v++)
        {
            if(!mSET[v] && (u == -1 || key[v]<key[u])){
                u = v;
            }
        }
        mSET[u] = true;
        res += key[u];

        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 && !mSET[u])
            {
                key[u]=min(key[u],graph[u][v]);
            }
            
        }
        
    }
    return res;
    
}
//* O(VlogV) time
int spanningTree(int V, vector<vector<int>> adj[]){
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
       pq.push({0,0}); //?{weight,node}
       vector<bool>visited(V,false);
       int ans=0;
       while(!pq.empty()){
           auto p=pq.top();
           pq.pop();
           int x=p.second;
           int w=p.first;
           if(visited[x])continue;
           visited[x]=true;
           ans+=w;
           for(auto y:adj[x]){
               if(!visited[y[0]]){
                   pq.push({y[1],y[0]});
               }
           }
       }
       return ans;
   }
 


//^ Dijkstra algorithm

//! O(V^2) time (adjacency matrix)
vector<int> dijkstra(vector<int> graph[],int V,int src){
    vector<int> distance(V,INT_MAX);
    distance[src] = 0;
    vector<bool> finalized(V,false);

    for (int count = 0; count < V-1; count++)
    {
        int u = -1;
        for (int i = 0; i < V; i++)
        {
            if (!finalized[u] && (u == -1 || distance[i] < distance[u]))
            {
                u = i;
            }
        }

        finalized[u] = true;
        for (int v = 0; v < V; v++)
        {
            if (graph[u][v] != 0 && finalized[v]==false)
            {
                distance[v] = min(distance[v],distance[u]+graph[u][v]);
            }
            
        }
        
    }
    return distance;
    
}

//*O(VlogV)

vector<int> dijkstra_2(int V,vector<vector<int>> adj[],int S){
 /*    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<int> distance(V);
    fill(distance.begin(),distance.end(),INT_MAX); //@ set all distances to infinity
    distance[S] = 0;
    pq.push({0,S});
    while(!pq.empty()){
        auto p=pq.top();
        pq.pop();
        int dis = p.first;
        int node=p.second;


        for (auto &it : adj[node]) //? update the distance of each node 
        {
           int edgeWt = it[1];
           int adjNodes = it[0];

           if (dis + edgeWt < distance[adjNodes]) //* relaxation operation
           {
                distance[adjNodes] = dis + edgeWt;
                // pq.push({distance[adjNodes],adjNodes});
                pq.emplace(distance[adjNodes],adjNodes);
           }  
        }
        }
    return distance; */


    //* SET method
    set<pair<int,int>> st;
    vector<int> dist(V,INT_MAX);
    st.insert({0,S});
    dist[S]=0;
    while(!st.empty()){
        auto it=*(st.begin());
        int node = it.second;
        int dis=it.first;
        st.erase(it);
        for (auto &&i : adj[node])
        {
            int adjNode = i[0];
            int edgeWt = i[1];

            if(dis+edgeWt < dist[adjNode]){
                if (dist[adjNode]!=INT_MAX)
                {
                    st.erase({dist[adjNode],adjNode});
                }
                dist[adjNode] = dis + edgeWt;
                st.insert({dist[adjNode],adjNode});
                
            }
        }
    }
    return dist;
}

//^ floodfill problem
void floodFillUtil(int row,int col,vector<vector<int>> &ans,vector<vector<int>> &images,int newColor,int delRow[],int delCol[],int iniColor){
    ans[row][col] = newColor;
    int n = images.size();
    int m = images[0].size();
    for (int i = 0; i < 4; i++)
    {
        int nrow = row + delRow[i];
        int ncol = col + delCol[i];
    if(nrow>=0 && ncol>=0 && nrow<n && ncol<m && images[nrow][ncol]== iniColor && ans[nrow][ncol]!=newColor){
        floodFillUtil(nrow,ncol,ans,images,newColor,delRow,delCol,iniColor);
    }
    }
    
}

vector<vector<int>> floodFill(vector<vector<int>> &image,int sr,int sc,int newColor){
    int iniColor=image[sr][sc];
    vector<vector<int> > ans = image;
    int delRow[] = {-1,0,1,0};
    int delCol[] = {0,1,0,-1};
    floodFillUtil(sr,sc,ans,image,newColor,delRow,delCol,iniColor);
}



//^ Kruskal's algorithm O(ElogV) time 
// a structure to represent a weighted edge in graph 
class Edge 
{ 
	public: 
	int src, dest, weight; 
}; 

// a structure to represent a connected, undirected 
// and weighted graph 
class Graph 
{ 
	public: 
	// V-> Number of vertices, E-> Number of edges 
	int V, E; 

	// graph is represented as an array of edges. 
	// Since the graph is undirected, the edge 
	// from src to dest is also edge from dest 
	// to src. Both are counted as 1 edge here. 
	Edge* edge; 
}; 

// Creates a graph with V vertices and E edges 
Graph* createGraph(int V, int E) 
{ 
	Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 

	graph->edge = new Edge[E]; 

	return graph; 
} 

// A structure to represent a subset for union-find 
class subset 
{ 
	public: 
	int parent; 
	int rank; 
}; 

// A utility function to find set of an element i 
// (uses path compression technique) 
int find(subset subsets[], int i) 
{ 
	// find root and make root as parent of i 
	// (path compression) 
	if (subsets[i].parent != i) 
		subsets[i].parent = find(subsets, subsets[i].parent); 

	return subsets[i].parent; 
} 

// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(subset subsets[], int x, int y) 
{ 
	int xroot = find(subsets, x); 
	int yroot = find(subsets, y); 

	// Attach smaller rank tree under root of high 
	// rank tree (Union by Rank) 
	if (subsets[xroot].rank < subsets[yroot].rank) 
		subsets[xroot].parent = yroot; 
	else if (subsets[xroot].rank > subsets[yroot].rank) 
		subsets[yroot].parent = xroot; 

	// If ranks are same, then make one as root and 
	// increment its rank by one 
	else
	{ 
		subsets[yroot].parent = xroot; 
		subsets[xroot].rank++; 
	} 
} 

// Compare two edges according to their weights. 
// Used in qsort() for sorting an array of edges 
int myComp(const void* a, const void* b) 
{ 
	Edge* a1 = (Edge*)a; 
	Edge* b1 = (Edge*)b; 
	return a1->weight > b1->weight; 
} 

// The main function to construct MST using Kruskal's algorithm 
void KruskalMST(Graph* graph) 
{ 
	int V = graph->V; 
	Edge result[V]; // Tnis will store the resultant MST 
	int e = 0; // An index variable, used for result[] 
	int i = 0; // An index variable, used for sorted edges 

	// Step 1: Sort all the edges in non-decreasing 
	// order of their weight. If we are not allowed to 
	// change the given graph, we can create a copy of 
	// array of edges 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp); 

	// Allocate memory for creating V ssubsets 
	subset *subsets = new subset[( V * sizeof(subset) )]; 

	// Create V subsets with single elements 
	for (int v = 0; v < V; ++v) 
	{ 
		subsets[v].parent = v; 
		subsets[v].rank = 0; 
	} 
    
    int res =0;
	// Number of edges to be taken is equal to V-1 
	while (e < V - 1 && i < graph->E) 
	{ 
		// Step 2: Pick the smallest edge. And increment 
		// the index for next iteration 
		Edge next_edge = graph->edge[i++]; 

		int x = find(subsets, next_edge.src); 
		int y = find(subsets, next_edge.dest); 

		// If including this edge does't cause cycle, 
		// include it in result and increment the index 
		// of result for next edge 
		if (x != y) 
		{ 
			result[e++] = next_edge; 
			Union(subsets, x, y); 
			res+=next_edge.weight;
		} 
		// Else discard the next_edge 
	} 

	// print the contents of result[] to display the 
	// built MST 
	
	cout<<"Weight of MST is: "<<res<<endl;
	return; 
} 

//^ Kosharaju algorithm O(V+E) and O(V+E) space,

void DFSKosharaju(int node,vector<bool > &visited,vector<int> adj[],stack<int> &s){
    visited[node] = true;
    for (auto &&it : adj[node])
    {
        if(!visited[it]){
            DFSKosharaju(it,visited,adj,s);
        }
    }
    s.push(node);
    
    
}
int Kosharaju(int V, vector<int> adj[]){
    //~ Create a hash table for storing graph
    vector<int> edges[V];
    for(int i = 0; i < V; i++){
        int u = adj[i][0];
        int v = adj[i][1];
        edges[u].push_back(v);
    }

    //? topo Sort
    stack<int> st;
    vector<bool> visited;
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            DFSKosharaju(i,visited,edges,st);
        }   
    }

    //~ transpose graph ------------------------
    vector<int> transpose[V];
    for(int i = 0; i < V; i++){
        visited[i] = false;
        for(auto &it : adj[i]){
            transpose[it].push_back(i);
        }
    }

    //? dfs call 
    int count = 0;
    while (!st.empty())
    {
        int top = st.top();
        st.pop();
        if(!visited[top]){
            count++;
            DFS(edges,V,top);
        }
    }
    return count;
    
}

//^Bellman Ford Shortest Path Algorithm O(VE)
vector<int> bellman_shortest_path_algorithm(int V, vector<vector<int>> &edges,int src){
    vector<int> distances(V,1e8);
    for (int i = 0; i < V-1; i++)
    {
        for (auto &&it : edges) {
            int u = it[0];
            int v=  it[1];
            int weight = it[2];
            if (distances[u] + weight < distances[v] && distances[u] != 1e8){
                distances[v] = distances[u] + weight;
            }
        }
    }

    //? Nth relaxation to check negative cycle
    for (auto &&it : edges) 
    {
        int u = it[0];
            int v=it[1];
            int weight = it[2];
            if (distances[u] + weight < distances[v] && distances[u] != 1e8){
                distances[v] = distances[u] + weight;
            }
    }
    
    
}



//^ Articulation point 
/* 
? if root of dfs tree has two children then it is a articulation point.
? u is not the root of DFS tree and it has a child v such that no vertex in the subtree rooted with v has a back edge to one of the ancestors (in DFS tree) of u.
 */

void APutil(int u,vector<bool> &visited,vector<int> &discoveryTime,vector<int> &low,vector<int> &parent,vector<bool> &ap,vector<int> adj[]){
    static int time = 0;
    int children = 0;
    visited[u] = true;



    discoveryTime[u] = low[u] = ++time;

    for (auto &&i : adj[u])
    {
        int v = i;


        //? If v is not visited yet, then make it a child of u
        //? in DFS tree and recur for it

        if (!visited[i])
        {
            children++;
            parent[v] = u;
            APutil(v,visited,discoveryTime,low,parent,ap,adj);
            // ~Check if the subtree rooted with v has a connection to
            //~ one of the ancestors of u
            low[u] = min(low[u],low[v]);

            //? u is an articulation point in following cases

            //? (1) u is root of DFS tree and has two or more children.
            if(parent[u] == -1 && children > 1)
                ap[u] = true;
            
            //? (2) If u is not root and low value of one of its child is more
            //? than discovery value of u.
            if (parent[u] != -1 && low[v]>= discoveryTime[u])   
            {
                ap[u] = true;
            }
            //~ update low value of u for parent function call
            else if (v!=parent[u])
            {
                low[u] = min(low[u],discoveryTime[v]);
            }
            
        }
        
    }
    
}



vector<int> AP(int V, vector<int> adj[]){
    vector<bool> visited(V);
    vector<int> discoveryTime(V);
    vector<int> low(V);
    vector<bool> ap(V);
    vector<int> parent(V,-1);

    vector<int> res;
    //? Call the recursive helper function to find articulation points
    //? in DFS tree rooted with vertex 'i

    for (int i = 0; i < V; i++)
    {
        if(!visited[i])
            APutil(i,visited,discoveryTime,low,parent,ap,adj);
    }
    // return ap; //~ returns articulation points
    for (int i = 0; i < V; i++)
    {
        if (ap[i] == true)
        {
            res.push_back(i);
        }
        
    }
    return res;
    
    
}

/* 
~An edge in an undirected connected graph is a bridge if and only if removing it disconnects the graph. For a disconnected undirected graph, the definition is similar, a bridge is an edge removing which increases the number of disconnected components.
^bridges in a graph 
 */

void bridgeUtil(int u,vector<bool> &visited,vector<int> &discoveryTime,vector<int> &low,vector<int> &parent,vector<pair<int,int>> &edges,vector<int> adj[])
{
    static int time =0;
    visited[u] = true;

    for (auto &&i : adj[u])
    {
        int v = i;
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v,visited,discoveryTime,low,parent,edges,adj);

             //~ Check if the subtree rooted with v has a 
            //~ connection to one of the ancestors of u

            low[u] = min(low[u],low[v]);
            //? If the lowest vertex reachable from subtree 
            //? under v is  below u in DFS tree, then u-v 
            //? is a bridge

            if (low[v] > discoveryTime[u])
            {
                edges.push_back(make_pair(u,v));

            }
            
            else if (v!=parent[u])
            {
                low[v] = min(low[u],discoveryTime[v]);
            }
        }
        
    }
    
}

vector<pair<int,int>> bridge(int V,vector<int> adj[]){
    vector<int> discoveryTime(V);
    vector<bool> visited(V);
    vector<int> parent(V,-1);
    vector<int> low(V);
    vector<pair<int,int>> edges;

    //? Call the recursive helper function to find Bridges
    //? in DFS tree rooted with vertex 'i'

    for(int i = 0; i < V; i++){
        if (!visited[i])
        {
            bridgeUtil(i,visited,discoveryTime,low,parent,edges,adj);
        }
        
    }
    return edges;
}


/* 

^Tarjan Algorithm is based on the following facts: 


?    DFS search produces a DFS tree/forest 
?    Strongly Connected Components form subtrees of the DFS tree. 
?    If we can find the head of such subtrees, we can print/store all the nodes in that subtree (including the head) and that will be one SCC. 
?    There is no back edge from one SCC to another (There can be cross edges, but cross edges will not be used while processing the graph).



?       To find the head of an SCC, we calculate disc and low array (as done for articulation point, bridge, and biconnected component). As discussed in the previous posts, low[u] indicates the earliest visited vertex (the vertex with minimum discovery time) that can be reached from a subtree rooted with u. A node u is head if disc[u] = low[u].
 */

void SCCUtil(int u,vector<int> &disc,vector<int> &low,stack<int> &s,vector<bool>    &stackMember,vector<int> adj[]){
    static int time = 0;
    disc[u] = low[u] = ++time;
    s.push(u);
    stackMember[u] = true;
    for (auto &&i : adj[u])
    {
        int v = i;
               //~ If v is not visited yet, then recur for it 
        if (disc[v] == -1)
        {
            SCCUtil(v,disc,low,s,stackMember,adj);

            //? Check if the subtree rooted with 'v' has a 
            //? connection to one of the ancestors of 'u' 
            low[u] = min(low[u],low[v]);
        }
         //? Update low value of 'u' only of 'v' is still in stack 
        // ?(i.e. it's a back edge, not cross edge). 
        else if (stackMember[v])
        {
            low[u] = min(low[u],disc[v]);
        }

        //? head node found, pop the stack and print an SCC 
        int w = 0;
        if (low[u] == disc[u]) 
        {
            while (!s.empty() && s.top() != u)
            {
                w = s.top();
                cout << w << " ";
                stackMember[w] = false;
                s.pop();
            }

            w = s.top();
            cout << w << " ";
            stackMember[w] = false;
            s.pop();
            
        }
    }
}

void SCC(vector<int> adj[], int V){
    vector<int> disc(V);
    vector<int> low(V);
    vector<bool> stackMember(V);
    stack<int> s;
    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    for (int i = 0; i < V; i++)
    {
        if(disc[i] == -1)
            SCCUtil(i,disc,low,s,stackMember,adj);
    }
    
}


/* 
^ Floyd warshall Algorithm
~ The Floyd Warshall Algorithm is for solving all pairs shortest path problems. 
~ The problem is to find the shortest distances between every pair of vertices in a given edge-weighted directed Graph. 
 */

void shortest_distance(vector<vector<int>> &matrix){
    int n = matrix.size();

    /* 
    ? 1st two loops to adjust the given matrix to apply the algorithm
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == -1)
            {
                matrix[i][j] = 1e9;
            }
            if (i==j) //?diagonal elements are always zero
            {
                matrix[i][j] = 0;
            }
            
        }
    }

    //!main algorithm O(N^3)
    //& the resultant matrix will have shortest distance from every point to other point
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++) 
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j]);
            }
            
        }
        
    }
    
    //& Loop to check negative cycles (optional)
/*     for (int i = 0; i < n; i++)
    {
        if(matrix[i][i]<0){
            //* do something
        }
    } */
    

    /* 
    ?3rd two loops for adjusting the matrix according to the question(output answer)
     */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1e9)
            {
                matrix[i][j] = -1;
            }
        }
    }
    
}



//^ Bipartite graph.. O(V+E)

//! Not working for all testcases
/* bool BipartiteUtil(vector<int> adj[],vector<pair<bool,int>> &visited,int src){
        queue<pair<int,int>> q;

    visited[src].first = true;
    visited[src].second = 1;
    q.push({src,1});

    while (q.empty() == false)
    {
        auto u = q.front();
        q.pop();
        // cout << u << " ";
        int prevColor = u.second;
        for (int v : adj[u.first])
        {
            if (visited[v].first == false)
            {
                visited[v].first = true;
                visited[v].second = (prevColor == 1)?2:1;
                
                q.push({v,visited[v].second});
                prevColor = visited[v].second;
            }
            else if(visited[v].first && prevColor == visited[v].second){
                return false;
            }
        }
    }
    return true;
}
bool isBipartite(vector<int> adj[],int V){
    vector<pair<bool,int>> visited(V+1);
    return BipartiteUtil(adj,visited,1);
    
} */


//* BFS approach

bool BipartiteUtil(int start , int V, vector<int> adj[],vector<int> &color){
    queue<int> q;
    q.push(start);
    vector<int> color(V,-1);
    while (!q.empty()){
        int node = q.front();
        q.pop();
        for (auto &&it : adj[node]){
        {
            if(color[it] == -1){
                color[it] = !color[node];
            }
            else if(color[it] == color[node]){
                return false;
                }
        }
        

    }
    }
    return true; 
}

bool isBipartite(vector<int> adj[], int V){
/*     //^ single component
    queue<int> q;
    q.push(0);
    vector<int> color(V,-1);
    while (!q.empty()){
        int node = q.front();
        q.pop();
        for (auto &&it : adj[node]){
        {
            if(color[it] == -1){
                color[it] = !color[node];
            }
            else if(color[it] == color[node]){
                return false;
                }
        }
        

    }
    }
    return true; */

    //! Handling multiple components
    vector<int> color(V,-1);
    for (int i = 0; i < V; i++)
    {
        if(color[i] == -1){
            if(BipartiteUtil(i,V,adj,color) == false)
                return false;
        }
    }
    return true;

}


//* DFS Approach

bool Bipartite_DFS(int start ,int col,vector<int> adj[],vector<int> &color){
    color[start] = col;
    for (auto &it : adj[start])
    {
        if(color[it] == -1){
            // return false;
            if(Bipartite_DFS(it,!col,adj,color))return false;
        }
        else if (color[it] == col)
        {
            return false;
        }
        
    }
    return true;
}
bool isBipartite_DFS(int V , vector<int> adj[]){
    vector<int> color(V,-1);
    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            return Bipartite_DFS(i,0,adj,color);
        }
        
    }
    return true;
    
}



int main(int argc, char const *argv[])
{
    int v = 9;
    vector<int> adj[v] = {{0},{2},{1,3,6},{2,4},{3,5,7},{4,6},{2,5},{4,8},{7}};
    // printGraph(adj, v);


    return 0;
}
