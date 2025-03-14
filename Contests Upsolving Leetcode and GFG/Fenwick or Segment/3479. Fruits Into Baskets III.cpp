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
        You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.

        From left to right, place the fruits according to these rules:

            Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
            Each basket can hold only one type of fruit.
            If a fruit type cannot be placed in any basket, it remains unplaced.

        Return the number of fruit types that remain unplaced after all possible allocations are made.



        Example 1:

        Input: fruits = [4,2,5], baskets = [3,5,4]

        Output: 1

        Explanation:

            fruits[0] = 4 is placed in baskets[1] = 5.
            fruits[1] = 2 is placed in baskets[0] = 3.
            fruits[2] = 5 cannot be placed in baskets[2] = 4.

        Since one fruit type remains unplaced, we return 1.

        Example 2:

        Input: fruits = [3,6,1], baskets = [6,4,7]

        Output: 0

        Explanation:

            fruits[0] = 3 is placed in baskets[0] = 6.
            fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity) but can be placed in the next available basket, baskets[2] = 7.
            fruits[2] = 1 is placed in baskets[1] = 4.

        Since all fruits are successfully placed, we return 0.

     */
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        const int n = baskets.size();
        set<int> availableBaskets;
        for (int i = 0; i < n; i++)
            availableBaskets.insert(i);

        int last = INT_MAX;
        int unplaced = 0;
        for (int &fruit : fruits)
        {
            if (fruit >= last)
            { // all fruits that are greater than last (which couldn't be placed) can never be placed;
                unplaced++;
                continue;
            }

            bool placed = false;
            for (auto &availableBasket : availableBaskets)
            {
                const int idx = availableBasket;
                if (baskets[idx] >= fruit) // place the fruit here
                {
                    availableBaskets.erase(availableBaskets.find(availableBasket));
                    placed = true;
                    break;
                }
            }

            if (!placed) // there is no baskets that can fit this type of fruit
            {
                last = fruit;
                unplaced++;
            }
        }
        return unplaced;
    }
};

// SEGMENT TREE SOLUTION
class SegmentTree
{
private:
    vector<int> tree;
    int LEAF_SIZE;

    int calculate_size(int n)
    {
        // 2** ceil(lg(n))
        if ((n & (n - 1)) == 0)
            return n; // perfect power of 2
        // lg n
        int tmp = n;
        int count = 0;
        while (tmp)
        {
            count++;
            tmp = tmp >> 1;
        }
        return 2 << count;
    }

public:
    SegmentTree(vector<int> &arr)
    {
        int n = arr.size();

        LEAF_SIZE = calculate_size(n);
        tree.resize(2 * LEAF_SIZE, -1); // max seg tree

        // O(nlgn) ---> can be replaced with build , O(n)
        // for(int i =0; i<n; i++){
        //     update(i + LEAF_SIZE, arr[i]);
        // }

        build(arr);
    }

    void build(vector<int> &arr)
    {
        // populate leaf first;
        for (int i = 0; i < arr.size(); i++)
        {
            tree[i + LEAF_SIZE] = arr[i];
        }
        // populate internal nodes
        int index = LEAF_SIZE - 1;
        while (index > 0)
        {
            tree[index] = max(tree[2 * index], tree[2 * index + 1]);
            index--;
        }
    }

    void update(int index, int val)
    {
        tree[index] = val;
        index = index >> 1;
        while (index > 0)
        {
            tree[index] = max(tree[2 * index], tree[2 * index + 1]);
            index = index >> 1;
        }
    }

    int findIndex(int query)
    { // leftmost index where tree[index] >= query
        if (tree[1] < query)
        { // root is less than query
            return -1;
        }
        int index = 1;
        while (index < LEAF_SIZE && tree[index] >= query)
        {
            if (tree[2 * index] >= query)
            {
                index = 2 * index;
            }
            else
            {
                index = 2 * index + 1;
            }
        }
        return index;
    }
};

class Solution
{
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
    {
        SegmentTree seg(baskets);

        int unplaced = 0;

        for (int quantity : fruits)
        {
            int index = seg.findIndex(quantity);
            if (index == -1)
            {
                unplaced++;
            }
            else
            {
                seg.update(index, -1);
            }
        }

        return unplaced;
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