#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>

using namespace std;


class Graph {

    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        string line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string name;
        string code;
        string zone;
        double latitude;
        double longitude;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    void dijkstra(int s);
    double static getDistance(Node n1, Node n2);


public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1, string line = "");

    map<int, pair<double, double>> getNodes();

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);
};

#endif
