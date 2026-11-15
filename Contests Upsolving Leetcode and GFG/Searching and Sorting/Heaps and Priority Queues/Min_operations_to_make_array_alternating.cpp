#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
#define mod 1000000007
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef unordered_map<int, int> hmpi;
typedef unordered_map<ll, ll> hmpll;
typedef unordered_map<int, pii> hmppi;
typedef unordered_map<int, vi> hmpvi;
typedef unordered_set<int> hsi;
typedef unordered_set<ll> hsll;
typedef unordered_set<pii> hspi;
typedef unordered_set<pl> hspl;
typedef map<int, int> mpi;
typedef map<ll, ll> mpll;
typedef map<int, pii> mppi;
typedef map<int, vi> mpvi;
typedef set<int> si;
typedef set<ll> sll;
typedef set<pii> spi;
typedef set<pl> spl;
#define sz(x) ((ll)(x).size())

/*
    &- The minimumOperations function aims to find the minimum number of operations required to make the input array nums alternating. An array is called alternating if the following conditions are met:
        nums[i - 2] == nums[i] for 2 <= i <= n - 1.
        nums[i - 1] != nums[i] for 1 <= i <= n - 1.

    &- The function first counts the frequency of each element in the input array nums and stores the highest and second-highest frequencies of even and odd elements separately. It also keeps track of the corresponding elements with the highest frequencies.

    &- The function then checks if the highest frequency even element and the highest frequency odd element are different. If they are different, we can simply change all other elements to the element with the second-highest frequency, which will result in an alternating array.

    &- If the highest frequency even element and the highest frequency odd element are the same, we have two cases to consider:
        Case 1: Changing all other elements to the element with the second-highest frequency in even positions and the element with the second-highest frequency in odd positions.
        Case 2: Changing all other elements to the element with the second-highest frequency in odd positions and the element with the second-highest frequency in even positions.

    &- The function returns the minimum of Case 1 and Case 2 as the result.

    &- The time complexity of the code is O(n), where n is the size of the input array nums. The function iterates through the array once to calculate the frequency of elements and find the highest and second-highest frequencies.

    &- The space complexity of the code is O(n), where n is the number of unique elements in the input array nums. The function uses two unordered maps to store the frequencies of even and odd elements.

Hints:

    &- The problem requires finding the minimum number of operations to make the input array alternating.
    &- To solve the problem, you need to count the frequencies of even and odd elements in the array and find the highest and second-highest frequencies along with their corresponding elements.
    &- You can then consider two cases: one where the highest frequency even element and the highest frequency odd element are different, and another where they are the same.
    &- In the first case, you can change all other elements to the second-highest frequency element to make the array alternating.
    &- In the second case, you need to consider two subcases to change elements in odd and even positions alternately to make the array alternating.
    &- Finally, you can return the minimum number of operations required from both cases as the result.
 */

int minimumOperations(vector<int> &nums)
{
    if (nums.size() < 1)
        return 0;
    unordered_map<int, int> highestFrequencyOdd, highestFrequencyEven;
    int maxi = -1e9;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i % 2 == 0)
        {
            highestFrequencyEven[nums.at(i)]++;
        }
        else
        {
            highestFrequencyOdd[nums.at(i)]++;
        }
        maxi = max(maxi, nums.at(i));
    }

    int firstMaxFrequencyOddIndex = 0, firstMaxFrequencyEvenIndex = 0;
    int firstMaxOddElement = 0, firstMaxEvenElement = 0;

    int secondMaxFrequencyOddIndex = 0, secondMaxFrequencyEvenIndex = 0;
    int secondMaxOddElement = 0, secondMaxEvenElement = 0;

    for (int i = 1; i <= maxi; i++)
    {
        if (highestFrequencyEven.find(i) != highestFrequencyEven.end())
        {
            if (highestFrequencyEven[i] > firstMaxFrequencyEvenIndex)
            {
                secondMaxFrequencyEvenIndex = firstMaxFrequencyEvenIndex;
                secondMaxEvenElement = firstMaxEvenElement;
                firstMaxFrequencyEvenIndex = highestFrequencyEven[i];
                firstMaxEvenElement = i;
            }
            else if (highestFrequencyEven[i] > secondMaxFrequencyEvenIndex)
            {
                secondMaxFrequencyEvenIndex = highestFrequencyEven[i];
                secondMaxEvenElement = i;
            }
        }
        if (highestFrequencyOdd.find(i) != highestFrequencyOdd.end())
        {
            if (highestFrequencyOdd[i] > firstMaxFrequencyOddIndex)
            {
                secondMaxFrequencyOddIndex = firstMaxFrequencyOddIndex;
                secondMaxEvenElement = firstMaxOddElement;
                firstMaxFrequencyOddIndex = highestFrequencyOdd[i];
                firstMaxOddElement = i;
            }
            else if (highestFrequencyOdd[i] > secondMaxFrequencyOddIndex)
            {
                secondMaxFrequencyOddIndex = highestFrequencyOdd[i];
                secondMaxOddElement = i;
            }
        }
    }

    if (firstMaxEvenElement != firstMaxOddElement)
    {
        return nums.size() - firstMaxFrequencyEvenIndex - firstMaxFrequencyOddIndex;
    }

    return min((nums.size() - firstMaxFrequencyEvenIndex - secondMaxFrequencyOddIndex), (nums.size() - firstMaxFrequencyOddIndex - secondMaxFrequencyEvenIndex));
}

