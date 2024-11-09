#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution
{
private:
    static const int MOD = 1e9 + 7;
    static const int OFFSET = 400;
    static const int LIMIT = 42; // Adjust as needed

    // Static arrays for factorials and inverse factorials
    static int factorials[LIMIT];
    static int inverseFactorials[LIMIT];

    // Modular exponentiation
    static int modPow(int base, int exp, int mod)
    {
        int result = 1;
        base %= mod;
        while (exp > 0)
        {
            if (exp & 1)
                result = (1LL * result * base) % mod;
            base = (1LL * base * base) % mod;
            exp >>= 1;
        }
        return result;
    }

    // Modular multiplicative inverse
    static int modInverse(int a, int m)
    {
        return modPow(a, m - 2, m);
    }

    // Precompute factorials and inverse factorials
    static void preComputeFactorials()
    {
        factorials[0] = 1;
        for (int i = 1; i < LIMIT; i++)
        {
            factorials[i] = (1LL * factorials[i - 1] * i) % MOD;
        }

        inverseFactorials[LIMIT - 1] = modInverse(factorials[LIMIT - 1], MOD);
        for (int i = LIMIT - 2; i >= 0; i--)
        {
            inverseFactorials[i] = (1LL * inverseFactorials[i + 1] * (i + 1)) % MOD;
        }
    }

    // Compute nCr with modular arithmetic
    static int nCr(int n, int r)
    {
        if (n < r)
            return 0;
        if (r == 0)
            return 1;

        int numerator = factorials[n];
        int denominator = (1LL * inverseFactorials[r] * inverseFactorials[n - r]) % MOD;

        return (1LL * numerator * denominator) % MOD;
    }

    // Main solve function with memoization
    int solve(int currentDigit, int currentDifference, int oddPositionsLeft,
              int evenPositionsLeft, vector<int> &digitsMap, vector<vector<vector<int>>> &dp)
    {
        // Base cases
        if (abs(currentDifference) > OFFSET)
            return 0;
        if (currentDigit == 10)
        {
            return (currentDifference == 0 && oddPositionsLeft == 0);
        }

        // Memoization
        const int memoIndex = currentDifference + OFFSET;
        if (dp[currentDigit][memoIndex][oddPositionsLeft] != -1)
        {
            return dp[currentDigit][memoIndex][oddPositionsLeft];
        }

        int res = 0;
        for (int i = 0; i <= digitsMap[currentDigit]; i++)
        {
            if (oddPositionsLeft >= i)
            {
                int remainingDigitsCount = digitsMap[currentDigit] - i;

                // Compute new difference and positions
                int newDifference = currentDifference + (i * currentDigit - remainingDigitsCount * currentDigit);
                int newOddPositionsLeft = oddPositionsLeft - i;
                int newEvenPositionsLeft = evenPositionsLeft - remainingDigitsCount;

                // Recursive call
                int subResult = solve(currentDigit + 1, newDifference,
                                      newOddPositionsLeft, newEvenPositionsLeft,
                                      digitsMap, dp);

                // Compute combinations
                int oddCombinations = nCr(oddPositionsLeft, i);
                int evenCombinations = nCr(evenPositionsLeft, remainingDigitsCount);

                // Update result with modular arithmetic
                res = (res + (1LL * subResult * oddCombinations % MOD * evenCombinations % MOD)) % MOD;
            }
        }

        return dp[currentDigit][memoIndex][oddPositionsLeft] = res;
    }

public:
    int countBalancedPermutations(string &num)
    {
        // Precompute factorials if not already done
        static bool initialized = false;
        if (!initialized)
        {
            preComputeFactorials();
            initialized = true;
        }

        // Create digits map
        vector<int> digitsMap(10, 0);
        for (char ch : num)
        {
            digitsMap[ch - '0']++;
        }

        // Create DP table with 32-bit integers
        vector<vector<vector<int>>> dp(
            11,
            vector<vector<int>>(2 * OFFSET + 1,
                                vector<int>((num.size() + 1) / 2 + 1, -1)));

        // Solve the problem
        return solve(0, 0, (num.size() + 1) / 2, num.size() / 2, digitsMap, dp);
    }
};

// Initialize static arrays
int Solution::factorials[LIMIT] = {0};
int Solution::inverseFactorials[LIMIT] = {0};