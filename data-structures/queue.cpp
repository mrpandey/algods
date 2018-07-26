#include<iostream>

using namespace std;

//link-list based queue implementation

//template based

template <class T>
class QNode {
    public:
        T val;
        QNode<T> *next, *prev;
        
        QNode(): next(NULL), prev(NULL) {}
        QNode(T v): val(v), next(NULL), prev(NULL) {}
};

template <class T>
class Queue {
    QNode<T> *head, *tail;
    int sz;

    public:

        Queue(): sz(0), head(NULL), tail(NULL) {}
        void push(T x);
        void pop();
        T front();
        T back();
        int size(){return sz;};
};

template <class T>
void Queue<T>::push(T x) {
    QNode<T> *p = new QNode<T>(x);
    if(tail) tail->prev = p;
    else head = p;
    p->next = tail;
    tail = p;
    sz++;
}

template <class T>
void Queue<T>::pop() {
    try{
        if(sz==0) throw string("Cannot pop from empty queue.");

        head = head->prev;
        delete head->next;
        sz--;
    }
    catch(string msg){
        cerr << msg << endl;
    }
}

template <class T>
T Queue<T>::front(){
    try {
        if(sz==0) throw string("Queue is empty. Cannot return front element.");

        return head->val;
    }
    catch (string msg){
        cerr << msg << endl;
    }
}

template <class T>
T Queue<T>::back(){
    try {
        if(sz==0) throw string("Queue is empty. Cannot return back element.");

        return tail->val;
    }
    catch (string msg){
        cerr << msg << endl;
    }
}

int main(){

    Queue<int> q;

    q.push(43);
    q.push(25);

    cout << q.size() << endl; //2
    
    q.push(33);
    cout << q.front() << endl; //43
    cout << q.back() << endl; //33

    q.pop();
    cout << q.front() << endl; //25
}