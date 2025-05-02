#include <iostream>
#include <stack>
#include <vector>
#include <map>
using namespace std;

class GraphColor
{
public:
    vector<vector<int>> create(int V)
    {
        vector<vector<int>> graph(V, vector<int>(V, 0));
        cout << "\nEnter 1 if edge present else enter 0:" << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                int a;
                cout << "\nEnter for edge between vertex " << i << " and " << j << ": ";
                cin >> a;
                graph[i][j] = a;
                graph[j][i] = a;
            }
        }
        return graph;
    }
    void display(vector<vector<int>> graph, int V)
    {
        cout << "\n----------Graph-----------" << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << graph[i][j] << "\t";
            }
            cout << endl;
        }
    }

    map<int, string> setColor(int m, int color[])
    {
        map<int, string> VColor;
        for (int i = 1; i <= m; i++)
        {
            string shade;
            cout << "\nEnter colour shade: ";
            cin >> shade;
            VColor[i] = shade;
        }
        return VColor;
    }

    bool isSafe(int v, vector<vector<int>> &graph, int color[], int c, int V)
    {
        for (int i = 0; i < V; i++)
        {
            if (graph[v][i] && c == color[i])
            {
                return false;
            }
        }
        return true;
    }

    bool branchAndBound(vector<vector<int>> &graph, int m, int color[], int v, int V, int &upperBound)
{
    if (v == V)
    {
        int colorsUsed = 0;
        for (int i = 0; i < V; i++)
        {
            if (color[i] != 0)
                colorsUsed = max(colorsUsed, color[i]);
        }
        if (colorsUsed < upperBound)
        {
            upperBound = colorsUsed;
        }
        return true;
    }
     int colorsUsed = 0;
        for (int i = 0; i < V; i++)
        {
            if (color[i] != 0)
            {
                colorsUsed = max(colorsUsed, color[i]);
            }
        }
        if (colorsUsed >= upperBound)
        {
            return false;  // Prune this branch as it exceeds the upper bound
        }
    bool foundSolution = false;
    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, graph, color, c, V))
        {
            color[v] = c;  
            if (branchAndBound(graph, m, color, v + 1, V, upperBound))
            {
                return true;
            }

            color[v] = 0;
        }
    }

    return false;
}



    void printColor(map<int, string> ColorVertex, int color[], int V)
    {
        for (int i = 0; i < V; i++)
        {
            if (color[i] != 0)
            {
                cout << "\nVertex: " << i << "--->Colour: " << ColorVertex[color[i]] << endl;
            }
            else
            {
                cout << "\nVertex: " << i << "--->Colour: No Colour" << endl;
            }
        }
    }
   
    bool gColor(vector<vector<int>> &graph, int m, int color[], int v, int V)
    {
        if(v==V)
        {
            return true;
        }
        for(int c=1;c<=m;c++)
        {
            if(isSafe(v,graph,color,c,V))
            {
                color[v]=c;
                if(gColor(graph,m,color,v+1,V))
                {
                    return true;
                }
                color[v]=0;
            }
        }
        return false;
    }
};

int main()
{
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    GraphColor gc;
    vector<vector<int>> graph = gc.create(V);
    gc.display(graph, V);

    int m;
    cout << "Enter number of colours available: ";
    cin >> m;

    int color[V] = {0};
    map<int, string> ColorVertex;
    ColorVertex = gc.setColor(m, color);

    int v;
    cout << "\nEnter starting vertex: ";
    cin >> v;
   
    int choice;
    do
    {
        cout<<"\nMenu : \n1)Backtracking \n2)Branch and Bound";
        cout<<"\n\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                bool result=gc.gColor(graph,m,color,v,V);
                gc.printColor(ColorVertex, color, V);
                if(result==1)
                {
                    cout<<"\nGraph coloring possible!"<<endl;
                }
                else
                {
                    cout<<"\nGraph coloring not possible!"<<endl;
                }
            }
            case 2:
            {
                int upperBound = m;  
                bool result = gc.branchAndBound(graph, m, color, v, V, upperBound);
           
                gc.printColor(ColorVertex, color, V);
                if (result)
                {
                    cout << "\nGraph coloring possible with " << upperBound << " colors!" << endl;
                }
                else
                {
                    cout << "\nGraph coloring not possible with " << m << " colors!" << endl;
                }
                break;
            }
        }
    }while(choice<=2);


    return 0;
}