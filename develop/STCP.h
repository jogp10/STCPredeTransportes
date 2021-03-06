//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_STCP_H
#define STCPREDETRANSPORTES_STCP_H


#include "graph/graph.h"
#include <map>
#include <iomanip>
#include <iostream>

class STCP {
    map<string, string> lines; // key: codigo da linha, value: nome da linha
    map<string, int> stops; //key: codigo da paragem, value: index no vetor de nodes do grafo
    Graph graph = Graph(0);
    string time;

    /**
     * Number lines in file
     * @param myfile file path
     * @return number of lines
     */
    static int numberOfLines(const string& myfile);

    /**
     * Goes to file and reads stops, adds them to graph
     */
    void readStops();

    /**
     * Goes to file and reads code and name of lines
     * @param myFile file path
     */
    void readLines(const string& file);

    /**
     * Goes to file and connects stops and lines, by adding edges to graph
     * @param code Line Code
     */
    void readEdges(const string& code);

public:
    /**
     * STCP Constructor
     */
    STCP();

    /**
     * Function to load lines after being chosen day or night
     */
    void toRead();

    /**
     * Set time
     * @param time
     */
    void setTime(string time);

    /**
     *
     * Convert code of stop to index in vector<Node> nodes that belongs to graph
     * @param code
     * @return index
     */
    int convertCodeToIndex(const string& code);

    /**
     * From x to y, prints out the path
     * @param a Start of path
     * @param b End of path
     * @param choice Type of trajectory to follow
     * @return path
     */
    list<int> fromTo(const string& a, const string& b, const string& choice);

    /**
     * Get best and closest stop from coordinate at departure
     * @param depLat
     * @param depLon
     * @return code stop
     */
    string auxDeparture(double depLat, double depLon);

    /**
     * Get best and closest stop from coordinate at arrival
     * @param arrLat
     * @param arrLon
     * @return code stop
     */
    string auxArrival(double arrLat, double arrLon);
};


#endif //STCPREDETRANSPORTES_STCP_H