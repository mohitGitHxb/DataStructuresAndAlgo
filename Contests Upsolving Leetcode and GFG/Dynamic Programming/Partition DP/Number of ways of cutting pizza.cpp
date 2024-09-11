#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

// This stores sub-matrix prefix sum of apple counts from (row, col) to (n-1, m-1)
vector<vector<int>> subMatrixPrefix;
ll dp[51][51][11]; // dp[row][col][k] will store the number of ways to cut pizza from (row, col) with k pieces

// Fills the sub-matrix prefix sums to get the total number of apples in any submatrix
void fillSubMatrixPrefix(const vector<vector<bool>> &pizza)
{
    int n = pizza.size();
    int m = pizza[0].size();
    subMatrixPrefix.resize(n, vector<int>(m));

    // Start with the bottom-right cell
    subMatrixPrefix[n - 1][m - 1] = pizza[n - 1][m - 1];

    // Fill last row (right to left)
    for (int i = m - 2; i >= 0; --i)
    {
        subMatrixPrefix[n - 1][i] = subMatrixPrefix[n - 1][i + 1] + pizza[n - 1][i];
    }

    // Fill last column (bottom to top)
    for (int i = n - 2; i >= 0; --i)
    {
        subMatrixPrefix[i][m - 1] = subMatrixPrefix[i + 1][m - 1] + pizza[i][m - 1];
    }

    // Fill the rest of the sub-matrix prefix sum
    for (int i = n - 2; i >= 0; --i)
    {
        for (int j = m - 2; j >= 0; --j)
        {
            subMatrixPrefix[i][j] = subMatrixPrefix[i + 1][j] + subMatrixPrefix[i][j + 1] - subMatrixPrefix[i + 1][j + 1] + pizza[i][j];
        }
    }
}

// Converts the given pizza grid into a boolean grid indicating where apples exist ('A' -> true, '.' -> false)
vector<vector<bool>> convertToBool(const vector<string> &pizza)
{
    int n = pizza.size();
    int m = pizza[0].size();
    vector<vector<bool>> board(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            board[i][j] = (pizza[i][j] == 'A');
        }
    }
    return board;
}

// Recursively computes the number of ways to cut the pizza starting from (row, col) into k pieces
ll solve(int row, int col, int k, const vector<vector<bool>> &pizza)
{
    // Pruning: If there are fewer apples than required pieces, return 0
    if (subMatrixPrefix[row][col] < k)
        return 0;

    // Base case: If k = 1, check if the current submatrix has at least one apple
    if (k == 1)
        return subMatrixPrefix[row][col] >= 1 ? 1 : 0;

    // Cache check
    if (dp[row][col][k] != -1)
        return dp[row][col][k];

    ll totalWays = 0;

    // Horizontal cuts
    for (int horizontal = row + 1; horizontal < pizza.size(); ++horizontal)
    {
        /* 
        
        &- This is why we pre computed the sub-matrix prefix sum. To check the count of apples in both slices (when cutting) in O(1) time, we can simply subtract the count of apples in the left slice (when cutting horizontally) from the count of apples in the right slice (when cutting vertically).
        
         */
        ll upperSlice = subMatrixPrefix[row][col] - subMatrixPrefix[horizontal][col];
        ll lowerSlice = subMatrixPrefix[horizontal][col];

        if (upperSlice >= 1 && lowerSlice >= (k - 1))
        {
            totalWays = (totalWays + solve(horizontal, col, k - 1, pizza)) % MOD;
        }
    }

    // Vertical cuts
    for (int vertical = col + 1; vertical < pizza[0].size(); ++vertical)
    {
        ll leftSlice = subMatrixPrefix[row][col] - subMatrixPrefix[row][vertical];
        ll rightSlice = subMatrixPrefix[row][vertical];

        if (leftSlice >= 1 && rightSlice >= (k - 1))
        {
            totalWays = (totalWays + solve(row, vertical, k - 1, pizza)) % MOD;
        }
    }

    // Store result in dp table and return
    return dp[row][col][k] = totalWays % MOD;
}

// Main function to calculate the number of ways to cut the pizza into k pieces
int ways(vector<string> &pizza, int k)
{
    // Convert pizza to a boolean matrix indicating where apples are
    vector<vector<bool>> board = convertToBool(pizza);

    // Fill the sub-matrix prefix sum table
    fillSubMatrixPrefix(board);

    // Initialize dp table with -1 for memoization
    memset(dp, -1, sizeof(dp));

    // Solve starting from the top-left corner with k pieces
    return solve(0, 0, k, board);
}

int main()
{
    return 0;
}