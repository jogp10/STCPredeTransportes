//
// Created by john on 20/01/22.
//

#include <fstream>

#include "STCP.h"

int STCP::numberOfLines(string myfile){
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

/**
 * Goes to file and gets code and name of lines
 * @param myFile
 */
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

        if (file.is_open()) {

        }
    }
}

STCP::STCP() {
    int nodes = numberOfLines("../dataset/stops.csv");
    Graph g(nodes, true);
    this->graph = g;

    readLines("../dataset/lines.csv");
}
