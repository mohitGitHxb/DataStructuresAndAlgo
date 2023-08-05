#include <bits/stdc++.h>
using namespace std;
/*
% Some basic theory about graphs
~ total degree of a graph = 2 x Edges (undirected graph)
~ Given N nodes and M edges
    ! M lines (represents edges)
 */
class GraphTraversals
{
public:
    //* O(V+E) T.C | O(V) space directed graph
    vector<int> BFS(int node, vector<vector<int>> adj, int vertices)
    {
        vector<bool> visited(vertices + 1);
        visited[node] = true;
        queue<int> q;
        vector<int> bfs;
        q.emplace(node);
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            bfs.emplace_back(x);
            for (auto &it : adj.at(x))
            {
                if (!visited[it])
                {
                    visited[it] = true;
                    q.emplace(it);
                }
            }
        }
        return bfs;
    }

    //* O(N) S.C | O(2E) T.C for undirected graph
    void DFS(vector<vector<int>> &adj, vector<bool> &visited, int node)
    {
        visited.at(node) = true;
        cout << node << "\n";
        for (auto &it : adj.at(node))
        {
            if (!visited[it])
            {
                DFS(adj, visited, it);
            }
        }
    }
};

//^ 2 Number of provinces
class NumberOfProvinces
{
private:
    /*
        The function dfs is a depth-first search (DFS) implementation to traverse the connected nodes in the graph. It takes a node as the starting point, the adjacency matrix adj, and a vis array to keep track of visited nodes.
&-    The dfs function marks the current node as visited and then explores its adjacent nodes by recursively calling dfs on unvisited and connected nodes.
&-    The findCircleNum function uses the dfs function to find the number of provinces in the given graph (which represents a collection of cities connected by direct roads).
&-    It initializes the provinces count to zero, as initially, no province is discovered. It also initializes a vis array to keep track of visited nodes.
&-    The function then iterates through each node in the graph and checks if it is not visited. If a node is not visited, it means it belongs to a new province. So, it increments the provinces count and calls the dfs function to mark all nodes connected to this node as visited and belonging to the same province.
&-    The final provinces count gives the total number of provinces in the graph, where each province represents a group of cities connected by roads.

Intuition:
~ The given problem is about finding the number of connected components in an undirected graph represented by the adjacency matrix. The idea is to perform a DFS traversal on the graph starting from each unvisited node and mark all connected nodes as visited. Each DFS traversal corresponds to discovering one province. The final count of DFS traversals (provinces) gives the answer to the problem.

Time Complexity:

*    The time complexity of the dfs function is O(n), where n is the number of nodes, as in the worst case, it can visit all the nodes.
 *   The dfs function is called once for each node in the graph in the findCircleNum function, resulting in a total time complexity of O(n^2) for the findCircleNum function due to the nested loop.

Space Complexity:

*    The space complexity of the dfs function is O(n) due to the recursion stack, as in the worst case, it can go up to depth n.
 *   The vis array of size n is used to keep track of visited nodes, contributing to the space complexity of O(n).
    Overall, the space complexity of the findCircleNum function is also O(n).
     */
public:
    void dfs(unsigned node, vector<vector<int>> &adj, vector<bool> &vis)
    {
        vis.at(node) = true;
        for (unsigned i = 0; i < adj.at(node).size(); i++)
        {
            if (!vis.at(i) && adj.at(node).at(i) == 1)
            {
                dfs(i, adj, vis);
            }
        }
    }
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        const unsigned n = isConnected.size();
        unsigned provinces = 0;
        vector<bool> vis(n);
        for (unsigned i = 0; i < n; i++)
        {
            if (!vis.at(i))
            {
                provinces++;
                dfs(i, isConnected, vis);
            }
        }
        return provinces;
    }
};

