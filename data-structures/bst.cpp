#include<iostream>

using namespace std;

class Node {
public:
    int val;
    Node *left, *right;
    Node();
    Node(int);
};

Node::Node(): left(NULL), right(NULL) {};
Node::Node(int v): val(v), left(NULL), right(NULL) {};

class BST {
    Node *root;
    int sz;
    
    void inorderPrint(Node*);
    Node* removeNode(Node*, const int &);
    void destructTree(Node*);

public:

    BST();
    ~BST();
    bool find(const int &);
    void insert(const int &);
    void print();
    void remove(const int &);
    int size();
};

BST::BST(){
    root = NULL;
    sz = 0;
}

BST::~BST(){
    destructTree(root);
}

void BST::destructTree(Node* nd){
    if(!nd) return;
    destructTree(nd->left);
    destructTree(nd->right);
    delete nd;
}

bool BST::find(const int &x) {
    Node *nd = root;

    while(nd) {
        if(nd->val == x) return true;
        else if(x < nd->val) {
            nd = nd->left;
        }
        else {
            nd = nd->right;
        }
    }

    return false;
}

void BST::inorderPrint(Node *nd) {
    if(!nd) return;
    inorderPrint(nd->left);
    cout << nd->val << " ";
    inorderPrint(nd->right);
}

void BST::insert(const int &x) {

    if(!root){
        root = new Node(x);
        sz = 1;
        return;
    }

    Node *nd = root;

    while(true) {
        if(x <= nd->val) {
            if(!nd->left) {
                nd->left = new Node(x);
                break;
            }
            else nd = nd->left;
        }
        else {
            if(!nd->right) {
                nd->right = new Node(x);
                break;
            }
            else nd = nd->right;
        }
    }

    sz++;
}

void BST::print() {
    inorderPrint(root);
    cout << "\n";
}

Node* BST::removeNode(Node* nd, int const &x) {
    if(!nd) return NULL;
    Node* temp = NULL;
    
    if(x < nd->val) {
        nd->left = removeNode(nd->left, x);
        return nd;
    }
    if(x > nd->val) {
        nd->right = removeNode(nd->right, x);
        return nd;
    }

    //cases for nd->val==x below

    //no child
    if(!nd->left && !nd->right){
        delete nd;
        return NULL;
    }
    //only right child
    if(!nd->left) {
        temp = nd->right;
        delete nd;
        return temp;
    }
    //only left child
    if(!nd->right) {
        temp = nd->left;
        delete nd;
        return temp;
    }

    //nd has both childs
    //swap value with inorder successor, and delete successor
    Node* succ = nd->right;
    while(succ->left) succ = succ->left;
    nd->val = succ->val;
    succ->val = x;
    nd->right = removeNode(nd->right, x);
    return nd;
}

void BST::remove(const int &x) {
   if(!root) return;
   root = removeNode(root, x);
   sz--;
}

int BST::size() {
    return sz;
}

int main() {
    BST t;
    t.insert(30);
    t.insert(20);
    t.insert(25);
    t.insert(40);
    t.insert(35);
    
    cout << t.size() << "\n";   //5

    t.insert(45);
    t.insert(50);
    t.insert(42);
    t.insert(38);
    t.insert(-1);

    cout << t.size() << "\n";   //10

    t.remove(30);
    cout << t.size() << "\n";   //9

    if(t.find(30)) cout << "Bad news!! Not working.\n"; //not printed
    if(t.find(-1)) cout << "Good news!! -1 found.\n";   //printed

    t.remove(40);
    cout << t.size() << "\n";   //8
    t.print();  //-1 20 25 35 38 42 45 50

    t.remove(45);
    t.print();  //-1 20 25 35 38 42 50

    t.remove(50);
    t.print();  //-1 20 25 35 38 42

    return 0;
}
