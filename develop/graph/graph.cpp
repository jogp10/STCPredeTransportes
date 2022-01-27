#include "graph.h"


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
    nodes[s].pred =s;

    if(type=="lessStops") {
        bfs(s, finish);
        return;
    }
    float multiplier;

    if(nodes[s].dist==0) return;

    for(Node &n: nodes){
        n.dist=INT16_MAX;
        n.visited=false;
    }

    nodes[0].visited=true;
    nodes[s].dist=0;
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
                    multiplier = 1;

                    //Less Zones
                    if(type=="lessZones" && nodes[e.dest].zone!=nodes[u].zone)
                        multiplier = 100;

                    int addweight = e.weight * multiplier;
                    nodes[e.dest].dist = nodes[u].dist + addweight;
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


double Graph::dijkstra_distance(int a, int b, string type) {
    dijkstra(a, b, type);
    if(nodes[b].dist==INT16_MAX) return -1;
    return nodes[b].dist;
}


list<int> Graph::dijkstra_path(int a, int b, string type) {
    dijkstra_distance(a, b, type);
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


void Graph::bfs(int a, int b) {
    vector<int> distances(nodes.size(), -1);
    distances[a] = 0;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(a);
    nodes[a]. visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        if(u==b) break;
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].pred = u;
                nodes[w].visited = true;
                distances[w] = distances[u] + 1;
            }
        }
    }
}


