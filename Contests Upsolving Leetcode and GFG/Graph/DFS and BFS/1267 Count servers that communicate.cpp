#include <bits/stdc++.h>
using namespace std;
/*
You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.

Return the number of servers that communicate with any other server.

Explanation

    Row Processing:
        For each row, sum up the servers. If the count exceeds 1, all servers in that row are added to the total. This is because each server in such a row can communicate with others in the same row.
        Rows with multiple servers are marked using a bitset to avoid redundant counting in the column phase.

    Column Processing:
        For each column, count the total servers and track how many were already counted in the row phase (using the marked rows).
        If a column has multiple servers, the difference between the column's total servers and those already counted from rows is added to the total. This captures servers that communicate via the column but weren't part of a multi-server row.

This approach ensures each server is counted once, either through its row or column, leading to an efficient O(m*n) time complexity where m and n are the grid dimensions. The use of a bitset optimizes space for tracking rows.
Share
New
Edit

 */
class Solution
{
public:
    int countServers(const vector<vector<int>> &grid)
    {
        int servers = 0;  // Total communicating servers
        bitset<251> rows; // Tracks rows with multiple servers (max 250 rows)

        // Step 1: Process each row to count servers in rows with multiple servers
        for (int i = 0; i < grid.size(); i++)
        {
            // Sum all servers in current row
            int totalServersInCurrentRow = accumulate(grid.at(i).begin(), grid.at(i).end(), 0);
            if (totalServersInCurrentRow > 1)
            {                                        // Row has multiple servers
                servers += totalServersInCurrentRow; // Add all servers in this row
                rows.set(i);                         // Mark this row as having multiple servers
            }
        }

        // Step 2: Process each column to count servers in columns with multiple servers
        for (int j = 0; j < grid.front().size(); j++)
        {
            int totalServersInCurrentCol = 0; // Total servers in column j
            int alreadyCounted = 0;           // Servers in column j already counted via rows

            for (int i = 0; i < grid.size(); i++)
            {
                if (grid.at(i).at(j))
                { // If there's a server at (i,j)
                    totalServersInCurrentCol++;
                    // Check if this row was already counted (has multiple servers)
                    alreadyCounted += rows[i]; // rows[i] is 1 if row i has multiple
                }
            }

            // If column has multiple servers, add those not counted via rows
            if (totalServersInCurrentCol > 1)
            {
                servers += (totalServersInCurrentCol - alreadyCounted);
            }
        }

        return servers;
    }
};