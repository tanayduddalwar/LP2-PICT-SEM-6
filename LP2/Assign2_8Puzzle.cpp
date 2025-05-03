#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

struct Node 
{
    Node *par;
    int st[3][3];
    int g;
    int h;
    int x, y;
};

int dr[] = {1, 0, -1, 0};
int dc[] = {0, -1, 0, 1};

void printMat(int mat[3][3], int g, int h) 
{
    for(int i = 0; i < 3; i++) 
    {
        for(int j = 0; j < 3; j++) 
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

    cout << "g: " << g << " ";
    cout<< "h: " << h << " ";
    cout<< "f: " << g + h << endl;
}

Node *newNode(int mat[3][3], int x, int y, int nx, int ny, int g,Node *par) 
{
    Node *node = new Node;
    node->par = par;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            node->st[i][j] = mat[i][j];
        }
    }

    swap(node->st[x][y], node->st[nx][ny]);

    node->h = INT_MAX;
    node->g = g;
    node->x = nx;
    node->y = ny;

    return node;
}

int heur(int init[3][3], int goal[3][3]) 
{
    int c = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (init[i][j] && init[i][j] != goal[i][j])
            {
                c++;
            }
        }
            
    }
    return c;
}

bool isSafe(int x, int y)
 { 
    return (x >= 0 && x < 3 && y >= 0 && y < 3); 
}

void printPath(Node *root)
{
    if (root == NULL)
        return;
    printPath(root->par);
    printMat(root->st, root->g, root->h);
    cout << endl;
}

struct comp 
{
    bool operator()(const Node *lhs, const Node *rhs) const 
    {
        return (lhs->h + lhs->g) > (rhs->h + rhs->g);
    }
};

void solve(int start[3][3], int x, int y, int goal[3][3]) 
{
    int cnt = 0;
    priority_queue<Node *, vector<Node *>, comp> pq;

    Node *root = newNode(start, x, y, x, y, 0, NULL);
    root->h = heur(start, goal);

    pq.push(root);

    while (!pq.empty()) 
    {
        Node *m = pq.top();
        pq.pop();

        if (m->h == 0) 
        {
            cout << "\n\nThis puzzle is solved in " << cnt << " moves \n";
            printPath(m);
            return;
        }

        cnt++;
        for (int i = 0; i < 4; i++) 
        {
            int dx = m->x + dr[i];
            int dy = m->y + dc[i];

            if (isSafe(dx, dy)) 
            {
                Node *child = newNode(m->st, m->x, m->y, dx, dy, m->g + 1, m);
                child->h = heur(child->st, goal);
                pq.push(child);
            }
        }
    }
}

int main()
{
    int start[3][3];
    int goal[3][3];

    int x = -1;
    int y = -1;

    cout << "Enter the start state: " << endl;
    for (int i = 0; i < 3; i++)
     {
        for (int j = 0; j < 3; j++)
        {
            cin >> start[i][j];
            if (start[i][j] == 0) 
            {
                x = i;
                y = j;
            }
        }
    }
    cout << endl;
    cout << "Enter the goal state: " << endl;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
         {
            cin >> goal[i][j];
        }
    }

    solve(start, x, y, goal);
    return 0;
}