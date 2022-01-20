// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight, string line) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
// TODO
int Graph::dijkstra_distance(int a, int b) {

    for(Node &n: nodes){
        n.dist=INT16_MAX;
        n.visited=false;
    }

    nodes[0].visited=true;
    nodes[a].dist=0;
    nodes[a].pred = a;
    int u = a;

    bool allVis = false;
    while(!allVis){
        int min_dist = INT16_MAX;
        for(int i=0; i<nodes.size(); ++i){
            if(nodes[i].dist<=min_dist && !nodes[i].visited){
                u=i;
                min_dist = nodes[i].dist;
            }
        }
        nodes[u].visited=true;
        if(nodes[u].dist==INT16_MAX) break;

        for(Edge &e: nodes[u].adj){
            if(!nodes[e.dest].visited){
                if(nodes[u].dist + e.weight < nodes[e.dest].dist) {
                    nodes[e.dest].dist = nodes[u].dist + e.weight;
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
    if(nodes[b].dist==INT16_MAX) return -1;
    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
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
