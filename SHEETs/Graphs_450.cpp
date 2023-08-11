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

    The given code is an implementation of the Flood Fill algorithm. The Flood Fill algorithm is used to fill an area of connected pixels in an image with a specified color. In this case, the image is represented as a 2D grid of integers, where each integer represents a color.

The main function `floodFill` takes as input a reference to the image, the row and column indices of the starting pixel `sr` and `sc`, and the new color `color`. It returns the modified image after performing the flood fill operation.

First, the function calculates the dimensions of the image `m` and `n`. It then checks if the color of the starting pixel is already equal to the new color. If it is, it returns the original image without making any changes.

Otherwise, it creates a 2D boolean vector `vis` to keep track of visited pixels. It then calls the helper function `dfs` to perform a depth-first search (DFS) starting from the pixel at `(sr, sc)`.

The helper function `dfs` takes as input the row and column indices of the current pixel, the dimensions of the image, references to the image and visited vectors, the new color, and the initial color of the starting pixel. It first marks the current pixel as visited and changes its color to the new color.

Next, it iterates over all four directions using a pre-defined vector of pairs `dirs`. For each direction, it calculates the row and column indices of the next pixel. It then checks if this pixel is within bounds, has not been visited yet, and has the same color as the initial color. If all these conditions are met, it calls itself recursively to continue the DFS from this pixel.

After completing the DFS, it returns control back to the main function `floodFill`, which returns the modified image.

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

//^ 5 rotten oranges
class RottenOrange
{
public:
    /*
        Intuition:
            The problem is to determine how long it takes for all fresh oranges to become rotten, considering that rotten oranges can affect adjacent fresh oranges in each minute.
            This problem can be solved using a Breadth-First Search (BFS) approach, where you simulate the process of oranges rotting and keep track of the time taken.

        Code Explanation:
            The code starts by creating a queue to hold the coordinates of rotten oranges and initializes a counter countFreshOrange to keep track of the number of fresh oranges.
            It iterates through the grid and adds the coordinates of rotten oranges to the queue, as well as counts the number of fresh oranges.
            The BFS process begins with a loop that runs until the queue is empty. In each iteration, it processes all the oranges that were rotten in the previous minute.
            For each rotten orange, it checks its adjacent cells (up, down, left, and right) and if there's a fresh orange, it marks it as rotten and decrements the countFreshOrange. The newly rotten oranges are then added to the queue.
            The outer loop runs for each minute, and the inner loop processes all oranges rotten in the previous minute. After processing, the minute counter is incremented.
            Finally, if all fresh oranges are rotten (countFreshOrange becomes 0), it returns the number of minutes taken. Otherwise, it returns -1.

        Time Complexity:
            In the worst case, each cell can be visited at most once, and each visit involves constant time operations (adding to queue, marking as rotten, etc.). Therefore, the time complexity is O(m * n), where m is the number of rows and n is the number of columns in the grid.

        Space Complexity:
            The space complexity is O(m * n) because of the visited grid and the queue used to store the coordinates of rotten oranges.

        Hints:
            BFS is a common approach for problems involving the spread of effects through adjacent cells or nodes.
            Think about how to represent rotten and fresh oranges efficiently.
            Consider how to mark an orange as rotten and how to update adjacent cells in each minute of the simulation.
     */
    int orangesRotting(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> visited = grid;
        // making queue in which we will fill rotten oranges
        queue<pair<int, int>> q;
        int countFreshOrange = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visited[i][j] == 2)
                {
                    q.push({i, j});
                }
                if (visited[i][j] == 1)
                {
                    countFreshOrange++;
                }
            }
        }
        // q.empty() means there is no rotten orange in the grid and countFreshOrange = 0 means we will rotten the freshoranges in 0 mins
        if (countFreshOrange == 0)
            return 0;
        if (q.empty())
            return -1;

        int minutes = -1;
        // we will cover four directions i.e. up, down, left, right
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                auto it = q.front();
                int x = it.first;
                int y = it.second;
                q.pop();
                for (pair<int, int> &p : dirs)
                {
                    int i = x + p.first;
                    int j = y + p.second;
                    if (i >= 0 && i < m && j >= 0 && j < n && visited[i][j] == 1)
                    {
                        visited[i][j] = 2;
                        countFreshOrange--;
                        q.push({i, j});
                    }
                }
            }
            minutes++;
        }

        if (countFreshOrange == 0)
            return minutes;
        return -1;
    }
};

