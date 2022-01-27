#include "graph.h"
#include <climits>
#include <cmath>


// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}


// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, double weight, string line) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
}


map<int, pair<double, double>> Graph::getNodes(){
    map<int, pair<double, double>> localizations;
    for(int i=1; i<=nodes.size(); i++){
        localizations.insert(make_pair(i, make_pair(nodes[i].longitude, nodes[i].latitude)));
    }
    return localizations;
}

Graph::Node Graph::getNode(int at){
    return nodes[at];
}


void Graph::dijkstra(int s, int finish, string type) {
    float multiplier = 1;
    if(type == "shortest") { multiplier = 1; }
    else if(type == "lessChanges") {}
    else if(type == "lessZones") { multiplier = 10; }
    else if(type == "lessStops") {}

    if(nodes[s].dist==0) return;

    for(Node &n: nodes){
        n.dist=INT16_MAX;
        n.visited=false;
    }

    nodes[0].visited=true;
    nodes[s].dist=0;
    nodes[s].pred =s;
    int u = s;

    bool allVis = false;
    while(!allVis){
        double min_dist = INT16_MAX;
        for(int i=0; i<nodes.size(); ++i){
            if(nodes[i].dist<=min_dist && !nodes[i].visited){
                u=i;
                min_dist = nodes[i].dist;
            }
        }
        nodes[u].visited=true;
        if(nodes[u].dist==INT16_MAX) break;
        if(nodes[finish].visited && finish!=0) break;

        for(Edge &e: nodes[u].adj){
            if(!nodes[e.dest].visited){
                if(nodes[u].dist + e.weight < nodes[e.dest].dist) {
                    nodes[e.dest].dist = nodes[u].dist + e.weight * multiplier;
                    nodes[e.dest].pred = u;
                }
            }
        }

        allVis = true;
        for(Node n: nodes){
            if(!n.visited){
                allVis = false;
            }
        }
    }
}


double Graph::dijkstra_distance(int a, int b) {
    dijkstra(a, b);
    if(nodes[b].dist==INT16_MAX) return -1;
    return nodes[b].dist;
}


list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra_distance(a, b);
    list<int> path;
    int u=b;

    while(a!=u){
        path.insert(path.begin(), u);
        if(u==nodes[u].pred || !(nodes[u].pred>0 && nodes[u].pred<=nodes.size())) return {};
        u=nodes[u].pred;
    }
    path.insert(path.begin(), a);
    return path;
}


void Graph::createWalkEdges() {
    for(int i=0; i<nodes.size(); ++i){ // Stop x
        for(int j=i+1; j<nodes.size(); ++j){ // Stop y
            double distance12 = getDistance(nodes[i].latitude, nodes[i].longitude, nodes[j].latitude, nodes[j].longitude); // Distance between x - y
            if(distance12 < 0.5){
                addEdge(i, j, distance12, "walk");
            }
        }
    }
}


void Graph::setNode(string code, string name, string zone, double latitude, double longitude, int index) {
    Node n;
    n.code = code;
    n.name = name;
    n.zone = zone;
    n.latitude = latitude;
    n.longitude = longitude;
    n.dist = INT16_MAX;
    nodes[index] = n;
    //nodes.insert(nodes.begin()+index, n);
}


double  Graph::getDistance(double lat1, double long1, double lat2, double long2) {
    const double PI = 3.141592653589793238463;

    auto earthRadiusKM = 6371;

    auto dLat = (lat1-lat2) * PI /180;
    auto dLon = (long1-long2) * PI /180;

    lat1 = lat1 * PI / 180;
    lat2 = lat2 * PI / 180;

    auto a = sin(dLat/2) * sin(dLat/2) +
             sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2);
    auto c = 2 * atan2(sqrt(a), sqrt(1-a));
    return earthRadiusKM * c;
}


