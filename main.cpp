//
// Created by john on 20/01/22.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "develop/Menu.h"


int main(int argc, char* argv[]) {

    testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

    STCP stcp;
    Menu menu = Menu(stcp);

    return 0;
}

