#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - String s of digits, queries [l, r]
     * - For each query:
     *   1. Extract s[l..r]
     *   2. Concatenate all non-zero digits → integer x
     *   3. Compute sum of digits in x (= sum of non-zero digits in s[l..r])
     *   4. Return (x * sum) % MOD
     *
     * KEY INSIGHT – Prefix Arrays for O(1) per Query:
     *
     * CHALLENGE: x can be astronomically large (up to 10^n digits long).
     * We cannot build x explicitly; we must derive it mod MOD.
     *
     * OBSERVATION 1: prefixConcatValue[i]
     * - Running concatenation of non-zero digits from s[0..i-1]
     * - When s[i] = 0: value unchanged   (zero doesn't affect concatenation)
     * - When s[i] = d: value = value * 10 + d  (append digit d)
     *
     * OBSERVATION 2: Extracting x for a query [l, r]
     * - prefixConcatValue[r+1] includes non-zero digits from s[0..r]
     * - prefixConcatValue[l]   includes non-zero digits from s[0..l-1]
     * - The "left anchor" must be stripped out of prefixConcatValue[r+1]
     *
     * HOW TO STRIP:
     * Let k = number of non-zero digits in s[l..r]
     * prefixConcatValue[r+1] = prefixConcatValue[l] * 10^k + x
     * So: x = prefixConcatValue[r+1] - prefixConcatValue[l] * 10^k
     *
     * VISUAL EXAMPLE: s = "10203004", query [0, 7]
     *
     *  Position:  0  1  2  3  4  5  6  7
     *  Digit:     1  0  2  0  3  0  0  4
     *
     *  prefixConcatValue after each digit:
     *  [0] = 0         (initial)
     *  [1] = 1         (append 1)
     *  [2] = 1         (skip 0)
     *  [3] = 12        (append 2)
     *  [4] = 12        (skip 0)
     *  [5] = 123       (append 3)
     *  [6] = 123       (skip 0)
     *  [7] = 123       (skip 0)
     *  [8] = 1234      (append 4)
     *
     *  For query [0,7]: l=0, r=7
     *    leftAnchorValue   = prefixConcatValue[0] = 0
     *    rightConcatValue  = prefixConcatValue[8] = 1234
     *    nonZeroCount      = prefixNonZeroCount[8] - prefixNonZeroCount[0] = 4
     *    x = 1234 - 0 * 10^4 = 1234
     *    sum = prefixDigitSum[8] - prefixDigitSum[0] = 10
     *    answer = 1234 * 10 = 12340 ✓
     *
     * TIME:  O(n + m) – O(n) to build prefix arrays, O(1) per query
     * SPACE: O(n) – four prefix arrays of length n+1
     */

    static constexpr long long MOD = 1e9 + 7;

    /**
     * Precomputes 10^0, 10^1, ..., 10^n (mod MOD).
     * Needed to "shift" the left anchor value by the count of non-zero digits.
     */
    vector<long long> buildPowerTable(int n)
    {
        vector<long long> powerOf10(n + 1, 1);
        for (int i = 1; i <= n; i++)
        {
            powerOf10[i] = (powerOf10[i - 1] * 10) % MOD;
        }
        return powerOf10;
    }

    /**
     * Builds four prefix arrays over s:
     *
     *  prefixConcatValue[i]  = concat of non-zero digits in s[0..i-1], mod MOD
     *  prefixDigitSum[i]     = sum of all digits in s[0..i-1]
     *  prefixNonZeroCount[i] = count of non-zero digits in s[0..i-1]
     *
     * The zero-skipping rule for prefixConcatValue:
     *   d == 0 → value unchanged (zero contributes nothing to concatenation)
     *   d != 0 → value = value * 10 + d  (append the digit)
     */
    void buildPrefixArrays(const string &s,
                           vector<long long> &prefixConcatValue,
                           vector<long long> &prefixDigitSum,
                           vector<int> &prefixNonZeroCount)
    {
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            int digit = s[i] - '0';

            prefixDigitSum[i + 1] = prefixDigitSum[i] + digit;
            prefixNonZeroCount[i + 1] = prefixNonZeroCount[i] + (digit != 0 ? 1 : 0);

            if (digit == 0)
            {
                prefixConcatValue[i + 1] = prefixConcatValue[i]; // zero: no change
            }
            else
            {
                prefixConcatValue[i + 1] =
                    (prefixConcatValue[i] * 10 + digit) % MOD; // append digit
            }
        }
    }

    /**
     * Evaluates a single query [l, r]:
     *
     *   nonZeroCount     = number of non-zero digits in s[l..r]
     *   leftAnchorValue  = prefixConcatValue[l]   (digits before the window)
     *   rightConcatValue = prefixConcatValue[r+1] (digits through end of window)
     *
     *   x   = rightConcatValue - leftAnchorValue * 10^nonZeroCount   (mod MOD)
     *   sum = sum of digits in s[l..r]  (= sum of non-zero digits, since zeros add 0)
     *
     *   answer = (x * sum) % MOD
     */
    long long evaluateQuery(int l, int r,
                            const vector<long long> &prefixConcatValue,
                            const vector<long long> &prefixDigitSum,
                            const vector<int> &prefixNonZeroCount,
                            const vector<long long> &powerOf10)
    {
        int nonZeroCount = prefixNonZeroCount[r + 1] - prefixNonZeroCount[l];

        long long leftAnchorValue = prefixConcatValue[l];
        long long rightConcatValue = prefixConcatValue[r + 1];

        // Strip out the left anchor's contribution:
        // x = rightConcatValue - leftAnchorValue * 10^nonZeroCount
        long long x = (rightConcatValue - (leftAnchorValue * powerOf10[nonZeroCount]) % MOD + MOD) % MOD;

        long long sum = prefixDigitSum[r + 1] - prefixDigitSum[l];

        return (x * sum) % MOD;
    }