//^ 6 detect a cycle in an undirected graph
class DetectCycle
{
private:
/* 
    Intuition:
        A cycle in an undirected graph occurs when there is a path from a vertex back to itself through a sequence of adjacent vertices, and the path is not just a single edge.
        We can use Breadth-First Search (BFS) traversal to detect cycles in an undirected graph.
        During BFS traversal, if we encounter a visited vertex that is not the parent of the current vertex, then a cycle is detected.

    Code Explanation:
        The code uses BFS to traverse the graph.
        For each vertex, it performs BFS starting from that vertex.
        In each BFS traversal, it maintains the parent of each vertex. If a visited vertex is encountered that is not the parent of the current vertex, a cycle is detected.
        The vis array is used to keep track of visited vertices.
        The function bfs returns true if a cycle is detected in the BFS traversal starting from the given source vertex.
        The isCycle function checks for cycles in the entire graph by calling the bfs function for each unvisited vertex.
        If a cycle is detected in any BFS traversal, the function returns true. Otherwise, it returns false.

    Time Complexity:
        The BFS traversal takes O(V + E) time, where V is the number of vertices and E is the number of edges.
        Since the code calls BFS for each vertex, the overall time complexity is O(V * (V + E)).

    Space Complexity:
        The code uses a queue for BFS, which requires O(V) space for storing vertices in the queue.
        Additionally, the vis array requires O(V) space.
        The overall space complexity is O(V).

    Hints:
        Use BFS to traverse the graph.
        During BFS traversal, maintain the parent of each vertex.
        If a visited vertex is encountered that is not the parent of the current vertex, a cycle is detected.
 */
public:
    bool bfs(int V, vector<int> adj[], int src, vector<bool> &vis)
    {
        queue<pair<int, int>> q;
        q.push({src, -1});

        vis[src] = true;

        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            int node = it.first;
            int parentNode = it.second;
            for (auto &i : adj[node])
            {
                if (!vis[i])
                {
                    q.push({i, node});
                    vis[i] = true;
                }
                else if (vis[i] && i != parentNode)
                {
                    return true; // Cycle detected
                }
            }
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[])
    {
        vector<bool> vis(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (bfs(V, adj, i, vis))
                {
                    return true;
                }
            }
        }

        return false;
    }

    // Function to detect cycle in an undirected graph.
    bool dfs(int parent, int src, vector<int> adj[], vector<bool> &vis)
    {
        vis[src] = true;
        for (auto node : adj[src])
        {
            if (!vis[node])
            {
                if (dfs(src, node, adj, vis))
                    return true;
            }
            else if (parent != node)
            {
                return true;
            }
        }
        return false;
    }
};

//^ 7 Matrix 0/1 problem (similar like rotten oranges)
class Matrix01
{
public:
/*
    Intuition:
        The problem is about finding the distance of each cell in a matrix from the nearest cell with a value of 1.
        We can solve this using Breadth-First Search (BFS). The idea is to start BFS from each cell with value 1 and propagate the distances to neighboring cells with value 0.

    Code Explanation:
        The code initializes two 2D vectors, vis and dis, both with the same dimensions as the input grid.
        It starts by finding all cells with value 1 and initializing a BFS queue with these cells and a distance of 0.
        Then, it performs BFS to spread the distances from these cells to their neighboring cells with value 0.
        During BFS, it keeps track of visited cells using the vis array to avoid visiting the same cell multiple times.
        The delrow and delcol arrays represent the possible movements (up, down, left, right) to neighboring cells.
        The distances are updated in the dis array for each cell.
        Finally, the dis array is returned, representing the distances of each cell from the nearest 1 cell.

    Time Complexity:
        The code visits each cell in the grid at most once during BFS.
        Since BFS has a time complexity of O(V + E), where V is the number of vertices (cells) and E is the number of edges (connections between neighboring cells), the overall time complexity is O(n * m), where n is the number of rows and m is the number of columns.

    Space Complexity:
        The code uses two 2D arrays (vis and dis) of size n x m, where n is the number of rows and m is the number of columns.
        Additionally, the BFS queue can have at most n x m elements.
        The overall space complexity is O(n * m).

    Hints:
        Use BFS to traverse the matrix starting from cells with value 1.
        Keep track of visited cells to avoid revisiting the same cell during BFS.
        Update the distances of neighboring cells with value 0 during BFS.

The code 
 */
    vector<vector<int>> nearest(vector<vector<int>> grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        vector<vector<int>> dis(n, vector<int>(m, 0));
        queue<pair<pair<int, int>, int>> q;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1)
                {
                    vis[i][j] = 1;
                    q.push({{i, j}, 0});
                }
            }
        }

        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, -1, 0, 1};

        while (!q.empty())
        {
            int row = q.front().first.first;
            int col = q.front().first.second;
            int steps = q.front().second;
            q.pop();

            dis[row][col] = steps;

            for (int i = 0; i < 4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0 && grid[nrow][ncol] == 0)
                {
                    vis[nrow][ncol] = 1;
                    q.push({{nrow, ncol}, steps + 1});
                }
            }
        }
        return dis;
    }
};

