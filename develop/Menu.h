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
     * Travel Menu
     */
    void travel();

public:
    /**
     * STCP Menu
     * @param stcp
     */
    Menu(STCP stcp);
};


#endif //STCPREDETRANSPORTES_MENU_H
