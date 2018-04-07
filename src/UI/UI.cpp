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
            {"View Map", viewGraph},
            {"BFS and DFS (TODO: CHANGE THIS NAME)", menuSearch},
            {"Dijkstra and A* comparison", menuDijkstraAStar},
            {"Refuel on the way", menuDijBiDir},
            {"Go through all the POI's", menuTSP}
    });
}

void loadSmallMap(){
    loadMap("../maps/map_small_A.txt","../maps/map_small_B.txt","../maps/map_small_C.txt");
    closeFunction();
}
void loadMediumMap(){
    loadMap("../maps/map_medium_A.txt","../maps/map_medium_B.txt","../maps/map_medium_C.txt");
    closeFunction();
}
void loadBigMap(){
    loadMap("../maps/map_big_A.txt","../maps/map_big_B.txt","../maps/map_big_C.txt");
    closeFunction();
}

void loadMap(const string &a, const string &b, const string &c){
    try {
        loadedGraph = parseMap(a, b, c);
        cout << "\nSucessfuly loaded map with " << loadedGraph.getNumNodes() << " node and "
             << loadedGraph.getNumEdges() << " edges." << endl;
    }
    catch (GraphLoadFailed err){
        cerr << "Failed to load graph: Could not open " << err.fileName << "." << endl;
    }
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
    createMenu("Easy Pilot - Optimal path between two locations",
               {{"Dijkstra", calcDijkstra},
                       {"A*", calcAStar},
                {"Dijkstra and A* comparison", calcDijkstraAndAStar}});
}

void calcDijkstra(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    u_int finishNodeId = getNodeInput("Please insert the id for the finish location");

    Dijkstra d = Dijkstra(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result = d.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if(d.foundSolution()) {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << d.getSolutionWeight() << " m" << endl;

    }else {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }
    showShortestPath(result);
}

void calcAStar(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    u_int finishNodeId = getNodeInput("Please insert the id for the finish location");

    AStar a = AStar(loadedGraph);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result = a.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());


    if(a.foundSolution()) {
        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " m" << endl;
    }else {

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found no available path"
             << endl;
    }

    showShortestPath(result);
}

