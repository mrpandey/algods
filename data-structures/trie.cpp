#include<iostream>

using namespace std;

// implementation of trie (prefix tree) which stores strings consisting of lowercase english alphabets
// find, insert, remove each take O(n) where n is length of string

struct Node {
    bool isEnd = false;
    int child = 0;
    Node* alph[26] = {nullptr};
    ~Node();
};

Node::~Node(){
    for(int i=0; i<26; i++){
        if(alph[i]) delete alph[i];
    }
}

class Trie{
    Node* root;

    public:

        Trie();
        ~Trie();
        bool find(const string &s);
        void insert(const string &s);
        void remove(const string &s);
};

Trie::Trie(){
    root = new Node();
}

Trie::~Trie(){
    delete root;
}

bool Trie::find(const string &s){
    int n = s.size();

    Node *cur = root;
    for(int i=0, ch; i<n; i++){
        ch = s[i]-'a';
        if(ch<0 || ch>25) return false;
        if(cur->alph[ch]) {
            cur = cur->alph[ch];
        }
        else return false;
    }

    return cur->isEnd;
}

void Trie::insert(const string &s){
    int n = s.size();
    if(!n) return;
    for(int i=0; i<n; i++) if(s[i]-'a'<0 || s[i]-'a'>25) return;

    Node *cur = root;
    int i=0, ch;
    while(true) {
        if(i==n) {
            cur->isEnd = true;
            return;
        }

        ch = s[i]-'a';
        if(cur->alph[ch]) {
            cur = cur->alph[ch];
            i++;
        }
        else break;
    }

    while(i<n){
        ch = s[i]-'a';
        cur->alph[ch] = new Node();
        cur->child++;
        cur = cur->alph[ch];
        i++;
    }
    cur->isEnd = true;
}

void Trie::remove(const string &s){
    int n = s.size();
    if(!n) return;

    Node *cur=root, *p=root;
    int i=0, j=0, ch;
    while(i<n){
        ch = s[i]-'a';
        if(ch<0 || ch>25) return;
        if(!(cur->alph[ch])) return;

        if(cur->child>1 || cur->isEnd) {
            p = cur;
            j = i;
        }
        cur = cur->alph[ch];
        i++;
    }

    if(cur->child) cur->isEnd = false;
    else {
        ch = s[j]-'a';
        delete p->alph[ch];
        p->alph[ch] = nullptr;
        (p->child)--;
    }
}

int main(){
    Trie t;

    t.insert("git");
    t.insert("gitlab");
    t.insert("github");
    cout << t.find("git") << endl;
    cout << t.find("gitlab") << endl;
    cout << t.find("github") << endl;
    t.remove("gitlab");
    cout << t.find("git") << endl;
    cout << t.find("gitlab") << endl;
    cout << t.find("github") << endl;
}