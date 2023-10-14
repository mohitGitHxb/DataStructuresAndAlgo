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
class DistinctIslands
{
private:
    /*
        Intuition:
    &        The goal is to count the number of distinct islands in a given grid.
    &        An island is defined as a connected group of cells with value 1.
    &        Two islands are considered distinct if they differ in their shapes or relative positions.

        Code Explanation:
    &-       The countDistinctIslands function takes a 2D grid of integers as input and returns the count of distinct islands.
    &-       It initializes an empty set named distinct to store distinct island shapes.
    &-       For each cell in the grid, if it's part of an unvisited island (value 1), the code initiates a Depth-First Search (DFS) to find all the connected cells of the island.
    &-       During DFS, it tracks the coordinates of each connected cell relative to the starting cell's position.
    &-       Once a complete island is explored, the coordinates of its cells are stored in the coords vector.
    &-       The distinct set is used to store these relative coordinates vectors, ensuring uniqueness.
    &-       Finally, the size of the distinct set represents the count of distinct islands.

        Time Complexity:
    *-     The code involves traversing through each cell in the grid and performing DFS in a worst-case scenario.
    *-     The time complexity of the DFS for each island is proportional to the number of cells in that island.
    *-     Overall, the time complexity is O(n * m), where n and m are the dimensions of the grid.

        Space Complexity:
    *-     The code uses several vectors and sets to store information, resulting in a space complexity of O(n * m).

        Hints:
    *        Use Depth-First Search (DFS) to explore each connected island.
    *        Store the relative coordinates of each cell within an island.
    *        Use a set to keep track of distinct island shapes.
    *        Count the size of the set to get the number of distinct islands.
     */
public:
    set<vector<pair<int, int>>> distinct;
    vector<pair<int, int>> dirs{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    bool inBound(int row, int col, unsigned m, unsigned n)
    {
        return row >= 0 && row < m && col >= 0 && col < n;
    }

    void dfs(int row, int col, int src, vector<vector<bool>> &vis, vector<vector<int>> &grid, vector<pair<int, int>> &coords, int baseR, int baseC)
    {
        vis.at(row).at(col) = true;
        coords.emplace_back(make_pair(row - baseR, col - baseC));
        for (auto &dir : dirs)
        {
            int nrow = row + dir.first;
            int ncol = col + dir.second;
            if (inBound(nrow, ncol, grid.size(), grid.front().size()) && !vis.at(nrow).at(ncol) && grid.at(nrow).at(ncol) == 1)
            {
                dfs(nrow, ncol, grid.at(nrow).at(ncol), vis, grid, coords, baseR, baseC);
            }
        }
    }

    int countDistinctIslands(vector<vector<int>> &grid)
    {
        // code here
        unsigned n = grid.size(), m = grid.back().size();
        vector<vector<bool>> vis(n, vector<bool>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!vis[i][j] && grid[i][j] == 1)
                {
                    //? perform dfs
                    vector<pair<int, int>> coords;
                    dfs(i, j, grid[i][j], vis, grid, coords, i, j);
                    distinct.insert(coords);
                }
            }
        }
        return distinct.size();
    }
};

//^ 11 Bipartite graph
class Bipartite
{
public:
    /*

    1. **Intuition**:
       - A bipartite graph is a graph in which the vertices can be divided into two disjoint sets such that no two vertices within the same set are adjacent.
       - The problem is to determine if the given graph is bipartite or not.

    2. **Code Explanation**:
       - The `isBipartiteUtil` function is a BFS-based approach to check if a single connected component of the graph is bipartite.
       - It uses a queue to perform BFS traversal of the graph, starting from a source node.
       - The `colored` vector is used to assign colors to the nodes. The colors are represented by values 0 and 1.
       - The BFS starts by coloring the source node with color 0 (or 1), and then colors its neighbors with the opposite color (1 or 0).
       - If any neighbor is already colored with the same color as the current node, then the graph cannot be bipartite.
       - The `isBipartite` function iterates over all nodes and calls `isBipartiteUtil` for each unvisited node.
       - If a connected component is found to be non-bipartite, the function immediately returns `false`.
       - If all connected components are bipartite, the function returns `true`.

    3. **Time Complexity**:
       - The code involves BFS traversal of the graph.
       - Each node is visited once, and each edge is explored once.
       - The time complexity is O(V + E), where V is the number of vertices and E is the number of edges.

    4. **Space Complexity**:
       - The code uses several vectors to store information, resulting in a space complexity of O(V) for the `colored` vector.

    5. **Hints**:
       - Use BFS to traverse the graph component by component.
       - Assign colors (0 or 1) to nodes while traversing.
       - If a node's neighbor is already colored with the same color, the graph is not bipartite.
       - Return `false` as soon as you find a non-bipartite component.
       - Return `true` if all connected components are bipartite.


     */
    bool isBipartiteUtil(int V, int src, vector<int> adj[], vector<int> &colored)
    {

        queue<int> q;
        q.emplace(src);
        colored[src] = 0;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            for (auto &it : adj[node])
            {
                if (colored.at(it) == -1)
                {
                    q.emplace(it);
                    colored.at(it) = !colored[node];
                }
                else if (colored.at(it) == colored[node])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool isBipartite(int V, vector<int> adj[])
    {

        vector<int> colored(V, -1);
        for (int i = 0; i < V; i++)
        {
            if (colored[i] == -1)
            {
                if (isBipartiteUtil(V, i, adj, colored))
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }

    //? DFS approach
    /*
        Intuition:
        Similar to the previous approach, this code also aims to determine if a given graph is bipartite.
        Bipartite graphs are those that can be divided into two disjoint sets such that no two vertices within the same set are adjacent.

    Code Explanation:
        The code uses a DFS-based approach to traverse the graph and assign colors to nodes.
        The dfs function takes a node, its adjacent list, and an array color where each node is colored with either 0 or 1.
        The color assignment is done in such a way that adjacent nodes have different colors.
        The DFS visits each node and colors it. If any adjacent node is already colored with the same color, the graph cannot be bipartite, and the function returns false.
        If no inconsistencies are found during DFS traversal, the function returns true.
        The isBipartite function initializes the color array with -1 (indicating uncolored nodes) and iterates through all nodes. For each uncolored node, it assigns a color and starts DFS from that node.
        If DFS returns false, indicating an inconsistency in coloring, the function immediately returns false. Otherwise, it returns true.

    Time Complexity:
        The code involves a DFS traversal of the graph.
        Each node is visited once, and each edge is explored once.
        The time complexity is O(V + E), where V is the number of vertices and E is the number of edges.

    Space Complexity:
        The code uses additional memory for the color array.
        The space complexity is O(V) for the color array.

    Hints:
        Use DFS to traverse the graph and assign colors while visiting nodes.
        If any adjacent node is already colored with the same color, the graph is not bipartite.
        Return false as soon as you find an inconsistency in coloring.
        Return true if all nodes are colored consistently.
     */
    bool dfs(int node, vector<int> adj[], int color[])
    {
        for (auto it : adj[node])
        {
            if (color[it] == -1)
            {
                color[it] = 1 - color[node];
                if (!dfs(it, adj, color))
                {
                    return false;
                }
            }
            else if (color[it] == color[node])
            {
                return false;
            }
        }
        return true;
    }
    bool isBipartite(int V, vector<int> adj[])
    {
        // Code here
        int color[V];
        memset(color, -1, sizeof color);
        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 1;
                if (!dfs(i, adj, color))
                {
                    return false;
                }
            }
        }
        return true;
    }
};

//^ 12 Detect a cycle in a directed graph
class CycleInADirectedGraph
{
private:
    /*
        Intuition:
            This code aims to detect cycles in a directed graph.
            It uses a Depth-First Search (DFS) approach to traverse the graph while maintaining two boolean arrays: vis and pathVis.
            The vis array keeps track of whether a node has been visited during the entire traversal, while the pathVis array keeps track of whether a node is currently visited within the current path.

        Code Explanation:
            The dfs function takes a source node, the adjacency list, and performs a DFS traversal.
            During traversal, it marks the node as visited in both vis and pathVis arrays.
            It then recursively explores all adjacent nodes that have not been visited.
            If it encounters a node that is already visited and is also currently part of the current path (according to pathVis), then a cycle is detected and the function returns true.
            After backtracking from the recursion, the pathVis of the current node is set to false, indicating that this node is not part of the current path anymore.
            If no cycle is detected during traversal, the function returns false.
            The isCyclic function initializes the vis and pathVis arrays and iterates through all nodes, performing DFS from each unvisited node.
            If a cycle is detected during any DFS, the function immediately returns true. Otherwise, it returns false.

        Time Complexity:
            The code involves a DFS traversal of the graph.
            Each node is visited once, and each edge is explored once.
            The time complexity is O(V + E), where V is the number of vertices and E is the number of edges.

        Space Complexity:
            The code uses additional memory for the vis and pathVis arrays.
            The space complexity is O(V) for these arrays.

        Hints:
            Use DFS to traverse the graph while keeping track of visited nodes and nodes currently visited in the current path.
            If a visited node is encountered again in the current path, a cycle is detected.
            Return true as soon as a cycle is detected during DFS traversal.
            Return false if no cycles are found after DFS from all unvisited nodes.
     */
public:
    vector<bool> vis, pathVis;
    bool dfs(int src, vector<int> adj[])
    {
        vis[src] = true;
        pathVis[src] = true;
        for (auto &it : adj[src])
        {
            if (!vis[it])
            {
                if (dfs(it, adj))
                    return true;
            }
            else if (pathVis[it] && vis[it])
            {
                return true;
            }
        }
        pathVis[src] = false; //? Backtracking
        return false;
    }
    bool isCyclic(int V, vector<int> adj[])
    {
        // code here
        vis.resize(V + 1);
        pathVis.resize(V + 1);
        for (int i = 1; i < V; i++)
        {
            if (!vis[i])
            {
                if (dfs(i, adj))
                {
                    return true;
                }
            }
        }
        return false;
    }
};

//^ 13 Eventually Safe Nodes [DFS]
class SafeNodes1
{
private:
    /*
        Intuition:
            This code aims to find all the safe nodes in a directed graph.
            A safe node is a node from which every possible path leads to a terminal node (a node with no outgoing edges) or another safe node.
            The code utilizes a Depth-First Search (DFS) approach to traverse the graph and mark safe nodes.

        Code Explanation:
            The dfs function takes a source node, the adjacency list, and two boolean arrays: vis (to track visited nodes) and recst (to track nodes in the current recursion stack).
            It marks the current node as visited (vis[src] = true) and adds it to the current recursion stack (recst[src] = true).
            Then, for each neighbor x of the current node, it checks whether x is visited and whether a cycle is present in the current recursion stack. If so, it returns true.
            If x is not visited, it recursively calls dfs on x.
            If a cycle is detected or if all neighbors have been visited without detecting a cycle, the current node is removed from the current recursion stack (recst[src] = false) and false is returned.
            In the eventualSafeNodes function, it initializes the adjacency list adj based on the given graph representation.
            It initializes the vis and recst arrays.
            For each unvisited node, it calls the dfs function to determine whether the node is a safe node.
            It then iterates through the recst array to find nodes that are not in the current recursion stack, indicating that they are safe nodes.
            It returns a vector containing the indices of safe nodes.

        Time Complexity:
            The code involves a DFS traversal of the graph.
            Each node is visited once, and each edge is explored once.
            The time complexity is O(V + E), where V is the number of vertices and E is the number of edges.

        Space Complexity:
            The code uses additional memory for the vis and recst arrays.
            The space complexity is O(V) for these arrays.

        Hints:
            Use DFS to traverse the graph while keeping track of visited nodes and nodes in the current recursion stack.
            During DFS, check for cycles by detecting nodes that are already in the current recursion stack.
            Return true if a cycle is detected during DFS.
            If no cycle is detected, return false and mark the node as safe.
            Iterate through all nodes and identify nodes that are not in the current recursion stack as safe nodes.
     */
public:
    bool dfs(vector<vector<int>> &adj, int src, vector<bool> &vis, vector<bool> &recst)
    {
        vis[src] = true;
        recst[src] = true; //? path visited already
        for (auto x : adj[src])
        {
            if (vis[x] == false && dfs(adj, x, vis, recst))
            {
                return true;
            }
            else if (recst[x] == true)
            {
                return true;
            }
        }
        recst[src] = false;
        return false;
    }
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].size(); j++)
            {
                adj[i].push_back(graph[i][j]);
            }
        }
        vector<bool> vis(n, false);
        vector<bool> recst(n, false);
        for (int i = 0; i < n; i++)
        {
            if (vis[i] == false)
            {
                dfs(adj, i, vis, recst);
            }
        }
        vector<int> ans;
        for (int i = 0; i < recst.size(); i++)
        {
            if (!recst[i])
                ans.push_back(i);
        }
        return ans;
    }
};

