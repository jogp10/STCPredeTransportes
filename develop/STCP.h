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


    /**
     * Number lines in file
     * @param myfile file path
     * @return number of lines
     */
    int numberOfLines(const string& myfile);

    /**
     * Goes to file and gets stops
     */
    void readStops();

    /**
     * Goes to file and gets code and name of lines
     * @param myFile file path
     */
    void readLines(string file);

    /**
     * Goes to file and connects stops and lines
     * @param code Line Code
     */
    void readEdges(string code);
    
public:
    /**
     * STCP Constructor
     */
    STCP();

    /**
     *
     * @param code
     * @return
     */
    int convertCodeToIndex(string code);

    list<int> fromTo(string a, string b);

};


#endif //STCPREDETRANSPORTES_STCP_H
