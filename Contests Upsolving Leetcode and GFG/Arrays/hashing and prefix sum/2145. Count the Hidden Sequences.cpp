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
        You are given a 0-indexed array of n integers differences, which describes the differences between each pair of consecutive integers of a hidden sequence of length (n + 1). More formally, call the hidden sequence hidden, then we have that differences[i] = hidden[i + 1] - hidden[i].

        You are further given two integers lower and upper that describe the inclusive range of values [lower, upper] that the hidden sequence can contain.

            For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden sequence is a sequence of length 4 whose elements are in between 1 and 6 (inclusive).
                [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
                [5, 6, 3, 7] is not possible since it contains an element greater than 6.
                [1, 2, 3, 4] is not possible since the differences are not correct.

        Return the number of possible hidden sequences there are. If there are no possible sequences, return 0.
        Example 1:

        Input: differences = [1,-3,4], lower = 1, upper = 6
        Output: 2
        Explanation: The possible hidden sequences are:
        - [3, 4, 1, 5]
        - [4, 5, 2, 6]
        Thus, we return 2.

        Example 2:

        Input: differences = [3,-4,5,1,-2], lower = -4, upper = 5
        Output: 4
        Explanation: The possible hidden sequences are:
        - [-3, 0, -4, 1, 2, 0]
        - [-2, 1, -3, 2, 3, 1]
        - [-1, 2, -2, 3, 4, 2]
        - [0, 3, -1, 4, 5, 3]
        Thus, we return 4.

        @approach:
        &- First we can observe that if we somehow get the first element we can build the entire sequence by adding difference
        &- Once obtained such an array we can determine the maximum and minimum element of the sequence
        &- an additional shift of K on each element wouldn't affect the differences array

        &- This K is essentially our answer because the range of K will determine the number of possible sequences

        &- Range of K would be (lower - minimum element) to (upper - maximum element)
     */
public:
    int numberOfArrays(vector<int> &differences, const int lower, const int upper)
    {

        int minElement = 0, maxElement = 0;
        int differencesSum = 0;

        int upperRange = 0;
        int lowerRange = 0;

        for (int &difference : differences)
        {
            differencesSum += difference;
            minElement = min(minElement, differencesSum);
            maxElement = max(maxElement, differencesSum);
            lowerRange = lower - minElement;
            upperRange = upper - maxElement;
            if ((upperRange - (lowerRange) + 1) <= 0)
            {
                return 0;
            }
        }

        return (upperRange - lowerRange + 1);
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif