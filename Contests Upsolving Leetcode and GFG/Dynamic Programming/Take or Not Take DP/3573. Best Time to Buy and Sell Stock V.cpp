#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given stock prices over n days and max k transactions
     * - Two types of transactions allowed:
     *   1. Normal: Buy low, sell high (profit = sellPrice - buyPrice)
     *   2. Short: Sell high, buy back low (profit = sellPrice - buyBackPrice)
     * - Must complete each transaction before starting another
     * - Goal: Maximize total profit
     *
     * KEY INSIGHT - State Machine Approach:
     * We have 3 possible states at any day:
     *
     * STATE 0: NEUTRAL (no active position)
     *   ├─> Buy stock (enter STATE 1: LONG position)
     *   ├─> Short sell (enter STATE 2: SHORT position)
     *   └─> Skip (stay in STATE 0)
     *
     * STATE 1: LONG POSITION (holding stock, waiting to sell)
     *   ├─> Sell stock (close position, return to STATE 0, transaction complete)
     *   └─> Hold (stay in STATE 1)
     *
     * STATE 2: SHORT POSITION (shorted stock, waiting to buy back)
     *   ├─> Buy back (cover short, return to STATE 0, transaction complete)
     *   └─> Hold (stay in STATE 2)
     *
     * DP STATE:
     * dp[day][transactionsRemaining][position]
     *   - day: current day index (0 to n-1)
     *   - transactionsRemaining: how many transactions we can still do (0 to k)
     *   - position: 0=neutral, 1=long, 2=short
     *
     * TRANSITIONS:
     * From NEUTRAL (state 0):
     *   - Skip: dp[day+1][k][0]
     *   - Go long: dp[day+1][k][1] - price (pay to buy)
     *   - Go short: dp[day+1][k][2] + price (receive from selling)
     *
     * From LONG (state 1):
     *   - Hold: dp[day+1][k][1]
     *   - Sell: dp[day+1][k-1][0] + price (receive from selling, transaction done)
     *
     * From SHORT (state 2):
     *   - Hold: dp[day+1][k][2]
     *   - Buy back: dp[day+1][k-1][0] - price (pay to buy back, transaction done)
     *
     * TIME: O(n * k * 3) = O(n * k)
     * SPACE: O(n * k * 3) = O(n * k)
     */

    // State constants for better readability
    static const int NEUTRAL = 0;
    static const int LONG_POSITION = 1;
    static const int SHORT_POSITION = 2;

    // Store prices globally for easier access
    vector<int> prices;

    // DP memoization table
    // dp[day][transactionsLeft][position]
    long long dp[1003][503][3];

    // Sentinel value for impossible states
    const long long IMPOSSIBLE = -1e14;

    /**
     * Recursive DP function to find maximum profit
     *
     * @param day - current day index
     * @param transactionsLeft - number of transactions remaining
     * @param position - current position: 0=neutral, 1=long, 2=short
     * @return maximum profit achievable from this state onward
     */
    long long findMaxProfit(int day, int transactionsLeft, int position)
    {
        // Base case: reached the end of all days
        if (day == prices.size())
        {
            // If we're in neutral position, we're done (profit = 0)
            // If we're still holding a position, it's invalid (return IMPOSSIBLE)
            return (position == NEUTRAL) ? 0 : IMPOSSIBLE;
        }

        // Return memoized result if already computed
        if (dp[day][transactionsLeft][position] != -1)
        {
            return dp[day][transactionsLeft][position];
        }

        long long currentPrice = prices[day];
        long long maxProfit = IMPOSSIBLE;

        // Option 1: Skip this day (always available)
        maxProfit = max(maxProfit, findMaxProfit(day + 1, transactionsLeft, position));

        // STATE 0: NEUTRAL - Can start a new transaction
        if (position == NEUTRAL)
        {
            // Option 2a: Buy stock (go long)
            // Cost: currentPrice, new state: LONG_POSITION
            long long profitIfBuy = findMaxProfit(day + 1, transactionsLeft, LONG_POSITION) - currentPrice;
            maxProfit = max(maxProfit, profitIfBuy);

            // Option 2b: Short sell (go short)
            // Gain: currentPrice, new state: SHORT_POSITION
            long long profitIfShort = findMaxProfit(day + 1, transactionsLeft, SHORT_POSITION) + currentPrice;
            maxProfit = max(maxProfit, profitIfShort);
        }
        // STATE 1 or 2: In a position - Can close it if we have transactions left
        else if (transactionsLeft >= 1)
        {
            // STATE 1: LONG POSITION - Can sell to close
            if (position == LONG_POSITION)
            {
                // Sell stock: gain currentPrice, use 1 transaction, return to NEUTRAL
                long long profitIfSell = findMaxProfit(day + 1, transactionsLeft - 1, NEUTRAL) + currentPrice;
                maxProfit = max(maxProfit, profitIfSell);
            }
            // STATE 2: SHORT POSITION - Can buy back to cover
            else
            { // position == SHORT_POSITION
                // Buy back: cost currentPrice, use 1 transaction, return to NEUTRAL
                long long profitIfCover = findMaxProfit(day + 1, transactionsLeft - 1, NEUTRAL) - currentPrice;
                maxProfit = max(maxProfit, profitIfCover);
            }
        }

        // Memoize and return result
        return dp[day][transactionsLeft][position] = maxProfit;
    }