//^ 8 Replace O's with X's
class Replacement
{
private:
/* 
    Intuition:
        The problem is about finding and marking connected regions of 'O's that are not surrounded by 'X's.
        We can solve this using Depth-First Search (DFS) or Breadth-First Search (BFS).
        The idea is to start from the boundary of the matrix and perform DFS/BFS to mark all connected 'O's as visited. The remaining unvisited 'O's are the ones that are not surrounded by 'X's.

    Code Explanation:
        The code uses a dirs vector to represent the four possible directions to move (up, down, left, right).
        The inBound function checks whether a given row and column are within the bounds of the matrix.
        The dfs function performs DFS to mark all connected 'O's starting from a given cell.
        The fill function iterates through the boundary cells and performs DFS for each 'O' cell encountered. This marks all connected 'O's that are not surrounded by 'X's.
        Finally, the code iterates through the entire matrix and replaces unvisited 'O's with 'X's.

    Time Complexity:
        The code visits each cell in the matrix once during the DFS/BFS.
        Since DFS/BFS has a time complexity of O(V + E), where V is the number of vertices (cells) and E is the number of edges (connections between neighboring cells), the overall time complexity is O(n * m), where n is the number of rows and m is the number of columns.

    Space Complexity:
        The code uses a 2D array vis of size n x m to keep track of visited cells.
        Additionally, the DFS/BFS queue can have at most n x m elements.
        The overall space complexity is O(n * m).

    Hints:
        Use DFS or BFS to traverse the matrix starting from the boundary cells.
        Mark all connected 'O' cells as visited during traversal.
        Replace unvisited 'O' cells with 'X' at the end.
 */
public:
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }

    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &mat, int n, int m)
    {
        vis[row][col] = true;
        for (auto &dir : dirs)
        {
            int nrow = row + dir.first;
            int ncol = col + dir.second;
            if (inBound(nrow, ncol, n, m) && !vis[nrow][ncol] && mat[nrow][ncol] == 'O')
            {
                dfs(nrow, ncol, vis, mat, n, m);
            }
        }
    }
    vector<vector<char>> fill(int n, int m, vector<vector<char>> &mat)
    {
        vector<vector<int>> vis(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            if (vis[i][0] == 0 && mat[i][0] == 'O')
            {
                dfs(i, 0, vis, mat, n, m);
            }
            if (vis[i][m - 1] == 0 && mat[i][m - 1] == 'O')
            {
                dfs(i, m - 1, vis, mat, n, m);
            }
        }

        for (int j = 0; j < m; j++)
        {
            if (vis[0][j] == 0 && mat[0][j] == 'O')
            {
                dfs(0, j, vis, mat, n, m);
            }
            if (vis[n - 1][j] == 0 && mat[n - 1][j] == 'O')
            {
                dfs(n - 1, j, vis, mat, n, m);
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (vis[i][j] == 0 && mat[i][j] == 'O')
                {
                    mat[i][j] = 'X';
                }
            }
        }
        return mat;
    }
};