//^ 14 Topoglogical sort
class TopoglogicalSort
{
public:
    void dfs(int src, vector<int> adj[], vector<int> &stk, vector<bool> &vis)
    {
        vis.at(src) = true;
        for (auto &node : adj[src])
        {
            if (!vis.at(node))
            {
                dfs(node, adj, stk, vis);
            }
        }
        stk.emplace_back(src);
    }
    vector<int> topoSort(int V, vector<int> adj[])
    {
        vector<bool> vis(V);
        vector<int> ans;
        for (int i = 0; i < V; i++)
        {
            if (!vis.at(i))
            {
                dfs(i, adj, ans, vis);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/* BFS Approach || Kahn's Algo

    Idea

    The idea is that all nodes which will be at starting will have indegree 0.

Algorithm

    Store Indegree of all nodes in Array.
    Push nodes in Queue whose indegree == 0.
    Now, For each node in Queue.
        Pop the current node & Store into resultant Array
        Remove indegree count of all neighbours of current node.
        If neighbours indegree becomes 0 the push into queue.
    Finally, return resultant Array.

Source Code */
//^ 15 Kahns ALgorithm
class KahnAlgo
{
public:
    // Function to return list containing vertices in Topological order.
    vector<int> topoSort(int V, vector<int> adj[])
    {
        vector<int> res;
        vector<int> indegree(V, 0);

        for (int i = 0; i < V; i++)
        {
            for (int nbr : adj[i])
            {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            for (int nbr : adj[curr])
            {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }

        return res;
    }
};

//^ 16 Detect a cycle in a directed graph using topological sorting
bool isCyclic(int V, vector<int> adj[])
{
    // code here
    vector<int> indegree(V);
    for (int i = 0; i < V; i++)
    {
        for (int &j : adj[i])
        {
            indegree.at(j)++;
        }
    }
    queue<int> q;
    for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }
    int topoSize = 0;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        topoSize++;
        for (int it : adj[node])
        {
            indegree.at(it)--;
            if (indegree.at(it) == 0)
            {
                q.push(it);
            }
        }
    }
    return !(topoSize == V);
}

//^ 17 Course Scheduling
class CourseScheduling
{
public:
    bool isCyclic(int V, vector<int> adj[])
    {
        vector<int> indegree(V);
        for (int i = 0; i < V; i++)
        {
            for (int &j : adj[i])
            {
                indegree.at(j)++;
            }
        }
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }
        int topoSize = 0;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topoSize++;
            for (int it : adj[node])
            {
                indegree.at(it)--;
                if (indegree.at(it) == 0)
                {
                    q.push(it);
                }
            }
        }
        return (topoSize == V);
    }
    bool isPossible(int N, int P, vector<pair<int, int>> &prerequisites)
    {
        vector<int> adj[N];
        for (auto it : prerequisites)
            adj[it.first].push_back(it.second);
        return isCyclic(N, adj);
    }
    //^ Printing the order
    vector<int> topoSort(int V, vector<int> adj[])
    {
        vector<int> res;
        vector<int> indegree(V);

        for (int i = 0; i < V; i++)
        {
            for (int nbr : adj[i])
            {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            for (int nbr : adj[curr])
            {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }

        return (res.size() == V) ? res : vector<int>();
    }
    vector<int> findOrder(int n, int m, vector<vector<int>> prerequisites)
    {
        vector<int> adj[n];
        for (auto &it : prerequisites)
        {
            adj[it.back()].push_back(it.front());
        }
        return topoSort(n, adj);
    }
};

//^ 18 Alien dictionary
class AlienDictionary
{
public:
    vector<int> getTopoSort(int V, vector<int> adj[])
    {
        vector<int> res;
        vector<int> indegree(V, 0);

        for (int i = 0; i < V; i++)
        {
            for (int nbr : adj[i])
            {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            for (int nbr : adj[curr])
            {
                indegree[nbr]--;
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }

        return res;
    }
    string findOrder(string dict[], int N, int K)
    {
        //? Pick first two pairs of strings then find out the order of occurrence of characters
        //? keep doing this for all consecutive pairs;
        vector<int> adj[K];
        for (int i = 0; i < N - 1; i++)
        {
            string s1 = dict[i], s2 = dict[i + 1];
            int minlength = min(s1.length(), s2.length());
            for (int ptr = 0; ptr < minlength; ptr++)
            {
                if (s1.at(ptr) != s2.at(ptr))
                {
                    adj[s1.at(ptr) - 'a'].push_back(s2.at(ptr) - 'a');
                    break;
                }
            }
        }

        vector<int> topo = getTopoSort(K, adj);
        string ans = "";
        for (int it : topo)
        {
            ans.push_back((char)(it + (int)'a'));
        }
        return ans;
    }
};

//^ 19 Shortest distance in a DAG
class ShortestDistanceInDAG
{
public:
    vector<int> getTopoSort(int V, vector<pair<int, int>> adj[])
    {
        vector<int> res;
        vector<int> indegree(V);

        for (int i = 0; i < V; i++)
        {
            for (auto &nbr : adj[i])
            {
                indegree[nbr.first]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            res.push_back(curr);

            for (auto nbr : adj[curr])
            {
                indegree[nbr.first]--;
                if (indegree[nbr.first] == 0)
                    q.push(nbr.first);
            }
        }

        return res;
    }
    vector<int> shortestPath(int N, int M, vector<vector<int>> &edges)
    {
        // find topological sort first using any algorithm(Kahn's or dfs);
        vector<pair<int, int>> graph[N];
        for (int i = 0; i < M; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            graph[u].push_back({v, wt});
        }
        vector<int> topo = getTopoSort(N, graph);
        reverse(topo.begin(), topo.end()); // using vector as a stack
        // for(auto &i : topo) cout << i << "\n";
        vector<int> distance(N, 1e9);
        distance[0] = 0;
        while (!topo.empty())
        {
            int node = topo.back();
            topo.pop_back();
            for (auto &it : graph[node])
            {
                int v = it.first;
                int wt = it.second;
                distance[v] = min(distance[v], distance[node] + wt);
            }
        }
        for (int &i : distance)
        {
            if (i >= 1e9)
                i = -1;
        }
        return distance;
    }
};

//^ 20 Shortest path in a Undirected graph
vector<int> shortestPath(vector<vector<int>> &edges, int N, int M, int src)
{
    // code here
    vector<int> graph[N];
    for (auto &it : edges)
    {
        int u = it.front();
        int v = it.back();
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    //? Simple BFS
    vector<int> dist(N, INT_MAX);
    queue<pair<int, int>> q; //? <Node,distance>

    dist[src] = 0;
    q.emplace(src, 0);
    while (!q.empty())
    {
        int node = q.front().first;
        int d = q.front().second;
        q.pop();
        for (auto &nbr : graph[node])
        {
            if (dist[nbr] > d + 1)
            {
                dist[nbr] = d + 1;
                q.emplace(nbr, d + 1);
            }
        }
    }
    for (int &i : dist)
    {
        i = (i == INT_MAX) ? -1 : i;
    }
    return dist;
}

//^ 21 Word ladder 1
int wordLadderLength(string beginWord, string endWord, vector<string> &wordList)
{
    queue<pair<string, int>> q;
    unordered_set<string> hs(wordList.begin(), wordList.end());
    q.emplace(beginWord, 1);

    while (!q.empty())
    {
        string curr = q.front().first;
        int transformation = q.front().second;
        q.pop();
        for (int i = 0; i < curr.length(); i++)
        {
            string temp = curr;
            for (char c = 'a'; c <= 'z'; c++)
            {
                temp[i] = c;
                if (temp == endWord && hs.count(temp))
                {
                    return transformation + 1;
                }
                if (hs.count(temp))
                {
                    q.emplace(temp, transformation + 1);
                    hs.erase(hs.find(temp));
                }
            }
        }
    }
    return 0;
}

//^ 22 Word ladder 2

/*
Initial configuration:

    Queue: Define a queue data structure to store the level-wise formed sequences. The queue will be storing a List of strings, which will be representing the path till now. The last word in the list will be the last converted word.
    Hash set: Create a hash set to store the elements present in the word list to carry out the search and delete operations in O(1) time.
    Vector: Define a 1D vector ‘usedOnLevel’ to store the words which are currently being used for transformation on a particular level and a 2D vector ‘ans’ for storing all the shortest sequences of transformation.

The Algorithm for this problem involves the following steps:

    Firstly, we start by creating a hash set to store all the elements present in the wordList which would make the search and delete operations faster for us to implement.
    Next, we create a Queue data structure for storing the successive sequences/ path in the form of a vector which on transformation would lead us to the target word.
    Now, we add the startWord to the queue as a List and also push it into the usedOnLevel vector to denote that this word is currently being used for transformation in this particular level.
    Pop the first element out of the queue and carry out the BFS traversal, where for each word that popped out from the back of the sequence present at the top of the queue, we check for all of its characters by replacing them with ‘a’ – ‘z’ if they are present in the wordList or not. In case a word is present in the wordList, we simply first push it onto the usedOnLevel vector and do not delete it from the wordList immediately.
    Now, push that word into the vector containing the previous sequence and add it to the queue. So we will get a new path, but we need to explore other paths as well, so pop the word out of the list to explore other paths.
    After completion of traversal on a particular level, we can now delete all the words that were currently being used on that level from the usedOnLevel vector which ensures that these words won’t be used again in the future, as using them in the later stages will mean that it won’t be the shortest path anymore.
    If at any point in time we find out that the last word in the sequence present at the top of the queue is equal to the target word, we simply push the sequence into the resultant vector if the resultant vector ‘ans’ is empty.
    If the vector is not empty, we check if the current sequence length is equal to the first element added in the ans vector or not. This has to be checked because we need the shortest possible transformation sequences.
    In case, there is no transformation sequence possible, we return an empty 2D vector.

 */
vector<vector<string>> findSequences(string beginWord, string endWord,
                                     vector<string> &wordList)
{
    // Push all values of wordList into a set
    // to make deletion from it easier and in less time complexity.
    unordered_set<string> st(wordList.begin(), wordList.end());
    // Creating a queue ds which stores the words in a sequence which is
    // required to reach the targetWord after successive transformations.
    queue<vector<string>> q;
    // BFS traversal with pushing the new formed sequence in queue
    // when after a transformation, a word is found in wordList.
    q.push({beginWord});
    // A vector defined to store the words being currently used
    // on a level during BFS.
    vector<string> usedOnLevel;
    usedOnLevel.push_back(beginWord);
    int level = 0;
    // A vector to store the resultant transformation sequence.
    vector<vector<string>> ans;
    while (!q.empty())
    {
        vector<string> vec = q.front();
        q.pop();
        // Now, erase all words that have been
        // used in the previous levels to transform
        if (vec.size() > level)
        {
            level++;
            for (auto it : usedOnLevel)
            {
                st.erase(it);
            }
        }
        string word = vec.back();
        // store the answers if the end word matches with targetWord.
        if (word == endWord)
        {
            // the first sequence where we reached end
            if (ans.size() == 0)
            {
                ans.push_back(vec);
            }
            else if (ans[0].size() == vec.size())
            {
                ans.push_back(vec);
            }
        }
        for (int i = 0; i < word.size(); i++)
        {
            // Now, replace each character of ‘word’ with char
            // from a-z then check if ‘word’ exists in wordList.
            char original = word[i];
            for (char c = 'a'; c <= 'z'; c++)
            {
                word[i] = c;
                if (st.count(word) > 0)
                {
                    // Check if the word is present in the wordList and
                    // push the word along with the new sequence in the queue.
                    vec.push_back(word);
                    q.push(vec);
                    // mark as visited on the level
                    usedOnLevel.push_back(word);
                    vec.pop_back();
                }
            }
            word[i] = original;
        }
    }
    return ans;
}

//^ 23 Dijekstra algorithm
class Dijekstra
{
private:
public:
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Code here
        // Using Set
        set<pair<int, int>> st;
        st.insert({0, S});

        vector<int> dist(V, 1e9);
        dist[S] = 0;

        while (!st.empty())
        {
            auto it = *(st.begin()); // value at starting of set

            int distance = it.first;
            int node = it.second;
            st.erase(it);

            for (auto i : adj[node])
            {
                int adjNode = i[0];
                int edgeWeight = i[1];

                if (distance + edgeWeight < dist[adjNode])
                {
                    // erase if it is existed
                    if (dist[adjNode] != 1e9)
                    {
                        st.erase({dist[adjNode], adjNode});
                    }

                    dist[adjNode] = distance + edgeWeight;
                    st.insert({dist[adjNode], adjNode});
                }
            }
        }

        return dist;
    }

    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        vector<int> dist(V, 1e9);
        dist[S] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, S});

        while (!pq.empty())
        {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto x : adj[node])
            {
                int adj_node = x[0];
                int wt = x[1];

                if (dist[adj_node] > dis + wt)
                {
                    dist[adj_node] = dis + wt;
                    pq.push({dist[adj_node], adj_node});
                }
            }
        }
        return dist;
    }
};

//^24 Print the shortest path
class PrintShortestPath
{
public:
    void dijekstra(vector<vector<int>> adj[], vector<int> &dist, vector<int> &parent)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        while (!pq.empty())
        {
            int node = pq.top().second;
            int d = pq.top().first;
            pq.pop();
            for (auto &it : adj[node])
            {
                int edgeWt = it.back();
                int adjNode = it.front();

                if (d + edgeWt < dist[adjNode])
                {
                    dist[adjNode] = d + edgeWt;
                    parent[adjNode] = node;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
    }

    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj[n + 1];
        for (auto &it : edges)
        {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        vector<int> dist(n + 1, 1e9);
        dist.at(1) = 0;
        vector<int> parent(n + 1);
        for (int i = 0; i <= n; i++)
            parent.at(i) = i;
        dijekstra(adj, dist, parent);
        if (dist[n] == 1e9)
            return {-1};
        vector<int> path;
        int node = n;
        while (parent[node] != node)
        {
            path.emplace_back(node);
            node = parent[node];
        }
        path.emplace_back(1);
        reverse(path.begin(), path.end());
        return path;
    }
};

//^25 Shortest path in a binary maze

/* 
Intuition:

To find the shortest path between a source cell and a destination cell in a binary grid, we can use Breadth-First Search (BFS) starting from the source cell and stopping when we reach the destination cell. During the BFS traversal, we'll keep track of the distance from the source cell to each cell we visit.

Here's how the algorithm works:

    Initialize a 2D vector dist of size n x m where each element is initially set to a large value (e.g., 1e9). This vector will store the minimum distance from the source cell to each cell.

    Initialize a queue q for BFS. Each element in the queue will be a pair (distance, cell) where distance is the distance from the source cell to the current cell, and cell is a pair (row, col) representing the coordinates of the cell.

    Initialize the distance of the source cell to 0 and add it to the queue: dist[source.first][source.second] = 0, q.push({0, source}).

    Implement the BFS traversal as follows:
        While the queue is not empty, dequeue the front element (dis, {r, c}).
        Check if the current cell grid[r][c] is valid for movement (i.e., it is 1 and the new distance 1 + dis is less than the current distance dist[r][c]).
        If the above conditions are met, update dist[r][c] with the new distance and enqueue the adjacent cells (up, down, left, right) with the new distance.

    After the BFS traversal, if the dist[dest.first][dest.second] is still the initial large value, it means there is no path from the source to the destination, so return -1.

    Otherwise, return dist[dest.first][dest.second] as the shortest distance from the source to the destination.

Time Complexity:

    The BFS traversal visits each cell at most once, resulting in a time complexity of O(n * m), where n is the number of rows and m is the number of columns in the grid.

Space Complexity:

    The space complexity is O(n * m) for the dist vector and O(n * m) for the queue q, resulting in a total space complexity of O(n * m).

Hint:

    Use BFS to explore the grid while keeping track of the minimum distance from the source cell to each visited cell. If the destination cell is reached, return its distance; otherwise, return -1 if no path is found.
 */
class BinaryMazePath {
  public:
  vector<pair<int,int>> dirs = {{1,0},{0,1},{-1,0},{0,-1}};
  bool isValid(int row,int col,int n,int m,vector<vector<int>> &vis,vector<vector<int>> &grid,int distance){
      return row>=0 && row<n && col>=0 && col<m && grid[row][col] == 1 && 1 + distance < vis[row][col];
  }
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> dest) {
        // code here
        int n = grid.size() , m = grid.front().size();
        vector<vector<int>> dist(n,vector<int> (m,1e9));
        dist[source.first][source.second] = 0;
        queue<pair<int,pair<int,int>>> q;
        q.push({0,{source.first,source.second}});
        while(!q.empty()){
            int dis = q.front().first;
            int r = q.front().second.first;
            int c = q.front().second.second;
            q.pop();
            for(auto &it : dirs){
                int nrow = r + it.first;
                int ncol = c + it.second;
                if(isValid(nrow,ncol,n,m,dist,grid,dis)){
                    dist[nrow][ncol] = 1 + dis;
                    q.push({1 + dis , {nrow,ncol}});
                }
            }
        }
        if(dist[dest.first][dest.second] == 1e9) return -1;
        return dist[dest.first][dest.second];
    }
};

//^26 Path to minimum efforts
class MinimumEfforts
{
private:
    typedef pair<int, int> pi;
    typedef pair<int, pi> pii;

    vector<pi> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool isValid(int row, int col, int n, int m)
    {
        return row >= 0 && col >= 0 && row < n && col < m;
    }

public:
    int MinimumEffort(vector<vector<int>> &heights)
    {
        // Code here
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        int n = heights.size(), m = heights.front().size();
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist.at(0).at(0) = 0;
        pq.push({0, {0, 0}});

        while (!pq.empty())
        {
            int diff = pq.top().first;
            int row = pq.top().second.first;
            int col = pq.top().second.second;
            pq.pop();

            if (row == n - 1 && col == m - 1)
            {
                return dist.at(row).at(col);
            }

            for (auto &it : dirs)
            {
                int nrow = row + it.first;
                int ncol = col + it.second;

                if (isValid(nrow, ncol, n, m))
                {
                    int newEfforts = max(abs(heights[row][col] - heights[nrow][ncol]), diff);

                    if (newEfforts < dist[nrow][ncol])
                    {
                        dist.at(nrow).at(ncol) = newEfforts;
                        pq.push({newEfforts, {nrow, ncol}});
                    }
                }
            }
        }
        return 0;
    }
};

//^ 27 Cheapest flights in K stops

class Solution
{
private:
    /*
    Certainly, let's break down the intuition, code explanation, and complexities for the "Cheapest Flights Within K Stops" problem:

    Intuition:

        The problem involves finding the cheapest price to reach a destination city (dst) from a source city (src) with at most K stops.
        We can use a modified Dijkstra's algorithm to explore flight paths efficiently.
        The algorithm starts from the source city and explores all possible flights while keeping track of the minimum cost to reach each city with the constraint of a maximum number of stops.

    Code Explanation:

        Create Graph: We create a graph where each city is a node, and each flight is an edge. The edge weight represents the cost of the flight. This graph is stored in the adj vector.

        Initialize Distances: We initialize an array dist to store the minimum cost to reach each city. We set the distance to the source city (src) as 0 and all other distances to a high value.

        BFS with Modified Dijkstra:
            We use a BFS approach with a queue to explore possible flight paths.
            Each element in the queue contains three values: stops (number of stops made so far), node (current city), and distance (distance traveled so far).
            The BFS loop continues as long as the queue is not empty.

        BFS Loop:
            We dequeue a flight path from the queue.
            If the number of stops exceeds K, we skip this path and continue to the next iteration.
            Otherwise, for each adjacent city reachable from the current city:
                We calculate the total cost to reach that city (distance + edgeWt).
                If this cost is less than the previously recorded minimum distance to that city (dist[adjNode]), we update dist[adjNode] with the new cost.
                We enqueue the flight path to the adjacent city with an incremented number of stops (stops + 1).

        Result: After the BFS loop, if dist[dst] is still equal to its initial value (1e9), it means there is no valid path to reach the destination with at most K stops, so we return -1. Otherwise, we return dist[dst], which represents the minimum cost to reach the destination city (dst).

    Time Complexity:

        The BFS loop runs in O(E) time, where E is the number of flights.
        In the worst case, each flight is explored once.
        Overall, the time complexity is O(E), where E is the number of flights.

    Space Complexity:

        We use additional space to store the dist array of size n (number of cities) and the queue q.
        Therefore, the space complexity is O(n) for the dist array and O(maximum queue size) for q, which can be O(V) in the worst case.
        Overall, the space complexity is O(n + V), where V is the maximum queue size.

    Hints:

        Think of this problem as finding the shortest path in a graph but with the added constraint of the maximum number of stops (K).
        Use a modified Dijkstra's algorithm or BFS to efficiently explore possible flight paths while keeping track of the minimum costs.
        Initialize distances to a high value and use a BFS queue to explore flights within the stop limit.
        Pay attention to the special case where there is no valid path within the stop limit.
     */
    typedef vector<int> vi;
    typedef vector<pair<int, int>> vpii;

public:
    int CheapestFLight(int n, vector<vector<int>> &flights, int src, int dst, int K)
    {
        // creating graph
        vpii adj[n];
        for (auto &it : flights)
        {
            adj[it[0]].emplace_back(it[1], it[2]);
        }

        vi dist(n, 1e9);
        dist.at(src) = 0;
        queue<vi> q;
        // {stops,node,dist}
        q.push({0, src, 0});

        // dijekstra modified
        while (!q.empty())
        {
            int stops = q.front().at(0);
            int node = q.front().at(1);
            int distance = q.front().at(2);

            q.pop();
            if (stops > K)
                continue;
            for (auto &it : adj[node])
            {
                int adjNode = it.first;
                int edgeWt = it.second;

                if (distance + edgeWt < dist[adjNode])
                {
                    dist[adjNode] = distance + edgeWt;
                    q.push({stops + 1, adjNode, dist[adjNode]});
                }
            }
        }
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};

//^ 28 Minimum multiplications to reach end using the array
class MinimumMultiplicationsToReachEnd
{
private:
    /*
    &- Simple BFS + dijekstra algorithm
    &- Since the value of MOD is 10^5 at max there can be 0 to 9999 nodes in a graph
    &- Go level wise (steps) and the first time we get the "end" we can simply return steps + 1;

    *T.C O(10^5 * N) [Hypothetical]
     */
public:
    int minimumMultiplications(vector<int> &arr, int start, int end)
    {
        // code here
        if (start == end)
            return 0;
        vector<int> dist(1e5, 1e9);
        dist[start] = 0;
        queue<pair<int, int>> q;
        q.emplace(0, start);

        while (!q.empty())
        {
            int steps = q.front().first;
            int node = q.front().second;
            q.pop();
            for (int &it : arr)
            {
                int newNumber = (it * node) % 100000;
                if (steps + 1 < dist[newNumber])
                {
                    if (newNumber == end)
                        return steps + 1;
                    dist[newNumber] = 1 + steps;
                    q.emplace(steps + 1, newNumber);
                }
            }
        }
        return -1;
    }
};

//^ 29 Number of ways to arrive at destination
/* 
**Intuition:**

This problem can be solved using Dijkstra's algorithm to find the shortest paths from the source node (intersection 0) to all other intersections. Additionally, we can keep track of the number of shortest paths to each intersection.

Here's how the algorithm works:

1. Create an adjacency list `adj` to represent the graph, where `adj[i]` is a vector of pairs `(j, w)` indicating that there is a road from intersection `i` to intersection `j` with a travel time of `w` minutes.

2. Initialize two arrays:
   - `dist` to store the minimum travel time to reach each intersection. Initialize it with a large value (e.g., `INT_MAX`) except for `dist[0]` which is set to 0 since we start at intersection 0.
   - `ways` to store the number of ways to reach each intersection with the minimum travel time. Initialize it with zeros except for `ways[0]` which is set to 1 since there is one way to reach intersection 0 (starting from 0).

3. Use a min-heap (priority queue) to perform Dijkstra's algorithm. Initially, push the pair `(0, 0)` into the priority queue, where the first element is the travel time (0 minutes) and the second element is the intersection (0).

4. While the priority queue is not empty, do the following:
   - Pop the top element `(distance, node)` from the priority queue.
   - For each neighbor `(adjNode, edgeWt)` of the current node, check if the new travel time `distance + edgeWt` is equal to the current minimum travel time `dist[adjNode]`. If it is equal, increment the `ways[adjNode]` by `ways[node]` to account for the number of ways to reach `adjNode` with the minimum travel time. If it is less than `dist[adjNode]`, update `dist[adjNode]` with the new travel time and set `ways[adjNode]` to `ways[node]`.
   - Push the pair `(dist[adjNode], adjNode)` into the priority queue.

5. After the loop, `ways[n-1]` will contain the number of ways to reach intersection `n-1` with the minimum travel time.

6. Return `ways[n-1] % MOD` as the answer, where `MOD = 1e9 + 7`.

*Time Complexity:

- The time complexity of Dijkstra's algorithm is O(E * log(V)), where E is the number of edges and V is the number of vertices. In this case, E is the number of roads, and V is the number of intersections.

*Space Complexity:**

- The space complexity is O(V) for the `dist` and `ways` arrays and O(E) for the adjacency list `adj`.

**Hint:**

- Use Dijkstra's algorithm to find the shortest paths and keep track of the number of ways to reach each intersection with the minimum travel time. Be mindful of using a min-heap (priority queue) to efficiently explore nodes with the shortest travel times.
 */
class NumberOfWaysToArrive
{
private:
    typedef vector<int> vi;
    typedef pair<int, int> pii;
    typedef vector<pii> vpii;

    const int MOD = 1e9 + 7;

public:
    int countPaths(int n, vector<vector<int>> &roads)
    {
        // code here
        vpii adj[n];
        for (auto &it : roads)
        {
            adj[it[0]].emplace_back(it[1], it[2]);
            adj[it[1]].emplace_back(it[0], it[2]);
        }

        vi ways(n);
        vector<long> dist(n, INT_MAX);
        dist.at(0) = 0;
        ways.at(0) = 1;
        // min heap for dijekstra
        priority_queue<pii, vpii, greater<pii>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            long distance = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for (auto &it : adj[node])
            {
                int adjNode = it.first;
                long edgeWt = it.second;
                if (distance + edgeWt == dist[adjNode])
                {
                    ways[adjNode] = ways[node] % MOD + ways[adjNode] % MOD;
                }
                else if (distance + edgeWt < dist[adjNode])
                {
                    dist[adjNode] = distance + edgeWt;
                    ways[adjNode] = ways[node] % MOD;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return ways.back() % MOD;
    }
};

//^ 30 bellman ford algorithm
/*
    Initialize Distances: We start by initializing an array dist of size V (number of vertices) with a large value (1e8) to represent infinity. We also set the distance of the source vertex S to 0 because the distance from S to itself is always 0.

    Relax Edges: The algorithm performs a relaxation step for each edge in the graph. It iterates V times to ensure that it has found the shortest paths to all vertices.

    Nested Loop: Within the iteration over vertices, there is a nested loop that iterates through all edges. For each edge (u, v) with weight wt:
        It checks if the distance to vertex u (dist[u]) is not infinity (1e8) and if the sum of the distance to u and the weight wt of the edge is less than the current distance to vertex v (dist[v]).
        If the condition is met, it updates the distance to vertex v with the new shorter distance: dist[v] = dist[u] + wt.

    Negative Cycle Detection: After completing the relaxation steps, the algorithm performs another loop through all edges. If it finds an edge where the relaxation condition still holds (indicating a negative cycle), it returns {-1} to indicate that there is a negative cycle in the graph.

    Return Distances: Finally, the algorithm returns the dist array, which contains the shortest distances from the source vertex S to all other vertices in the graph.

Time Complexity:

    The Bellman-Ford algorithm has a time complexity of O(V * E), where V is the number of vertices and E is the number of edges.
    In your implementation, the outer loop iterates V times, and the inner loop iterates through all edges E for each vertex, resulting in a total time complexity of O(V * E).

Space Complexity:

    The space complexity of this implementation is O(V), where V is the number of vertices, due to the dist array.

Hint:

    Bellman-Ford is a dynamic programming-based algorithm used for finding the shortest paths from a single source vertex to all other vertices, even in graphs with negative weight edges (but without negative cycles).
    It's essential to initialize distances properly before running the algorithm.
 */
vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S)
{
    // Code here
    vector<int> dist(V, 1e8);
    dist[S] = 0;
    for (int i = 0; i < V; i++)
    {
        for (auto &it : edges)
        {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            if (dist.at(u) != 1e8 && dist.at(u) + wt < dist.at(v))
            {
                dist.at(v) = dist.at(u) + wt;
            }
        }
    }
    for (auto &it : edges)
    {
        int u = it[0];
        int v = it[1];
        int wt = it[2];

        if (dist.at(u) != 1e8 && dist.at(u) + wt < dist.at(v))
        {
            return {-1};
        }
    }
    return dist;
}

//^ 32 Floyd warshall algorithm [multi source shortest path]
/*
Code Explanation:

    Initialization: The code begins by initializing the variable n to the number of vertices in the graph (the size of the matrix).

    Triple Nested Loop: The code uses three nested loops to perform the Floyd-Warshall algorithm. These loops are responsible for considering all possible paths between pairs of vertices via an intermediate vertex via.

        The outermost loop iterates over the vertex via. This vertex is considered as a potential intermediate stop between all pairs of vertices.

        The middle loop iterates over the source vertex i, representing the starting vertex of a path.

        The innermost loop iterates over the destination vertex j, representing the ending vertex of a path.

    Validity Check: Inside the nested loops, the code checks whether there is an edge from i to via and from via to j. If either of these edges is missing (indicated by -1 in the matrix), it continues to the next iteration since it's not possible to form a path from i to j via via.

    Path Calculation: If both edges are present, the code calculates the sum part of the distances from i to via and from via to j. This represents the potential distance of the path from i to j via via.

    Updating Matrix: The code updates the entry matrix[i][j] in the adjacency matrix with the minimum of its current value (if it exists) and the newly calculated part. This step ensures that the shortest distance between i and j is stored in the matrix.

    Result: Once all iterations are complete, the adjacency matrix matrix contains the shortest distances between all pairs of vertices.

Time Complexity:

    The code uses three nested loops to iterate over all pairs of vertices and their potential intermediate vertices. The time complexity of the Floyd-Warshall algorithm is O(n^3), where n is the number of vertices.

Space Complexity:

    The code performs the calculations in-place, meaning it doesn't use additional data structures that depend on the size of the input graph. Therefore, the space complexity is O(1).

Hint:

    The code efficiently calculates the shortest distances between all pairs of vertices in a weighted directed graph using the Floyd-Warshall algorithm. It updates the adjacency matrix with the shortest distances as it iterates through all possible paths.
 */
void shortest_distance(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    for (int via = 0; via < n; via++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][via] == -1 or matrix[via][j] == -1)
                    continue;

                int part = matrix[i][via] + matrix[via][j];

                if (matrix[i][j] == -1)
                    matrix[i][j] = part;
                else
                    matrix[i][j] = min(matrix[i][j], part);
            }
}

//^ 33 Find the city with the smallest number of neighbors in a threshold distance
/*
    Initialize Matrix: A 2D matrix mat of size n x n is created and initialized with a large value (1e9) for all pairs of cities. This matrix will store the shortest distances between cities.

    Edge Weights: For each edge in the edges vector, the corresponding entry in the mat matrix is updated with the edge weight. Since the edges are bidirectional, entries in both directions are updated.

    Diagonal Elements: The diagonal elements of the mat matrix, representing the distance from a city to itself, are set to 0.

    Floyd-Warshall Algorithm: The Floyd-Warshall algorithm is applied to find the shortest distances between all pairs of cities. This algorithm iteratively updates the distances in the mat matrix by considering each city as an intermediate stop between any two cities.

    Count Reachable Cities: For each city i, the code counts the number of cities that can be reached from city i within the given distance threshold. This is done by iterating through all cities j and checking if the distance from city i to city j in the mat matrix is less than or equal to the distanceThreshold.

    Find the City: The code keeps track of the city ans that has the smallest number of reachable cities within the distance threshold. If multiple cities have the same minimum number of reachable cities, the code selects the one with the greatest city number.

    Return Result: Finally, the code returns the city ans, which represents the city with the smallest number of reachable cities within the distance threshold.

Time Complexity:

    The time complexity of the Floyd-Warshall algorithm is O(n^3), where n is the number of cities.
    The outer loop iterates n times, and for each iteration, there are two nested loops that iterate n times each, resulting in a total of O(n^3) operations.

Space Complexity:

    The space complexity is O(n^2) due to the mat matrix, which stores the shortest distances between all pairs of cities.

Hint:

    The code uses the Floyd-Warshall algorithm to calculate the shortest distances between all pairs of cities efficiently.
    It then counts the number of reachable cities from each city within the given distance threshold and selects the city with the smallest number of reachable cities.
 */
int findCity(int n, int m, vector<vector<int>> &edges,
             int distanceThreshold)
{
    //^ Floyd warshall algo
    vector<vector<int>> mat(n, vector<int>(n, 1e9));
    for (auto it : edges)
    {
        mat[it[0]][it[1]] = it[2];
        mat[it[1]][it[0]] = it[2];
    }
    for (int i = 0; i < n; i++)
    {
        mat[i][i] = 0;
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
            }
        }
    }

    int ans;
    int mini = 1e9;
    for (int i = 0; i < n; i++)
    {
        int reach = 0;
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] <= distanceThreshold)
            {
                reach++;
            }
        }
        if (reach <= mini)
        {
            mini = reach;
            ans = i;
        }
    }

    return ans;
}

