#include <bits/stdc++.h>
using namespace std;

/*
You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.

Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.

    Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.

The power of a city is the total number of power stations it is being provided power from.

The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.

Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.

Note that you can build the k power stations in multiple cities.



Example 1:

Input: stations = [1,2,4,5,0], r = 1, k = 2
Output: 5
Explanation:
One of the optimal ways is to install both the power stations at city 1.
So stations will become [1,4,4,5,0].
- City 0 is provided by 1 + 4 = 5 power stations.
- City 1 is provided by 1 + 4 + 4 = 9 power stations.
- City 2 is provided by 4 + 4 + 5 = 13 power stations.
- City 3 is provided by 5 + 4 = 9 power stations.
- City 4 is provided by 5 + 0 = 5 power stations.
So the minimum power of a city is 5.
Since it is not possible to obtain a larger power, we return 5.

Example 2:

Input: stations = [4,4,4,4], r = 0, k = 3
Output: 4
Explanation:
It can be proved that we cannot make the minimum power of a city greater than 4.


*/

class Solution
{
    using ll = long long;

public:
    vector<ll> partialSum;

    bool check(vector<ll> &partial, const int r, int k,
               const ll minimumThreshold)
    {
        // cout << "\n=== CHECK called with minimumThreshold = "
        //      << minimumThreshold << ", k = " << k << " ===" << endl;

        const int n = partial.size() - 1;
        vector<ll> tracking(n + 1);
        int stationsUsed = 0;

        for (int i = 0; i < n; i++)
        {
            tracking[i] += (i - 1 >= 0) ? tracking[i - 1] : 0;
            // cout << "\tracking power per city: [";
            // for (int m = 0; m < n; m++) {
            //     cout << tracking[m] << (m < n - 1 ? "," : "");
            // }
            // cout << "]" << endl;
            const ll currentPower = partial[i] + tracking[i];
            const ll required = minimumThreshold - currentPower;

            // cout << "City " << i << ": currentPower=" << currentPower
            //      << ", required=" << required << ", k_remaining=" << k <<
            //      endl;

            if (required <= 0)
            {
                // cout << "  -> Already satisfied" << endl;
                continue;
            }
            else
            {
                const bool canIncrease = (required <= k) && (k > 0);
                if (!canIncrease)
                {
                    // cout << "  -> CANNOT satisfy! Need " << required
                    //      << " but only have " << k << endl;
                    return false;
                }

                const int maxBound =
                    min(n, i + 2 * r + 1); // FIXED: should be i + 2*r + 1
                tracking[i] += required;
                tracking[maxBound] -= required;
                k -= required;
                stationsUsed += required;

                // cout << "  -> Added " << required << " stations at range ["
                // << i
                //      << ", " << maxBound << ")" << endl;
                // cout << "  -> k_remaining now: " << k
                //      << ", total used: " << stationsUsed << endl;
            }
        }

        // cout << "CHECK PASSED! Total stations used: " << stationsUsed <<
        // endl;
        return true;
    }

    long long maxPower(vector<int> &stations, int r, int k)
    {
        const int n = stations.size();

        // cout << "Input: stations = [";
        // for (int i = 0; i < n; i++)
        //     cout << stations[i] << (i < n - 1 ? "," : "");
        // cout << "], r = " << r << ", k = " << k << endl;

        this->partialSum.resize(n + 1);

        // Build difference array
        for (int i = 0; i < n; i++)
        {
            const int leftBound = max(0, i - r);
            const int rightBound =
                min(n, i + r + 1); // FIXED: should be n, not n-1
            partialSum[leftBound] += stations[i];
            partialSum[rightBound] -= stations[i];

            // cout << "Station " << i << " (power=" << stations[i]
            //      << ") affects range [" << leftBound << ", " << rightBound
            //      << ")" << endl;
        }

        // Convert to actual power values
        partial_sum(partialSum.begin(), partialSum.end(), partialSum.begin());

        // cout << "\nInitial power per city: [";
        // for (int i = 0; i < n; i++) {
        //     cout << partialSum[i] << (i < n - 1 ? "," : "");
        // }
        // cout << "]" << endl;

        const ll minimumElement =
            *min_element(partialSum.begin(), partialSum.begin() + n);
        ll low = minimumElement;
        ll high = minimumElement + k;
        ll answer = low;

        // cout << "\nBinary search range: [" << low << ", " << high << "]"
        //      << endl;

        while (low <= high)
        {
            const ll mid = low + (high - low) / 2;
            const bool isPossible = check(partialSum, r, k, mid);

            if (isPossible)
            {
                answer = max(mid, answer);
                // cout << "mid=" << mid << " is POSSIBLE, searching higher ["
                //      << (low + 1) << ", " << high << "]" << endl;
                low = mid + 1;
            }
            else
            {
                // cout << "mid=" << mid << " is NOT possible, searching lower ["
                //      << low << ", " << (mid - 1) << "]" << endl;
                high = mid - 1;
            }
        }

        // cout << "\n=== FINAL ANSWER: " << answer << " ===" << endl;
        return answer;
    }
};
int main()
{
    return 0;
}