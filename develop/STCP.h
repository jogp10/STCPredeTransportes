//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_STCP_H
#define STCPREDETRANSPORTES_STCP_H


#include "graph/graph.h"

class STCP {
    Graph graph = Graph(0);

    map<string, int> stops; //key: codigo da paragem, value: index no vetor de nodes do grafo
    int numberOfLines(const string& myfile);
    void readStops();
public:
    STCP();

};


#endif //STCPREDETRANSPORTES_STCP_H
