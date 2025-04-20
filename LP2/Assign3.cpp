#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

void prims(vector<pair<int, int>> adj[], int n)
{
    vector<int> visit(n, 0);
    int totalWeight = 0;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    int start;
    cout << "\nEnter start node : ";
    cin >> start;
    pq.push({0, {-1, start}});
    while (!pq.empty())
    {
        int dist = pq.top().first;
        int par = pq.top().second.first;
        int node = pq.top().second.second;
        pq.pop();
        if (visit[node] == 1)
        {
            continue;
        }
        if (par != -1)
        {
            cout << "(" << par << "," << node << ") -> " << dist << endl;
        }
        totalWeight += dist;
        visit[node] = 1;
        for (auto it : adj[node])
        {
            if (visit[it.first] == 0)
            {

                pq.push({it.second, {node, it.first}});
            }
        }
    }

    cout << "Total cost of spanning tree : " << totalWeight << endl
         << endl;
}

int findParent(vector<int> &parent, int u)
{
    while (parent[u] != u)
    {
        u = parent[u];
    }
    return u;
}

void findUnion(vector<int> &parent, vector<int> &size, int u, int v)
{
    int pu = parent[u];
    int pv = parent[v];
    int size_u = size[pu];
    int size_v = size[pv];

    if (size_u >= size_v)
    {
        parent[pv] = pu;
        size[pu] += size[pv];
    }
    else
    {
        parent[pu] = pv;
        size[pv] += size[pu];
    }
}

void kruskals(vector<pair<int, pair<int, int>>> &e, int n)
{
    vector<int> size(n, 1);
    vector<int> parent;
    int totalWeight = 0;
    for (int i = 0; i < n; i++)
    {
        parent.push_back(i);
    }

    for (int i = 0; i < e.size(); i++)
    {
        int u = e[i].second.first;
        int v = e[i].second.second;
        if (findParent(parent, u) != findParent(parent, v))
        {
            totalWeight += e[i].first;
            findUnion(parent, size, u, v);
            cout << "(" << u << "," << v << ") -> " << e[i].first << endl;
        };
    }
    cout << "Total cost of spanning tree : " << totalWeight << endl
         << endl;
}

void dijkstra(vector<pair<int, int>> adj[], int V, int start)
{
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> sptSet(V, false);

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = -1;
        // Find the vertex with the minimum distance that is not yet processed
        for (int i = 0; i < V; i++)
        {
            if (!sptSet[i] && (u == -1 || dist[i] < dist[u]))
            {
                u = i;
            }
        }

        sptSet[u] = true;

        // Update distances of the adjacent vertices of the selected vertex
        for (auto v : adj[u])
        {
            int vertex = v.first;
            int weight = v.second;

            if (!sptSet[vertex] && dist[u] + weight < dist[vertex])
            {
                dist[vertex] = dist[u] + weight;
                parent[vertex] = u;
            }
        }
    }

    // Output the results
    cout << "\nDijkstra's Shortest Path from vertex " << start << ":\n";
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
        {
            cout << "Vertex " << i << ": Unreachable" << endl;
        }
        else
        {
            cout << "Vertex " << i << ": Cost = " << dist[i] << ", Path = ";
            int j = i;
            while (j != start)
            {
                cout << j << " <- ";
                j = parent[j];
            }
            cout << start << endl;
        }
    }
}

int main()
{
    int n;
    cout << "\nEnter the number of vertices : ";
    cin >> n;

    vector<vector<int>> edges = {
    {0, 1, 28}, {0, 5, 10}, 
    {1, 2, 16}, {1, 6, 14}, 
     {2, 3, 12}, 
    {3, 4, 22}, {3, 6, 18}, 
    {4, 5, 25}, {4, 6, 24}
};
    vector<pair<int, int>> adj[n];
    for (auto it : edges)
    {
        adj[it[0]].push_back({it[1], it[2]});
        adj[it[1]].push_back({it[0], it[2]});
    }

    int choice;
    do
    {
        cout << "\n1)Prims  2)Kruskal  3)Djikstras";
        cout << "\nEnter your choice :";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "\nPrims : " << endl;
            prims(adj, n);
        }
        case 2:
        {
            cout << "\nkruskals : " << endl;
            vector<pair<int, pair<int, int>>> e;
            for (int i = 0; i < n; i++)
            {
                for (auto it : adj[i])
                {
                    e.push_back({it.second, {i, it.first}});
                }
            }
            sort(e.begin(), e.end());
            kruskals(e, n);
        }
        case 3:
        {
            int start;
            cout << "\nEnter start node for Dijkstra's algorithm: ";
            cin >> start;
            dijkstra(adj, n, start);
        }
        }

    } while (choice <= 3);
}