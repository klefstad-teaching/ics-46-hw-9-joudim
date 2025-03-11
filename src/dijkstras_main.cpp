#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2){
        cerr << "Usage: " << argv[0] << " input_file" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    
    try{
        file_to_graph(filename, G);
    } 
    catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    int source = 0; 
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    for (int dest = 0; dest < G.numVertices; dest++) {
        if (distances[dest] == INF) {
            cout << "No path from " << source << " to " << dest << endl;
        } else {
            vector<int> p = extract_shortest_path(distances, previous, dest);
            print_path(p, distances[dest]);
        }
    }
    
    return 0;
}