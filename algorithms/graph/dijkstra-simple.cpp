#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// simple implementation of dijkstra algorithm with adjacency list
// this implementation is better suited for DENSE GRAPHS i.e. graphs with high number of edges
// time complexity: O(V+E + V^2) = O(V^2)
// V+E for traversing through adjacency list
// V^2 because while loop runs V times and in each while loop entire d[] is scanned
// space complexity: O(V) for vis and d

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
    vector<bool> vis(n, false);
    //d[i]==-1 means distance is infinity
    vector<int> d(n, -1);

    // node 0 is source
    d[0] = 0;
    int curr=0, nbr, wt, minNbr;

    while(curr!=-1){
        
        vis[curr] = true;
        minNbr = -1;

        //set distances of neighbours of curr node
        for(int i=0; i<adj[curr].size(); i++){
            nbr = adj[curr][i][0];
            if(vis[nbr]) continue;

            wt = adj[curr][i][1];
            if(d[nbr]==-1) d[nbr] = d[curr] + wt;
            else d[nbr] = min(d[nbr], d[curr]+wt);
        }

        //find unvisited node with least distance
        for(int i=0; i<n; i++){
            if(vis[i] || d[i]==-1) continue;
            if(minNbr==-1) minNbr = i;
            else minNbr = d[i]<d[minNbr] ? i : minNbr;
        }

        curr = minNbr;
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