#include <bits/stdc++.h>

using namespace std;

/*
^ Activity selection problem
* method:
todo     1. sort activity according to finish time
todo     2. initialize solution as first activity
todo     3. for remaining activities {
todo         check if current activity overlaps with previous activity in the solution
todo         ignore the current activity
todo
todo         else add the current activity to the solution
todo     }
 */
bool cmp(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}
int activity(vector<pair<int, int>> &activity)
{
    sort(activity.begin(), activity.end(), cmp);
    int cnt = 1;
    auto it = activity.begin();
    int current = it->second;
    it++;
    for (auto iter = it; iter != activity.end(); iter++)
    {
        if (iter->second >= current || iter->first <= current)
        {
            continue;
        }
        else
        {
            current = iter->second;
            cnt++;
        }
    }
    return cnt;
}
/*
^ Fractional knapsack
 */
//! O(n) space and O(NlogN)time
int getFractionalKnapsack(int knapsack, vector<pair<int, int>> &arr)
{
    vector<pair<float, pair<int, int>>> copy; //~{val/weight , weight , val}
    for (int i = 0; i < arr.size(); i++)
    {
        pair<float, pair<int, int>> p;
        p.first = (float)arr[i].second / arr[i].first;
        p.second.first = arr[i].first;
        p.second.second = arr[i].second;
        copy.push_back(p);
    }
    sort(copy.rbegin(), copy.rend());

    for (auto &it : copy)
    {
        cout << it.first << " " << it.second.first << " " << it.second.second << endl;
    }
    int n = copy.size();
    int ans = 0;
    int currWeight = 0;
    for (int i = 0; i < n; i++)
    {
        if (currWeight == knapsack)
        {
            break;
        }
        if (currWeight + copy[i].second.first > knapsack)
        {
            continue;
        }
        if (currWeight + copy[i].second.first <= knapsack)
        {
            currWeight += copy[i].second.first;
            ans += copy[i].second.second;
            continue;
        }
        else
        {
            currWeight += (knapsack - copy[i].second.first);
            ans += (int)copy[i].first * (knapsack - copy[i].second.first);
        }
    }
    return ans;
}

/*
^ Job scheduling algorithm
 */

struct compare
{
    bool operator()(pair<int, int> p1, pair<int, int> p2)
    {
        return p1.second < p2.second;
    }
};
int maxProfit(vector<pair<int, int>> &jobs)
{

    // ! O(N^2) time;
    /*     //~ Sort all jobs according to
        //~ decreasing order of profit
        sort(jobs.begin(),jobs.end(),cmp);

        vector<int> result(jobs.size());
        vector<bool> slot(jobs.size());

        for(int i = 0; i < jobs.size(); i++) {
              //? Find a free slot for this job
            //? (Note that we start
            //? from the last possible slot)

            for(int j = min((int)jobs.size(),jobs[i].first); j < jobs.size(); j++) {
                //~ free slot found
                if(slot[j] == false) {
                    slot[j] = true; //~ make this slot occupied
                    result[j] = i;  //~ add this to job result
                    break;
                }
            }
        }


        //?print the result
        int profit = 0;
        for(int i=0;i<jobs.size();i++)
            if(slot[i])
                profit+=jobs[result[i]].second;
        return profit;
     */

    //* O(NlogN) and O(N) time and space respectively

    /*
    &    Sort the jobs based on their deadlines.
    &    Iterate from the end and calculate the available slots between every two consecutive deadlines. Insert the profit, deadline, and job ID of ith job in the max heap.
    &    While the slots are available and there are jobs left in the max heap, include the job ID with maximum profit and deadline in the result.
    &    Sort the result array based on their deadlines.
     */
    vector<int> result;
    sort(jobs.begin(), jobs.end());
    priority_queue<pair<int, int>, vector<pair<int, int>>, compare()> pq;

    for (int i = jobs.size() - 1; i >= 0; i--)
    {
        //~ we count the slots available between two jobs
        int slot;
        if (i == 0)
        {
            slot = jobs.at(i).first;
        }
        else
        {
            slot = jobs.at(i).first - jobs.at(i - 1).first;
        }
        //~ include the profit of job(as priority),
        //~ deadline and job_id in maxHeap
        pq.push(make_pair(slot, jobs.at(i).second));
        while (slot > 0 && pq.size() > 0)
        {
            auto it = pq.top();
            pq.pop();
            slot--;

            result.push_back(it.second);
        }
    }

    sort(result.begin(), result.end());
    for (auto &it : result)
    {
        cout << it << " ";
    }
}
 
/*
^ Huffman Algorithm
* method:
todo    1. Build a Huffman tree
?        -> every input character is a leaf
?        -> every left child edge is labelled as 0 and right child edge is labelled as 1.
?        -> every root to leaf path represents the huffman code for that leaf

todo    2.Traverse the huffman tree(binary tree) and print the codes

* building the huffman tree:
?    -> create leaf nodes and build a min heap h of all leaves initally
?    -> while (h.size() > 1){
?        left = h.extractMinimum();
?        right = h.extractMinimum();
?        create a new tree node with
            * character a $
            * frequency as left.freq + right.freq
            * left and right children as left and right respectively.
?        insert the new node into h
?    }
?    -> the only node left in h is our required binary tree(huffman tree)
 */

struct HuffmanNode{
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
    char ch;
    HuffmanNode(char ch, int freq, HuffmanNode *left=NULL, HuffmanNode *right=NULL){
        this->freq = freq;
        this->ch = ch;
        this->left = left;
        this->right = right;
    }
};

struct hufComp {
    bool operator()(const HuffmanNode &a, const HuffmanNode &b){
        return a.freq < b.freq;
    }
};

//~ printing codes
void printCodes(HuffmanNode* root,string str=""){
    if(root==NULL)
        return;
    if(root->ch != '$'){
        cout << root->ch << " " << str << "\n";
        return;
    }
    printCodes(root->left,str+"0");
    printCodes(root->right,str+"1");
}

//% main algorithm
void huffman(vector<char> &arr , vector<int> &freq){
    priority_queue<HuffmanNode* , vector<HuffmanNode*> , hufComp> pq;
    for (int i = 0; i < arr.size(); i++)
    {
        pq.push(new HuffmanNode(arr[i],freq[i]));
    }
    while (pq.size() > 1)
    {
        HuffmanNode* l = pq.top();
        pq.pop();
        HuffmanNode* r = pq.top();
        pq.pop();
        HuffmanNode* node = new HuffmanNode('$',l->freq+r->freq,l,r);
        pq.emplace(node);
    }

    printCodes(pq.top(),"");
}
int main(int argc, char const *argv[])
{
    vector<pair<int, int>> arr = {{10, 200}, {5, 100}, {25, 500}, {50, 700}};
    // cout <<activity(a);
    cout << getFractionalKnapsack(15, arr);
    return 0;
}