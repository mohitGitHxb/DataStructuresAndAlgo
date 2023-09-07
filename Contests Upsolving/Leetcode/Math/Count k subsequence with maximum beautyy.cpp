#include <bits/stdc++.h>
using namespace std;
#define ll long long

/* 
You are given a string s and an integer k.

A k-subsequence is a subsequence of s, having length k, and all its characters are unique, i.e., every character occurs once.

Let f(c) denote the number of times the character c occurs in s.

The beauty of a k-subsequence is the sum of f(c) for every character c in the k-subsequence.

For example, consider s = "abbbdd" and k = 2:

    f('a') = 1, f('b') = 3, f('d') = 2
    Some k-subsequences of s are:
        "abbbdd" -> "ab" having a beauty of f('a') + f('b') = 4
        "abbbdd" -> "ad" having a beauty of f('a') + f('d') = 3
        "abbbdd" -> "bd" having a beauty of f('b') + f('d') = 5

Return an integer denoting the number of k-subsequences whose beauty is the maximum among all k-subsequences. Since the answer may be too large, return it modulo 109 + 7.

A subsequence of a string is a new string formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.

Notes

    f(c) is the number of times a character c occurs in s, not a k-subsequence.
    Two k-subsequences are considered different if one is formed by an index that is not present in the other. So, two k-subsequences may form the same string.

 

Example 1:

Input: s = "bcca", k = 2
Output: 4
Explanation: From s we have f('a') = 1, f('b') = 1, and f('c') = 2.
The k-subsequences of s are: 
bcca having a beauty of f('b') + f('c') = 3 
bcca having a beauty of f('b') + f('c') = 3 
bcca having a beauty of f('b') + f('a') = 2 
bcca having a beauty of f('c') + f('a') = 3
bcca having a beauty of f('c') + f('a') = 3 
There are 4 k-subsequences that have the maximum beauty, 3. 
Hence, the answer is 4. 

Example 2:

Input: s = "abbcd", k = 4
Output: 2
Explanation: From s we have f('a') = 1, f('b') = 2, f('c') = 1, and f('d') = 1. 
The k-subsequences of s are: 
abbcd having a beauty of f('a') + f('b') + f('c') + f('d') = 5
abbcd having a beauty of f('a') + f('b') + f('c') + f('d') = 5 
There are 2 k-subsequences that have the maximum beauty, 5. 
Hence, the answer is 2. 

 */

/* 
Intuition

    Maximum kkk-subsequence is to be formed using kkk unique elements.
    f(c)f(c)f(c) = Sum of all the occurrances of ccc
    Value of the kkk-subsequence is decided by ∑i=1kf(ci)\sum_{i=1}^{k}f(c_i)∑i=1k​f(ci​)
    It's better to choose top kkk characters frequency-wise because it will produce the maximum sum.

How to choose top kkk elements?

    Mantain a priority queue of frequencies.
    Pick them until you reach up kkk.
    Now suppose, you have to pick yyy more elements but there are xxx elements with the same frequency, such that x>yx > yx>y. Then, out of these xxx elements, you have to choose yyy elements. This can be done by using (xy){x \choose y}(yx​).

How to calculate answer?

    You know the top kkk elements by now. So, if there are aia_iai​ occurrances of the iii element, then the answer would be ∏i=1kai\prod_{i=1}^{k}a_i∏i=1k​ai​
    Make sure to multiply (xy){x \choose y}(yx​) at the end.

 */


/* 
    Helper Functions power, fact, and nCr:
        power: Calculates x^n % MOD efficiently using recursive exponentiation.
        fact: Calculates n! % MOD using a simple loop and taking modulo at each step.
        nCr: Calculates "n choose r" (binomial coefficient) using the formula n! / (r! * (n - r)!) % MOD. It uses the fact function for factorial calculation and power for modular inverse.

    Main Function countKSubsequencesWithMaxBeauty:
        Initializes a priority queue pq to store the frequency of characters in the input string s.
        Creates a freq vector to store the frequency of each character in s.
        Fills the freq vector by iterating through s.
        Pushes the frequencies (non-zero only) into the priority queue pq.
        Checks if the size of pq is less than k. If it is, it's impossible to form k unique characters, so it returns 0.
        Initializes a variable ans to 1 to accumulate the result.
        Iterates while k is greater than 0:
            Keeps track of how many equal frequencies are at the top of the priority queue (countEqual) and the corresponding element (ele).
            If countEqual is less than or equal to k, it reduces k by countEqual, updates ans by multiplying it by power(ele, countEqual) % MOD, and pops these elements from the priority queue.
            If countEqual is greater than k, it calculates power(ele, k) % MOD and nCr(countEqual, k) % MOD, multiplies them together, updates ans, and breaks from the loop.
        Returns the final ans as the result.

    Time Complexity:
        The code has a time complexity of O(N * log(N)), where N is the length of the input string s. This complexity arises from iterating through the string to count character frequencies and from the priority queue operations.

    Space Complexity:
        The space complexity is O(1) since the size of the priority queue and the freq vector are limited to the number of characters in the alphabet (26). The other variables have constant space requirements.

    Hint:
        The code effectively calculates the maximum beauty by considering characters with the highest frequency and then distributing them among k-subsequences using combinations (nCr) to maximize the beauty.
 */
class Solution
{
    int MOD = 1000000007;
    ll power(int x, int n)
    {
        if (n == 0)
            return 1;

        ll ans = power(x, n / 2);
        ans *= ans;
        ans %= MOD;

        if (n % 2 != 0)
        {
            ans *= x;
            ans %= MOD;
        }
        return ans;
    }

    ll fact(int n)
    {
        ll ans = 1;

        for (int i = 1; i <= n; i++)
        {
            ans *= i;
            ans %= MOD;
        }

        return ans;
    }

    ll nCr(int n, int r)
    {
        ll ans = fact(n);
        ll denominator = (fact(r) * fact(n - r)) % MOD;

        return (ans * power(denominator, MOD - 2)) % MOD;
    }

public:
    Solution()
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    int countKSubsequencesWithMaxBeauty(string s, int k)
    {
        priority_queue<int> pq;

        vector<int> freq(26);
        for (auto x : s)
        {
            freq[x - 'a'] += 1;
        }

        for (int i = 0; i < 26; i++)
        {
            if (freq[i] > 0)
                pq.push(freq[i]);
        }

        if (pq.size() < k)
        {
            return 0;
        }

        ll ans = 1;
        while (k > 0)
        {
            int countEqual = 0, ele = pq.top();
            while (pq.size() > 0 && pq.top() == ele)
            {
                countEqual += 1;
                pq.pop();
            }

            if (countEqual <= k)
            {
                k -= countEqual;
                ans *= power(ele, countEqual);
                ans %= MOD;
            }
            else
            {
                ans *= power(ele, k);
                ans %= MOD;

                ans *= nCr(countEqual, k);
                ans %= MOD;
                break;
            }
        }

        return ans;
    }
};
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