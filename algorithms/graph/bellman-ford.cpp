#include<iostream>
#include<vector>
#include<climits>

using namespace std;

//bellman-ford is used to find shortes path length of all nodes from SINGLE SOURCE

//time complexity: O(VE) when graph is given as edge list
//space complexity: O(V) for storing d

//bellman-ford works for directed/undirected weighted graphs
//with possible negative weights, but NO NEGATIVE CYCLES.
//parallel edges and self-loops are okay, but self-loops can't be negative

int main(){
    //graph is taken as set of V, and set of E
    //vertices are numbered from 0 to 6
    //edges are directed and have form {source, target, weight}
    vector<vector<int> > edges = {
        {0, 1, 5},
        {0, 2, 7},
        {1, 4, 4},
        {2, 0, -4},
        {2, 5, 1},
        {3, 0, 2},
        {4, 2, -3},
        {4, 5, 2},
        {5, 6, 0},
        {6, 2, 2},
        {6, 3, 1}
    };

    //INT_MAX is used as infinity
    vector<int> d(7, INT_MAX);
    //0 is source
    d[0] = 0;

    //run |V|-1 times
    int u, v, wt, k = 6;
    while(k--){
        for(int i=0; i<edges.size(); i++){
            u = edges[i][0];
            v = edges[i][1];
            wt = edges[i][2];
            
            if(d[u]!=INT_MAX && d[u]+wt < d[v]) d[v] = d[u]+wt;
        }
    }

    //check for negative cycle
    bool ok = true;
    for(int i=0; i<edges.size(); i++){
        u = edges[i][0];
        v = edges[i][1];
        wt = edges[i][2];
        //if d[u]==INT_MAX, then its unreachable
        if(d[u]!=INT_MAX) continue;
        if(d[u]+wt < d[v]){
            cout << "There exists a negative cycle in graph" << endl;
            ok = false;
        }
    }

    if(ok){
        for(int i=0; i<d.size(); i++) cout << "d(" << i << ") = " << d[i] << endl;
    }

    //output:
    // d(0) = 0
    // d(1) = 5
    // d(2) = 6
    // d(3) = 8
    // d(4) = 9
    // d(5) = 7
    // d(6) = 7

    return 0;
}