//^ 34 Prims algorithm for Minimum Spanning Tree
/*
Intuition:

The problem can be solved using Prim's algorithm, which is a greedy algorithm for finding the Minimum Spanning Tree (MST) of a connected, undirected graph.

Explanation:

    Create a priority queue pq to keep track of edges, where each element in the queue is a pair (weight, node).

    Initialize a boolean vector visit of size V to keep track of visited nodes. Initially, all nodes are unvisited.

    Initialize a variable ans to 0. This variable will store the sum of weights of the edges in the MST.

    Start with an arbitrary node as the initial node (e.g., node 0), and push it into the priority queue with a weight of 0: pq.push({0, 0}).

    While the priority queue is not empty, do the following:

        Pop the top element p from the priority queue.

        Extract the node x and weight w from p.

        If x is already visited, continue to the next iteration.

        Mark node x as visited: visit[x] = true.

        Add the weight w to the ans as this weight is part of the MST.

        Iterate through all adjacent nodes of x in the adjacency list adj[x]. For each adjacent node y with weight edgeWeight, if y is not visited, push {edgeWeight, y} into the priority queue. This step considers adding edges to the MST.

    After the loop, ans will contain the sum of weights of the edges in the MST.

    Return ans as the final result.

Time Complexity:

    The time complexity of Prim's algorithm with a priority queue is O(E * log(V)), where E is the number of edges and V is the number of vertices.

Space Complexity:

    The space complexity is O(V) for the visit array and O(E) for the priority queue.

Hint:

    Use a priority queue to select the edge with the smallest weight at each step.

    Maintain a visit array to keep track of visited nodes.

    Add the weights of selected edges to the ans variable to calculate the MST weight.
 */
