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

    cout << "1) Travel by stops keys" << endl;
    cout << "2) Travel by coordinates" << endl;

    cin >> choice;

    switch(choice) {
        case 1:
            travelStops();
            break;

        case 2:
            travelCoordinates();
            break;

        default:
            travelStops();
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


void Menu::travelStops(){
    flush();

    string departure = "";
    string arrival = "";

    cout << "Choose your departure local:" << endl;
    cin >> departure;

    cout << "Choose your arrival local:" << endl;
    cin >> arrival;

    string choiceString = travelMode();

    stcp.fromTo(departure, arrival, choiceString);
}


void Menu::travelCoordinates() {
    double departureLatitude = 0;
    double departureLongitude = 0;
    double arrivalLatitude = 0;
    double arrivalLongitude = 0;

    cout << "Departure latitude: "; cin >> departureLatitude; cout << endl;
    cout << "Departure longitude: "; cin >> departureLongitude; cout << endl;
    cout << "Arrival latitude: "; cin >> arrivalLatitude; cout << endl;
    cout << "Arrival longitude: "; cin >> arrivalLongitude; cout << endl;

    string choiceString = travelMode();

    stcp.fromTo(departureLatitude, departureLongitude, arrivalLatitude, arrivalLongitude, choiceString);
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

