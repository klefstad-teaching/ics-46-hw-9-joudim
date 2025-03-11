#include "dijkstras.h"
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

struct Node{
    int vertex;
    int distance;
    Node(int v, int d) : vertex(v), distance(d) {}
};

struct CompareNode{
    bool operator()(const Node &a, const Node &b){
        return a.distance > b.distance; 
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> d(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, CompareNode> pq;

    d[source] = 0;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        int u = curr.vertex;

        if (visited[u])
            continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && d[u] != INF && d[u] + weight < d[v]) {
                d[v] = d[u] + weight;
                previous[v] = u;
                pq.push(Node(v, d[v]));
            }
        }
    }
    return d;
}


vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> p;
    for (int at = destination; at != -1; at = previous[at])
        p.push_back(at);
    reverse(p.begin(), p.end());
    return p;
}

void print_path(const vector<int>& v, int total){
    
    for (size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " "; 
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}