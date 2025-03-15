#include "dijkstras.h"
#include <vector>
#include <queue>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({source, 0});

    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) {
            continue;
        }
        for (Edge edge : G[u]) {
            int v = edge.dest;
            int weight = edge.second;
            if (!visited[u] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    int vertex = destination;
    while (vertex != -1) {  
        path.insert(0, vertex);
        vertex = previous[vertex];
    }
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is  " << total << endl;
}