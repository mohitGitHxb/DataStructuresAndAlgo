#include <bits/stdc++.h>
// #include<utility> //pairs
// #include<vector> //vectors
// #include<forward_list> //forward list
// #include<list> //lists
using namespace std;

/* Pairs in STL -->
pair<int,int> p(0,5)
pair<int,string> p2(10,"prozone");
g2 = make_pair(1, 'a');  */

/* Comparison (==) operator with pair : For given two pairs say pair1 and pair2, the comparison operator compares the first value and second value of those two pairs i.e. if pair1.first is equal to pair2.first or not AND if pair1.second is equal to pair2.second or not .
Not equal (!=) operator with pair : For given two pairs say pair1 and pair2, the != operator compares the first values of those two pairs i.e. if pair1.first is equal to pair2.first or not, if they are equal then it checks the second values of both.
Logical( >=, <= )operators with pair : For given two pairs say pair1 and pair2, the =, >, can be used with pairs as well. It returns 0 or 1 by only comparing the first value of the pair. */

// sort array according to another array...
/* void sortArray(int a[], char b[], int n){
    vector<pair<int,char>> temp;
    for(int i=0;i<n;i++){
        temp.push_back({a[i],b[i]});
    }
    sort(temp.begin(),temp.end());
    for(const auto &i : temp)
        cout<<i.second<<" ";
    temp.clear();

} */

/* Vectors -->
 */

void performVectors(void)
{
    vector<int> v{10, 40, 20, 30, 50, 100};
    cout << v.front() << "\n"; // provides reference
    cout << v.size() << "\n";
    cout << v.empty() << "\n";
    cout << v.back() << "\n"; // provides reference
    v.pop_back();
    v.insert(v.begin(), 69);         // 69 inserted at index 0 or at beginning
    v.insert(v.begin() + 1, 3, 999); // 999 inserted 3 times at index 1
    vector<int> v2;
    v2.insert(v2.begin(), v.begin(), v.begin() + 3);
    for (const auto &i : v)
        cout << i << " ";
    cout << "\n";
    for (const auto &j : v2)
        cout << j << " ";
    cout << "\n";
    v.erase(v.begin() + 1); // removes item at index 1;
    // v.erase(v.begin(),v.end()); //clears vector from begin to end v.clear()
    v2.resize(2);
    for (const auto &j : v2)
        cout << j << " ";
    cout << "\n";
}
/* Minimum vertical sum */
int minimum_vertical_sum(vector<vector<int>> v)
{
    // Your code here
    int maxVerticalSum = INT_MAX;
    int maxSizedVector = -1000000;
    for (int i = 0; i < v.size(); i++)
    {
        maxSizedVector = max((int)v[i].size(), maxSizedVector);
    }
    cout << maxSizedVector << "\n";
    for (int i = 0; i < maxSizedVector; i++)
    {
        int currentSum = 0;
        for (int j = 0; j < v.size(); j++)
        {
            if (i < v[j].size())
            {
                currentSum += v[j][i];
            }
            else
            {
                currentSum += 0;
            }
        }
        cout << currentSum << "\n";
        maxVerticalSum = min(maxVerticalSum, currentSum);
        cout << maxVerticalSum << "\n";
    }
    return maxVerticalSum;
}

/* Forward list(singly linked list) */
// void perfromForwardList(void){
//     forward_list<int> l1={1,3,5,7,9,11};
//     for (auto &&i : l1)
//     {
//         cout<<i<<" ";
//     }
//     cout<<"\n";
//     l1.assign({2,4,6});
//     for (auto &&i : l1)
//     {
//         cout<<i<<" ";
//     }
//     cout<<"\n";
//     l1.pop_front();
//     l1.push_front(100);
//     cout<<l1.front()<<"\n";
//     l1.erase_after(l1.begin());
//     l1.reverse();
//     l1.sort();
//     for (auto &&i : l1)
//     {
//         cout<<i<<" ";
//     }
//     cout<<"\n";
//     l1.emplace_after(l1.begin(),2,4);
//     for (auto &&i : l1)
//     {
//         cout<<i<<" ";
//     }
//     cout<<"\n";

// }

/* list or doubly linked list */
int josephus(int n, int k)
{
    // Your code here
    list<int> ls;
    for (int i = 0; i < n; i++)
    {
        ls.push_back(i + 1);
    }
    auto it = ls.begin();
    while (ls.size() != 1)
    {
        for (int i = 1; i < k; i++)
        {
            it++;
            if (it == ls.end())
                it = ls.begin();
        }
        cout << *it << " ";
        it = ls.erase(it);
        if (it == ls.end())
            it = ls.begin();
    }
    return *ls.begin();
}

