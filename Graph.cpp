#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * \brief Graph
 */

class Node {
public:
    int data;
    Node(int val) : data(val) {}
};

class Graph {
public:
    vector<Node> nodes;
    list<int>* adjlist;
    int n;

    Graph(int v) : n(v) {
        adjlist = new list<int>[v];
        for (int i = 0; i < v; ++i) {
            nodes.push_back(Node(i));
        }
    }

    Node getNode(int index) {
        return nodes[index];
    }

    list<int> getAdjacentNodes(int index) {
        return adjlist[index];
    }

    vector<Node> getVertices() {
        return nodes;
    }

    vector<pair<int, int>> getEdges() {
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; ++i) {
            for (auto it : adjlist[i]) {
                edges.push_back({ i, it });
            }
        }
        return edges;
    }

    int getSize() {
        return n;
    }

    bool isEmpty() {
        return n == 0;
    }

    void insertNode(int val) {
        Node newNode(val);
        nodes.push_back(newNode);
        ++n;
    }

    void insertEdge(int u, int v, bool bi) {
        adjlist[u].push_back(v);
        if (bi) {
            adjlist[v].push_back(u);
        }
    }

    void insertRandomEdge() {
        srand(time(0));
        int u = rand() % n;
        int v = rand() % n;
        bool bi = rand() % 2 == 0;
        insertEdge(u, v, bi);
    }

    void insertEdgeAtNode(int nodeIndex, int v, bool bi) {
        if (nodeIndex < 0 || nodeIndex >= n) {
            cout << "Invalid node index\n";
            return;
        }
        insertEdge(nodeIndex, v, bi);
    }

    void deleteNode(int nodeIndex) {
        if (nodeIndex < 0 || nodeIndex >= n) {
            cout << "Invalid node index\n";
            return;
        }

        nodes.erase(nodes.begin() + nodeIndex);
        --n;

        for (int i = 0; i < n; ++i) {
            adjlist[i].remove(nodeIndex);
        }
        adjlist[nodeIndex].clear();
    }

    void deleteEdge(int u, int v, bool bi) {
        adjlist[u].remove(v);
        if (bi) {
            adjlist[v].remove(u);
        }
    }

    void breadthFirstTraversal(int start) {
        bool* visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }

        list<int> queue;
        visited[start] = true;
        queue.push_back(start);

        while (!queue.empty()) {
            start = queue.front();
            cout << start << " ";
            queue.pop_front();

            for (auto it = adjlist[start].begin(); it != adjlist[start].end(); ++it) {
                if (!visited[*it]) {
                    visited[*it] = true;
                    queue.push_back(*it);
                }
            }
        }

        delete[] visited;
    }

    void print() {
        for (int i = 0; i < n; ++i) {
            cout << nodes[i].data << "-->";
            for (auto it : adjlist[i]) {
                cout << nodes[it].data << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    ~Graph() {
        delete[] adjlist;
    }
};

int main() {
    Graph g(5);
    g.insertEdge(1, 2, true);
    g.insertEdge(4, 2, true);
    g.insertEdge(1, 3, true);
    g.insertEdge(4, 3, true);
    g.insertEdge(1, 4, true);

    g.print();

    cout << "Vertices in graph: " << g.getSize() << endl;
    cout << "Is the graph empty? " << (g.isEmpty() ? "Yes" : "No") << endl;

    cout << "\nInserting a random edge:\n";
    g.insertRandomEdge();
    g.print();

    cout << "Deleting node 2:\n";
    g.deleteNode(2);
    g.print();

    cout << "Deleting edge between nodes 1 and 4:\n";
    g.deleteEdge(1, 4, true);
    g.print();

    cout << "Breadth-first traversal starting from node 0: ";
    g.breadthFirstTraversal(0);
    cout << endl;

    return 0;
}