/*
@ Max-heap

The given code is a C++ implementation to find the minimum number of operations required to make the input array nums alternating, following the same problem statement as before. The code uses unordered maps and priority queues to find the highest and second-highest frequencies of even and odd elements and then calculates the minimum number of operations accordingly.

    The code first calculates the frequency of even and odd elements in the input array nums using two unordered maps, even and odd. It also keeps track of the highest frequencies for even and odd elements using max_even and max_odd variables.

    The code then creates two priority queues, Even and Odd, to store pairs of frequency and element. These queues will be used to find the elements with the highest frequency for even and odd positions.

    Next, the code checks if the input array nums has only one element. If it does, the result is 0, as there is no need to perform any operations on a single element.

    If the highest frequency even element and the highest frequency odd element are different, the code calculates the number of operations needed to make the array alternating. It computes the number of elements that need to be changed in even and odd positions separately and adds them to the variable ans.

    If the highest frequency even element and the highest frequency odd element are the same, the code needs to handle two sub-cases where both the highest and second-highest frequency elements are the same in both even and odd positions.

    If both Even and Odd priority queues are empty, the array is made alternating by changing all elements in the odd positions, which is equal to nums.size()/2 operations.

    If either Even or Odd priority queue is empty, the code calculates the number of operations needed to make the array alternating by changing elements in the empty priority queue.

    If both Even and Odd priority queues are not empty, the code calculates the number of operations needed for two sub-cases: one where it changes the highest frequency even element in even positions and the second highest frequency odd element in odd positions, and vice versa.

    Finally, the code returns the minimum of all these calculations as the result.

    The time complexity of the code is O(n log n), where n is the size of the input array nums. The code uses priority queues, and inserting elements and extracting the maximum element from the priority queues takes logarithmic time.

    The space complexity of the code is O(n), where n is the number of unique elements in the input array nums. The code uses unordered maps and priority queues to store the frequencies of elements.

    The code is a valid implementation to find the minimum number of operations required to make the array alternating. It handles all possible cases and calculates the operations needed accordingly.
 */
int minimumOperations(vector<int> &nums)
{
    unordered_map<int, int> odd, even;
    int max_even = 0, max_odd = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i % 2 == 0)
        {
            even[nums[i]]++;
            max_even = max(max_even, even[nums[i]]);
        }
        else
        {
            odd[nums[i]]++;
            max_odd = max(max_odd, odd[nums[i]]);
        }
    }

    if (nums.size() == 1)
        return 0;

    priority_queue<pair<int, int>> Even, Odd;
    for (auto x : even)
    {
        Even.push({x.second, x.first});
    }
    for (auto y : odd)
    {
        Odd.push({y.second, y.first});
    }
    int ans = 0;
    if (Even.top().second != Odd.top().second)
    {
        ans += ((nums.size() + 1) / 2 - Even.top().first);
        ans += nums.size() / 2 - Odd.top().first;
    }
    else
    {
        auto a = Even.top();
        Even.pop();
        auto b = Odd.top();
        Odd.pop();
        if (Even.empty() and Odd.empty())
            return nums.size() / 2;
        if (Even.empty() || Odd.empty())
        {
            if (Odd.empty())
            {
                return min(nums.size() / 2, (nums.size() + 1) / 2 - Even.top().first);
            }
            else
            {
                return min((nums.size() + 1) / 2, (nums.size()) / 2 - Odd.top().first);
            }
        }
        int sum1 = 0, sum2 = 0;
        sum1 += ((nums.size() + 1) / 2 - a.first);
        sum1 += nums.size() / 2 - Odd.top().first;

        sum2 += ((nums.size() + 1) / 2 - Even.top().first);
        sum2 += nums.size() / 2 - b.first;

        ans = min(sum1, sum2);
    }

    return ans;
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