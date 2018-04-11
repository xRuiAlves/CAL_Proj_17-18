//
// Created by reeckset on 05-04-2018.
//

#ifndef CAL_UI_H
#define CAL_UI_H

#include "../Utilities/defs.h"
#include "../GraphViewer/cpp/graphviewer.h"
#include "../Graph/Node.h"

using namespace std;

typedef void(*menuFunctionPtr)();

static void closeFunction();
static void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr>> menuItems);
static u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg);

void loadMap(const string &a, const string &b, const string &c);

void menuLoadMap();
    void loadTestMap();
    void loadSmallMap();
    void loadMediumMap();
    void loadBigMap();
void menuOperateGraph();
    void viewGraph();
        void viewGraphInViewer();
        void showGraphInTerm();
    void menuSearch();
    void dfsTwoNodes();
    void menuDijkstraAStar();
        void calcDijkstra();
        void calcDijBiDirNoPOIs();
        void calcAStar();
        void calcAStarBiDir();
        void calcDijkstraAndAStar();
        void calcAStarAndAStarBiDir();
    void menuDijBiDir();
    void menuTSP();
        void menuTSPNearestNeighbor();
        void menuTSP2opt();


GraphViewer* generateGV();
GraphViewer* generateGV(double minX, double minY, double maxX, double maxY, bool drawEdges, int vertexSize, const string &vertexColor, bool dashedEdges);
GraphViewer* generateGraphForNodes(const vector<u_int> &nodes);
GraphViewer* generateGraphForNodes(const NodeHashTable &region);

GraphViewer* showShortestPath(vector<u_int> path);
void showRegion(NodeHashTable dfsResult, u_int startNodeId);

void closeViewer(GraphViewer* gv);

void showNodes();
u_int getNodeInput(string msg);
vector<u_int> getPOIsFromUser();



#endif //CAL_UI_H
