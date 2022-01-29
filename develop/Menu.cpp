//
// Created by john on 20/01/22.
//

#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <utility>
#include <string>

using namespace std;

Menu::Menu(STCP stcp) {
    this->stcp=std::move(stcp);

    int choice = 0;

    cout << "1) Travel at day" << endl;
    cout << "2) Travel at night" << endl;
    cout << "Choice: "; cin >> choice;

    switch(choice) {
        case 1:
            travelDay();
            break;
        case 2:
            travelNight();
            break;
    }
}


void Menu::flush() {
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif
    system(CLEAR);
}


void Menu::travelDay() {
    stcp.setTime("");
    procedure();
}

void Menu::travelNight() {
    stcp.setTime("M");
    procedure();
}

void Menu::procedure() {
    int choice;

    stcp.toRead();

    cout << "1) Provide Stops" << endl;
    cout << "2) Provide Coordinates" << endl;
    cout << "Option: "; cin >> choice;

    switch(choice) {
        case 1:
            procedureStops();
            break;
        case 2:
            procedureCoordinates();
            break;
    }
}

void Menu::procedureStops() {
    string departure = "";
    string arrival = "";

    cout << "Choose your departure stop:" << endl;
    cin >> departure;

    cout << "Choose your arrival stop:" << endl;
    cin >> arrival;

    string choiceString = travelMode();

    stcp.fromTo(departure, arrival, choiceString);
}

void Menu::procedureCoordinates() {
    double depLat = 0, depLon = 0;
    double arrLat = 0, arrLon = 0;


    cout << "Choose your departure latitude: " << endl;
    cin >> depLat;
    cout << "Choose your departure longitude: " << endl;
    cin >> depLon;

    cout << "Choose your arrival latitude: " << endl;
    cin >> arrLat;
    cout << "Choose your arrival longitude: " << endl;
    cin >> arrLon;

    string start = stcp.auxDeparture(depLat, depLon);
    string end = stcp.auxArrival(arrLat, arrLon);

    string choiceString = travelMode();

    stcp.fromTo(start, end, choiceString);
}

string Menu::travelMode() {
    int choice = 1;

    cout << "How do you want to travel?" << endl;
    cout << "1) Shortest distance" << endl;
    cout << "2) Less line changes" << endl;
    cout << "3) Less stops" << endl;
    cout << "4) Cheapest way (less zones)" << endl;

    cout << "Option: "; cin >> choice;

    string choiceString;

    switch(choice) {
        case 1:
            choiceString = "shortest";
            break;

        case 2:
            choiceString = "lessChanges";
            break;

        case 3:
            choiceString = "lessStops";
            break;

        case 4:
            choiceString = "lessZones";
            break;

        default:
            choiceString = "shortest";
    }

    return choiceString;
}

