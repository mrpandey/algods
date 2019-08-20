#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//floyd-warshall finds shortest path length b/w ALL PAIRS of nodes
//it works for (un)directed, (un)weighted graphs

//negative weights are okay, but NO NEGATIVE CYCLES
//Like bellman-ford, it can be used to detect negative cycles

//parallel edges can be handled by only considering the least of them
//non-negative self-loops can be handled by ignoring them

//time-complexity: O(V^3)
//space-complexity: O(V^2)

//relevant link: https://math.stackexchange.com/questions/2952099/algorithm-for-modifying-graph-with-negative-cycles-to-be-able-to-conduct-floyd-w

int main(){

    vector<vector<int> > edges = {
        {0, 1, 4},
        {0, 3, 3},
        {1, 2, 1},
        {1, 4, 3},
        {2, 0, 2},
        {2, 5, 4},
        {2, 6, 3},
        {3, 6, -1},
        {5, 4, -3},
        {6, 2, -2},
        {6, 5, 1}
    };

    int n = 7;
    int inf = 1e9;

    //adj[i][j]=inf means no edge from i to j
    //adj[i][j]=k means edge of weight k from i to j
    vector<vector<int> > adj(n, vector<int>(n,inf));
    for(int i=0; i<n; i++) adj[i][i]=0;
    for(int i=0; i<edges.size(); i++) adj[edges[i][0]][edges[i][1]] = edges[i][2];

    //FLOYD-WARSHALL BEGINS

    vector<vector<int> > dp=adj, dpnext=adj;

    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dp[i][k]==inf || dp[k][j]==inf) dpnext[i][j] = dp[i][j];
                else dpnext[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
            }
        }
        dp.swap(dpnext);
    }

    //at this point, we can check for negative cycle
    //negative cycle exists iff dp[i][i]<0 for some i

    //print result
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(dp[i][j]!=inf) cout << dp[i][j] << "\t";
            else cout << "inf\t";
        }
        cout << endl;
    }

    return 0;
}