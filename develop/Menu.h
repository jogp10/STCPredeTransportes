//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_MENU_H
#define STCPREDETRANSPORTES_MENU_H

#include "STCP.h"

class Menu {
    STCP stcp;

    /**
     * FLush Screen
     */
    void flush();

    /**
     * Travel Menu during daytime
     */
    void travelDay();

    /**
     * Travel Menu at nighttime
     */
    void travelNight();

    void procedure();

    void procedureStops();

    void procedureCoordinates();

    /**
     * Preferred travel mode
     * @return travel mode in string format
     */
    string travelMode();

public:
    /**
     * STCP Menu
     * @param stcp STCP, bus service provider
     */
    Menu(STCP stcp);
};


#endif //STCPREDETRANSPORTES_MENU_H
