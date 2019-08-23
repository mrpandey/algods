#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
//for greater<T>:
#include<functional>
//for pair<T,T>
#include<utility>

using namespace std;

// implementation of prim's algorithm using adjacency list and binary minheap (priority-queue)
// this implementation is better suited for SPARSE GRAPHS i.e. graphs with low number of edges
// prim's works for UNDIRECTED connected weighted graphs
// negative weights and self-loops are okay
// preprocessing can be used to handle parallel edges (in that case E isn't bounded by V^2)

// time complexity: O(ElogE) (which is same as O(ElogV) in case of simple graphs)
// because there is at max E push/pop in queue and each push/pop takes at max logE
// space complexity: O(E+V), E for queue and V for inmst/mst

int main(){

    //each edge is represented as {v1, v2, weight}
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
        //huge negative self-loop
        {3,3,-1000},
        {3,6,1},
        {4,5,2},
        {5,6,7},
    };

    //number of vertices
    int n = 7;
    int u, v, wt, e;

    // representation: adj[u] stores indices of edges incident on u
    vector<vector<int> > adj(n, vector<int>(0));

    //construct adjacency list from edges
    for(int i=0; i<edges.size(); i++){
        u = edges[i][0];
        v = edges[i][1];
        adj[u].push_back(i);
        //if edge isn't a self-loop
        if(u!=v) adj[v].push_back(i);
    }

    //PRIM'S ALGORITHM

    //inmst[u]==true means u is included in mst
    vector<bool> inmst(n, false);
    //stores edge indices of mst
    vector<int> mst;

    //q will store pairs in format {wt, edge_index}
    using pr = pair<int, int>;
    priority_queue< pr, vector<pr>, greater<pr> > q;

    //tree is initialised with node 0
    int mstwt=0, s=0;
    q.push({0,-1});

    while(!q.empty()){
        wt = q.top().first;
        e = q.top().second;
        q.pop();
        
        if(e==-1) u = s;
        else u = inmst[edges[e][0]] ? edges[e][1] : edges[e][0];

        if(inmst[u]) continue;  //redundant entry

        inmst[u] = true;
        if(e!=-1) mst.push_back(e);
        mstwt += wt;

        for(int i:adj[u]){
            v = edges[i][0] == u ? edges[i][1] : edges[i][0];
            wt = edges[i][2];
            if(!inmst[v]) q.push({wt,i});
        }
    }

    cout << "MST weight is " << mstwt << " and consists of following edges:" << endl;
    for(int i:mst){
        cout << edges[i][0] << " " << edges[i][1] << " " << edges[i][2] << endl;
    }

    return 0;
}