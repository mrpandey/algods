#include<iostream>

using namespace std;

//read this: https://stackoverflow.com/a/41338070/8216204

struct Node {
    int val;
    Node *left, *right, *parent;
    Node();
    Node(const int &);
    Node(const int &, Node*);
    ~Node();
};

Node::Node(){
    left = right = parent = nullptr;
}

Node::Node(const int &x) {
    val = x;
    left = right = parent = nullptr;
}

Node::Node(const int &x, Node* p) {
    val = x;
    parent = p;
    left = right = nullptr;
}

Node::~Node(){
    delete left;
    delete right;
}

// BINARY MAXHEAP BEGINS

class Maxheap {
    Node *root, *lastNode;
    int sz;
    void heapifyUp(Node*);
    void heapifyDown(Node*);

    public:

        Maxheap();
        int size();
        int top();
        void pop();
        void push(const int&);
        ~Maxheap();
};

Maxheap::Maxheap(){
    lastNode = root = nullptr;
    sz = 0;
}

Maxheap::~Maxheap(){
    delete root;
    //this calls ~Node() which deletes left and right childs
    //so all nodes are deleted resursively (including lastNode)
}

int Maxheap::size(){
    return sz;
}

//bubble up the nd value to maintain heap property in O(log n) time
void Maxheap::heapifyUp(Node *nd){
    if(nd==root) return;
    if(nd->parent->val >= nd->val) return;

    //swap val with parent
    int temp = nd->parent->val;
    nd->parent->val = nd->val;
    nd->val = temp;

    heapifyUp(nd->parent);
}

//bubble down the nd value to maintain heap property in O(log n) time
void Maxheap::heapifyDown(Node *nd){
    //find the biggest among nd and its children
    Node *bigger = nd;
    if(nd->left) bigger = nd->val >= nd->left->val ? nd : nd->left;
    if(nd->right) bigger = bigger->val >= nd->right->val ? bigger : nd->right;

    //either nd is biggest or it has no children
    if(bigger==nd) return;

    //swap val with bigger
    int temp = nd->val;
    nd->val = bigger->val;
    bigger->val = temp;

    heapifyDown(bigger);
}

int Maxheap::top(){
    try{
        if(!root) throw string("Error. Cannot call top() on empty heap.");
        else return root->val;
    }
    catch(string s){
        cout << s << endl;
    }
    return -1;
}

void Maxheap::push(const int &x){
    //if heap is empty
    if(!root){
        root = new Node(x);
        lastNode = root;
        sz++;
        return;
    }

    //if last node is left child of its parent
    if(lastNode->parent && lastNode==lastNode->parent->left){
        lastNode = lastNode->parent;
        lastNode->right = new Node(x, lastNode);
        lastNode = lastNode->right;
        sz++;
        heapifyUp(lastNode);
        return;
    }

    //if control reaches here, last node is either root or right child of its parent
    //find the node where to insert new node in O(log n) time
    Node *p = lastNode;
    while(p->parent && p==p->parent->right) p = p->parent;
    if(p->parent) p = p->parent->right; //p non-null guaranteed
    while(p->left) p = p->left;

    //insert node at p
    p->left = new Node(x, p);
    lastNode = p->left;
    sz++;
    heapifyUp(lastNode);
}

void Maxheap::pop(){
    if(!sz) return;

    if(sz==1){
        delete root;
        root = lastNode = nullptr;
        sz = 0;
        return;
    }

    //swap val b/w root and last node
    int temp = root->val;
    root->val = lastNode->val;
    lastNode->val = temp;

    //before deleting current lastNode, find node that will become new lastNode
    Node *p = lastNode;
    //parent is guaranteed to exist coz sz>1
    if(p==p->parent->right) {
        p = p->parent->left;
    }
    else {
        while(p->parent && p==p->parent->left) p=p->parent;
        if(p->parent) p=p->parent->left;
        while(p->right) p = p->right;
    }

    //delete current lastNode
    Node *prnt = lastNode->parent;
    if(lastNode==prnt->left){
        delete lastNode;
        prnt->left = nullptr;
    }
    else {
        delete lastNode;
        prnt->right = nullptr;
    }

    //update lastNode
    lastNode = p;
    sz--;
    heapifyDown(root);
}

int main(){

    Maxheap h;

    cout << h.size() << endl;   //prints 0

    //push 2, 4, 6, ..., 40
    for(int i=1; i<=20; i++) h.push(2*i);

    while(h.size()){
        //prints: 40, 38, 36, ..., 2
        cout << h.top() << endl;
        h.pop();
    }

    cout << h.size() << endl;   //prints 0

    return 0;
}