int spanningTree(int V, vector<vector<int>> adj[])
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    vector<bool> visit(V);
    int ans = 0;
    while (!pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        int x = p.second; // node
        int w = p.first;  // weight
        if (visit[x])
            continue; // already visited means we have reached here using less amount of weight sum
        visit[x] = true;
        ans += w; // add weight to the MST sum
        for (auto y : adj[x])
        {
            if (!visit[y[0]])
            {
                pq.push({y[1], y[0]}); // add all nodes in the priority queue which are not visited yet
            }
        }
    }
    return ans;
}

//^ 35 Disjoint set data structure
/*
Data Structures Used:

rank: A vector that stores the rank of each element in the disjoint set. Rank is used to perform a union operation more efficiently by attaching the smaller tree to the larger tree to keep the tree balanced.
parent: A vector that stores the parent (representative) of each element in the disjoint set. Initially, each element is its own parent, representing a disjoint set with only one element.

Constructor:

The constructor initializes the Disjoint-Set data structure with 'n' elements. It allocates memory for the rank and parent vectors, sets each element's parent to itself, and initializes the rank to 0 for all elements.
findUPar Function:

This function is used to find the ultimate parent (representative) of a given element 'node' using the path compression technique. It starts from the given 'node' and traverses the parent pointers until it reaches the ultimate parent. Along the way, it updates the parent of each traversed node to the ultimate parent. This optimization flattens the tree structure and speeds up future findUPar operations. The time complexity of this operation is nearly O(1) on average due to path compression.
unionByRank Function:

This function is used to perform the union of two sets represented by 'u' and 'v'. It first finds the ultimate parent of both 'u' and 'v' using findUPar. Then, it compares their ranks. If the rank of 'u's ultimate parent is less than the rank of 'v's ultimate parent, it attaches 'u' to 'v'. If the rank of 'v's ultimate parent is less than the rank of 'u's ultimate parent, it attaches 'v' to 'u'. If both ranks are the same, one tree is attached to the other, and the rank of the ultimate parent is increased by 1. This union-by-rank and path compression strategy ensures that the tree remains balanced, and the time complexity of this operation is nearly O(1) on average.
Time Complexity:

findUPar: Nearly O(1) on average due to path compression.
unionByRank: Nearly O(1) on average due to union by rank and path compression.

Space Complexity:

The space complexity is O(n) for the rank and parent vectors, where 'n' is the number of elements in the disjoint set.

This Disjoint-Set data structure is efficient for managing disjoint sets and performing union and find operations. It is commonly used in various algorithms like Kruskal's Minimum Spanning Tree algorithm and cycle detection in graphs, among others.
*/
class DisjointSet
{
private:
public:
    vector<int> rank, parent, size;
    DisjointSet(int n)
    {
        rank.resize(n + 1);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i < n + 1; i++)
        {
            parent.at(i) = i;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (rank.at(ultimateParentU) < rank.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
        }
        else if (rank.at(ultimateParentV) < rank.at(ultimateParentU))
        {
            parent[ultimateParentV] = ultimateParentU;
        }
        else
        {
            parent.at(ultimateParentV) = parent.at(ultimateParentU);
            rank.at(ultimateParentU)++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (size.at(ultimateParentU) < size.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
            size.at(ultimateParentV) += size.at(ultimateParentU);
        }
        else
        {
            parent.at(ultimateParentV) = parent.at(ultimateParentU);
            size.at(ultimateParentU) += size.at(ultimateParentV);
        }
    }
};

//^ 36 Kruskals algorithm
class Kruskal
{
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++)
        {
            for (auto &it : adj[i])
            {
                int v = it[0];
                int wt = it[1];
                edges.push_back({wt, {i, v}});
            }
        }
        sort(edges.begin(), edges.end());
        int mstWeight;
        DisjointSet ds(V);
        for (auto &it : edges)
        {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            if (ds.findUPar(u) != ds.findUPar(v))
            {
                mstWeight += wt;
                ds.unionByRank(u, v);
            }
        }
        return mstWeight;
    }
};
//^ 37 Number of Operations to make network connected
/*
Intuition:

The problem is to find the minimum number of operations required to make all computers connected in a network. We can solve this problem using the concept of disjoint sets (also known as a union-find data structure).

Explanation:

    Create a DisjointSet object ds with n nodes. Each node represents a computer, and initially, each computer is in its own component.

    Initialize a variable extraEdges to 0. This variable will keep track of the number of extra cables that are not needed.

    Iterate through each connection in the connections vector:

        Check if the computers at both ends of the connection (it.front() and it.back()) are already in the same component. If they are, it means adding this connection would create a cycle, so increment extraEdges.

        Otherwise, perform a union operation to merge the components of the two computers using ds.unionBySize(it[0], it[1]).

    After processing all connections, initialize a variable numberOfComponents to 0. This variable will keep track of the number of components in the network.

    Iterate through all nodes (computers) from 0 to n-1. For each node i, check if it is the parent of itself in the disjoint set. If it is, increment numberOfComponents.

    Now, we have the following information:

        extraEdges: The number of extra cables.

        numberOfComponents: The number of components in the network.

    To connect all computers, we need at least numberOfComponents - 1 cables. If extraEdges is greater than or equal to numberOfComponents - 1, it means we have enough extra cables to connect all components. In this case, return numberOfComponents - 1 as the minimum number of operations required.

    If extraEdges is less than numberOfComponents - 1, it means we don't have enough extra cables to connect all components, and it's impossible to make all computers connected. Return -1 in this case.

Time Complexity:

    The time complexity of the union-find operations (union and find) is typically O(log n) on average, where n is the number of nodes (computers). In the worst case, it can be O(n) for a find operation, but this is rare.

    The loop that iterates through the connections has a time complexity of O(E), where E is the number of connections.

    The loop that counts the number of components has a time complexity of O(n).

    Overall, the time complexity of the algorithm is dominated by the union-find operations, so it is approximately O(E * log n).

Space Complexity:

    The space complexity is O(n) for the DisjointSet object, as it stores the parent and size arrays for each node.

Hint:

    Use a disjoint-set data structure (union-find) to keep track of connected components.

    Calculate the number of extra edges that are not needed.

    Calculate the number of connected components in the network.

    Determine if it's possible to connect all computers by comparing the number of extra edges with the number of components.

 */
