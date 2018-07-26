#include<iostream>
#define MAX 10000

using namespace std;

class Stack {
    int a[MAX];
    int sz;

    public:
        Stack(){sz=0;}
        void push(int x);
        void pop();
        int top();
        int size();
};

void Stack::push(int x){
    try {
        if(sz>=MAX) throw string("Cannot push in stack. It's full.");
        a[sz++] = x;
    }
    catch(string msg) {
        cerr << msg << endl;
    }
}

void Stack::pop(){
    try {
        if(sz==0) throw string("Cannot pop from empty stack.");
        sz--;
    }
    catch(string msg) {
        cerr << msg << endl;
    }
}

int Stack::top(){
    try {
        if(sz==0) throw string("Cannot pop from empty stack.");
        return a[sz-1];
    }
    catch(string msg) {
        cerr << msg << endl;
    }
}

int Stack::size(){
    return sz;
}

int main(){
    Stack s;
    s.push(12);
    s.push(21);
    s.push(9);

    cout << s.size() << endl; //3
    cout << s.top() << endl; //9

    s.pop();
    cout << s.size() << endl; //2
    cout << s.top() << endl; //21

    s.pop();
    s.pop();
    s.pop(); //Cannot pop from empty stack
}