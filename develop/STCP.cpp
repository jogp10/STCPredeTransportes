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
    return number_of_lines-1;
}

void STCP::readLines(string myFile) {
    int pos;
    string line, code, name;
    ifstream file(myFile);
    string delimiter = ",";

    if(file.is_open()){
        int count = 1;
        getline(file, line);

        while(!file.eof()){
            getline(file, line);

            pos = line.find(delimiter);
            code = line.substr(0, pos);
            name = line.substr(pos+1, line.size()-pos);

            //If it is nighttime we are looking at
            if (code.find("M") != std::string::npos && this->time == "M") {
                lines.insert(make_pair(code, name));
                readEdges(code);
            }

            //If it is daytime we are looking at
            else if (this->time == "" && code.find("M") == std::string::npos) {
                lines.insert(make_pair(code, name));
                readEdges(code);
            }

            //cout << code << " // " << name << endl;
            count++;
        }

        //cout << count << " number of lines read" << endl;
        file.close();
    }
}

void STCP::readEdges(string code) {
    for (int i = 0; i <= 1; i++) {
        string myfile = "../dataset/line_" + code + "_" + to_string(i) + ".csv";
        ifstream file(myfile);

        if (file.is_open()) {
            int count = 1;
            string line, origin, dest;
            double weight;
            map<int, pair<double, double>> nodes = graph.getNodes();

            getline(file, line); // trash
            getline(file, origin); // origin node code

            while(!file.eof()) {
                getline(file, dest); // destination node code

                int originIndex = convertCodeToIndex(origin);
                int destIndex = convertCodeToIndex(dest);

                weight = graph.getDistance(nodes[originIndex].first, nodes[originIndex].second,
                                   nodes[destIndex].first, nodes[destIndex].second);

                graph.addEdge(originIndex, destIndex, weight, code);

                origin = dest;
                count++;
            }
            //cout << count << " number of edges read in file " << myfile << endl;
        }
    }
}

void STCP::readStops() {
    string line;
    string delimiter = ",";
    size_t pos;
    string token;
    ifstream file("../dataset/stops.csv");
    int count = 1;

    if(file.is_open()){
        getline(file, line);
        while(!file.eof()){

            token = "";
            vector<string> extra;
            getline(file, line);
            pos = 0;

            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                extra.push_back(token);
                line.erase(0, pos + delimiter.length());
            }

            graph.setNode(extra[0],extra[1],extra[2], stod(extra[3]), stod(extra[4]), count);
            stops.insert(make_pair(extra[0], count));
            count++;
        }
        //cout << count << "number of stops read" << endl;
        file.close();
    }
}

STCP::STCP() {
    int nodes = numberOfLines("../dataset/stops.csv");
    Graph g(nodes, true);
    this->graph = g;

    readStops();

    graph.createWalkEdges();

/*
    cout << lines.size() << " number of lines stored " << endl;
    cout << endl <<  stops.size() << " number of stops stored " << endl;
    cout << graph.getNodes().size() << " number of stops stored in getNodes " << endl;
    */
}

void STCP::toRead() {
    readLines("../dataset/lines.csv");
}

void STCP::setTime(string time) { this->time = time; }

int STCP::convertCodeToIndex(string a) {
    return stops.find(a)->second;
}

list<int> STCP::fromTo(string a, string b, string choice){
    int origin = convertCodeToIndex(a);
    int destino = convertCodeToIndex(b);

    list<int> path = graph.dijkstra_path(origin, destino, choice);
    int tmp = *path.begin();
    int zone = 0;
    for(int i: path){
        if(graph.getNode(tmp).zone!=graph.getNode(i).zone) {
            cout << endl << "zone change" << endl << endl; // for testing
            zone++;
        }
        cout << setw(25) << std::left <<  graph.getNode(i).name << setw(15) <<  graph.getNode(i).code << setw(15) <<  graph.getNode(i).zone;
        cout << setw(15) <<  graph.getNode(i).dist; // for testing
        for(auto i: graph.getNode(i).predLines){
            cout << i << " ";
        }
        cout << endl;
        tmp = i; // for testing
    }
    double totalDist = graph.getNode(*--path.end()).dist;
    //if(choice == "lessZones") totalDist -= zone*999;
    cout << totalDist<< "\n";
    cout << path.size() << endl;
    return path;
}

string STCP::auxDeparture(const double depLat, const double depLon) {
    double walking, distance;
    string code;

    cout << "How far can the departure stop be from you?" << endl;
    cin >> walking;

    cout << "Stops near you: " << endl;
    auto m = graph.getNodes();
    for(auto n: m) {
        distance = Graph::getDistance(depLat, depLon, n.second.first, n.second.second);

        if(distance <= walking) {
            cout << graph.getNode(n.first).code << " (code) || " <<  graph.getNode(n.first).name << " (name);" << endl;
        }
    }

    cout << "What stop code?" << endl;
    cout << "Option: "; cin >> code;

    return code;
}

string STCP::auxArrival(const double arrLat, const double arrLon) {
    double walking, distance;
    string code;

    cout << "How far can the arrival stop be from your arrival stop?" << endl;
    cin >> walking;

    cout << "Stops near arrival spot: " << endl;
    for(auto n: graph.getNodes()) {
        if(n.first == 0) { continue; }

        distance = graph.getDistance(arrLat, arrLon, graph.getNode(n.first).latitude, graph.getNode(n.first).longitude);

        if(distance <= walking) {
            cout << graph.getNode(n.first).code << " (code) || " <<  graph.getNode(n.first).name << " (name);" << endl;
        }
    }

    cout << "What stop code?" << endl;
    cout << "Option: "; cin >> code;

    return code;
}