public:
    vector<int> sumAndMultiply(string s, vector<vector<int>> &queries)
    {
        int n = s.size();
        int m = queries.size();

        // Precompute power-of-10 table
        vector<long long> powerOf10 = buildPowerTable(n);

        // Precompute prefix arrays (1-indexed, length n+1)
        vector<long long> prefixConcatValue(n + 1, 0);
        vector<long long> prefixDigitSum(n + 1, 0);
        vector<int> prefixNonZeroCount(n + 1, 0);
        buildPrefixArrays(s, prefixConcatValue, prefixDigitSum, prefixNonZeroCount);

        // Answer each query in O(1)
        vector<int> answer(m);
        for (int i = 0; i < m; i++)
        {
            answer[i] = evaluateQuery(
                queries[i][0], queries[i][1],
                prefixConcatValue, prefixDigitSum,
                prefixNonZeroCount, powerOf10);
        }
        return answer;
    }
};

/*
 * DETAILED WALKTHROUGH – Example 3: s = "9876543210", queries = [[0,9]]
 *
 * n = 10, query [l=0, r=9]
 *
 * ===== Prefix Arrays =====
 *
 *  i  digit  concatVal  digitSum  nonZeroCnt
 *  0    —        0          0          0
 *  1    9        9          9          1
 *  2    8       98         17          2
 *  3    7      987         24          3
 *  4    6     9876         30          4
 *  5    5    98765         35          5
 *  6    4   987654         39          6
 *  7    3  9876543         42          7
 *  8    2 98765432         44          8
 *  9    1 987654321        45          9
 * 10    0 987654321        45          9   ← 0 doesn't change concatVal
 *
 * ===== Query [0, 9] =====
 *
 * nonZeroCount     = prefixNonZeroCount[10] - prefixNonZeroCount[0] = 9 - 0 = 9
 * leftAnchorValue  = prefixConcatValue[0]  = 0
 * rightConcatValue = prefixConcatValue[10] = 987654321
 *
 * x = (987654321 - 0 * 10^9) % MOD = 987654321
 * sum = prefixDigitSum[10] - prefixDigitSum[0] = 45
 *
 * answer = (987654321 * 45) % (10^9 + 7)
 *        = 44444444445 % (10^9 + 7)
 *        = 444444137  ✓
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH – Example 1, query [1,3]: s[1..3] = "020"
 *
 * nonZeroCount     = prefixNonZeroCount[4] - prefixNonZeroCount[1] = 2 - 1 = 1
 * leftAnchorValue  = prefixConcatValue[1]  = 1
 * rightConcatValue = prefixConcatValue[4]  = 12
 *
 * x = (12 - 1 * 10^1) % MOD = (12 - 10) = 2
 * sum = prefixDigitSum[4] - prefixDigitSum[1] = 7 - 1 = 2  (digits: 0+2+0)
 *       Wait: sum counts ALL digits, but zeros contribute 0 anyway
 *       prefixDigitSum[1] = 1 (digit '1'), prefixDigitSum[4] = 1+0+2+0 = 3
 *       sum = 3 - 1 = 2 ✓
 *
 * answer = (2 * 2) % MOD = 4 ✓
 *
 * ===================================================================
 *
 * FORMULA PROOF (why x = right - left * 10^k):
 *
 * Let digits in s[0..l-1] produce value A (= leftAnchorValue).
 * Let digits in s[l..r] produce value B (= x, what we want).
 * There are k non-zero digits in s[l..r].
 *
 * Concatenating A then B gives: A * 10^k + B
 * But that's exactly prefixConcatValue[r+1]!
 *
 * So: prefixConcatValue[r+1] = A * 10^k + B
 *     B = prefixConcatValue[r+1] - A * 10^k   ✓
 */

int main()
{
    return 0;
}