#include<bits/stdc++.h>

using namespace std;
// class MyHash{
//     private:
//     protected:
//     list<int> *table;
//     public:
//     int BUCKET=INT16_MAX;
//     MyHash(int b = 100){
//         this->BUCKET=b;
//         this->table = new list<int>[b];
//     }
//     bool Search(int key){
//         int i = key%BUCKET;
//         auto it=find(table[i].begin(),table[i].end(),key);
//         return !(it==table[i].end());
//     }
//     void insert(int key){
//         int i = key%BUCKET;
//         table[i].emplace_back(key);
//     }
//     void Delete(int key){
//         int i = key%BUCKET;
//         table[i].remove(key);
//     }

// };


//^open addressing (linear probing)
// template <class T=int>
// class MyHash{
//     protected:
//     T* arr;
//     public:
//     int size;
//     int cap;
//     MyHash(int cap){
//         this->cap = cap;
//         arr = new T[cap];
//         size = 0;
//         fill(arr,arr+cap,-1);
//     }
//     int hash(T key){
//         return key%cap;
//     }
//     bool insert(T key){
//         if(size!=cap){
//             int i = hash(key);
//             while (arr[i]!= -1 && arr[i] != -2 && arr[i]!=key)
//             {
//                 i=(i + 1)%cap;
//             }
//             if(arr[i]==key)return false;
//             else
//             {
//                 arr[i] = key;
//                 size++;
//                 return true;
//             }
            
//         }
//         return false;
//     }
//     bool erase(T key){
//         int i = hash(key);
//         while (arr[i]!=-1)
//         {
//             if (arr[i] == key)
//             {
//                 arr[i] = -2;
//                 return true;
//             }
//             i=(i+1)%cap;
//             if (i == hash(key))
//             {
//                 return false;
//             }
            
//         }
//         return false;
//     }
//     bool search(T key){
//         int h = hash(key);
//         int i = h;
//         while (arr[i] != -1)
//         {
//             if(arr[i] == key)
//             return true;
//             i = (i+1)%cap;
//             if( i == h){
//                 return false;
//             }
//         }
//         return false;
//     }
// };


//^ subarray with 0 sum
bool isSubarrayWith0sum(vector<int> &arr){
    unordered_set<int> s;
    int prefix_sum=0; /* 
    ?calculating prefix sum and checking if the prefix sum is being repeated
    ?or not if it is repeating itself means the elements b/w the first occurrence of the prefix sum
    ?and the current occurrence have their sum as 0..
    
    ~if prefix sum or arr[i] becomes 0 we return true (corner cases)
    
     */
    for (auto &x : arr)
    {
        prefix_sum+=x;
        if(s.find(prefix_sum)!=s.end())
            return true;
        if(x==0 || prefix_sum==0)
            return true;
        s.emplace(prefix_sum);
    }
        
}


//^ subarray with given sum
bool isSubarrayWithSum(vector<int> &arr , int k){
    unordered_set<int> s;
    int prefixSum = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        prefixSum += arr.at(i);
        if(prefixSum == arr.at(i) || arr[i] == k)return true;
        if (s.find(prefixSum - k)!=s.end())return true;
        s.insert(prefixSum);        
    }
    return false;
    
}

//^ longest Subarray with k sum

int LongestSubarrayWithSum(vector<int> &arr , int k){
    unordered_map<int,int> mp;
    int prefixSum = 0,res = INT32_MIN;
    for (int i = 0; i < arr.size(); i++)
    {
        prefixSum+=arr.at(i);
        if (mp.find(prefixSum - k)!=mp.end())
        {
            res = max(res,abs(i - mp.find(prefixSum-k)->second));
            continue;
        }
        if (prefixSum == k || arr[i] == k)
        {
            res = max(res,i+1);
            continue;
        }
        mp.emplace(prefixSum,i);
        
    }
    return res;
}

//^Longest subarray with equal no. of 0s and 1s;
int getLongestSubarray(vector<int> &arr) {
    unordered_map<int , int> mp;
    int prefixSum = 0, res = 0;
    /* 
    todo: Reduce this problem into longest subarray with 0 sum by changing 0s to -1;
     */
    for (int i = 0; i < arr.size(); i++)
    {
        prefixSum += (arr.at(i) == 0)?-1:arr.at(i);
        if (mp.find(prefixSum)!=mp.end())       
        {
            res= max(res,(i-mp[prefixSum]));
            continue;
        }
        if(prefixSum == 0){
            res = max(res,i+1);
            continue;
        }
        mp.emplace(prefixSum,i);
        
    }
    
   
    return  res;
}


