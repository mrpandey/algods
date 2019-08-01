#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
//for greater<T>:
#include<functional>
//for pair<T,T>
#include<utility>

using namespace std;

// implementation of prim's algorithm using adjacency matrix
// this implementation is better suited for DENSE GRAPHS i.e. graphs with high number of edges

// time complexity: O(V^2)
// space complexity: O(V) ignoring the adjacency matrix

// prim's works for undirected connected weighted graphs
// negative weights, self-loops and parallel edges are okay
// Among parallel edges, consider only those with least weights (this will add extra time complexity of E which might be larger than V^2)

int main(){

    //each edge is represented as {v1, v2, weight}
    //this graph contains parallel edges and self loops
    vector<vector<int> > edges = {
        {0,1,11},
        {0,1,3},
        {0,2,4},
        {0,3,5},
        {1,2,-6},
        {1,4,-4},
        {2,5,3},
        {2,6,0},
        {2,6,-1},
        {3,3,-1000},
        {3,6,1},
        {4,5,2},
        {5,6,7},
    };

    //number of vertices
    int n = 7;
    int u, v, e;

    // representation: adj[u][v] stores indices of edges incident on u
    vector<vector<int> > adj(n, vector<int>(n,-1));

    //construct adjacency matrix from edges
    for(int i=0; i<edges.size(); i++){
        u = edges[i][0];
        v = edges[i][1];
        if(adj[u][v]==-1) adj[v][u] = adj[u][v] = i;
        else if(edges[adj[u][v]][2]>edges[i][2]) adj[v][u] = adj[u][v] = i;
    }

    //PRIM'S ALGORITHM

    //inmst[u]==true means u is included in mst
    vector<bool> inmst(n, false);
    //min_e[u] = index of edge from u to mst having min weight
    vector<int> min_e(n, -1);
    //stores edge indices of mst
    vector<int> mst(n-1, -1);
    int mi = 0;

    //tree is initialised with node 0
    int mstwt=0, s=0;
    inmst[s] = true;
    //relax neighbours of s
    for(v=0; v<n; v++){
        if(adj[s][v]!=-1 && !inmst[v]){
            if(min_e[v]==-1 || edges[min_e[v]][2] > edges[adj[s][v]][2]) min_e[v] = adj[s][v];
        }
    }

    //add suitable n-1 edges in mst
    for(int i=0; i<n-1; i++){

        u = -1;
        //find nearest node note in mst
        for(v=0; v<n; v++){
            if(!inmst[v]) {
                if(u==-1 || min_e[u]==-1) u = v;
                else if( min_e[v]!=-1 && edges[min_e[v]][2] < edges[min_e[u]][2] ) u = v;
            }
        }

        if(u==-1 || min_e[u]==-1){
            cout << "No spanning tree" << endl;
            return 0;
        }

        //add node and edge in mst
        inmst[u] = true;
        mst[mi++] = min_e[u];
        mstwt += edges[min_e[u]][2];

        //relax neighbors of u
        for(v=0; v<n; v++){
            if(adj[u][v]!=-1 && !inmst[v]){
                if(min_e[v]==-1 || edges[min_e[v]][2] > edges[adj[u][v]][2]) {
                    min_e[v] = adj[u][v];
                }
            }
        }
    }

    cout << "MST weight is " << mstwt << " and consists of following edges:" << endl;
    for(int i:mst){
        cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
    }

    return 0;
}