#include <bits/stdc++.h>
using namespace std;

int minOperations(vector<int> &nums, int k)
{
    // Calculate the XOR value of all the numbers in the vector
    int xorVal = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        xorVal ^= nums[i];
    }

    // Convert the XOR value and the target value to bitsets
    bitset<32> b1(xorVal);
    bitset<32> b2(k);

    // Count the number of differing bits between the two bitsets
    int operations = 0;
    for (int i = 0; i < 32; i++)
    {
        if (b1[i] != b2[i])
        {
            operations++;
        }
    }

    // Return the number of differing bits, which represents the minimum number of operations needed
    return operations;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}