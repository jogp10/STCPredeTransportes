#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <climits>
#include <cmath>
#include <queue>

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
        int pred = 0;
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

    /**
     * Dijkstra Algorithm
     * @param s Node to start algorithm
     * @param finish Node to finish algorithm
     * @param type Type of trajectory the algorithm is going to use
     */
    void dijkstra(int s, int finish=0, string type="shortest");


public:
    /**
     *  Constructor
     * @param nodes nr nodes
     * @param dir direction ( default: undirected)
     */
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
     * @param Name Name of Stop
     * @param Code Code of Stop
     * @param Zone Zone of Stop
     * @param Latitude Latitude of Stop
     * @param Longitude Longitude of Stop
     * @param index Index in vector<Node> of Graph
     */
    void setNode(string name, string code, string zone, double latitude, double longitude, int index);

    /**
     * Get Map of nodes which belong to graph
     * @return map where key: code of stop, value: latitude, longitude
     */
    map<int, pair<double, double>> getNodes();

    /**
     * Get Node
     * @param at index of Node
     * @return Node
     */
    Node getNode(int at);

    /**
     * Get Distance between two points
     * @param lat1 Latitude of point x
     * @param long1 Longitude of point x
     * @param lat2 Latitude of point y
     * @param long2 Longitude of point y
     * @return distance in km
     */
    double static getDistance(double lat1, double long1, double lat2, double long2);

    /**
     * Get Distance between two nodes using dijkstra algorithm
     * @param a Node to start algorithm
     * @param b Node to end algorithm
     * @param type Type of trajectory the algorithm is going to use
     * @return  distance in km
     */
    double dijkstra_distance(int a, int b, string type="shortest");

    /**
     * Dijkstra Path
     * @param a Departure local
     * @param b Destination local
     * @param type Type of trajectory the algorithm is going to use
     * @return list of code's stop which belong to path
     */
    list<int> dijkstra_path(int a, int b, string type="shortest");

    /**
     * Create edges to which you can walk, without need to take transport
     * This type of edge has in maximum weight 2, because the distance between 2 points is 1 km.
     * We duplicated the default weight to this type of edge
     */
    void createWalkEdges();

    /**
     * BFS Algortihm
     * @param a Node to start algorithm
     * @param b Node to end algortihm
     */
     void bfs(int a, int b);
};

#endif
