#include<iostream>
#include<vector>
#include<queue>

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

    //bfs

    //nodes that are encountered first
    //are visited first
    queue<int> q;

    //vis keeps track whether node is visited
    vector<bool> vis(adj.size(), false);

    //add node where traversal will begin
    q.push(0);
    vis[0] = true;
    int u=0, v=0;

    while(!q.empty()){
        
        //u is current node
        u = q.front();
        q.pop();
        cout << u << " ";

        //add unvisited neighbours of u to q
        for(int v:adj[u]){
            if(!vis[v]){
                q.push(v);
                vis[v] = true;
            }
        }
    }
    
    cout << endl;

    //output: 0 1 2 3 4 5 6 7 8
}