//^ 3 Number of islands
class NumberOfIslands
{
public:
    /*
    @ DFS approach
        &- The given code solves the problem of counting the number of islands in a 2D binary grid using the Depth-First Search (DFS) algorithm.
        &- The grid represents a map where '1's represent land (islands) and '0's represent water.
        &- The dfs function performs a depth-first search starting from a given cell and marks all connected lands of the island as visited.
        &- The inBound function checks if a given row and column are within the valid bounds of the grid.
        &- The numIslands function iterates through each cell of the grid. If the cell contains a '1' and has not been visited yet, it increments the count of islands and calls the dfs function to mark all connected lands of the island as visited.
        &- The function then returns the total count of islands.
        *- The time complexity of the code is O(m * n), where m is the number of rows and n is the number of columns in the grid.
        *- The space complexity of the code is O(m * n) due to the use of the vis array to keep track of visited cells and the recursion stack during the DFS traversal.

    Hints:

        *- The problem can be efficiently solved using a depth-first search (DFS) or breadth-first search (BFS) approach.
        *- Remember to mark visited cells to avoid revisiting the same cell multiple times during the DFS traversal.
        *- Pay attention to the grid's boundaries while traversing the adjacent cells. The 'inBound' function helps check if a cell is within the valid grid range.
     */
    //? vector<pair<int,int>> dirs{{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};  use if allowed all 8 directions
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
    void dfs(int row, int col, unsigned m, unsigned n, vector<vector<char>> &grid, vector<vector<bool>> &vis)
    {
        vis.at(row).at(col) = true;
        for (auto &it : dirs)
        {
            int x = row + it.first;
            int y = col + it.second;
            if (inBound(x, y, m, n) && !vis[x][y] && grid[x][y] == '1')
            {
                dfs(x, y, m, n, grid, vis);
            }
        }
    }
    int numIslands(vector<vector<char>> &grid)
    {
        const unsigned m = grid.size();
        const unsigned n = grid.front().size();
        vector<vector<bool>> vis(m, vector<bool>(n));
        int islands = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!vis[i][j] && grid.at(i).at(j) == '1')
                {
                    islands++;
                    dfs(i, j, m, n, grid, vis);
                }
            }
        }
        return islands;
    }
    /*
    @ BFS approach
        &- The given code also solves the problem of counting the number of islands in a 2D binary grid using the Breadth-First Search (BFS) algorithm.
    &- The bfs function performs a breadth-first search starting from a given cell and marks all connected lands of the island as visited.
    &- The numIslands function iterates through each cell of the grid. If the cell contains a '1' and has not been visited yet, it increments the count of islands and calls the bfs function to mark all connected lands of the island as visited.
    &- The visited vector is used to keep track of visited cells, and it ensures that each cell is processed only once during the BFS traversal.
    &- The queue data structure is used to perform the BFS traversal efficiently by exploring all the adjacent cells in a level-wise manner.
    &- The delta_row and delta_col arrays represent the changes in row and column values for exploring the adjacent cells (up, right, down, left).
    &- For each cell, the bfs function explores all its adjacent cells and marks them as visited if they are valid cells containing '1' and have not been visited before.
    &- The numIslands function returns the total count of islands after visiting all cells of the grid.
    &- The time complexity of the code is O(n * m), where n is the number of rows and m is the number of columns in the grid.
    &- The space complexity of the code is O(n * m) due to the use of the visited vector and the queue to keep track of visited cells and store cells to be visited during BFS.

Hints:

    &- The BFS algorithm can be effectively used to traverse and explore adjacent cells in the grid while marking them as visited.
    &- The queue data structure is a key component of BFS that helps process cells in a level-wise manner.
    &- Be careful with boundary checks while exploring adjacent cells to avoid index out of bounds errors. The inBound function in the previous code helps with this check.
     */
    void bfs(int row, int col, vector<vector<int>> &visited, vector<vector<char>> &grid, int delta_row[], int delta_col[])
    {
        int n = grid.size();
        int m = grid[0].size();

        visited[row][col] = 1;
        queue<pair<int, int>> q;
        q.push({row, col});

        while (!q.empty())
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++)
            {
                int neighbour_row = r + delta_row[i];
                int neighbour_col = c + delta_col[i];

                // for each neighbour check boundary
                if (neighbour_row >= 0 && neighbour_row < n && neighbour_col >= 0 && neighbour_col < m)
                {
                    // check for land and prev visited
                    if (grid[neighbour_row][neighbour_col] == '1' && !visited[neighbour_row][neighbour_col])
                    {
                        visited[neighbour_row][neighbour_col] = 1;
                        q.push({neighbour_row, neighbour_col});
                    }
                }
            }
        }
    }

    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        int ans = 0;
        int delta_row[] = {-1, 0, 1, 0};
        int delta_col[] = {0, 1, 0, -1};

        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                if (!visited[r][c] && grid[r][c] == '1')
                {
                    ++ans;
                    bfs(r, c, visited, grid, delta_row, delta_col);
                }

        return ans;
    }
};

//^ 4 Flood Fill
class FloodFIll
{
public:
/* 
@ DFS approach
&- Same as Number of Islands with few extra parameters(initialColor,newColor)
 */
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
    void dfs(int row, int col, unsigned m, unsigned n, vector<vector<int>> &grid, vector<vector<bool>> &vis, int newColor, int initialColor)
    {
        vis.at(row).at(col) = true;
        grid.at(row).at(col) = newColor;
        for (auto &it : dirs)
        {
            int x = row + it.first;
            int y = col + it.second;
            if (inBound(x, y, m, n) && !vis[x][y] && grid[x][y] == initialColor)
            {
                dfs(x, y, m, n, grid, vis, newColor, initialColor);
            }
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        const unsigned m = image.size();
        const unsigned n = image.front().size();
        if (image.at(sr).at(sc) == color)
            return image;
        vector<vector<bool>> vis(m, vector<bool>(n));
        dfs(sr, sc, m, n, image, vis, color, image[sr][sc]);
        return image;
    }
};
int main()
{
    return 0;
}