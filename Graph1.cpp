#include <iostream>
#include <queue>
using namespace std;

struct graph_matrix {
	int n;
	int** graph;
	graph_matrix(int n) {
		this->n = n;
		graph = new int* [n];
		for (int i = 0; i < n; i++) {
			graph[i] = new int[n];
			for (int j = 0; j < n; j++) {
				graph[i][j] = 0;
			}
		}
	}
};

graph_matrix input() {
	int n, m, u, v;
	cin >> n >> m; // Nhap so luong dinh va so luong canh
	graph_matrix g(n);
	for (int i = 1; i <= m; i++) {
		cin >> u >> v; // Nhap dinh dau va dinh cuoi
		g.graph[u - 1][v - 1] = 1;
		g.graph[v - 1][u - 1] = 1; // Do thi co huong thi khong co dong nay
	}
	return g;
}

void dfs(int v, graph_matrix g, bool* visited) {
	visited[v - 1] = true;
	cout << v << " ";

	for (int i = 1; i <= g.n; i++) {
		if (g.graph[v - 1][i - 1] == 1 && !visited[i - 1]) {
			dfs(i, g, visited);
		}
	}
}

void bfs(int s, graph_matrix g, bool* visited) {
	queue<int> q;
	visited[s - 1] = true;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		cout << u << " ";

		for (int i = 0; i < g.n; i++) {
			if (g.graph[u - 1][i] == 1 && !visited[i]) {
				visited[i] = true;
				q.push(i + 1);
			}
		}
	}
}

int main() {
	graph_matrix g = input();
	bool* visited = new bool[g.n];
	
	for (int i = 0; i < g.n; i++) {
		visited[i] = false;
	}
	dfs(1, g, visited);
	
	for (int i = 0; i < g.n; i++) {
		visited[i] = false;
	}
	cout << endl;
	bfs(1, g, visited);
	
	delete[] visited;
	return 0;
}