public:
    long long maximumProfit(vector<int> &prices, int k)
    {
        // Initialize DP table with -1 (uncomputed)
        memset(dp, -1, sizeof(dp));

        // Store prices for global access
        this->prices = prices;

        // Start from day 0, with k transactions available, in neutral position
        return findMaxProfit(0, k, NEUTRAL);
    }
};

/*
 * EXAMPLE WALKTHROUGH: prices = [1, 7, 9, 8, 2], k = 2
 *
 * Optimal Strategy (Profit = 14):
 *
 * Day 0: price = 1
 *   Action: BUY (go long)
 *   Cost: -1
 *   Position: LONG
 *   Transactions left: 2
 *
 * Day 1: price = 7
 *   Action: HOLD
 *   Position: LONG
 *
 * Day 2: price = 9
 *   Action: SELL (close long)
 *   Gain: +9
 *   Total profit so far: 9 - 1 = 8
 *   Position: NEUTRAL
 *   Transactions left: 1
 *
 * Day 3: price = 8
 *   Action: SHORT SELL
 *   Gain: +8
 *   Position: SHORT
 *   Transactions left: 1
 *
 * Day 4: price = 2
 *   Action: BUY BACK (cover short)
 *   Cost: -2
 *   Transaction profit: 8 - 2 = 6
 *   Total profit: 8 + 6 = 14
 *   Position: NEUTRAL
 *   Transactions left: 0
 *
 * Final Profit: 14 ✓
 *
 * ===================================================================
 *
 * WHY THIS APPROACH WORKS:
 *
 * 1. STATE TRACKING: We track whether we're neutral, long, or short
 *    This ensures we don't buy twice without selling, or sell twice
 *    without buying back.
 *
 * 2. TRANSACTION COUNTING: A transaction is only counted as "used"
 *    when we CLOSE a position (sell from long or buy back from short).
 *    Opening a position doesn't consume a transaction.
 *
 * 3. PROFIT CALCULATION:
 *    - Long transaction: -buyPrice + sellPrice
 *    - Short transaction: +sellPrice - buyBackPrice
 *    Both accumulate to total profit across all days.
 *
 * 4. MEMOIZATION: Prevents recalculating the same state multiple times.
 *    Without it, time complexity would be exponential.
 *
 * 5. GREEDY LOCAL CHOICES: At each day, we try all valid actions and
 *    pick the one that maximizes future profit. DP ensures this leads
 *    to the globally optimal solution.
 */
int main()
{
    return 0;
}