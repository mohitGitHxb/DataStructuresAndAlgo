#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
static int init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
        You are given an m x n binary matrix matrix.

You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).

Return the maximum number of rows that have all values equal after some number of flips.



Example 1:

Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:

Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:

Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.

    @ Observations
    &- The problem is asking for the maximum number of rows that have all values equal after some number of flips
    &- Two rows will have all values equal if they are either equal or inverted
    &- We just need to find the maximum number of pairs of (R1,R2) such that R1 == R2 or R1 == !R2

    * Time Complexity: O(rows*cols) + O(rows*rows)
    * Space Complexity: O(rows) [because we are using bitsets instead of entire vectors]

    @ Another Approach using Hashmap
    &- We can use a hashmap to store the count of each row
    &- Then we can iterate over the hashmap and find the maximum number of pairs of (R1,R2) such that R1 == R2 or R1 == !R2
    &- This approach will have the same time complexity as the previous one but it may use less space

     */
public:
    const int mod = 1e9 + 7;
    int maxEqualRowsAfterFlips(vector<vector<int>> &matrix)
    {

        int rows = matrix.size(), columns = matrix.front().size();
        vector<bitset<300>> rowsBit(rows), invertedRowsBits(rows);
        for (int i = 0; i < rows; i++)
        {
            bitset<300> bit, invertedBit;
            for (int j = 0; j < columns; j++)
            {
                bit[j] = matrix[i][j];
                invertedBit[j] = !matrix[i][j];
            }
            rowsBit.at(i) = bit;
            invertedRowsBits.at(i) = invertedBit;
        }

        int maxRows = 0;
        for (int i = 0; i < rows; i++)
        {
            int count = 0;
            for (int j = 0; j < rows; j++)
                count += (rowsBit.at(i) == rowsBit.at(j) || (invertedRowsBits.at(i) == rowsBit.at(j)));

            maxRows = max(maxRows, count);
        }
        return maxRows;
    }
    int maxEqualRowsAfterFlips_Hashing(vector<vector<int>> &matrix)
    {
        unordered_map<bitset<300>, int, hash<bitset<300>>> mp;
        mp.reserve(matrix.size());
        for (int i = 0; i < matrix.size(); i++)
        {
            bitset<300> pattern;
            for (int j = 0; j < matrix.front().size(); j++)
            {
                pattern[j] = matrix[i][j] ^ matrix[i][0];
            }
            mp[pattern]++;
        }
        int ans(0);
        for (auto &[_, v] : mp)
        {
            ans = max<int>(v, ans);
        }
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
