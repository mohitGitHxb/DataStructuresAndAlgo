#include <bits/stdc++.h>
using namespace std;

//^ 1 Valid parenthesis

class ValidParenthesis
{
    public:
    //Function to check if brackets are balanced or not.
     bool isMatching(char a,char b){
    return ((a=='('&&b==')'))||((a=='{'&&b=='}'))||((a=='['&&b==']'));
    }
    bool ispar(const string &str)
    {
        if(str.empty())return true;
        // Your code here
        stack<char> s;
        // s.push(x[0]);
 for (int i = 0; i < str.length(); i++)
    {
        if(str.at(i)=='('||str.at(i)=='{'||str.at(i)=='['){
            s.push(str[i]);
        }
        else{
            if(s.empty())
                return false;
            else if(isMatching(s.top(),str[i])==false)
                return false;
            else 
                s.pop();
        }
    }
    return s.empty();
        
    }

};

//^ 2 Implementation of min stack
class MinStack{
    int minEle;
    stack<pair<int,int>> s;
    public:
    
       /*returns min element from stack*/
       int getMin(){
           
           //Write your code here
           if(s.empty()) return -1;
           minEle = s.top().second;
           return minEle;
       }
       
       /*returns poped element from stack*/
       int pop(){
           if(s.empty()) return -1;
           int element = s.top().first;
           s.pop();
           return element;
       }
       
       /*push element x into the stack*/
       void push(int x){
           
           if(s.empty()){
               s.push({x,x});
           }else{
               s.push({x,min(s.top().second,x)});
           }
       }
};

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
        //write code here
    }
    return 0;
}