//^ 9 Number of Enclaves
class NumberEnclaves
{
    private:
    /* 
        Intuition:
        The problem is about finding the number of '1's in the grid that are not connected to the boundary of the grid.
        We can solve this using Breadth-First Search (BFS).
        The idea is to start from the boundary cells that have '1's and perform BFS to mark all connected '1's as visited.
        At the end, we count the remaining unvisited '1's, which represent the enclaves.

    Code Explanation:
        The code uses a dirs vector to represent the four possible directions to move (up, down, left, right).
        The inBound function checks whether a given row and column are within the bounds of the matrix.
        The numberOfEnclaves function iterates through the boundary cells and performs BFS for each '1' cell encountered. This marks all connected '1's that are not connected to the boundary.
        After BFS traversal, the code counts the remaining unvisited '1's, which represent the enclaves.

    Time Complexity:
        The code visits each cell in the matrix once during the BFS.
        Since BFS has a time complexity of O(V + E), where V is the number of vertices (cells) and E is the number of edges (connections between neighboring cells), the overall time complexity is O(n * m), where n is the number of rows and m is the number of columns.

    Space Complexity:
        The code uses a 2D array vis of size n x m to keep track of visited cells.
        Additionally, the BFS queue can have at most n x m elements.
        The overall space complexity is O(n * m).

    Hints:
        Use BFS to traverse the matrix starting from the boundary cells that have '1's.
        Mark all connected '1' cells as visited during traversal.
        Count the remaining unvisited '1's at the end to find the number of enclaves.
     */
public:
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
    int numberOfEnclaves(vector<vector<int>> &grid)
    {
        unsigned n = grid.size(), m = grid.front().size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            if (grid[i][0] == 1 && !vis[i][0])
            {
                q.emplace(i, 0);
                vis[i][0] = true;
            }
            if (grid[i][m - 1] == 1 && !vis[i][m - 1])
            {
                q.emplace(i, m - 1);
                vis[i][m - 1] = true;
            }
        }

        for (int j = 0; j < m; j++)
        {
            if (grid[0][j] == 1 && !vis[0][j])
            {
                q.emplace(0, j);
                vis[0][j] = true;
            }
            if (grid[n - 1][j] == 1 && !vis[n - 1][j])
            {
                q.emplace(n - 1, j);
                vis[n - 1][j] = true;
            }
        }

        // bfs
        while (!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            for (auto &it : dirs)
            {
                int nrow = row + it.first;
                int ncol = col + it.second;
                if (inBound(nrow, ncol, n, m) && !vis[nrow][ncol] && grid[nrow][ncol] == 1)
                {
                    vis.at(nrow).at(ncol) = true;
                    q.emplace(nrow, ncol);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (vis[i][j] == false && grid[i][j] == 1)
                {
                    ans++;
                }
            }
        }
        return ans;
    }
};

//^ 10 Number of distinct islands
class DistinctIslands {
  public:
    set<vector<pair<int,int>>> distinct;
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }
    
    void dfs(int row,int col,int src,vector<vector<bool>> &vis,vector<vector<int>> &grid,vector<pair<int,int>> &coords,int baseR,int baseC){
        vis.at(row).at(col) = true;
        coords.emplace_back(make_pair(row-baseR,col-baseC));
        for(auto &dir : dirs){
            int nrow = row + dir.first;
            int ncol = col + dir.second;
            if(inBound(nrow,ncol,grid.size(),grid.front().size()) && !vis.at(nrow).at(ncol) && grid.at(nrow).at(ncol) == 1){
                dfs(nrow,ncol,grid.at(nrow).at(ncol),vis,grid,coords,baseR,baseC);
            }
        }
    }
    
    int countDistinctIslands(vector<vector<int>>& grid) {
        // code here
        unsigned n = grid.size() , m = grid.back().size();
        vector<vector<bool>> vis(n,vector<bool> (m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!vis[i][j] && grid[i][j] == 1){
                    //? perform dfs
                    vector<pair<int,int>> coords;
                    dfs(i,j,grid[i][j],vis,grid,coords,i,j);
                    distinct.insert(coords);
                }
            }
        }
        return distinct.size();
    }
};
int main()
{
    return 0;
}