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

void STCP::readLines(string myFile) {
    int pos;
    string line, code, name;
    ifstream file(myFile);
    string delimiter = ",";

    if(file.is_open()){
        getline(file, line);

        while(!file.eof()){
            getline(file, line);

            pos = line.find(delimiter);
            code = line.substr(0, pos);
            name = line.substr(pos+1, line.size()-pos);

            lines.insert(make_pair(code, name));
            readEdges(code);

            cout << code << " // " << name << endl;
        }

        file.close();
    }
}

void STCP::readEdges(string code) {
    for (int i = 0; i <= 1; i++) {
        ifstream file("../dataset/line_" + code + "_" + to_string(i) + ".cvs");
        string line, origin, dest;
        double weight;

        if (file.is_open()) {
            map<int, pair<double, double>> nodes = graph.getNodes();

            getline(file, line); // trash
            getline(file, origin); // origin node code

            while(!file.eof()) {
                getline(file, dest); // destination node code

                auto node1 = nodes[origin];

                weight = Graph::getDistance(nodes.find(origin));
                graph.addEdge(origin, dest, weight, code);
                auto it = stops.find(code);

                origin = dest;
            }
        }
    }
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

STCP::STCP() {
    int nodes = numberOfLines("../dataset/stops.csv");
    Graph g(nodes, true);
    this->graph = g;

    readStops();
    readLines("../dataset/lines.csv");

    map<string, int> stops;
}
