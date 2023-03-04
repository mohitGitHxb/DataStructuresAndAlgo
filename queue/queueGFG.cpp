#include <bits/stdc++.h>
using namespace std;

/* Queue implementation using array */
// class Queue{
//     public:
//     unsigned size;
//     unsigned capacity;
//     int* arr;
//     Queue(unsigned int c){
//         capacity = c;
//         size = 0;
//         arr = new int[capacity];
//     }
//     void enqueue(int x);
//     void dequeue(void);
//     int getFront(void);
//     int getRear(void);
//     bool isFull(void);
//     bool isEmpty(void);
//     int getSize(void);
// };
// void Queue::enqueue(int x){
//     if(isFull())return;
//     arr[size] = x;
//     size++;
// }
// void Queue::dequeue(void){
//     if(isEmpty())return ;
//     for (int i = 0; i < size-1; i++)
//     {
//         arr[i] = arr[i+1];
//     }
//     size--;
// }
// int Queue::getFront(void){
//     if(isEmpty()){
//         return -1;
//     }
//     return 0;
// }
// int Queue::getRear(void){
//     if(isEmpty())return -1;
//     return size-1;
// }
// int Queue::getRear(void){
//   return size;
// }
// bool Queue::isFull(void){
//     return capacity==size;
// }
// bool Queue::isEmpty(void){
//     return size==0;
// }

/*
 *Queue using linked lists.. */

// struct Node
// {
//     int data;
//     Node *next;
//     Node(int x)
//     {
//         data = x;
//         next = NULL;
//     }
// };

// class Queue
// {
// private:
// public:
//     Node *front;
//     Node *rear;
//     Queue(int);
//     ~Queue();
//     void Enqueue(int x)
//     {
//         Node *temp = new Node(x);
//         if (front == NULL)
//         {
//             front = rear = temp;
//             return;
//         }
//         rear->next = temp;
//         rear = temp;
//     }
//     void Dequeue(void)
//     {
//         if (front == NULL)
//             return;
//         Node *temp = front;
//         front = front->next;
//         if (front == NULL)
//         {
//             rear = NULL;
//         }
//         delete(temp);
//     }

//     int getFront(void){
//         return front->data;
//     }
//     int getRear(void){
//         return rear->data;
//     }
//     bool isEmpty(void){
//         return (front==NULL);
//     }
// };

// Queue::Queue(int x)
// {
//     front = NULL;
//     rear = NULL;
// }

// Queue::~Queue()
// {
// }

/*
 *Dequeue using doubly LL */
// struct Node
// {
//     int data;
//     Node *prev, *next;
//     // Function to get a new node
//     static Node* getnode(int data)
//     {
//         Node* newNode = (Node*)malloc(sizeof(Node));
//         newNode->data = data;
//         newNode->prev = newNode->next = NULL;
//         return newNode;
//     }
// };

// class Deque{
//     Node* front;
//     Node* rear;
//     int Size;
//     public:
//     Deque(){
//         front=rear=NULL;
//         Size=0;
//     }
//     void insertFront(int);
//     void insertRear(int);
//     void deleteFront();
//     void deleteRear();
//     bool isEmpty(){
//         return front==NULL;
//     }
//     int getFront(){
//         if(front!=NULL)
//         return front->data;
//         return -1;
//     }
//     int getRear(){
//         if(rear!=NULL){
//             return rear->data;
//         }
//         return -1;
//     }
// };

// void Deque::insertFront(int val) {
//     // Your code here
//     // Node* temp = getnode(data);
// Node* newNode = new Node;
//         newNode->data = val;
//         Size++;
//         if (front == NULL) {
//             rear = front = newNode;
//         } else {
//             newNode->next = front;
//             front->prev = newNode;
//             front = newNode;
//         }
// }

// // Function to insert an element
// // at the rear end
// void Deque::insertRear(int val) {
//     // Your code here
//     // Node* temp = getnode(data);
// Node* newNode = new Node;
//         newNode->data = val;
//         Size++;
//         if (rear == NULL) {
//             rear = front = newNode;
//         } else {
//             rear->next = newNode;
//             newNode->prev = rear;
//             rear = newNode;
//         }
// }

// // Function to delete the element
// // from the front end
// void Deque::deleteFront() {
//     // Your code here
//     if (isEmpty()) {
//             // cout << "UNDERFLOW" << nl;
//         } else if (front == rear) { // only one node
//             front = rear = NULL;
//             Size--;
//         } else {
//             Node* temp = front;
//             front = front->next;
//             delete temp;
//             Size--;
//         }
// }

// // Function to delete the element
// // from the rear end
// void Deque::deleteRear() {
//     // Your code here
//        if (isEmpty()) {
//             // cout << "UNDERFLOW" << nl;
//         } else if (front == rear) { // only one node
//             front = rear = NULL;
//             Size--;
//         } else {
//             Node* temp = rear;
//             rear = rear->prev;
//             delete temp;
//             Size--;
//         }

