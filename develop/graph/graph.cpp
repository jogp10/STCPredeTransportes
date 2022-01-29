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
    for(int i=1; i<nodes.size(); ++i){
        localizations.insert(make_pair(i, make_pair(nodes[i].latitude, nodes[i].longitude)));
    }
    return localizations;
}

Graph::Node Graph::getNode(int at){
    return nodes[at];
}

void Graph::dijkstra(int s, int finish, string type, bool walk) {
    MinHeap<int, double> q(nodes.size()-1, -1);

    for(int v=1; v<nodes.size(); ++v){
        nodes[v].dist=INT16_MAX;
        q.insert(v, INT16_MAX);
        nodes[v].visited=false;
    }

    nodes[0].visited=true;
    nodes[s].dist=0;
    q.decreaseKey(s, 0);
    nodes[s].pred =s;
    nodes[s].pred =0;

    if(type=="lessStops") {
        bfs(s, finish);
        return;
    }

    int u = 0;
    double weight;
    while(q.getSize()>0) {
        weight = q.getValue();
        u = q.removeMin();

        nodes[u].visited=true;
        if(nodes[u].dist==INT16_MAX) break;
        if(nodes[finish].visited && finish!=0) break;

        for(Edge& e: nodes[u].adj){
            if(!walk) continue;

            int multiplier = 1;

            if(e.line=="walk") multiplier += 4;

            // Less Zones
            if(nodes[e.dest].zone!=nodes[u].zone && type=="lessZones") multiplier += 99;

            if(type=="lessChanges"){
                bool flag = false;
                // Posible ways from where I came to u
                for(auto l: nodes[u].predLines){
                    if(l=="walk") continue;
                    if(e.line==l) flag = true;
                }
                if(!flag && u!=s) multiplier += 14;
                if(e.line=="walk") multiplier += 4;
            }

            if(!nodes[e.dest].visited && weight + e.weight * multiplier < q.getValue(e.dest)){


                nodes[e.dest].predLines.insert(nodes[e.dest].predLines.begin(), e.line);

                nodes[e.dest].dist = nodes[u].dist + e.weight;
                q.decreaseKey(e.dest, weight + e.weight * multiplier);
                nodes[e.dest].pred = u;
            }
        }
    }
}

double Graph::dijkstra_distance(int a, int b, string type) {
    dijkstra(a, b, type);
    if(nodes[b].dist==INT16_MAX) {
        dijkstra(a, b, type, true);
        if(nodes[b].dist== INT16_MAX)
            return -1;
    }
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
            if(distance12 < 0.2){
                addEdge(i, j, distance12, "walk");
                addEdge(j, i, distance12, "walk");
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
}

double Graph::getDistance(double lat1, double long1, double lat2, double long2) {
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
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(a);
    nodes[a].dist=0;
    nodes[a].visited=true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].pred = u;
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + e.weight;
                //nodes[w].dist = nodes[u].dist + 1;
            }
            if(w==b) break;
        }
    }
    cout << endl;
}
