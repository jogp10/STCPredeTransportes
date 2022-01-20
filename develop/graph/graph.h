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
        double weight; // An integer weight
        string line;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double dist;
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
    double static getDistance(const Node& n1, Node n2);


public:
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, double weight = 1.00, string line = "");

    void setNode(string name, string code, string zone, double latitude, double longitude, int index);

    map<int, pair<double, double>> getNodes();

    double static getDistance(Node n1, Node n2);

    // ----- Functions to implement in this class -----
    double dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);

    void createWalkEdges();
};

#endif
