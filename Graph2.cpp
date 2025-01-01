#include <iostream>
#include <queue>

using namespace std;

struct Node {
    int vertex;
    Node* next;
};

void addEdge(Node* g, int u, int v) {
    Node* newNode = new Node;
    newNode->vertex = v;
    newNode->next = g[u - 1].next;
    g[u - 1].next = newNode;
}

Node* input() {
    int n, m, u, v;
    cin >> n >> m;
    Node* g = new Node[n];
    for (int i = 0; i < n; ++i) {
        g[i].vertex = i + 1;
        g[i].next = nullptr;
    }

    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        addEdge(g, u, v);
        // addEdge(g, v, u); // Nếu đồ thị vô hướng
    }
    return g;
}

void dfs(int v, Node* g, bool* visited) {
    visited[v - 1] = true;
    cout << v << " ";

    Node* temp = g[v - 1].next;
    while (temp != nullptr) {
        if (!visited[temp->vertex - 1]) {
            dfs(temp->vertex, g, visited);
        }
        temp = temp->next;
    }
}

void bfs(int s, Node* g, bool* visited) {
    visited[s - 1] = true;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << ' ';

        Node* temp = g[u - 1].next;
        while (temp != nullptr) {
            if (!visited[temp->vertex - 1]) {
                visited[temp->vertex - 1] = true;
                q.push(temp->vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    Node* g = input();
    int n;
    cin >> n;
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    dfs(1, g, visited);
    cout << endl;

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }
    bfs(1, g, visited);

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; ++i) {
        Node* temp = g[i].next;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
    delete[] g;
    delete[] visited;
    return 0;
}