//^ Pair with given sum in an unsorted array. . .

bool isPairSum(vector<int> &arr,int k){
    unordered_set<int> s(arr.begin(),arr.end());
    for (auto &&i : arr)
    {
        if(s.find(k - i)!=s.end())
            return true;
        s.emplace(i);
    }
    
}


//^ longest common span with same sum in binary array... O(n) space and time

int commonSpan(vector<int> &arr1,vector<int> &arr2){
    /* 
    ?Assuming both arrays have the same size
    
    &subtract the elements of arr1 from arr2 then apply the method
    &which is used to find longest subarray w/ 0 sum to get the max length of
    &the subarray...
     */
    vector<int> temp;
    for (int i = 0; i < arr1.size(); i++)
    {
        temp.push_back(arr1[i] - arr2[i]);
    }

    unordered_map<int,int> mp;
    int prefixSum = 0,lengthMAX=0;
    for (int i = 0; i < temp.size(); i++)
    {
        prefixSum+= temp.at(i);
        if (prefixSum == 0)
        {
            lengthMAX=max(lengthMAX,i+1);
            continue;
        }

        if (mp.find(prefixSum)!=mp.end())
        {
            lengthMAX=max(lengthMAX,(i - mp[prefixSum]));
            continue;
        }
        mp.emplace(prefixSum,i);
        
    }
    return lengthMAX;
}


//^longest consecutive subsequence
int longestSub(vector<int> &arr){
    // ! sorting method O(nlogn)
/*     sort(arr.begin(),arr.end());
    int res = 1,curr=1;
    for (int i = 1; i < arr.size(); i++)
    {
        if (arr[i-1]+1==arr[i])
        {
            curr++;
        }
        else if (arr[i]!=arr[i-1]+1)
        {
            res = max(res , curr);
            curr = 1;
        }
        
        
    }
    return max(res,curr); */

    //* efficient approach O(n) space and time
    unordered_set<int> s(arr.begin(),arr.end());
    int res = 1;
    for (auto &x : s)
    {
        if(s.find(x-1)!=s.end()){
        int curr=1;
            while (s.find(x + curr)!=s.end())
            {
                curr++;
            }
            res = max(res,curr);
        }
    }
    return res;

}
//watch this later...

//^ count distinct elements in every windows

void countDistinct(vector<int> &arr,int k){

    //!O((N-K)*K*K) time 
/*     for (int i = 0; i <= arr.size()-k; i++)
    {
        int count = 0;
        for (int j = 0; j < k; j++)
        {
            bool flag = false;
            for (int p = 0; p < j; p++)
            {
                if (arr[i+j] == arr[i+p])
                {
                    flag = true; break;
                }
                
            }
            if (!flag)
            {
                count++;
            }
            
        }
        cout << count << " ";
        
    } */
    
    //*O(N) time and O(K) space

    /* 
    & create a frequency map of first k items;
    & print the size of the freq map;
    ? for(i=k;i<n;i++)
        todo-> decrease frequency of arr[i-k]
        todo-> if freq. of arr[i-k] == 0 remove this element
        todo-> if arr[i-k] not exists , insert it
        todo-> print size of the map;
     */
       unordered_map<int, int> m; 
   
    for (int i = 0; i < k; i++) { 
        m[arr[i]] += 1; 
    } 
   
    cout << m.size() << " "; 
   
    for (int i = k; i < arr.size(); i++) { 
        
        m[arr[i - k]] -= 1;  //? decreasing freq for the upcoming window
        
        if (m[arr[i - k]] == 0) { 
            m.erase(arr[i-k]); 
        }   
        m[arr[i]] += 1; 
   
        cout << m.size() << " "; 
    }
    
}
int main(int argc, char const *argv[])
{
    vector<int> arr = {10,20,20,10,30,40,10};
    vector<int> brr = {1,0,1,0,0,1};
    // cout << isSubarrayWith0sum(arr);
    // cout << LongestSubarrayWithSum(arr,5);
    // cout << getLongestSubarray(arr);
    // cout << isPairSum(arr,17);
    // cout << commonSpan(arr,brr);
    countDistinct(arr,4);
    return 0;
}
