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

    /**
     * Add edge from source to destination with a certain weight
     * @param src Origin Stop
     * @param dest Destination Stop
     * @param weight Distance between Origin and Destination
     * @param line Line wich i can get from Origin to Destination
     */
    void addEdge(int src, int dest, double weight = 1.00, string line = "");

    /**
     * Set Node's updated with Stop's info
     * @param Name of Stop
     * @param Code of Stop
     * @param Zone of Stop
     * @param Latitude of Stop
     * @param Longitude of Stop
     * @param index in Graph
     */
    void setNode(string name, string code, string zone, double latitude, double longitude, int index);

    /**
     *
     * @return map where key: code of stop, value: latitude, longitude
     */
    map<int, pair<double, double>> getNodes();
    double static getDistance(double lat1, double long1, double lat2, double long2);

    // ----- Functions to implement in this class -----
    /**
     *
     * @param a
     * @param b
     * @return
     */
    double dijkstra_distance(int a, int b);

    /**
     *
     * @param Departure local
     * @param Destination local
     * @return path;
     */
    list<int> dijkstra_path(int a, int b);

    /**
 * Create edges to wich you can walk, without need to take transport
 * This type of edge has in maximum weight 2, because the distance beetween 2 points is 1 km.
 * We duplicated the default weight to this type of edge
 */
    void createWalkEdges();
};

#endif