// maximum in all subarrays of size k
void printMaxSubarray(vector<int> &arr, int k)
{
    deque<int> dq;
    for (int i = 0; i < k; i++)
    {
        while (!dq.empty() && arr[i] >= arr[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    for (int i = k; i < arr.size(); i++)
    {
        cout << arr[dq.front()];
        while (!dq.empty() && dq.front() <= i - k)
        {
            dq.pop_front();
        }
        while (!dq.empty() && arr[i] >= arr[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(arr[i]);
    }
    cout << arr[dq.front()] << " ";
}

/* stack library */
/* bool compare(char a,char b){
    return ((a=='('&&b==')'))||((a=='{'&&b=='}'))||((a=='['&&b==']'));
}
bool isBalanced(string &str){
    stack<char> s;
    for (int i = 0; i < str.length(); i++)
    {
        if(str.at(i)=='('||str.at(i)=='{'||str.at(i)=='['){
            s.push(str[i]);
        }
        else{
            if(s.empty())
                return false;
            else if(compare(s.top(),str[i])==false)
                return false;
            else
                s.pop();
        }
    }
    return s.empty();

} */

// stock span problem
 void getSpan(int arr[] , int N){
//      stack<pair<int,int>> s;
//      if(N==0)return;
//      else if(N==1)cout<<1<<" ";
//      for (int i = 0; i < N; i++)
//      {
//          pair<int,int> p={arr[i],1};
//          while (!s.empty() && s.top().first<=arr[i])
//          {
//              p.second+=s.top().second;
//              s.pop();
//          }
//          s.push(p);
//          cout<<p.second<<" ";
//      }

// slightly optimization
 stack<int> s;
 s.push(0);  //storing indexes to get span
 for (int i = 1; i < N; i++)
 {
     while (!s.empty()&&arr[s.top()]<=arr[i])
     {
         s.pop();
     }
     int span=(s.empty())?i+1:i-s.top();
     cout<<span<<" ";
     s.push(i);

}
}

//^previous greater element;
vector<int> previousGreater(int arr[], int n)
{
    vector<int> ans; //? similar problem like stock span
    ans.emplace_back(-1);
    stack<int> s;
    s.push(arr[0]);
    for (int i = 1; i < n; i++)
    {
        while (!s.empty() && s.top() <= arr[i])
        {
            s.pop();
        }
        int min = (s.empty()) ? -1 : s.top();
        s.push(arr[i]);
        ans.push_back(min);
    }
    return ans;
}

//^next greater element
vector<int> nextGreater(int arr[], int n)
{
    vector<int> ans;
    ans.push_back(-1);
    stack<int> s;
    s.push(arr[n - 1]);
    for (int i = n - 2; i >= 0; i--)
    {
        while (!s.empty() && s.top() <= arr[i])
        {
            s.pop();
        }
        int mx = (s.empty()) ? -1 : s.top();
        s.push(arr[i]);
        ans.push_back(mx);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

/* minimum step destination */
int minimum_distance(int sx, int sy, int dx, int dy)
{
    // if(sx==dx)return abs(dy-sy);
    // if(sy==dy)return abs(dx-sx);
    // int minDistance=0;
    // int i;
    // for (i = sx; i < dx; i++)
    // {
    //     minDistance++;
    // }
    // for (i = sy; i < dy; i++)
    // {
    //     minDistance++;
    // }
    // return minDistance;

    //* best solution
    // if(sx > dx || sy > dy)
    //     return -1;
    // if(sx == dx && sy == dy)
    //     return 0;

    // return (dx - sx) + (dy - sy);
}

/* Print K largest element in an array min-heap */
void printKlargest(int arr[], int n, int k)
{
    priority_queue<int, vector<int>, greater<int>> pq(arr, arr + k);
    for (int i = k; i < n; i++)
    {
        if (arr[i] > pq.top())
        {
            pq.top();
            pq.push(arr[i]);
        }
    }
    while (pq.empty() == false)
    {
        cout << pq.top() << " ";
        pq.pop();
    }
}
//^ Purchase maximum items with given money...
//! O(nlogn) sorting + O(n) space
/*
~ Sort the array and subtract the arr elements from the sum and update the count
~ ,if sum goes -ve return count
*/
//* efficient solution using min heap O(count*logn) time + O(n) space
int purchaseMax(int arr[], int n, int sum)
{
    priority_queue<int, vector<int>, greater<int>> pq(arr, arr + n);
    int res = 0;
    while (sum >= 0 && pq.empty() == false && pq.top() <= sum)
    {
        sum -= pq.top();
        pq.pop();
        res++;
    }
    return res;
}

//^ print k most frequent elements
//! O(nlogn) time and O(n) space ...
// bool myCmp(pair<int,int> p1,pair<int,int> p2){
//     if(p1.second==p2.second)
//         return p1.first<p2.first;
//     return
//         p1.second>p2.second;
// }
// void printKfrequent(int arr[],int n,int k){
//     unordered_map<int,int> m;
//     for (int i = 0; i < n; i++)
//     {
//         m[arr[i]]++;
//     }
//     vector<pair<int,int>> v(m.begin(),m.end());
//     sort(v.begin(),v.end(),myCmp);
//     for (int i = 0; i < k; i++)
//     {
//         cout << v.at(i).first <<" ";
//     }
// }

// todo better sol (klogn) time
/* struct myCmp
{
    bool operator()(pair<int,int> p1,pair<int,int> p2){
          if(p1.second==p2.second)
        return p1.first>p2.first;
    return
        p1.second<p2.second;
    }
};


void printKfrequent(int arr[],int n,int k){
    unordered_map<int,int> m;
    for (int i = 0; i < n; i++)
    {
        m[arr[i]]++;
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,myCmp> pq(m.begin(),m.end());
    for (int i = 0; i < k; i++)
    {
        cout << pq.top().first <<" ";
        pq.pop();
    }

} */

// todo O(N) solution

void printKfrequent(int arr[], int n, int k)
{
    unordered_map<int, int> umap;
    for (int i = 0; i < n; i++)
    {
        umap[arr[i]]++;
    }
    vector<int> freq[n + 1];

    //~ without specific order
    // for (auto &&i : umap)
    // {
    //     freq[i.second].emplace_back(i.first);
    // }

    //& element which appears first in the array is given priority
    for (int i = 0; i < n; i++)
    {
        int f = umap[arr[i]];
        if (f != -1)
        {
            freq[f].emplace_back(arr[i]);
            umap[arr[i]] = -1;
        }
    }
    int count = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (const auto &j : freq[i])
        {
            cout << j << " ";
            count++;
            if (count == k)
                return;
        }
    }
}

// todo Non-Mutating-algorithms

bool cmp(int x) { return x % 2 == 0; }
void NMA(void)
{
    /*
    ?               find()
    &The find() function in C++ STL is used to find an element in a given range in any container. This function returns an iterator to the first element in the range [first,last) that compares equal to a given value val. If no such element is found, the function returns last.
    &The find() function does a linear search on the container provided in the range [first, last) and compares the value to be searched every time with the current value during the search operation.
     */

    vector<int> v = {12, 42, 5, 32, 352, 32, 76, 84, 34, 65, 86};
    auto it1 = find(v.begin(), v.end(), 32);
    if (it1 != v.end())
        cout << it1 - v.begin() << " ";
    cout << "\n";

    /*
    ?       lower_bound() and upper_bound()
    &The lower_bound() is a built-in function in C++ STL which returns an iterator pointing to the first element which is greater than or equal to a given a value in a sorted range
    &The upper_bound() is a built-in function in C++ STL which returns an iterator pointing to the first element which is greater than a given a value in a sorted range.
     */

    vector<int> vSorted{3, 6, 9, 10, 21, 23, 30, 35, 66, 91};
    auto it2 = lower_bound(vSorted.begin(), vSorted.end(), 23);
    cout << *it2 << "\n";
    it2 = lower_bound(vSorted.begin(), vSorted.end(), 91);
    cout << *it2 << "\n";
    it2 = lower_bound(vSorted.begin(), vSorted.end(), 27);
    cout << *it2 << "\n";

    // index = it2 - v.begin()

    it2 = upper_bound(vSorted.begin(), vSorted.end(), 35);
    cout << *it2 << "\n";
    it2 = upper_bound(vSorted.begin(), vSorted.end(), 91);
    // cout << * it2 << "\n"; //vSorted.end()
    it2 = upper_bound(vSorted.begin(), vSorted.end(), 27);
    cout << *it2 << "\n";

    /*
    &The is_permutation() is a built-in function in C++ STL which is used to check whether two given containers are permutations of each other or not.
     */
    (is_permutation(v.begin(), v.end(), vSorted.begin())) ? cout << "True\n" : cout << "False\n";
    cout << *max_element(vSorted.begin(), vSorted.end()) << "\n"; // 3rd argument is for compare function
    cout << *min_element(vSorted.begin(), vSorted.end()) << "\n";
    cout << count(v.begin(), v.end(), 32) << " \n";
    (binary_search(vSorted.begin(), vSorted.end(), 55)) ? cout << "True\n" : cout << "False\n";

    list<int> v2(12);
    fill(v2.begin(), v2.end(), 10);
    auto it3 = v2.begin();
    advance(it3, 3);
    fill(it3, v2.end(), -10);
    rotate(v2.begin(), it3, v2.end());
    for (auto &i : v2)
        cout << i << " ";
    cout << "\n";
    int sumList = 0, sumVec = 1000;
    cout << accumulate(v2.begin(), v2.end(), sumList) << "\n"; //~takes 4th argument to perform other operations
    cout << accumulate(v.begin(), v.end(), sumVec) << "\n";

    srand(time(NULL));
    for (int i = 0; i < 6; i++) //~for custom range=(high-low+1) ==> rand()%range+low;
    {
        cout << rand() % 100 << " ";
    }
    cout << "\n";

    stable_partition(v.begin(), v.end(), cmp); //! partition works similar except maintaining order
    for (auto &i : v)
        cout << i << " ";
    cout << "\n";
}

int median(vector<vector<int>> &matrix, int r, int c)
{
    // code here
    int MIN = matrix[0][0], MAX = matrix[0][c - 1];
    for (int i = 0; i < r; i++)
    {
        MIN = min(matrix[i][0], MIN);
        MAX = max(matrix[i][c - 1], MAX);
    }
    int medPos = (r * c + 1) / 2;
    while (MIN < MAX)
    {
        int mid = (MIN + MAX) / 2;
        int midPos = 0;
        for (int i = 0; i < r; i++)
            midPos += (upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin());

        if (midPos < medPos)
        {
            MIN = mid + 1;
        }
        else
        {
            MAX = mid;
        }
    }
    return MIN;
}

void unorderedSets(void)
{
    unordered_set<int> s1, s2;
    s1.insert(10);
    s1.insert(30);
    s1.insert(50);
    s1.emplace(70);
    s1.emplace(100);
    s1.emplace(40);
    cout << s1.size()<< ' ' << s1.empty() << "\n";
    cout << *s1.find(30)<< ' ' << s1.count(100) << "\n";
    cout << s1.bucket(10)<< ' ' << s1.bucket_count() << '\n';
    auto it = s1.find(30);
    s1.erase(10);
    s1.erase(it);
    for (auto &&i : s1)
    {
        cout << i << " ";
    }
    cout << '\n';
}


//^Fractional Knapsack problem

bool myCmp(pair<int,int> a , pair<int,int> b){
    double r1 =  (double)a.first/a.second;
    double r2 =  (double)b.first/b.second;
    return r1 > r2;
}
double fractionalKnaps(int weight , vector<pair<int,int>> &arr){
    sort(arr.begin(),arr.end(),myCmp);
    double res=0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].second <= weight)
        {
            res += arr[i].first;
            weight-=arr.at(i).second;
        }
        else
        {
            res += arr.at(i).first *(double)(weight/arr.at(i).second); 
            break;
        }
        
    }

    return res;
}




//todo MUTATING ALGORITHMS  

//^ chocolate distribution 
int minimumDifference(vector<int> &arr , int m){
if (m > arr.size())
    {
        return -1;
    }
    sort(arr.begin(),arr.end());
    int res = arr[m-1] - arr[0];
    for (int i = 1; i+m-1 < arr.size(); i++)
    {
        res = min(res , (arr[i+m-1] - arr[i]));
    }
}




void heap(){
    vector<int> v{45,32,21,57,54,24,-53};
    vector<int> w{24,54,53};
    make_heap(v.begin(),v.end());
    for (auto &&i : v)
    {
        cout << i << " ";
    }
    cout << "\n";
    make_heap(v.begin(),v.end(),greater<int>());
    for (auto &&i : v)
    {
        cout << i << " ";
    }
    cout << "\n";

    push_heap(w.begin(),w.end(),greater<int>());

    for (auto &&i : w)
    {
        cout << i << " ";
    }
    cout << "\n";

    pop_heap(v.begin()+3,v.end());
    
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> v{{2, 3, 5}, {1, 2}, {1, 4, 5, 1}};
    int arr[] = {5, 16, 10, 8, 6, 12, 9, 18};
    // cout<<minimum_vertical_sum(v);
    // cout << josephus(5, 3);
    // getSpan(arr, 4);)
    // vector<int> ans=nextGreater(arr,8);
    // for (auto &&i : ans)
    // {
    //     cout<<i<<" ";
    // }
    // unorderedSets();
    // NMA();
    heap();


    return 0;
}
