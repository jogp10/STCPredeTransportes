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

    cout << "Choose your departure local:" << endl;
    cin >> departure;

    cout << "Choose your arrival local:" << endl;
    cin >> arrival;

    stcp.fromTo(departure, arrival);


}