int makeConnected(int n, vector<vector<int>> &connections)
{
    DisjointSet ds(n);
    int extraEdges = 0;
    for (auto &it : connections)
    {
        if (ds.findUPar(it.front()) == ds.findUPar(it.back()))
            extraEdges++;
        else
            ds.unionBySize(it[0], it[1]);
    }
    int numberOfComponents = 0;
    for (int i = 0; i < n; i++)
    {
        if (ds.parent[i] == i)
            numberOfComponents++;
    }
    return (extraEdges >= numberOfComponents - 1) ? numberOfComponents - 1 : -1;
}

//^ 38 Accounts Merge
/*
Intuition:

The problem is to merge accounts of the same person based on their emails. We can use a disjoint set (union-find) data structure to group accounts belonging to the same person. Here's the general approach:

    Create a DisjointSet object ds with n nodes, where n is the number of accounts. Each node represents an account.

    Sort the details vector lexicographically. This step is essential to ensure that we process accounts with the same name consecutively.

    Initialize an unordered map mapMailNode to keep track of the mapping from emails to their corresponding account node. We will use this map to quickly find the account to which an email belongs.

    Iterate through each account in the details vector:

        For each account, iterate through its emails starting from the second element (index 1).

        Check if the email is already in mapMailNode. If it's not, add it to the map with the corresponding account node index. If it's already in the map, it means this email belongs to multiple accounts. In this case, perform a union operation between the current account node and the account node associated with this email using ds.unionBySize(i, mapMailNode[mail]).

    After processing all accounts and merging them based on emails, create a vector of vectors called mergedMail. Each inner vector represents a group of merged emails belonging to the same person. We use the disjoint set data structure to find the parent (representative) node for each group of emails.

    Create a vector of vectors called ans to store the final merged accounts.

    Iterate through the mapMailNode map:

        For each email, find its corresponding account node using ds.findUPar(it.second).

        Append the email to the mergedMail vector corresponding to the representative account node.

    Finally, iterate through the mergedMail vector:

        Sort the emails lexicographically for each group.

        Create a temporary vector temp to store the merged account details, starting with the account name (details[i][0]) followed by the sorted emails.

        Append the temp vector to the ans vector.

    Sort the ans vector lexicographically based on the first element (account name).

    Return the ans vector as the result.

Time Complexity:

    The time complexity is dominated by the union-find operations (union and find) performed during the processing of accounts, which is approximately O(N * log N), where N is the total number of emails.

    Sorting the ans vector takes O(M * log M) time, where M is the total number of accounts. However, M is bounded by N, so the overall time complexity remains O(N * log N).

Space Complexity:

    The space complexity is O(N) for the DisjointSet object and the mapMailNode unordered map, where N is the number of accounts.

    The mergedMail and ans vectors also contribute to the space complexity, but they are bounded by the number of emails, so they do not dominate the space complexity.

Hint:

    Use a disjoint-set data structure to group accounts based on their emails.

    Sort the accounts lexicographically to ensure that accounts with the same name are processed together.

    Keep a map of email-to-account-node mapping to efficiently find the account node for each email.

    After merging accounts, iterate through the merged groups of emails and sort them before creating the final merged accounts.
 */
