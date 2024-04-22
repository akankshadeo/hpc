//Design and implement Parallel Depth First Search based on existing algorithms
//using OpenMP. Use a Tree or an undirected graph for DFS .

#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

using namespace std;

// Graph class representing the adjacency list
class Graph {
 int V; // Number of verƟces
 vector<vector<int>> adj; // Adjacency list

 // constructor
public:
 Graph(int V) : V(V), adj(V) {}

 // Add an edge to the graph
 void addEdge(int v, int w) {
 adj[v].push_back(w);
 }

 // Parallel Depth-First Search
 void parallelDFS(int startVertex) {
 vector<bool> visited(V, false);
 parallelDFS(startVertex, visited);
 }
 // Parallel DFS uƟlity funcƟon
 void parallelDFS(int v, vector<bool>& visited) {
 visited[v] = true;
 cout << v << " ";
 #pragma omp parallel for
 for (int i = 0; i < adj[v].size(); ++i) {
 int n = adj[v][i];
 if (!visited[n])
 parallelDFS(n, visited);
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
 cout << "Depth-First Search (DFS): ";
 g.parallelDFS(0);
 cout << endl;

 return 0;
}
