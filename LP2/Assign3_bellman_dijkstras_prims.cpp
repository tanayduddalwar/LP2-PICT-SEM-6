#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

void bellmanford(int start, vector<vector<pair<int, int>>> &adj, int nodes) {
    vector<int> dist(nodes, INT_MAX);
    dist[start] = 0;
// Here the logic is in bellman ford we relax the edges v-1 times so i have ran the loop nodes-1 times
    for (int i = 0; i < nodes - 1; i++) {
        for (int u = 0; u < nodes; u++) {
            for (auto it : adj[u]) {
                int v = it.first;
                int weight = it.second;
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < nodes; u++) {
        for (auto it : adj[u]) {
            int v = it.first;
            int weight = it.second;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                cout << "Graph contains a negative weight cycle!" << endl;
                return;
            }
        }
    }
    cout << "Shortest distances from node " << start << ":" << endl;
    for (int i = 0; i < nodes; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << ": Unreachable" << endl;
        else
            cout << "Node " << i << ": " << dist[i] << endl;
    }
}
void dijkstra(int start, vector<vector<pair<int, int>>> &adj, int nodes){
    vector<int>dist(nodes,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    dist[start]=0;
    pq.push({0,start});
    while(!pq.empty()){
        int node=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        for(auto it:adj[node]){
            int v=it.first;
            int weight=it.second;
            if(cost+weight<dist[v]){
                dist[v]=cost+weight;
                pq.push({dist[v],v});
            }
        }
    }
    cout << "Shortest distances from node " << start << ":" << endl;
    for (int i = 0; i < nodes; i++) {
        if (dist[i] == INT_MAX)
            cout << "Node " << i << ": Unreachable" << endl;
        else
            cout << "Node " << i << ": " << dist[i] << endl;
    }
}
int prims(vector<vector<pair<int, int>>> &adj, int nodes) {
   int ans=0;
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
   pq.push({0,0});
   vector<bool>visited(nodes,false);
   while(!pq.empty()){
    auto it=pq.top();
    int cost=it.first;
    int node=it.second;
    pq.pop();
    if(visited[node])continue;
    visited[node]=true;
    ans=ans+cost;
    for(auto it:adj[node]){
        if(!visited[it.first]){
            pq.push({it.second,it.first});
        }
    }

   }


    return ans;
}

int main() {
    int n, m, algo;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;
    cout << "Choose algorithm:\n1. Prims (MST)\n2. Dijkstra\n3. Bellman-Ford\nYour choice: ";
    cin >> algo;
    vector<vector<pair<int, int>>> adj(n);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        if (algo == 1) { 
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        } else { 
            adj[u].push_back({v, w});
        }
    }

    int start;
    if (algo != 1) {
        cout << "Enter starting node: ";
        cin >> start;
    }

    if (algo == 1) {
        int cost = prims(adj, n);
        cout << "Total cost of MST: " << cost << endl;
    } else if (algo == 2) {
        dijkstra(start, adj, n);
    } else if (algo == 3) {
        bellmanford(start, adj, n);
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
