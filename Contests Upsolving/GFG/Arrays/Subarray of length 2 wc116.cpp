#include <bits/stdc++.h>
using namespace std;

/* 
Intuition

As the problem statement state we can select any subarray of length 2 and multiply all elements of that subarray by -1 that means if the array has even number of negative elements then we can make all array positive else if the array has odd number of negative elements then, in that case, we can make all elements positive except one element but if there is an element with value zero in the array then we can shift negative at zero in that case also all elements of array become positive else only one element left negative, so can make that element negative whose contribution of all subarrays will be less and then calculate the sum of all possible subarrays.
Implementation

    Initialize ans with 0 variable which keeps track of maximum sum and ct stores the number of negative elements in the array.
    Initialize mx variable with -1 which keeps track of which elements has minimum contribution in all subarrays sum and ok variable which indicates whether zero value is present in the array or not.
    Now Run a loop over the array.
        Calculate the ith elements contribution in all subarrays sum, As we know the number of subarrays formed by ith elements is (i+1)*(N-i), multiply this value with A[i] and store into a variable x which is the total contribution of A[i] in all possible subarrays. 
        Check if A[i] is equal to zero then mark ok variable true.
        Check if A[i] is less than 0 then increase the ct variable.
        If mx is -1 then initialize mx with abs(x).
        Else update the mx with minimum of mx and abs(x).
        Add abs(x) into the answer.
    Now check if even number of negative elements or if there is 0 in the array then return ans.
    Else there must me one negative element which we have to reduce form the ans, so return ans-2*mx.
 */

long long maxSum(int N, vector<int> A)
{
    long long ans = 0, ct = 0;
    long long mx = -1, ok = 0;
    for (int i = 0; i < N; i++)
    {
        long long x = (i + 1) * 1ll * (N - i);
        x *= A[i];
        if (A[i] == 0)
            ok = 1;
        if (A[i] < 0)
            ct++;
        if (mx == -1)
            mx = abs(x);
        else
            mx = min(mx, abs(x));
        ans += abs(x);
    }
    if (ct % 2 == 0 || ok)
        return ans;
    return ans - 2 * mx;
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