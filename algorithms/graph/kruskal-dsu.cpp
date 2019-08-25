#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//kruskal's algorithm finds minimum spanning FOREST for a graph
//the graph must be UNDIRECTED and weighted
//negative weights are okay

//when graph is connected, we get a min spanning tree
//parallel edges can be handled by considering only the least weighted edge b/w any pair of nodes
//self-loops are ignored

//this implementation uses DSU to determine components in which a node lies
//time complexity: O(ElogE + ElogV) = O(ElogV)
//ElogE for sorting, and ElogV because of DSU operations on E edges
//space complexity: O(V)
//naive implementation takes O(ElogE + V^2) time and O(V) space

//NOTE: if union by rank is used alone for DSU, then E DSU operations take ElogV amortized time
//union by rank combined with path compression takes constant time (amortized) for DSU operations
//this implementation uses both rank union and path compression

bool comp(vector<int> &a, vector<int> &b){
    return a[2]<b[2];
}

int find(int x, vector<int> &p){
    if(p[x]!=x) p[x] = find(p[x], p);
    return p[x];
}

void unite(int x, int y, vector<int> &p, vector<int> &sz){
    int px = find(x, p);
    int py = find(y, p);
    if(px==py) return;
    
    if(sz[px]>=sz[py]){
        sz[px] += sz[py];
        p[py] = px;
    }
    else {
        sz[py] += sz[px];
        p[px] = py;
    }
}

int main(){

    //each edge is represented as {v1, v2, weight}
    vector<vector<int> > edges = {
        {0, 1, -3},
        {0, 2, 5},
        {0, 3, 0},
        {1, 2, 6},
        {1, 4, 10},
        {2, 3, 4},
        {2, 4, 2},
        {3, 4, 1},
        //another component
        {5, 6, 2},
        {5, 7, 7},
        {5, 8, 8},
        {6, 8, 3},
        {7, 8, 1},
        //another component
        {9, 10, 2}
    };

    int n=11, msfwt=0, u, v, wt, pu, pv;
    sort(edges.begin(), edges.end(), comp);

    //msf stores indices of edges selected for msf
    //p and sz represent parent and size arrays for DSU
    vector<int> msf, p(n, 0), sz(n,1);
    for(int i=0; i<n; i++) p[i]=i;

    for(int i=0; i<edges.size(); i++){
        u = edges[i][0];
        v = edges[i][1];
        wt = edges[i][2];

        pu = find(u, p);
        pv = find(v, p);
        //ignore if present in same component
        //this condition also handles self-loops
        if(pu==pv) continue;

        unite(pu, pv, p, sz);
        msf.push_back(i);
        msfwt += wt;
    }

    cout << "The weight of min spanning forest is " << msfwt << " and the edges are" << endl;

    for(int i:msf) cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;

    /* output is:
    The weight of min spanning forest is 8 and the edges are
    0 1 -3
    0 3 0
    3 4 1
    7 8 1
    2 4 2
    5 6 2
    9 10 2
    6 8 3
    */

    return 0;
}