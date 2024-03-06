#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
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

typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
class Solution
{
private:
    /*

        You are given a 1-indexed array of integers nums of length n.

We define a function greaterCount such that greaterCount(arr, val) returns the number of elements in arr that are strictly greater than val.

You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. Afterwards, in the ith operation:

    If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
    If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
    If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with a lesser number of elements.
    If there is still a tie, append nums[i] to arr1.

The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].

Return the integer array result.



Example 1:

Input: nums = [2,1,3,3]
Output: [2,3,1,3]
Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
In the 3rd operation, the number of elements greater than 3 is zero in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
In the 4th operation, the number of elements greater than 3 is zero in both arrays. As the length of arr2 is lesser, hence, append nums[4] to arr2.
After 4 operations, arr1 = [2,3] and arr2 = [1,3].
Hence, the array result formed by concatenation is [2,3,1,3].

Example 2:

Input: nums = [5,14,3,1,2]
Output: [5,3,1,2,14]
Explanation: After the first 2 operations, arr1 = [5] and arr2 = [14].
In the 3rd operation, the number of elements greater than 3 is one in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
In the 4th operation, the number of elements greater than 1 is greater in arr1 than arr2 (2 > 1). Hence, append nums[4] to arr1.
In the 5th operation, the number of elements greater than 2 is greater in arr1 than arr2 (2 > 1). Hence, append nums[5] to arr1.
After 5 operations, arr1 = [5,3,1,2] and arr2 = [14].
Hence, the array result formed by concatenation is [5,3,1,2,14].

     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    vector<int> resultArray_BruteForce(vector<int> &nums)
    {
        vi a1, a2;
        a1.pb(nums[0]);
        a2.pb(nums[1]);
        forsn(i, 2, nums.size())
        {
            int cnt1 = count_if(all(a1), [&](int x)
                                { return x > nums[i]; });
            int cnt2 = count_if(all(a2), [&](int x)
                                { return x > nums[i]; });
            if (cnt1 > cnt2)
            {
                a1.pb(nums[i]);
            }
            else if (cnt1 < cnt2)
            {
                a2.pb(nums[i]);
            }
            else if (cnt1 == cnt2 && sz(a1) == sz(a2))
            {
                a1.pb(nums[i]);
            }
            else
            {
                (sz(a1) < sz(a2)) ? a1.pb(nums[i]) : a2.pb(nums[i]);
            }
        }
        a1.insert(a1.end(), all(a2));
        return a1;
    }

    int greaterCount(mpi &mpx, int val)
    {
        int cnt = 0;
        auto greater = mpx.upper_bound(val);
        if (greater == mpx.end())
        {
            return 0;
        }
        for (auto it = greater; it != mpx.end(); it++)
        {
            cnt += it->second;
        }
        return cnt;
    }
    vi resultArray_BruteForce_2(vi &nums)
    {
        /*
        maintain two sorted containers to immediately find elements greater than x

        ! worst case T.c : O(N^2)logN;

         */
        vi a1, a2;
        mpi mp1, mp2;
        mp1[nums[0]]++;
        mp2[nums[1]]++;
        a1.pb(nums[0]);
        a2.pb(nums[1]);
        forsn(i, 2, nums.size())
        {
            int cnt1 = greaterCount(mp1, nums[i]);
            int cnt2 = greaterCount(mp2, nums[i]);
            if (cnt1 > cnt2)
            {
                mp1[nums[i]]++;
                a1.pb(nums[i]);
            }
            else if (cnt1 < cnt2)
            {
                mp2[nums[i]]++;
                a2.pb(nums[i]);
            }
            else if (cnt1 == cnt2 && sz(a1) == sz(a2))
            {
                mp1[nums[i]]++;
                a1.pb(nums[i]);
            }
            else
            {
                (sz(a1) < sz(a2)) ? mp1[nums[i]]++ : mp2[nums[i]]++;
                (sz(a1) < sz(a2)) ? a1.pb(nums[i]) : a2.pb(nums[i]);
            }
        }
        a1.insert(a1.end(), all(a2));
        return a1;
    }

    /*
    It performs all the operations as performed by the set data structure in STL in log(n) complexity and performs two additional operations also in log(n) complexity.

    order_of_key (k) : number of items strictly smaller than k.
    find_by_order(k) : K-th element in a set (counting from zero).

    Here, I am using an ordered set which stores elements in reversed order, thus the function order_of_key(k) gives the number of elements strictly greater than k.
    Comparison Predicates in Ordered Set

    greater: This comparison predicate is used to order elements in descending order. In this case, when you insert elements into the ordered_set, they will be stored in descending order of their values.

    greater_equal: This comparison predicate is used to order elements in non-strictly descending order. It means that elements with equal values will not be considered equivalent and will be stored in the order they were inserted.

    less: This comparison predicate is used to order elements in ascending order. In this case, when you insert elements into the ordered_set, they will be stored in ascending order of their values.

    less_equal: This comparison predicate is used to order elements in non-strictly ascending order. It means that elements with equal values will not be considered equivalent and will be stored in the order they were inserted.
    Intuition

    Since the task was to calculate the number of elements that are strictly greater than a particular value, using ordered set would be the perfect approach.
    Approach

        We need two vectors arr1, arr2 to push numbers. Each vector has a ordered set to count the values in that vector.
        Push the nums[0] to arr1, and nums[1] to arr2. Of course, insert them to the associated ordered set.
        Iterate through remaining numbers. Check conditions mentioned in the problems by using the order_of_key() function. Insert that number to arr1 or arr2 based on the conditions.
        Concatenate arr1 and arr2

    Complexity

        Time complexity: O(N log N)
        Space complexity: O(N)


     */
    vi resultArray(vi &nums)
    {
        vector<int> v1 = {nums[0]};
        vector<int> v2 = {nums[1]};
        ordered_set st1;
        ordered_set st2;
        st1.insert({nums[0], 0});
        st2.insert({nums[1], 1});
        int n = nums.size();
        for (int i = 2; i < n; i++)
        {
            // number of elements strictly greater than nums[i] in array 1
            int val1 = st1.size() - (st1.order_of_key({nums[i] + 1, -1}));
            // number of elements strictly greater than nums[i] in array 2
            int val2 = st2.size() - (st2.order_of_key({nums[i] + 1, -1}));

            // inserting based on given conditions
            if (val1 > val2)
            {
                v1.pb(nums[i]);
                st1.insert({nums[i], i});
            }
            else if (val1 < val2)
            {
                v2.pb(nums[i]);
                st2.insert({nums[i], i});
            }
            else
            {
                if (v2.size() < v1.size())
                {
                    v2.pb(nums[i]);
                    st2.insert({nums[i], i});
                }
                else
                {
                    v1.pb(nums[i]);
                    st1.insert({nums[i], i});
                }
            }
        }

        // concatenating v1 and v2 to get ans
        v1.insert(v1.end(), all(v2));
        return v1;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;

    return 0;
}
