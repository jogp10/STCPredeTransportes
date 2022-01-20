//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_STCP_H
#define STCPREDETRANSPORTES_STCP_H


#include "graph/graph.h"
#include <map>

class STCP {
    map<string, string> lines;

    Graph graph = Graph(0);

    int numberOfLines(string myfile);

    void readLines(string file);

public:
    STCP();

};


#endif //STCPREDETRANSPORTES_STCP_H
