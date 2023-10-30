#include <iostream>
#include<list>
#include <queue>
#include <vector>
using namespace std;


/**
 * \brief Tree
 */

void addEdge(int x, int y, vector<vector<int> >& adj)
{
    adj[x].push_back(y);
    adj[y].push_back(x);
}

void printParents(int node, vector<vector<int> >& adj,
    int parent)
{
    
    if (parent == 0)
        cout << node << "->Root" << endl;
    else
        cout << node << "->" << parent << endl;
   
    for (auto cur : adj[node])
        if (cur != parent)
            printParents(cur, adj, node);
}

void printChildren(int Root, vector<vector<int> >& adj)
{
    queue<int> q;
 
    q.push(Root);

    int vis[adj.size()] = { 0 };
 
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        vis[node] = 1;
        cout << node << "-> ";
        for (auto cur : adj[node])
            if (vis[cur] == 0) {
                cout << cur << " ";
                q.push(cur);
            }
        cout << endl;
    }
}

void printLeafNodes(int Root, vector<vector<int> >& adj)
{
    for (int i = 1; i < adj.size(); i++)
        if (adj[i].size() == 1 && i != Root)
            cout << i << " ";
    cout << endl;
}

void printDegrees(int Root, vector<vector<int> >& adj)
{
    for (int i = 1; i < adj.size(); i++) {
        cout << i << ": ";
        if (i == Root)
            cout << adj[i].size() << endl;
        else
            cout << adj[i].size() - 1 << endl;
    }
}


/**
 * \brief graph
 */

class graph {
public:
    list<int>* adjlist;
    int n;
    graph(int v) {
        adjlist = new list<int>[v];
        n = v;
    }

    void addedge(int u, int v, bool bi) {
        adjlist[u].push_back(v);
        if (bi) {
            adjlist[v].push_back(u);
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            cout << i << "-->";
            for (auto it : adjlist[i]) {
                cout << it << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    // Tree
    int N = 7, Root = 1;

	vector<vector<int> > adj(N + 1, vector<int>());

	addEdge(1, 2, adj);
    addEdge(1, 3, adj);
    addEdge(1, 4, adj);
    addEdge(2, 5, adj);
    addEdge(2, 6, adj);
    addEdge(4, 7, adj);

    cout << "The parents of each node are:" << endl;
    printParents(Root, adj, 0);

    cout << "The children of each node are:" << endl;
    printChildren(Root, adj);

    cout << "The leaf nodes of the tree are:" << endl;
    printLeafNodes(Root, adj);

    cout << "The degrees of each node are:" << endl;
    printDegrees(Root, adj);

    return 0;



    // Graph
	graph g(5);
    g.addedge(1, 2, true);
    g.addedge(4, 2, true);
    g.addedge(1, 3, true);
    g.addedge(4, 3, true);
    g.addedge(1, 4, true);

    g.print();
}

// Sources
// https://www.geeksforgeeks.org/introduction-to-tree-data-structure-and-algorithm-tutorials/
// https://www.section.io/engineering-education/graphs-in-data-structure-using-cplusplus/