// }

/*
?deque using circular arrays(efficient approach) */
// struct Deque
// {
//     int *arr;
//     int front,cap,size;
//     Deque(int c){
//         arr=new int[c];
//         cap=c;
//         front=size=0;
//     }
//     bool isFull(){
//         return size==cap;
//     }
//     bool isEmpty(){
//         return size==0;
//     }
//     void insertFront(int x){
//         if(isFull)return;
//         front=(front-1+cap)%cap;
//         arr[front]=x;
//         size++;
//     }
//     void insertRear(int x){
//         //!  rear=(rear+1)%cap;
//         //?  rear=(front+size-1)%cap;
//         if(isFull())return ;
//         int new_rear=(front+size)%cap;
//         arr[new_rear]=x;
//         size++;
//     }
//     void deleteFront(){
//         if(isEmpty())return;
//         front=(front+1)%cap;
//         size--;
//     }
//     void deleteRear(){
//         if(isEmpty())return;
//         size--;
//         // rear=(rear-1+cap)%cap;
//     }
//     int getFront(){
//         if(isEmpty())return INT_MIN;
//         else return arr[front];
//     }
//     int getRear(){
//         if(isEmpty()) return INT_MIN;
//         else return arr[(front+size-1)%cap];
//     }
// };

// ? Print queue
void displayQueue(queue<int> q)
{
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << "\n";
}
/*
?reverse a queue iterative and recursive approach */
// void reverseQueue(queue<int> &q){
//     stack<int> s;
//     while (!q.empty())
//     {
//         s.push(q.front());
//         q.pop();
//     }
//     while (!s.empty())
//     {
//         q.emplace(s.top());
//         s.pop();
//     }
// }

// void reverseQueueRecursive(queue<int> &q){
//     if(q.empty())return;
//     int x = q.front();
//     q.pop();
//     reverseQueueRecursive(q);
//     q.push(x);
// }

// ^generate numbers with given digits {5,6} eg:5,6,55,56,65,66..
/* void printFirstN(int n){
    queue<string> q;
    q.push("5");
    q.push("6");
    for (int i = 0; i < n; i++)
    {
        string curr = q.front();
        cout<<curr<<" ";
        q.pop();
        q.push(curr+"5");
        q.push(curr+"6");
    }

} */

// ^maximum in all subarrays of size k

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
        dq.push_back(i);
    }
    cout << arr[dq.front()] << " ";
}

/*
^first circular tour
^ Consider an arrangement where n petrol pumps are arranged in a circular manner.
^ We need to find the first petrol pump from where we can visit all petrol pumps and come back to the petrol pump without ever going out of the petrol. */

//!Naive approach
// int findPetrolPump(vector<int> &petrol,vector<int> &distance,int n){
//     for (int start = 0; start < n; start++)  //?starting off from each petrol pump and calc. petrol left for each destination.
//     {
//         int currentPetrol=0;
//         int end=start;
//         while (true)
//         {
//             currentPetrol+=(petrol[end]-distance[end]); //? check if petrols goes -ve.
//             if(currentPetrol<0)break;
//             end=(end+1)%n; //~ traversing in circular way to reach the initial position where we started
//             if(end==start) //~ if we reach the position, also the petrol left is not -ve.
//                 return start+1;    
//         }   
//     }
// }


//*Efficient approach
int findPetrolPump(vector<int> &petrol,vector<int> &distance,int n){
    int start=0,currentPetrol=0,prevPetrol=0;
    for (int i = 0; i < n; i++)
    {
        currentPetrol+=(petrol[i]-distance[i]);
        if(currentPetrol<0){
            start=i+1;
            prevPetrol+=currentPetrol;
            currentPetrol=0;
        }
    }
    return((currentPetrol+prevPetrol)>=0)?start+1:-1;
    
}

//~ custom data structure with min/max operations
struct customDs{
    deque<int> dq;
    void insertMin(int x){
        dq.emplace_front(x);
    }
    void insertMax(int y){
        dq.emplace_back(y);
    }
    int getMin(void){return dq.front();}
    int getMax(void){return dq.back();}
    void eraseMin(void){dq.pop_front();}
    void eraseMax(void){dq.pop_back();}
};
int main(int argc, char const *argv[])
{
    // queue<int> q;
    // q.push(10);
    // q.push(20);
    // q.push(40);
    // q.push(50);
    // displayQueue(q);
    // reverseQueueRecursive(q);
    // displayQueue(q);

    // vector<int> v{1, 2, 3, 1, 4, 5, 2, 3, 6};
    // printMaxSubarray(v, 3);
    return 0;
}