void calcDijkstraAndAStar(){
    u_int startNodeId = getNodeInput("Please insert the id for the starting location");
    u_int finishNodeId = getNodeInput("Please insert the id for the finish location");

    Dijkstra d = Dijkstra(loadedGraph);
    AStar a = AStar(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result = d.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    a.calcOptimalPath(startNodeId, finishNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    if (d.foundSolution()) {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << d.getSolutionWeight() << " m" << endl;

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " m" << endl;
    } else {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found no available path"
             << endl;
    }

    showShortestPath(result);
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
                 << dbd.getSolutionWeight() << " m going through " << dbd.getBestPOI().getName() << " (ID=" << dbd.getBestPOI().getId() << ")" << endl;
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
        if(currNode.getNumEdges() == 0) {
            cout << currNode.getId() << " - " << "Isolated" << endl;
        }else{
            cout << currNode.getId() << " - ";
            for(int j = 0; j < currNode.getNumEdges(); j++){
                Edge e = currNode.getEdges().at(j);
                cout << (e.name == "" ? "Unknown" : e.name);
                if(j != currNode.getNumEdges() - 1){
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

void viewGraph(){
    createMenu("Easy Pilot - View Map",
               {{"View Map/Graph in console", showGraphInTerm},
                {"View Map/Graph in a window", viewGraphInViewer}});
}

void showGraphInTerm(){
    showNodes();
    closeFunction();
}

void viewGraphInViewer(){
    GraphViewer* gv = generateGV();
    closeFunction();
    gv->closeWindow();
    delete(gv);
}

GraphViewer* generateGV(){
    GraphViewer* gv = generateGV(loadedGraph.getBoundLeft(),
                                 loadedGraph.getBoundBot(),
                                 loadedGraph.getBoundRight(),
                                 loadedGraph.getBoundTop(),
                                 true, 10, "yellow", false);
    gv->rearrange();
    return gv;
}

GraphViewer* generateGV(double minX, double minY, double maxX, double maxY, bool drawEdges, int vertexSize, const string &vertexColor, bool dashedEdges){
    double graphHeight = maxY - minY;
    double graphWidth = maxX - minX;

    int windowHeight = 700;
    int windowWidth = windowHeight * graphWidth/graphHeight;
    GraphViewer *gv = new GraphViewer(windowWidth, windowHeight, false);
    gv->setBackground("background.jpg");
    gv->createWindow(windowWidth, windowHeight);
    gv->defineVertexSize(vertexSize);
    gv->defineEdgeDashed(dashedEdges);
    gv->defineVertexColor(vertexColor);

    double yPercent, xPercent;

    for(size_t i = 0; i < loadedGraph.getNumNodes(); i++){
        Node n = loadedGraph.getNodeById(i);

        yPercent = 1.0 - ((n.getY() - minY)/graphHeight*0.9 + 0.05); //+5% to have margins
        xPercent = (n.getX() - minX)/graphWidth*0.9 + 0.05; //*90% to be within margins

        gv->addNode(i, (int)(xPercent*windowWidth), (int)(yPercent*windowHeight));
    }
    if(drawEdges) {
        int id1, id2;
        for (u_int i = 0; i < loadedGraph.getNumNodes(); i++) {
            for (Edge e : loadedGraph.getNodeById(i).getEdges()) {
                if (e.destNodeId < loadedGraph.getNumNodes()) {
                    id1 = min(i, e.destNodeId);
                    id2 = max(i, e.destNodeId);
                    gv->removeEdge(id1 * loadedGraph.getNumNodes() + id2);
                    gv->addEdge(id1 * loadedGraph.getNumNodes() + id2, i, e.destNodeId, EdgeType::UNDIRECTED);
                }
            }
        }
    }
    return gv;
}

GraphViewer* generateGraphForNodes(const vector<u_int> &nodes){

    Node n = loadedGraph.getNodeById(nodes.at(0));

    double minX = n.getX();
    double minY = n.getY();
    double maxX = n.getX();
    double maxY = n.getY();

    for(size_t i = 1; i < nodes.size(); i++){

        n = loadedGraph.getNodeById(nodes.at(i));

        if (n.getX() > maxX) {
            maxX = n.getX();
        }
        else if (n.getX() < minX) {
            minX = n.getX();
        }

        if (n.getY() > maxY) {
            maxY = n.getY();
        }
        else if (n.getY() < minY) {
            minY = n.getY();
        }
    }

    GraphViewer *gv = generateGV(minX - 1, minY - 1,
                                 maxX + 1, maxY + 1,
                                 false, 10, "gray", true);

    return gv;
}

void showShortestPath(vector<u_int> path){
    if(path.empty()){
        return;
    }

    GraphViewer *gv = generateGraphForNodes(path);

    //Generate styled path
    int id1, id2;
    for(size_t i = 1; i < path.size(); i++) {
        gv->addEdge(i, path.at(i-1), path.at(i), EdgeType::DIRECTED);
        gv->setEdgeDashed(i, false);
        gv->setEdgeThickness(i, 4);
        if(i != path.size()-1){
            gv->setVertexColor(path.at(i), "yellow");
        }
    }

    //Style start and finish
    gv->setVertexSize(path.at(0), 40);
    gv->setVertexSize(path.at(path.size()-1), 40);
    gv->setVertexColor(path.at(0), "green");
    gv->setVertexColor(path.at(path.size()-1), "red");
    gv->setVertexLabel(path.at(0), "Start location");
    gv->setVertexLabel(path.at(path.size()-1), "Destination");
    gv->rearrange();

    closeFunction();
    gv->closeWindow();
    delete (gv);
}