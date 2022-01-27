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

    cout << "1) Travel" << endl;
    cin >> choice;

    switch(choice) {
        case 1:
            travel();
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


void Menu::travel(){
    flush();

    string departure = "";
    string arrival = "";
    int choice = 1;

    cout << "Choose your departure local:" << endl;
    cin >> departure;

    cout << "Choose your arrival local:" << endl;
    cin >> arrival;

    cout << "How do you want to travel?" << endl;
    cout << "1) Shortest distance" << endl;
    cout << "2) Less line changes" << endl;
    cout << "3) Less stops" << endl;
    cout << "4) Cheapest way (less zones)" << endl;

    cout << "Option: "; cin >> choice;

    stcp.fromTo(departure, arrival);
}