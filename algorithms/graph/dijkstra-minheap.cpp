#include<iostream>
#include<vector>
#include<algorithm>
//priority_queue is in <queue>
#include<queue>
//for greater<T>:
#include<functional>
//for pair<T,T>
#include<utility>

using namespace std;

// implementation of dijkstra algorithm with adjacency list and min binary heap (priority_queue)
// this implementation is better suited for SPARSE GRAPHS i.e. graphs with low number of edges

// time complexity: O( VlogV + ElogV ) = O( (V+E)logV ) which becomes O( ElogV ) when graph is dense.
// VlogV because while loop runs V times, and each time we pop the nearest node in logV
// ElogV because the for loop inside while loop runs E times, and a node may be pushed in logV
// space complexity: O(E), at max one entry in queue per edge

// NOTE: priority_queue in STL does not supports decrease-priority function.
// So when we update a node's distance, we re-push it into queue.
// Among the duplicates, the one with least distance is popped first and utilised.
// When the rest duplicates are encountered, we simply pop them without utilising because they are redundant.
// So now the toal number of push/pop are E instead of V, and while loop runs a maximum of E times.
// So time complexity is O( ElogE + ElogE ) = O( ElogE )
// Since E<=V^2, this complexity is same as previous one (ElogV).
// Read answers on this post: https://stackoverflow.com/questions/9255620/why-does-dijkstras-algorithm-use-decrease-key

// dijkstra's algorithm works for directed/undirected graph with non-negative weights
// parallel edges and self-loops are okay as long as they have non-negative weights
// If parallel edges are there, then E isn't bounded by V^2
// Among parallel edges, its best to consider only those edges with least weights (not done in this implementation)

int main(){

    // there is an edges b/w node adj[i][j][0] and  node i having weight adj[i][j][1]
    vector<vector<vector<int> > > adj = {
        { {1,2}, {2,5}, {3,6} },
        { {0,2}, {2,2}, {4,1} },
        { {1,2}, {0,5}, {6,9} },
        { {0,6}, {6,4} },
        { {1,1}, {5,1}, {6,4}, {8,2} },
        { {4,1}, {7,3} },
        { {2,9}, {3,4}, {4,4}, {7,2} },
        { {5,3}, {6,2} },
        { {4,2} }
    };

    int n = adj.size();
    //d[i]==-1 means distance is infinity
    vector<int> d(n, -1);
    
    //priority-queue pairs have format {distance, node-index}
    using pr = pair<int, int>;
    priority_queue< pr, vector<pr>, greater<pr> > q;

    //0 is source
    d[0] = 0;
    q.push({0,0});

    int u, du, v, wt;

    while(!q.empty()){
        u = q.top().second;
        du = q.top().first;
        q.pop();

        //no need to process outdated duplicate entries
        if(du!=d[u]) continue;

        for(int i=0; i<adj[u].size(); i++){
            v = adj[u][i][0];
            wt = adj[u][i][1];

            if(d[v]==-1 || du+wt < d[v]) {
                d[v] = du+wt;
                q.push({d[v],v});
            }
        }
    }
    
    for(int i=0; i<n; i++){
        cout << "d(" << i << ") = " << d[i] << "\n";
    }

    /* output:
    d(0) = 0
    d(1) = 2
    d(2) = 4
    d(3) = 6
    d(4) = 3
    d(5) = 4
    d(6) = 7
    d(7) = 7
    d(8) = 5
    */

    return 0;
}