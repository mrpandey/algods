#include<iostream>
#include<stack>
#include<vector>

using namespace std;

//E=no. of edges
//V=no. of vertics (nodes)
//Time complexity: O(V+E)
//Extra-Space Complexity: O(n)

//https://stackoverflow.com/questions/11468621/why-is-the-time-complexity-of-both-dfs-and-bfs-o-v-e

//further the time complexity will be O(v^2)
//when using adjacency matrix instead of adjacency list

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