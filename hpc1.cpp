//Design and implement Parallel Breadth First Search based on existing algorithms
//using OpenMP. Use a Tree or an undirected graph for BFS

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
// Graph class represent the adjacency list
class Graph {
 int V; // Number of verƟces
 vector<vector<int>> adj; // Adjacency list
public:
 Graph(int V) : V(V), adj(V) {}
 // Add an edge to the graph
 void addEdge(int v, int w) {
 adj[v].push_back(w);
 }

 // Parallel Breadth-First Search
 void parallelBFS(int startVertex) {
 vector<bool> visited(V, false);
 queue<int> q;
 visited[startVertex] = true;
 q.push(startVertex);
 while (!q.empty()) {
 int v = q.front();
 q.pop();
 cout << v << " ";
 #pragma omp parallel for
 for (int i = 0; i < adj[v].size(); ++i) {
 int n = adj[v][i];
 if (!visited[n]) {
 visited[n] = true;
 q.push(n);
 }
 }
 }
 }
};
int main() {
 // Create a graph
 Graph g(7);
 g.addEdge(0, 1);
 g.addEdge(0, 2);
 g.addEdge(1, 3);
 g.addEdge(1, 4);
 g.addEdge(2, 5);
 g.addEdge(2, 6);

 cout << "Breadth-First Search (BFS): ";
 g.parallelBFS(0);
 cout << endl;
 return 0;
}
