#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

void dfs(string city, map<string, vector<string>>& adj, map<string, bool>& visited) {
    cout << city << " ";
    visited[city] = true;
    for (auto neighbor : adj[city]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

void bfs(string city, map<string, vector<string>>& adj, map<string, bool>& visited) {
    queue<string> q;
    q.push(city);
    visited[city] = true;

    while (!q.empty()) {
        string current = q.front();
        q.pop();
        cout << current << " ";
        for (auto neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter number of cities and edges: ";
    cin >> nodes >> edges;

    vector<string> cities(nodes);
    map<string, vector<string>> adj;
    map<string, bool> visited;

    cout << "Enter city names:\n";
    for (int i = 0; i < nodes; i++) {
        cin >> cities[i];
    }

    cout << "Enter edges (city1 city2):\n";
    for (int i = 0; i < edges; i++) {
        string u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int choice;
    cout << "Enter 1 for DFS, 2 for BFS: ";
    cin >> choice;
    if(choice==1){
        for (int i = 0; i < nodes; i++) {
            if (!visited[cities[i]]) {
                    dfs(cities[i], adj, visited);
            }
        }
    }
    if(choice==2){
        for (int i = 0; i < nodes; i++) {
            if (!visited[cities[i]]) {
                    bfs(cities[i], adj, visited);
            }
        }
    }
    cout << endl;
    

    return 0;
}
