//
// Created by reeckset on 05-04-2018.
//

#ifndef CAL_UI_H
#define CAL_UI_H

#include "../Utilities/defs.h"
#include "../GraphViewer/cpp/graphviewer.h"

using namespace std;

typedef void(*menuFunctionPtr)();

static void closeFunction();
static void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems);
static u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg);

void loadMap(const string &a, const string &b, const string &c);

void menuLoadMap();
    void loadSmallMap();
    void loadMediumMap();
    void loadBigMap();
void menuShortestPath();
    void viewGraph();
        void viewGraphInViewer();
        void showGraphInTerm();
    void menuSearch();
    void menuDijkstraAStar();
        void calcDijkstra();
        void calcAStar();
        void calcDijkstraAndAStar();
    void menuDijBiDir();
    void menuTSP();


GraphViewer* generateGV();
GraphViewer* generateGV(double minX, double minY, double maxX, double maxY, bool drawEdges, int vertexSize, const string &vertexColor, bool dashedEdges);
GraphViewer* generateGraphForNodes(const vector<u_int> &nodes);

void showShortestPath(vector<u_int> path);

void showNodes();
u_int getNodeInput(string msg);



#endif //CAL_UI_H
