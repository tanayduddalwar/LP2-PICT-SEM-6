#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

void dfs_depth_limited(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, string start, int depth, string city, bool &flag) {
    if (depth < 0) return;
    if (visited[start]) return;

    visited[start] = true;
    if (start == city) {
        cout << "(" << start << ", Depth: " << depth << ", Population: " << cityPopulation[start] << ")\n";
        flag = true;
        return;
    }

    for (auto it : graph[start]) {
        if (!visited[it.first]) {
            dfs_depth_limited(graph, visited, cityPopulation, it.first, depth - 1, city, flag);
            if (flag) return;
        }
    }
}

void iterative_deepening(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, string start, int maxDepth, string city, bool &flag) {
    for (int depth = 0; depth <= maxDepth; ++depth) {
        visited.clear();
        cout << "Searching at depth " << depth << " for city " << city << "...\n";

        dfs_depth_limited(graph, visited, cityPopulation, start, depth, city, flag);

        if (flag) {
            cout << "City " << city << " found at depth " << depth << ".\n";
            return;
        }

        cout << "City " << city << " not found at depth " << depth << ".\n";
    }

    if (!flag) {
        cout << "City " << city << " not found after searching up to depth " << maxDepth << ".\n";
    }
}

void dls(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, string start, int depth) {
    queue<pair<string, int>> q;
    q.push({start, 0});
    visited[start] = true;

    while (!q.empty()) {
        string node = q.front().first;
        int lvl = q.front().second;
        q.pop();

        if (lvl > depth) {
            continue;
        }

        if (cityPopulation[node] > 50000) {
            cout << "(" << node << ", Depth: " << lvl << ", Population: " << cityPopulation[node] << ")\n";
        }

        for (auto it : graph[node]) {
            if (!visited[it.first]) {
                visited[it.first] = true;
                q.push({it.first, lvl + 1});
            }
        }
    }
}

void dfs_rec(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, string start, int level) {
    visited[start] = true;

    if (cityPopulation[start] > 50000) {
        cout << "(" << start << ", Level: " << level << ", Population: " << cityPopulation[start] << ")\n";
    }

    for (auto it : graph[start]) {
        if (!visited[it.first]) {
            dfs_rec(graph, visited, cityPopulation, it.first, level + 1);
        }
    }
}

void bfs(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, string start) {
    queue<pair<string, int>> q;
    int level = 0;
    q.push({start, level});
    visited[start] = true;

    while (!q.empty()) {
        string node = q.front().first;
        int lvl = q.front().second;
        q.pop();

        if (cityPopulation[node] > 50000) {
            cout << "(" << node << ", Level: " << lvl << ", Population: " << cityPopulation[node] << ")\n";
        }

        for (auto it : graph[node]) {
            if (!visited[it.first]) {
                visited[it.first] = true;
                q.push({it.first, lvl + 1});
            }
        }
    }
}

void bfs_rec(map<string, vector<pair<string, int>>>& graph, map<string, bool>& visited, map<string, int>& cityPopulation, queue<pair<string, int>> q) {
    if (q.empty()) {
        return;
    }

    string node = q.front().first;
    int lvl = q.front().second;
    q.pop();

    if (cityPopulation[node] > 50000) {
        cout << "(" << node << ", Level: " << lvl << ", Population: " << cityPopulation[node] << ")\n";
    }

    for (auto it : graph[node]) {
        if (!visited[it.first]) {
            visited[it.first] = true;
            q.push({it.first, lvl + 1});
        }
    }
    bfs_rec(graph, visited, cityPopulation, q);
}

int main() {
    int m, pop1, pop2;
    string u, v;

    cout << "\nEnter the number of connections: ";
    cin >> m;

    map<string, vector<pair<string, int>>> graph;
    map<string, bool> visited;
    map<string, int> cityPopulation;

    for (int i = 0; i < m; i++) {
        cout << "Enter first city and its population: ";
        cin >> u >> pop1;
        cout << "Enter second city and its population: ";
        cin >> v >> pop2;

        cityPopulation[u] = pop1;
        cityPopulation[v] = pop2;

        graph[u].push_back({v, pop1});
        graph[v].push_back({u, pop2});
    }

    int choice;
    do {
        cout << "\n1) DFS Recursive  2) BFS  3) BFS Recursive  4) DLS  5) Iterative Deepening\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string start;
                cout << "\nEnter starting city: ";
                cin >> start;

                visited.clear();
                dfs_rec(graph, visited, cityPopulation, start, 0);
                break;
            }
            case 2: {
                string start;
                cout << "\nEnter starting city: ";
                cin >> start;

                visited.clear();
                bfs(graph, visited, cityPopulation, start);
                break;
            }
            case 3: {
                string start;
                cout << "\nEnter starting city: ";
                cin >> start;
                queue<pair<string, int>> q;
                q.push({start, 0});
                visited[start] = true;
                bfs_rec(graph, visited, cityPopulation, q);
                break;
            }
            case 4: {
                string start;
                int depth;
                cout << "\nEnter starting city: ";
                cin >> start;
                cout << "\nEnter depth: ";
                cin >> depth;

                visited.clear();
                dls(graph, visited, cityPopulation, start, depth);
                break;
            }
            case 5: {
                string start, city;
                int depth;
                cout << "\nEnter starting city: ";
                cin >> start;
                cout << "\nEnter city to search: ";
                cin >> city;
                cout << "\nEnter maximum depth: ";
                cin >> depth;

                bool flag = false;

                visited.clear();

                iterative_deepening(graph, visited, cityPopulation, start, depth, city, flag);

                break;
            }
        }
    } while (choice <= 5);

    return 0;
}
// (Pune, Level: 0, Population: 100000)
// (Mumbai, Level: 1, Population: 200000)
// (Nashik, Level: 1, Population: 75000)
// (Nagpur, Level: 2, Population: 120000)
// (Aurangabad, Level: 2, Population: 80000)
// (Kolhapur, Level: 3, Population: 60000)