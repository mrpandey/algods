#include<iostream>
#include<vector>

using namespace std;

class Maxheap {
    vector<int> a;

    public:

        Maxheap();
        Maxheap(vector<int>);

        int size();
        bool empty();
        void heapify(int, int&);
        int top();
        void push(int);
        void pop();
};

Maxheap::Maxheap(){
    a = {};
}

//Construct maxheap from given array
//Time Complexity: O(n), where n = b.size()
Maxheap::Maxheap(vector<int> b){
    a = b;
    if(a.size()<2) return;

    int sz = a.size();

    //no need to heapify leaf nodes
    //(size-2)/2 is parent index of last leaf
    for(int i=sz/2-1; i>=0; i--){
        heapify(i, sz);
    }
}

int Maxheap::size(){
    return a.size();
}

bool Maxheap::empty(){
    return a.empty();
}

//puts the element at i at right place
void Maxheap::heapify(int i, int &sz){
    //left and right childs
    int l=2*i+1, r=l+1;

    //index of bigger element in l,r,i
    int bigger=i;

    if(l<sz && a[l]>a[i]) bigger=l;
    if(r<sz && a[r]>a[bigger]) bigger=r;

    if(bigger!=i){
        int temp = a[i];
        a[i] = a[bigger];
        a[bigger] = temp;
        heapify(bigger, sz);
    }
}

//return the max-element (root value)
int Maxheap::top(){
    try {
        if(a.empty()) throw string("The heap is empty. Cannot access top element.\n");

        return a[0];
    }
    catch(string msg) {
        cout << msg;
    }
}

//insert into heap
void Maxheap::push(int x){
    a.push_back(x);
    
    //now put x at right position

    int i = a.size()-1;
    int p = (i-1)/2, temp=0;

    while(i>0 && a[p]<a[i]){
        temp = a[i];
        a[i] = a[p];
        a[p] = temp;
        i = p;
        p = (p-1)/2;
    }
}

//remove root
void Maxheap::pop(){
    try{
        int sz = a.size();
        if(sz==0) throw string("Cannot pop from empty heap.\n");
        if(sz==1) {a.clear(); return;}

        //swap root with last leaf
        sz--;
        int temp = a[sz];
        a[sz] = a[0];
        a[0] = temp;
        
        a.erase(a.begin()+sz);
        heapify(0, sz);
    }
    catch(string msg){
        cout << msg;
    }
}

int main(){

    Maxheap h({4, 5, 3, 8, 2, 10, 7});

    cout << h.size() << endl;   //7
    cout << h.top() << endl;    //10

    h.pop();
    cout << h.size() << endl;   //6
    cout << h.top() << endl;    //8

    h.push(9);
    cout << h.size() << endl;   //7
    cout << h.top() << endl;    //9
}