vector<vector<string>> accountsMerge(vector<vector<string>> &details)
{
    int n = details.size();
    DisjointSet ds(n);
    sort(details.begin(), details.end());
    unordered_map<string, int> mapMailNode;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < details[i].size(); j++)
        {
            string mail = details[i][j];
            if (mapMailNode.find(mail) == mapMailNode.end())
            {
                mapMailNode[mail] = i;
            }
            else
            {
                ds.unionBySize(i, mapMailNode[mail]);
            }
        }
    }

    vector<string> mergedMail[n];
    for (auto it : mapMailNode)
    {
        string mail = it.first;
        int node = ds.findUPar(it.second);
        mergedMail[node].push_back(mail);
    }

    vector<vector<string>> ans;

    for (int i = 0; i < n; i++)
    {
        if (mergedMail[i].size() == 0)
            continue;
        sort(mergedMail[i].begin(), mergedMail[i].end());
        vector<string> temp;
        temp.push_back(details[i][0]);
        for (auto it : mergedMail[i])
        {
            temp.push_back(it);
        }
        ans.push_back(temp);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

//^ 39 Number of Islands 2
class NumberOfIslands2
{
private:
    /*
    Intuition:

The problem is about simulating the process of adding islands (changing 0 to 1) in a grid and counting the number of connected islands after each addition. We can solve this problem using a disjoint-set (union-find) data structure to keep track of connected components (islands).

Here's the general approach:

    Define a vector dirs representing the four possible directions to adjacent cells: up, right, down, and left.

    Create a function getCellNumber to calculate the unique cell number based on the row, column, and total number of columns. This function is useful for mapping grid coordinates to a unique index for the disjoint-set data structure.

    Create a function inbound to check if a given row and column are within the bounds of the grid.

    Initialize a DisjointSet object ds with n * m nodes, where n is the number of rows and m is the number of columns. Each node represents a cell in the grid.

    Initialize a variable islands to keep track of the number of islands.

    Create an empty vector ans to store the answers for each operation.

    Create a 2D vector visited of size n x m to keep track of visited cells.

    Iterate through the operations (operators) provided as input:

        For each operator, extract the row and column coordinates.

        Check if the cell is already visited. If it is, append the current islands count to the ans vector and continue to the next operation.

        Mark the cell as visited.

        Increment the islands count since a new island is being added.

        Iterate through the four directions to check adjacent cells:

            Calculate the new row and column coordinates based on the direction.

            Check if the new coordinates are within the bounds of the grid (inbound function).

            If the adjacent cell is visited, perform a union operation using the DisjointSet object ds. This operation checks if the current cell and the adjacent cell belong to different islands. If they do, it merges them and decreases the islands count.

        Append the current islands count to the ans vector after processing the operation.

    After processing all operations, return the ans vector, which contains the number of islands after each operation.

Time Complexity:

    The time complexity is dominated by the union-find operations (union and find) performed during the processing of operations, which is approximately O(K * log(N * M)), where K is the number of operations, and N and M are the number of rows and columns in the grid.

Space Complexity:

    The space complexity is O(N * M) for the visited matrix and O(N * M) for the disjoint-set data structure.

Hint:

    Use a disjoint-set (union-find) data structure to keep track of connected islands.

    Mark visited cells to avoid double counting when adding new islands.

    Iterate through adjacent cells to check and merge islands when necessary.
     */
    vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int getCellNumber(int row, int col, int totalCols)
    {
        return (totalCols * row) + col;
    }
    bool inbound(int row, int col, int n, int m)
    {
        return row >= 0 && row < n && col >= 0 && col < m;
    }
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators)
    {
        // code here
        DisjointSet ds(n * m);
        int islands = 0;
        vector<int> ans;
        vector<vector<bool>> visited(n, vector<bool>(m));
        for (auto &it : operators)
        {
            int row = it.front();
            int col = it.back();
            if (visited[row][col])
            {
                ans.push_back(islands);
                continue;
            }
            visited[row][col] = true;
            islands++;
            for (auto &dir : dirs)
            {
                int nrow = row + dir.first;
                int ncol = col + dir.second;
                if (inbound(nrow, ncol, n, m) && visited[nrow][ncol])
                {
                    if (ds.findUPar(getCellNumber(row, col, m)) != ds.findUPar(getCellNumber(nrow, ncol, m)))
                    {
                        islands--;
                        ds.unionBySize(getCellNumber(row, col, m), getCellNumber(nrow, ncol, m));
                    }
                }
            }
            ans.push_back(islands);
        }
        return ans;
    }
};

