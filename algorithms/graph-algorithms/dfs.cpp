#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int main(){

    //graph represented as adjacency list
    vector<vector<int> > adj = {
        {1,2,3},
        {0,4},
        {0,3,5},
        {0,2,6},
        {1,5,7},
        {2,4},
        {3,7},
        {4,6,8},
        {7},
    };

    //dfs

    stack<int> s;
    
    //vis[u]==true iff u is visited
    vector<bool> vis(adj.size(), false);

    s.push(0);
    vis[0] = true;

    int u=0;

    while(!s.empty()){
        u = s.top();
        s.pop();

        cout << u << " ";

        for(int v:adj[u]){
            if(!vis[v]){
                s.push(v);
                vis[v] = true;
            }
        }
    }

    cout << endl;

    //output: 0 3 6 7 8 4 5 2 1
    //compare this with bfs output
}