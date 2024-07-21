#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl

class Fenwick
{
private:
    vector<long long> bit, a;
    long long n;

public:
    Fenwick(long long n)
    {
        this->n = n;
        bit.resize(n + 1);
    }
    Fenwick(vector<long long> &arr)
    {
        n = arr.size();
        bit.resize(n + 1);
        this->a = arr;
        build(a);
    }
    void build(vector<long long> &arr)
    {
        for (long long i = 0; i < n; i++)
        {
            update(i + 1, arr.at(i));
        }
    }
    long long query(long long idx)
    {
        long long sum = 0;
        while (idx > 0)
        {
            sum += bit.at(idx);
            idx -= idx & (-idx); // sets the last set bit to 0
        }
        return sum;
    }
    void update(long long idx, long long val)
    {
        while (idx <= n)
        {
            bit.at(idx) += val;
            idx += idx & (-idx); // sets the last unset bit to 1
        }
    }
    void replace(long long idx, long long val)
    {
        update(idx + 1, -a.at(idx) + val);
        a.at(idx) = val;
    }
    void printBitVector()
    {
        for (long long i = 1; i <= n; i++)
        {
            cout << bit.at(i) << " ";
        }
        cout << "\n";
    }
    void rangeUpdate(long long l, long long r, long long val)
    {
        update(l, val);
        update(r + 1, -val);
    }
};
//**********SEGMENT TREE******** */

/*
 * SEGMENT TREES
 % Can be applied to a relation which follows associativity
 % A + (B + C) = (A + B) + C
 % A * (B * C) = (A * B) * C
 % max(A,max(B,C)) = max(max(A,B),C) etc
 */

class SegmentTree
{
public:
    long long n;
    vector<long long> arr;
    vector<long long> tree;
    SegmentTree(long long n)
    {
        this->n = n;
        arr.resize(n);
        tree.resize(4 * n);
    }
    void build(vector<long long> &arr)
    {
        this->arr = arr;
        for (long long i = 0; i < n; i++)
        {
            tree[n + i] = arr[i];
        }
        for (long long i = n - 1; i > 0; i--)
        {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }
    /**
     * Builds a segment tree for the given array.
     *
     * @param arr The input array.
     * @param vertex The current vertex being processed.
     * @param lx The left index of the current range.
     * @param rx The right index of the current range.
     *
     * @throws None.
     */
    void build(vector<long long> &arr, long long vertex, long long lx, long long rx)
    {
        if (lx == rx)
        {
            tree[vertex] = arr[lx];
            return;
        }
        long long mid = (lx + rx) / 2;
        build(arr, 2 * vertex, lx, mid);
        build(arr, 2 * vertex + 1, mid + 1, rx);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }
};
int main()
{
    return 0;
}