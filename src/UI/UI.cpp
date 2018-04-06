//
// Created by reeckset on 05-04-2018.
//

#include "UI.h"
#include "../Graph/Graph.h"
#include "../Utilities/mapParser.h"
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/AStar.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"
#include "../Algorithms/DijkstraBiDir.h"
#include "../Algorithms/TSPNearestNeighbor.h"
#include <ctime>
#include <chrono>
#include <random>
#include <sstream>

using namespace std;
using namespace std::chrono;


void generateRandomGridGraph(int n, Graph & g);

static Graph loadedGraph;

void closeFunction(){
    cout << "\n\nPress ENTER to continue.";
    int character = getchar();

    if(character == '\n')	// enter key is pressed
        return;
    else
        cin.ignore(1000, '\n');
}

void createMenu(string menuTitle, vector<pair<string, menuFunctionPtr> > menuItems){

    string errorMsg = "Invalid Input. Insert a value beetween 0 and " + to_string(menuItems.size()) + "\n";

    while (1) {

        int selectedItem = -1;
        cout << "\n ------ " << menuTitle << " ------\n  _\n |\n";
        for (int i = 0; i < menuItems.size(); i++) {
            cout << " | " << i + 1 << " - " << menuItems[i].first << "\n |\n";
        }
        cout << " | 0 - Back\n |_\n\n----------------------------------------------- \n\n";

        cout << "Please insert a value beetween 0 and " + to_string(menuItems.size()) + "\n";

        selectedItem = getUnsignedIntInputInclusive(0, menuItems.size(), errorMsg);

        if (selectedItem == 0) {
            break;
        } else {
            menuItems[selectedItem - 1].second();
        }

    }
}

u_int getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg){
    int result;
    cin >> result;
    while(!cin.good() || result < lowerBound || result > higherBound){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << errorMsg << endl;
        cin >> result;
    }
    cin.ignore(1000, '\n');
    return result;
}

int main(){
    loadedGraph = Graph();
    generateRandomGridGraph(10, loadedGraph);

    //TODO DELETE EVERYTHING ABOVE THIS INSIDE THE MAIN METHOD
    createMenu("Easy Pilot - Main Menu", {
            {"Load Map", menuLoadMap},
            {"Navigate", menuShortestPath}
    });
    return 0;
}

void menuLoadMap(){
    createMenu("Easy Pilot - Load Map", {
            {"Small Map -> Castro Daire", loadSmallMap},
            {"Medium Map -> Senhora da Hora", loadMediumMap},
            {"Big Map -> Oporto", loadBigMap}
    });
}

void menuShortestPath(){
    createMenu("Easy Pilot - Navigator", {
            {"BFS and DFS (TODO: CHANGE THIS NAME)", menuSearch},
            {"Dijkstra and A* comparison", menuDijkstraAStar},
            {"Refuel on the way", menuDijBiDir},
            {"Go through all the POI's", menuTSP}
    });
}

void loadSmallMap(){
    cout << "YAY LOADING SMALL MAP!" << endl;
    closeFunction();
}
void loadMediumMap(){
    cout << "YAY LOADING MEDIUM MAP!" << endl;
    closeFunction();
}
void loadBigMap(){
    try {
        loadedGraph = parseMap("../maps/map_big_A.txt", "../maps/map_big_B.txt", "../maps/map_big_C.txt");
        cout << "\nSucessfuly loaded map with " << loadedGraph.getNumNodes() << " node and "
             << loadedGraph.getNumEdges() << " edges." << endl;
    }
    catch (GraphLoadFailed err){
        cerr << "Failed to load graph: Could not open " << err.fileName << "." << endl;
    }

    closeFunction();
}

void menuSearch(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    BFS bfs = BFS(loadedGraph);
    DFS dfs = DFS(loadedGraph);
    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    NodeHashTable bfsResult = bfs.performSearch(startNodeId);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    NodeHashTable dfsResult = dfs.performSearch(startNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    cout << "Ran Breadth-First Search in " << t1.count() - t0.count() << " milliseconds and there were " << bfsResult.size() - 1 << " nodes reachable, besides itself" << endl;
    cout << "Ran Depth-First Search in " << t2.count() - t1.count() << " milliseconds and there were " << dfsResult.size() - 1 << " nodes reachable, besides itself" << endl;

    closeFunction();
}

void menuDijkstraAStar(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    u_int finishNodeId = getNodeInput("Please insert the id for the finish location");

    Dijkstra d = Dijkstra(loadedGraph);
    AStar a = AStar(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    d.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    a.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    if(d.foundSolution()) {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << d.getSolutionWeight() << " km" << endl;

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " km" << endl;
    }else {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found no available path"
             << endl;
    }
    closeFunction();
}

void menuDijBiDir(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    u_int finishNodeId = getNodeInput("Please insert the id for the finish location");
    showNodes();
    cout << endl << "Insert the IDs for the locations of the possible drive-through locations separated by white spaces:" << endl;
    stringstream ss;
    string inputstr;
    std::getline( cin, inputstr);
    ss << inputstr;
    bool validInput = true;
    u_int chosenId;
    NodeHashTable chosenPOIs;
    while(ss >> chosenId){
        chosenPOIs.insert(chosenId);
        if(chosenId < 0 || chosenId >= loadedGraph.getNumNodes()){
            validInput = false;
            break;
        }

    }
    if(validInput){
        DijkstraBiDir dbd = DijkstraBiDir(loadedGraph);

        milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        dbd.calcOptimalPath(startNodeId, finishNodeId, chosenPOIs);

        milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        if(dbd.foundSolution()) {
            cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found path with "
                 << dbd.getSolutionWeight() << " km going through " << dbd.getBestPOI().getName() << " (ID=" << dbd.getBestPOI().getId() << ")" << endl;
        }else {
            cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found no available path through any of the given locations"
                 << endl;
        }
    }else{
        cout << "The inserted locations are not valid. Exiting to menu..." << endl;
    }
    closeFunction();
}
void menuTSP(){
    showNodes();
    closeFunction();
}

u_int getNodeInput(string msg){
    showNodes();
    cout << endl << msg << endl;
    return getUnsignedIntInputInclusive(0, loadedGraph.getNumNodes() - 1, "Invalid id. Please insert an id for a location presented on screen");
}

void showNodes(){
    Node currNode;
    for(size_t i = 0; i < loadedGraph.getNumNodes(); i++){
        currNode = loadedGraph.getNodeById(i);
        cout << currNode.getId() << " - " << currNode.getName() << endl;
    }
}
