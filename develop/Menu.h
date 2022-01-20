//
// Created by john on 20/01/22.
//

#ifndef STCPREDETRANSPORTES_MENU_H
#define STCPREDETRANSPORTES_MENU_H

#include "STCP.h"

class Menu {
    STCP stcp;

    void flush();

    void travel();

public:
    Menu(STCP stcp);
};


#endif //STCPREDETRANSPORTES_MENU_H
