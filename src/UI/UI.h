//
// Created by reeckset on 05-04-2018.
//

#ifndef CAL_UI_H
#define CAL_UI_H

#include "../Utilities/defs.h"

using namespace std;

typedef void(*menuFunctionPtr)();

static void closeFunction();
static void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems);
static u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg);

void menuLoadMap();
    void loadSmallMap();
    void loadMediumMap();
    void loadBigMap();
void menuShortestPath();
    void menuSearch();
    void menuDijkstraAStar();
    void menuDijBiDir();
    void menuTSP();

void showNodes();
u_int getNodeInput(string msg);



#endif //CAL_UI_H
