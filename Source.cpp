#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime> 
using namespace std;

/**
 * \brief Tree
 */

struct Node
{
    int key;
    vector<Node*> child;

    Node(int val) : key(val) {}

    Node* getParent(Node* root, Node* child);
    vector<Node*> getChildren(Node* node);
    Node* getRoot(Node* node);

    int size(Node* root);
    int depth(Node* node);
    bool isEmpty(Node* root);
    bool isRoot(Node* node);
    bool isLeaf(Node* node);

    void insertRandom(Node* root, int key);
    void insertAsChild(Node* parent, int key);

    void deleteNode(Node* root, int key);

    void breadthFirstTraversal(Node* root);
};

Node* Node::getParent(Node* root, Node* child) {
    if (root == nullptr || root == child)
        return nullptr;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (Node* c : current->child) {
            if (c == child)
                return current;
            q.push(c);
        }
    }

    return nullptr;
}

vector<Node*> Node::getChildren(Node* node) {
    return node->child;
}

Node* Node::getRoot(Node* node) {
    while (node->getParent(node, node) != nullptr) {
        node = node->getParent(node, node);
    }
    return node;
}

int Node::size(Node* root) {
    if (root == nullptr)
        return 0;

    int count = 1; 
    for (Node* child : root->child) {
        count += size(child);
    }

    return count;
}

int Node::depth(Node* node) {
    if (node == nullptr)
        return 0;

    int d = 0;
    while (node->getParent(node, node) != nullptr) {
        node = node->getParent(node, node);
        d++;
    }

    return d;
}

bool Node::isEmpty(Node* root) {
    return root == nullptr;
}

bool Node::isRoot(Node* node) {
    return node->getParent(node, node) == nullptr;
}

bool Node::isLeaf(Node* node) {
    return node->child.empty();
}

void Node::insertRandom(Node* root, int key) {
    if (root == nullptr)
        return;

    srand(time(0));
    int randomIndex = rand() % (root->child.size() + 1);

    root->child.insert(root->child.begin() + randomIndex, new Node(key));
}

void Node::insertAsChild(Node* parent, int key) {
    if (parent == nullptr)
        return;

    parent->child.push_back(new Node(key));
}

void Node::deleteNode(Node* root, int key) {
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (auto it = current->child.begin(); it != current->child.end(); ++it) {
            if ((*it)->key == key) {
                delete* it;
                current->child.erase(it);
                return;
            }
            q.push(*it);
        }
    }
}

void Node::breadthFirstTraversal(Node* root) {
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();

        while (n > 0) {
            Node* p = q.front();
            q.pop();
            cout << p->key << " ";

            for (Node* child : p->child)
                q.push(child);

            n--;
        }

        cout << endl;
    }
}

int main() {
    Node* root = new Node(10);
    Node* node2 = new Node(2);
    Node* node34 = new Node(34);
    Node* node56 = new Node(56);
    Node* node100 = new Node(100);
    Node* node77 = new Node(77);
    Node* node88 = new Node(88);
    Node* node1 = new Node(1);
    Node* node7 = new Node(7);
    Node* node8 = new Node(8);
    Node* node9 = new Node(9);

    root->child = { node2, node34, node56, node100 };
    node2->child = { node77, node88 };
    node56->child = { node1 };
    node100->child = { node7, node8, node9 };

    cout << "Level order traversal Before Mirroring\n";
    root->breadthFirstTraversal(root);

    cout << "Size of the tree: " << root->size(root) << endl;
    cout << "Depth of node 56: " << root->depth(node56) << endl;

    root->insertRandom(root, 999);
    cout << "After random insertion\n";
    root->breadthFirstTraversal(root);

    root->insertAsChild(node1, 555);
    cout << "After inserting 555 as a child of node 1\n";
    root->breadthFirstTraversal(root);

    root->deleteNode(root, 555);
    cout << "After deleting node with key 555\n";
    root->breadthFirstTraversal(root);

    return 0;
}