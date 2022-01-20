//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_STCP_H
#define STCPREDETRANSPORTES_STCP_H


#include "graph/graph.h"
#include <map>

class STCP {
    map<string, string> lines; // key: codigo da linha, value: nome da linha
    map<string, int> stops; //key: codigo da paragem, value: index no vetor de nodes do grafo
    Graph graph = Graph(0);


    int numberOfLines(const string& myfile);
    void readStops();

    /**
 * Goes to file and gets code and name of lines
 * @param myFile
 */
    void readLines(string file);
    void readEdges(string code);
    
public:
    STCP();

};


#endif //STCPREDETRANSPORTES_STCP_H
