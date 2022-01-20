//
// Created by john on 20/01/22.
//

#include <fstream>
#include <map>
#include <vector>

#include "STCP.h"

int STCP::numberOfLines(const string& myfile){
    int number_of_lines = 0;

    string line;
    ifstream file(myfile);

    if(file.is_open()){
        while(!file.eof()){
            getline(file, line);
            number_of_lines++;
        }
        file.close();
    }
    return number_of_lines-2;
}

STCP::STCP() {
    int nodes = numberOfLines("../dataset/stops.csv");
    Graph g(nodes, true);
    this->graph = g;

    readStops();

    map<string, int> stops;
}

void STCP::readStops() {
    string line;
    string delimiter = ",";
    size_t pos;
    string token;
    vector<string> extra;
    ifstream file("../dataset/stops.csv");
    int count = 0;
    pair<string, int> help1;

    if(file.is_open()){
        getline(file, line);
        while(!file.eof()){
            token = "";
            extra.clear();
            getline(file, line);
            pos = 0;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                extra.push_back(token);
                line.erase(0, pos + delimiter.length());
            }
            extra.push_back(token);
            //graph.setNode(extra[0],extra[1],extra[2],extra[3],extra[4],count);
            help1.first = extra[0];
            help1.second = count;
            stops.insert(help1);
            count++;
        }
        file.close();
    }
}
