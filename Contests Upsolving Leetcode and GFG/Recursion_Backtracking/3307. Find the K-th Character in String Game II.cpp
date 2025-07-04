#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
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
static int init = []()
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
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.

Now Bob will ask Alice to perform all operations in sequence:

    If operations[i] == 0, append a copy of word to itself.
    If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".

Return the value of the kth character in word after performing all the operations.

Note that the character 'z' can be changed to 'a' in the second type of operation.



Example 1:

Input: k = 5, operations = [0,0,0]

Output: "a"

Explanation:

Initially, word == "a". Alice performs the three operations as follows:

    Appends "a" to "a", word becomes "aa".
    Appends "aa" to "aa", word becomes "aaaa".
    Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".

Example 2:

Input: k = 10, operations = [0,1,0,1]

Output: "b"

Explanation:

Initially, word == "a". Alice performs the four operations as follows:

    Appends "a" to "a", word becomes "aa".
    Appends "bb" to "aa", word becomes "aabb".
    Appends "aabb" to "aabb", word becomes "aabbaabb".
    Appends "bbccbbcc" to "aabbaabb", word becomes "aabbaabbbbccbbcc".

    Approach:
    &- The problem can be solved using recursion. The key idea is to keep track of the length of the string after each operation and determine which operation affects the k-th character.

    &- The base case is when k == 1, in which case the answer is 'a'.
    &- For each operation, we double the length of the string. If the current length is greater than or equal to k, we determine which operation type was applied and recursively find the k-th character in the modified string.
    &- If the operation type is 0, we return the character as it is.
    &- If the operation type is 1, we generate the next character in the English alphabet and recursively find the k-th character in the modified string.

     */
public:
    char kthCharacter(long long k, vector<int> &operations, int operationType = -1)
    {
        if (k == 1)
            return 'a';
        const int n = operations.size();
        int _operationType = -1;
        ll length = 1;
        for (int i = 0; i < n; i++)
        {
            length *= 2;
            if (length >= k)
            {
                _operationType = operations[i];
                break;
            }
        }
        char ch = kthCharacter(k - (length / 2), operations, _operationType);
        if (_operationType == 0)
        {
            return ch;
        }
        if (ch == 'z')
            return 'a';
        return ch + 1;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    return 0;
}
#endif