//^ 40 Maximum stone removals
/* 
Intuition:

The problem is essentially asking how many stones can be removed while ensuring that there is at least one stone remaining in each row and each column. We can solve this problem using a disjoint-set (union-find) data structure to keep track of connected stones in both rows and columns.

Here's the general approach:

    Iterate through the given stones vector to find the maximum row index (maxRow) and maximum column index (maxCol). This information will help us map row and column indices into a single range.

    Initialize a DisjointSet object ds with the size of maxRow + maxCol + 1. This size is used to represent both rows and columns as disjoint sets. Each node in the disjoint-set corresponds to a row or column.

    Create an unordered set stoneNodes to keep track of nodes (rows and columns) where stones are placed.

    Iterate through the stones vector:

        For each stone, calculate its corresponding node index for the row (nodeRow) and column (nodeCol) by adding appropriate offsets (maxRow + 1 for columns).

        Use the DisjointSet object ds to perform a union operation between nodeRow and nodeCol. This operation connects the stone's row and column.

        Add nodeRow and nodeCol to the stoneNodes set to mark them as nodes with stones.

    Initialize a counter cnt to 0, which will be used to count the number of components (rows or columns) with stones that are not removed.

    Iterate through the elements in the stoneNodes set:
        For each node, check if it is the representative (parent) of its disjoint set. If it is, increment cnt. The representative nodes represent rows or columns with stones that cannot be removed.

    Calculate the maximum possible number of removed stones as n - cnt. This is because for each component with stones (either rows or columns), we can keep one stone, and all other stones in that component can be removed.

    Return the maximum possible number of removed stones.

Time Complexity:

    The time complexity is dominated by the union-find operations (union and find) performed during the processing of stones, which is approximately O(N * α(N)), where N is the number of stones, and α(N) is the inverse Ackermann function, a very slow-growing function.

Space Complexity:

    The space complexity is O(N) for storing the stone nodes and O(maxRow + maxCol) for the disjoint-set data structure.

Hint:

    Use a disjoint-set (union-find) data structure to connect stones in both rows and columns.

    Count the number of connected components (representatives) that cannot be removed, and subtract it from the total number of stones to get the maximum possible number of removed stones.
 */
int maxRemove(vector<vector<int>> &stones, int n)
{
    int maxRow = 0, maxCol = 0;
    for (auto &it : stones)
    {
        maxRow = max(maxRow, it.front());
        maxCol = max(maxCol, it.back());
    }
    DisjointSet ds(maxRow + maxCol + 1);
    unordered_set<int> stoneNodes;
    for (int i = 0; i < n; i++)
    {
        int nodeRow = stones[i][0];
        int nodeCol = stones[i][1] + maxRow + 1;
        ds.unionBySize(nodeRow, nodeCol);
        stoneNodes.insert(nodeRow);
        stoneNodes.insert(nodeCol);
    }
    int cnt = 0;
    for (auto &it : stoneNodes)
    {
        if (ds.findUPar(it) == it)
            cnt++;
    }
    return n - cnt;
}

