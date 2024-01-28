#include <bits/stdc++.h>
using namespace std;

class BruteForce
{
private:
public:
    // Function to calculate the sum of a submatrix
    int sumOfSubMatrix(vector<vector<int>> &matrix, int rowStart, int rowSize, int colStart, int colSize)
    {
        int subMatrixSum = 0; // Initialize the sum of the submatrix
        // Iterate over the rows of the submatrix
        for (int i = rowStart; i < rowStart + rowSize; i++)
        {
            // Iterate over the columns of the submatrix
            for (int j = colStart; j < colStart + colSize; j++)
            {
                // Add the current element to the sum of the submatrix
                subMatrixSum += matrix[i][j];
            }
        }
        // Return the sum of the submatrix
        return subMatrixSum;
    }

    // Function to calculate the number of submatrices that sum to the target
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        int ans = 0;              // Initialize the answer
        int m = matrix.size();    // Get the number of rows in the matrix
        int n = matrix[0].size(); // Get the number of columns in the matrix

        // Iterate over the possible starting rows of the submatrix
        for (int rowStart = 0; rowStart < m; rowStart++)
        {
            // Iterate over the possible sizes of the submatrix in terms of rows
            for (int rowSize = 1; rowStart + rowSize <= m; rowSize++)
            {
                // Iterate over the possible starting columns of the submatrix
                for (int colStart = 0; colStart < n; colStart++)
                {
                    // Iterate over the possible sizes of the submatrix in terms of columns
                    for (int colSize = 1; colStart + colSize <= n; colSize++)
                    {
                        // If the sum of the current submatrix is equal to the target
                        if (sumOfSubMatrix(matrix, rowStart, rowSize, colStart, colSize) == target)
                            ans++; // Increment the answer
                    }
                }
            }
        }
        // Return the answer
        return ans;
    }
};

class BetterApproach
{
public:
    //! O((N*N*M*M)) time and O(N*M) space
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        int ans = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> prefixSum(m, vector<int>(n));

        for (int i = 0; i < m; i++)
        {
            partial_sum(matrix[i].begin(), matrix[i].end(), prefixSum[i].begin());
        }

        for (int colStart = 0; colStart < n; colStart++)
        {
            for (int colEnd = colStart; colEnd < n; colEnd++)
            {
                for (int rowStart = 0; rowStart < m; rowStart++)
                {
                    int sum = 0;
                    for (int rowEnd = rowStart; rowEnd < m; rowEnd++)
                    {
                        sum += prefixSum[rowEnd][colEnd] - (colStart > 0 ? prefixSum[rowEnd][colStart - 1] : 0);
                        ans += (sum == target ? 1 : 0);
                    }
                }
            }
        }
        return ans;
    }
    //* O((N*M*M)) time and O(N*M) space
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
    {
        // Initialize the answer
        int ans = 0;

        // Get the number of rows in the matrix
        int m = matrix.size();

        // Get the number of columns in the matrix
        int n = matrix[0].size();

        // Iterate over the rows of the matrix
        for (int i = 0; i < m; i++)
        {
            // Initialize a vector to store the sums of the elements in the columns
            vector<int> sums(n, 0);

            // Iterate over the rows from the current row to the last row
            for (int j = i; j < m; j++)
            {
                // Update the sums of the elements in the columns
                for (int k = 0; k < n; k++)
                {
                    sums[k] += matrix[j][k];
                }

                // Initialize the sum of the elements in the current submatrix
                int sum = 0;

                // Initialize a map to store the sums of the elements in the submatrices and their frequencies
                unordered_map<int, int> mp;

                // The sum of the elements in an empty submatrix is 0
                mp[0] = 1;

                // Iterate over the sums of the elements in the columns
                for (int k = 0; k < n; k++)
                {
                    // Update the sum of the elements in the current submatrix
                    sum += sums[k];

                    // If there is a submatrix whose sum of elements is equal to the difference between the sum of the elements in the current submatrix and the target
                    if (mp.find(sum - target) != mp.end())
                    {
                        // Add the frequency of the sum of the elements in the submatrix to the answer
                        ans += mp[sum - target];
                    }

                    // Increment the frequency of the sum of the elements in the current submatrix
                    mp[sum]++;
                }
            }
        }

        // Return the answer
        return ans;
    }
};

int main()
{
    return 0;
}