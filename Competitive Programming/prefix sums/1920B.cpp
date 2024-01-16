#include <bits/stdc++.h>
using namespace std;
/* 
lice and Bob are playing a game. They have an array a1,a2,…,an

. The game consists of two steps:

    First, Alice will remove at most k

elements from the array.
Second, Bob will multiply at most x
elements of the array by −1

    . 

Alice wants to maximize the sum of elements of the array while Bob wants to minimize it. Find the sum of elements of the array after the game if both players play optimally.
Input

Each test consists of multiple test cases. The first line contains a single integer t
(1≤t≤104

) — the number of test cases. The description of the test cases follows.

The first line of each test case contains three integers n
, k, and x (1≤n≤2⋅105, 1≤x,k≤n) — the number of elements in the array, the limit on the number of elements of the array that Alice can remove, and the limit on the number of elements of the array that Bob can multiply −1

to.

The second line of each test case contains n
integers a1,a2,…,an (1≤ai≤1000

) — the elements of the array.

It is guaranteed that the sum of n
over all test cases does not exceed 2⋅105

.
Output

For each test case, output a single integer — the sum of elements of the array after the game if both players play optimally.
Example
Input
Copy

8
1 1 1
1
4 1 1
3 1 2 4
6 6 3
1 4 3 2 5 6
6 6 1
3 7 3 3 32 15
8 5 3
5 5 3 3 3 2 9 9
10 6 4
1 8 2 9 3 3 4 5 3 200
2 2 1
4 3
2 1 2
1 3

Output
Copy

0
2
0
3
-5
-9
0
-1

Note

In the first test case, it is optimal for Alice to remove the only element of the array. Then, the sum of elements of the array is 0

after the game is over.

In the second test case, it is optimal for Alice to not remove any elements. Bob will then multiply 4
by −1. So the final sum of elements of the array is 3+1+2−4=2

.

In the fifth test case, it is optimal for Alice to remove 9,9
. Bob will then multiply 5,5,3 by −1. So the final sum of elements of the array is −5−5−3+3+3+2=−5

.



 */
void solve()
{
    int n, k, x;
    cin >> n >> k >> x;

    int A[n + 1] = {};
    for (int i = 1; i <= n; i++)
        cin >> A[i];

    sort(A + 1, A + n + 1, greater<int>());

    for (int i = 1; i <= n; i++)
        A[i] += A[i - 1];

    int ans = -1e9;
    for (int i = 0; i <= k; i++)
        ans = max(ans, A[n] - 2 * A[min(i + x, n)] + A[i]);

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;

    while (tc--)
        solve();
}