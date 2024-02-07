#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
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
template <class T = int>
void print1dVector(const vector<T> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void print2dVector(const vector<vector<T>> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        print1dVector<T>(i);
    }
    cout << "]\n";
}
template <class T = int, class U = int>
void printHashmap(const unordered_map<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int, class U = int>
void printMap(const map<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int>
void printMultiSet(const multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void printSet(const set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void printHashSet(const unordered_set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int>
void printPriorityQueue(priority_queue<T> pq)
{
    cout << "[";
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printStack(stack<T> st)
{
    cout << "[";
    while (!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printQueue(queue<T> q)
{
    cout << "[";
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "]\n";
}
template <class T = int>
void printDeque(deque<T> dq)
{
    cout << "[";
    for (auto &i : dq)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
template <class T = int, class U = int>
void printHashMultimap(const unordered_multimap<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":" << i.second << "}\n";
    }
    cout << "]\n";
}
template <class T = int>
void printMultiHashSet(const unordered_multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << i << " ";
    }
    cout << "]\n";
}
void printBitRepresentation(long long n)
{
    string binary = bitset<64>(n).to_string(); // converts to binary
    cout << "Binary representation: " << binary << "\n";
}
long long binaryExponentiation(long long base, long long exponent, long long mod)
{
    long long res = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return res;
}
long long getModularMultiplicativeInverse(long long num, long long mod)
{
    // multiplicative inverse only exists if num and mod are relatively prime (coprime) i.e gcd(num, mod) = 1
    if (__gcd(num, mod) != 1)
    {
        return -1;
    }
    return binaryExponentiation(num, mod - 2, mod);
}

class Solution
{
private:
    /*
You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

We define the right direction as positive x-axis (increasing x-coordinate) and the left direction as negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive y-axis (increasing y-coordinate) and the down direction as negative y-axis (decreasing y-coordinate)

You have to place n people, including Chisato and Takina, at these points such that there is exactly one person at every point. Chisato wants to be alone with Takina, so Chisato will build a rectangular fence with Chisato's position as the upper left corner and Takina's position as the lower right corner of the fence (Note that the fence might not enclose any area, i.e. it can be a line). If any person other than Chisato and Takina is either inside the fence or on the fence, Chisato will be sad.

Return the number of pairs of points where you can place Chisato and Takina, such that Chisato does not become sad on building the fence.

Note that Chisato can only build a fence with Chisato's position as the upper left corner, and Takina's position as the lower right corner. For example, Chisato cannot build either of the fences in the picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:

    With Chisato at (3, 3) and Takina at (1, 1), Chisato's position is not the upper left corner and Takina's position is not the lower right corner of the fence.
    With Chisato at (1, 3) and Takina at (1, 1), Takina's position is not the lower right corner of the fence.

Input: points = [[6,2],[4,4],[2,6]]
Output: 2
Explanation: There are two ways to place Chisato and Takina such that Chisato will not be sad:
- Place Chisato at (4, 4) and Takina at (6, 2).
- Place Chisato at (2, 6) and Takina at (4, 4).
You cannot place Chisato at (2, 6) and Takina at (6, 2) because the person at (4, 4) will be inside the fence.
     */
public:
    Solution()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
    }

    bool isValidPair(pii &a, pii &b)
    {
        if (a.first <= b.first && a.second >= b.second)
            return true;
        return false;
    }

    bool isValidConfig(pii &a, pii &b, pii &c)
    {
        if (((a.first <= c.first && c.first <= b.first) and (a.second >= c.second && c.second >= b.second)))
        {
            return false;
        }
        return true;
    }

    int numberOfPairs(vvi &points)
    {

        //& Simple brute force O(N^3) Solution no need to explain

        int ans = 0;
        if (sz(points) < 3)
        {
            pii a = mp(points[0][0], points[0][1]);
            pii b = mp(points[1][0], points[1][1]);
            return isValidPair(a, b) || isValidPair(b, a);
        }
        forn(i, sz(points))
        {
            forn(j, sz(points))
            {
                pii a = mp(points[i][0], points[i][1]);
                pii b = mp(points[j][0], points[j][1]);
                if (i != j and isValidPair(a, b))
                {
                    bool isvalid = true;
                    forn(k, sz(points))
                    {
                        pii c = mp(points[k][0], points[k][1]);
                        if (i != k and j != k and !isValidConfig(a, b, c))
                        {
                            // cout << a.first << " " << a.second << " |\t " << b.first << " " << b.second << " |\t " << c.first << " " << c.second << endl;
                            isvalid = false;
                            break;
                        }
                    }
                    if (isvalid)
                    {
                        ans += 1;
                    }
                }
            }
        }
        return ans;
    }

    int numberOfPairs_OPTIMIZED(vvi &points)
    {
        /* 
        & Start believing in your intuitions lol I had got the approach at the very first time I actually understood the question

        & Sort in this order x1 < x2 and if (x1 == x2) then y1 > y2 

        & Set a bench mark height as all coordinates for (T) must have height greater than bench mark height to be a valid candidate

        & lets say benchmark height set due to a point (4,2) is 2 then all elements (x>4,y=2) are invalid and also (x=4,y<2) are invalid
        
        
         */
        int ans = 0;
        if (sz(points) < 3)
        {
            pii a = mp(points[0][0], points[0][1]);
            pii b = mp(points[1][0], points[1][1]);
            return isValidPair(a, b) || isValidPair(b, a);
        }
        vpii coordinates;
        tr(it, points)
        {
            coordinates.emplace_back(it->at(0), it->at(1));
        }

        sort(coordinates.begin(), coordinates.end(), [](pii &a, pii &b)
             { return (a.first < b.first) ? true : ((a.first == b.first && a.second > b.second)); });

        // tr(it, coordinates){
        //     cout << it->first << " " << it->second << endl;
        // }

        forn(i, sz(coordinates))
        {
            int benchMarkHeight = INT_MIN;
            forsn(j, i + 1, sz(coordinates))
            {
                if (isValidPair(coordinates[i], coordinates[j]))
                {
                    // cout << coordinates[i].first << " " << coordinates[i].second << " |\t " << coordinates[j].first << " " << coordinates[j].second << endl;
                    ans += (benchMarkHeight < coordinates[j].second) ? 1 : 0;
                    benchMarkHeight = max(benchMarkHeight, coordinates[j].second);
                }
            }
        }

        return ans;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