//^ 41 Kosharaju Algorithm
class Kosharaju{
    private:
    /* 
    Intuition:

This problem can be solved using Kosaraju's algorithm, which is a two-pass algorithm to find strongly connected components (SCCs) in a directed graph.

Here's how the algorithm works:

    First, perform a Depth-First Search (DFS) on the original graph and push nodes onto a stack in the order they finish processing (i.e., after exploring all of their descendants). This stack will contain the nodes in reverse topological order. We call this stack s.

    Reverse the directions of all edges in the graph to create a reversed graph. This can be done by iterating through each node in the original graph and reversing its edges. We call this reversed graph adjReverse.

    Initialize a count for strongly connected components (stronglyConnectedComponents) to 0.

    While the stack s is not empty:

        Pop a node from the stack s. If it has not been visited in the reversed graph:

            Perform a DFS from this node in the reversed graph, marking all reachable nodes as visited.

            Increment the stronglyConnectedComponents count by 1. This represents a new strongly connected component.

    Return the stronglyConnectedComponents count, which represents the number of SCCs in the graph.

Time Complexity:

    The time complexity is O(V + E), where V is the number of vertices (nodes) and E is the number of edges in the graph. Both the DFS passes take linear time in terms of the number of nodes and edges.

Space Complexity:

    The space complexity is O(V + E) to store the graph and adjacency lists, and O(V) for the vis array and the stack.

Hint:

    Use two DFS passes: one on the original graph to fill the stack, and another on the reversed graph to count SCCs.

    Pay attention to the order of processing nodes in the stack to ensure reverse topological order.
     */
    public:
	//Function to find number of strongly connected components in the graph.
	void DFS(int src,vector<vector<int>> &adj,vector<bool> &vis,stack<int> &s){
	    vis.at(src) = true;
	    for(auto &it : adj[src]){
	        if(!vis.at(it)){
	            DFS(it,adj,vis,s);
	        }
	    }
	    s.push(src);
	}
	
	void reverseDFS(int src,vector<vector<int>> &adj,vector<bool> &vis){
	    vis.at(src) = true;
	    for(auto &it : adj[src]){
	        if(!vis.at(it)){
	            reverseDFS(it,adj,vis);
	        }
	    }
	}
	
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //code here
        vector<bool> vis(V);
        stack<int> s;
        for(int i = 0; i < V; i++){
            if(!vis.at(i)){
                DFS(i,adj,vis,s);
            }
        }
        
        // reverse the graph
        vector<vector<int>> adjReverse(V);
        for(int i = 0; i < V; i++){
            vis[i] = false;
            for(auto &it : adj[i]){
                adjReverse[it].push_back(i); // directed graph
            }
        }
        
        int stronglyConnectedComponents = 0;
        while(!s.empty()){
            int node = s.top(); s.pop();
            if(!vis[node]){
                reverseDFS(node,adjReverse,vis);
                stronglyConnectedComponents++;
            }
        }
        return stronglyConnectedComponents;
        

    }
};

//^ 42 Tarjans Algorithmas
class Tarjans{
    private:    
    /* 
    Intuition:

This problem can be solved using Tarjan's algorithm for finding bridges in an undirected graph. A bridge is an edge in the graph such that if it is removed, the graph becomes disconnected or has an increase in the number of connected components.

Here's how the algorithm works:

    Perform a Depth-First Search (DFS) on the graph to find bridges. During the DFS traversal, maintain two arrays tin and low for each node. tin represents the time of entry for each node in the DFS traversal, and low represents the lowest tin value that can be reached from that node.

    Initialize a timer variable timer to 1 and increment it at each step to record the entry time.

    When exploring an edge (u, v) from node u to node v, do the following:

        If v is the parent of u, continue to the next iteration (skip the back edge).

        If v is not visited (vis[v] == 0), recursively call DFS on v and update low[u] with min(low[u], low[v]).

        If v is visited (vis[v] == 1), update low[u] with min(low[u], tin[v]).

        If low[v] is greater than tin[u], it means the edge (u, v) is a bridge, so add it to the bridges vector.

    After the DFS traversal, the bridges vector contains all the critical connections (bridges) in the graph.

Time Complexity:

    The time complexity is O(V + E), where V is the number of vertices (nodes) and E is the number of edges in the graph. Both the DFS pass and the bridge finding step take linear time in terms of the number of nodes and edges.

Space Complexity:

    The space complexity is O(V + E) to store the graph and adjacency lists, and O(V) for the vis, tin, and low arrays.

Hint:

    Maintain an additional array vis to keep track of the visited status of nodes (0 for unvisited, 1 for visiting, 2 for visited).

    Bridges are edges where low[v] > tin[u], where u and v are the nodes connected by the edge (u, v).

    Use Tarjan's algorithm to find bridges efficiently.
     */
    public:
    int timer = 1;
    void dfs(int node, int parent, vector<int> &vis,
             vector<int> adj[], int tin[], int low[], vector<vector<int>> &bridges) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer++;
        for (auto it : adj[node]) {
            if (it == parent) continue;
            if (vis[it] == 0) {
                dfs(it, node, vis, adj, tin, low, bridges);
                low[node] = min(low[it], low[node]);
                // node --- it
                if (low[it] > tin[node]) {
                    bridges.push_back({it, node});
                }
            }
            else {
                low[node] = min(low[node], low[it]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n,
    vector<vector<int>>& connections) {
        vector<int> adj[n];
        for (auto it : connections) {
            int u = it[0], v = it[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> vis(n, 0);
        int tin[n];
        int low[n];
        vector<vector<int>> bridges;
        dfs(0, -1, vis, adj, tin, low, bridges);
        return bridges;
    }
};

//^ 43 Articulation point
class ArticulationPoint{
    private:
    /* 
    
    Intuition:

    Articulation Points: Articulation points are the vertices in a graph whose removal increases the number of connected components in the graph. In other words, these are the critical points where the graph can be split into multiple disconnected parts if the vertex is removed.

    Depth-First Search (DFS): The code uses a depth-first search (DFS) algorithm to traverse the graph and find these articulation points.

Code:

    Depth-First Search (DFS):
        The core of the code is the dfs function, which performs a DFS traversal of the graph.
        It maintains two arrays, tin and low, to keep track of the entry time and the lowest reachable ancestor for each vertex.
        A timer variable is used to record the current time during the DFS traversal.

    DFS on the Graph:
        The code iterates through the vertices in the graph.
        For each vertex, it calls the dfs function. The dfs function explores the neighbors of the current vertex and determines if it's an articulation point based on the properties of tin and low.

    Articulation Point Detection:
        The key idea is that if, during the DFS traversal, we find a vertex it such that low[it] is greater than or equal to tin[src], it means that there is no back edge from the subtree rooted at it to any ancestor of src other than its immediate parent. In this case, src is marked as an articulation point.

    Counting Children:
        Additionally, the code keeps track of the number of children each vertex has. If a vertex is the root of the DFS tree (i.e., parent == -1) and has more than one child, it is also marked as an articulation point because removing the root will disconnect the children.

    Output:
        The code compiles a list of articulation points and returns them as a vector. If no articulation points are found, it returns a vector with a single element containing -1.

Time Complexity:

    The time complexity of this code is O(V + E), where V is the number of vertices, and E is the number of edges in the graph. This is because the DFS traversal visits each vertex and each edge once.

Space Complexity:

    The space complexity is O(V) to store the tin, low, mark, and vis arrays. This is because we need arrays of size V to keep track of information about each vertex.

Hints:

    DFS: The code uses a depth-first search to explore the graph. It starts from a vertex and traverses as deeply as possible before backtracking.
    Lowest Reachable Ancestor: The low array keeps track of the lowest reachable ancestor for each vertex. This is crucial for detecting articulation points.
    Tree Roots: If a vertex is th
    
     */
  public:
    int timer = 0;
    void dfs(int src,int parent,vector<int> adj[],vector<int> &tin,vector<int> &low,vector<bool> &mark,vector<bool> &vis){
        vis.at(src) = true;
        tin.at(src) = low.at(src) = timer++;
        int children = 0;
        for(auto &it : adj[src]){
            if(parent == it) continue;
            if(!vis[it]){
                dfs(it,src,adj,tin,low,mark,vis);
                low.at(src) = min(low.at(src),low.at(it));
                if(low.at(it) >= tin.at(src) && parent != -1){
                    mark[src] = true;
                }
                children++;
            }
            else{
                low.at(src) = min(low.at(src) , tin.at(it));
            }
        }
        if(children > 1 && parent == -1){
            mark.at(src) = true;
        }
    }
    vector<int> articulationPoints(int V, vector<int>adj[]) {
        // Code here
        vector<bool> vis(V),mark(V);
        vector<int> tin(V),low(V);
        for(int i = 0; i < V; i++){
            if(!vis.at(i)){
                dfs(i,-1,adj,tin,low,mark,vis);
            }
        }
        
        vector<int> ans;
        for(int i = 0; i < mark.size(); i++){
        
            if(mark.at(i)){
                ans.push_back(i);
            }
        }
        if(ans.empty()) return {-1};
        return ans;
    }
};
int main()
{
    return 0;
}