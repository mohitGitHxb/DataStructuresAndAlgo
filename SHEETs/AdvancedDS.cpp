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

int main()
{
    return 0;
}