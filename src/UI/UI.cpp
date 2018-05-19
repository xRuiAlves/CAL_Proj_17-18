#include "UI.h"
#include "../Graph/Graph.h"
#include "../Utilities/mapParser.h"
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/AStar.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"
#include "../Algorithms/DijkstraBiDir.h"
#include "../Algorithms/TSPNearestNeighbor.h"
#include "../Algorithms/Two_Opt.h"
#include "../Algorithms/AStarBiDir.h"
#include "../Algorithms/StringSearch.h"
#include <ctime>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;


void generateTestGraph(Graph & g);

static Graph loadedGraph;
static vector<string> loadedNodes;
static const vector<string> defaultDistricts = {"Mercúrio", "Vénus", "Terra", "Marte", "Júpiter", "Saturno", "Urano", "Neptuno", "Plutão"};

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
    srand (time(NULL));
    for (u_int i=0 ; i<loadedGraph.getNumNodes() ; i++) {
        Node n = loadedGraph.getNodeById(i);
        cout << i << endl;
        for (Edge e : n.getEdges()) {
            cout << "\t" << e.destNodeId << " - " << e.name << " - " << e.value << endl;
        }
    }

    //TODO DELETE EVERYTHING ABOVE THIS INSIDE THE MAIN METHOD
    createMenu("Easy Pilot - Main Menu", {
            {"Load Map", menuLoadMap},
            {"Navigate", menuOperateGraph}
    });
    return 0;
}

void menuLoadMap(){
    createMenu("Easy Pilot - Load Map", {
            {"Test Map", loadTestMap},
            {"Small Map -> Asprela", loadSmallMap},
            {"Medium Map -> Senhora da Hora", loadMediumMap},
            {"Big Map -> Oporto", loadBigMap}
    });
}

void menuOperateGraph(){
    if (loadedGraph.getNumNodes() == 0) {
        cout << "\n*** WARNING: No Graph in program memory. ***\nPlease load a Map first." << endl;
        closeFunction();
        return;
    }

    createMenu("Easy Pilot - Navigator", {
            {"Visualize Map", viewGraph},
            {"Test Path Possibility", dfsTwoNodes},
            {"Location Connectivity", menuSearch},
            {"Path Between Two Locations", menuDijkstraAStar},
            {"Path Between Two Locations through best POI", menuDijBiDir},
            {"Path Between Two Locations through several POIs", menuTSP}
    });
}

void loadTestMap(){
    cout << "\nLoading map ..." << endl;
    generateTestGraph(loadedGraph);
    cout << "\nMap loaded successfully.";
    closeFunction();

}

void loadSmallMap(){
    cout << "\nLoading map ..." << endl;
    loadMap("../maps/map_small_A.txt","../maps/map_small_B.txt","../maps/map_small_C.txt");
    closeFunction();
}
void loadMediumMap(){
    cout << "\nLoading map ..." << endl;
    loadMap("../maps/map_medium_A.txt","../maps/map_medium_B.txt","../maps/map_medium_C.txt");
    closeFunction();
}
void loadBigMap(){
    cout << "\nLoading map ..." << endl;
    loadMap("../maps/map_big_A.txt","../maps/map_big_B.txt","../maps/map_big_C.txt");
    closeFunction();
}

void loadMap(const string &a, const string &b, const string &c){
    try {
        loadedGraph = parseMap(a, b, c);
        loadNodes();
        cout << "\nSucessfuly loaded map with " << loadedGraph.getNumNodes() << " node and "
             << loadedGraph.getNumEdges() << " edges." << endl;
    }
    catch (GraphLoadFailed err){
        cout << "\nFailed to load graph: Could not open " << err.fileName << "." << endl;
    }
}

void menuSearch(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    BFS bfs = BFS(loadedGraph);
    DFS dfs = DFS(loadedGraph);
    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    NodeHashTable bfsResult = bfs.performSearch(startNodeId);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    NodeHashTable dfsResult = dfs.performSearch(startNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    cout << "Ran Breadth-First Search in " << t1.count() - t0.count() << " milliseconds and there were " << bfsResult.size() - 1 << " nodes reachable, besides itself" << endl;
    cout << "Ran Depth-First Search in " << t2.count() - t1.count() << " milliseconds and there were " << dfsResult.size() - 1 << " nodes reachable, besides itself" << endl;

    showRegion(dfsResult, startNodeId);

    closeFunction();
}

void menuDijkstraAStar(){
    createMenu("Easy Pilot - Optimal path between two locations",
               {{"Optimal path using Dijkstra algorithm", calcDijkstra},
                {"[Bidirectional] Optimal path using Dijkstra algorithm", calcDijBiDirNoPOIs},
                {"Optimal path using A* algorithm", calcAStar},
                {"[Bidirectional] Optimal path using A* algorithm", calcAStarBiDir},
                {"[Comparison] Dijkstra and A* algorithms", calcDijkstraAndAStar},
                {"[Comparison] A* and Bidirectional A* algorithms", calcAStarAndAStarBiDir}});
}

void calcDijkstra(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    Dijkstra d = Dijkstra(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    if (dfs.isPathPossible(startNodeId, finishNodeId)) {
        result = d.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if(d.foundSolution()) {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << d.getSolutionWeight() << " m" << endl;

    }else {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }
    closeViewer(showShortestPath(result));
}

void calcAStar(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    AStar a = AStar(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    if (dfs.isPathPossible(startNodeId, finishNodeId)) {
        result = a.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());


    if(a.foundSolution()) {
        cout << "Ran A* algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " m" << endl;
    }else {

        cout << "Ran A* algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }

    closeViewer(showShortestPath(result));
}

void calcAStarBiDir(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    GraphViewer *gv = nullptr;

    AStarBiDir adb = AStarBiDir(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    if (dfs.isPathPossible(startNodeId, finishNodeId)) {
        result = adb.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if(adb.foundSolution()) {
        cout << "Ran A* algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found path with "
             << adb.getSolutionWeight() << " m going" << endl;
    }else {
        cout << "Ran A* algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }

    gv = showShortestPath(result);

    closeViewer(gv);
}

void calcDijkstraAndAStar(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    Dijkstra d = Dijkstra(loadedGraph);
    AStar a = AStar(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    bool isPathPossible = dfs.isPathPossible(startNodeId, finishNodeId);
    if (isPathPossible) {
        result = d.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if (isPathPossible) {
        a.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if (d.foundSolution()) {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << d.getSolutionWeight() << " m" << endl;

        cout << "Ran A* algorithm in " << t2.count() - t1.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " m" << endl;
    } else {
        cout << "Ran Dijkstra algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;

        cout << "Ran A* algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }

    closeViewer(showShortestPath(result));
}

void calcAStarAndAStarBiDir(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    AStar a(loadedGraph);
    AStarBiDir abd(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    NodeHashTable pois;

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    bool isPathPossible = dfs.isPathPossible(startNodeId, finishNodeId);
    if (isPathPossible) {
        result = a.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if (isPathPossible) {
        abd.calcOptimalPath(startNodeId, finishNodeId);
    }

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if (a.foundSolution()) {
        cout << "Ran A* algorithm in " << t1.count() - t0.count() << " milliseconds and found path with "
             << a.getSolutionWeight() << " m" << endl;

        cout << "Ran A* algorithm in both directions in " << t2.count() - t1.count() << " milliseconds and found path with "
             << abd.getSolutionWeight() << " m" << endl;
    } else {
        cout << "Ran A* algorithm in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;

        cout << "Ran A* algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }

    closeViewer(showShortestPath(result));
}

void menuDijBiDir(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");
    showNodes();

    vector<u_int> pois = getPOIsFromUser();
    NodeHashTable chosenPOIs;
    for (u_int id : pois) {
        chosenPOIs.insert(loadedGraph.getNodeById(id));
    }

    GraphViewer *gv = nullptr; 

    if(!chosenPOIs.empty()){
        DijkstraBiDir dbd = DijkstraBiDir(loadedGraph);

        milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        vector<u_int> result = dbd.calcOptimalPath(startNodeId, finishNodeId, chosenPOIs);

        milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        if(dbd.foundSolution()) {
            cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found path with "
                 << dbd.getSolutionWeight() << " m going through " << dbd.getBestPOI().getName() << " (ID=" << dbd.getBestPOI().getId() << ")" << endl;
        }else {
            cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found no available path through any of the given locations"
                 << endl;
        }

        if(result.size() > 1) {
            gv = showShortestPath(result);
            gv->setVertexSize(dbd.getBestPOI().getId(), 50);
            gv->setVertexColor(dbd.getBestPOI().getId(), "blue");
        }

    }else{
        cout << "The inserted locations are not valid. Exiting to menu..." << endl;
    }

    closeViewer(gv);
}

void calcDijBiDirNoPOIs(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    NodeHashTable chosenPOIs;

    GraphViewer *gv = nullptr;

    DijkstraBiDir dbd = DijkstraBiDir(loadedGraph);
    DFS dfs = DFS(loadedGraph);

    milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    vector<u_int> result;
    if (dfs.isPathPossible(startNodeId,finishNodeId)) {
        result = dbd.calcOptimalPath(startNodeId, finishNodeId, chosenPOIs);
    }

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if(dbd.foundSolution()) {
        cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found path with "
             << dbd.getSolutionWeight() << " m going" << endl;
    }else {
        cout << "Ran Dijkstra algorithm in both directions in " << t1.count() - t0.count() << " milliseconds and found no available path"
             << endl;
    }

    gv = showShortestPath(result);

    closeViewer(gv);
}

void menuTSP(){
    createMenu("Easy Pilot - Path Between Two Locations through several POIs", {
            {"Using Nearest Neighbor Heuristic", menuTSPNearestNeighbor},
            {"Using Iterative 2-Opt Improvement", menuTSP2opt}
    });
}

void menuTSPNearestNeighbor(){
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");
    showNodes();

    vector<u_int> chosenPOIs = getPOIsFromUser();

    GraphViewer *gv = nullptr;

    if(!chosenPOIs.empty()){

        TSPNearestNeighbor tsp(loadedGraph);

        milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        vector<u_int> result = tsp.calcPath(startNodeId,finishNodeId,chosenPOIs);

        milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        if(!result.empty()) {
            cout << "Successfully found a path in " << t1.count() - t0.count() << " milliseconds with a distance of " << tsp.getSolutionWeight() << "m" << endl;
            gv = showShortestPath(result);
            for(u_int id : chosenPOIs) {
                gv->setVertexSize(id, 40);
                gv->setVertexColor(id, "blue");
            }
        }else{
            cout << "Could not find path between given locations" << endl;
        }
    }else{
        cout << "The inserted locations are not valid. Exiting to menu..." << endl;
    }

    closeViewer(gv);
}

void menuTSP2opt() {
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    cout << "\nPlease enter a positive number of iterations for 2-opt" << endl;
    u_int numIterations = getUnsignedIntInputInclusive(1, 20, "Please enter a positive number of iterations.");
    cout << endl;

    showNodes();
    vector<u_int> chosenPOIs = getPOIsFromUser();

    GraphViewer *gv = nullptr; 

    if(!chosenPOIs.empty()){

        TSPNearestNeighbor tsp(loadedGraph);

        milliseconds t0 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        vector<u_int> result = tsp.calcPath(startNodeId,finishNodeId,chosenPOIs);

        milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

        if(!result.empty()) {
            cout << "Nearest Neighbor Heuristic successfully found a path in " << t1.count() - t0.count() << " milliseconds with a distance of " << tsp.getSolutionWeight() << "m" << endl;
            Two_Opt topt(loadedGraph);
            double weight;

            milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

            result = topt.performImprovement(tsp.getVisitOrder(), tsp.getSolutionWeight(), numIterations);
            result = topt.buildSolution(result, weight);

            milliseconds t3 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
            cout << "2-Opt algorithm ran for " << t3.count() - t2.count() << " miliseconds and ";

            if (weight == tsp.getSolutionWeight()) {
                cout << "could not obtain a better solution." << endl;
            }
            else {
                cout << "improved the solution to a distance of " << weight << "m." << endl;
                cout << "Total improvement:  " << tsp.getSolutionWeight() - weight << "m." << endl;
            }

            gv = showShortestPath(result);
            for(u_int id : chosenPOIs) {
                gv->setVertexSize(id, 50);
                gv->setVertexColor(id, "blue");
            }
        }else{
            cout << "Could not find path between given locations" << endl;
        }
    }else{
        cout << "The inserted locations are not valid. Exiting to menu..." << endl;
    }

    closeViewer(gv);
}

vector<u_int> getPOIsFromUser() {
    vector<u_int> chosenPOIs;
    stringstream ss;
    string inputstr;

    cout << endl << "Insert the IDs for the locations of the possible drive-through locations separated by white spaces:" << endl;

    getline(cin, inputstr);
    ss << inputstr;


    u_int chosenId;
    while(ss >> chosenId){
        chosenPOIs.push_back(chosenId);
        if(chosenId < 0 || chosenId >= loadedGraph.getNumNodes()){
            chosenPOIs.clear();
            break;
        }
    }

    return chosenPOIs;
}

u_int getNodeInput(string msg){
    showNodes();
    cout << endl << msg << endl;
    cout << "Please select the type of search you want to use:" << endl;
    cout << "1 - Exact search" << endl;
    cout << "2 - Approximate search" << endl;
    u_int chosenId = getUnsignedIntInputInclusive(1,2, "Invalid search type. Please insert the id for the type you want.");
    cout << "You may now search for the node you want:" << endl;
    if(chosenId == 1){
        return getNodeInputExactSearch(msg);
    }
    return getNodeInputApproximateSearch(msg);
}

u_int getNodeInputApproximateSearch(string msg){
    string stringInput;
    vector<int> foundNodes = {};
    while(true) {
        getline(cin, stringInput);
        foundNodes = StringSearch::getStringsByDistance(loadedNodes, stringInput);
        if(!foundNodes.empty()){
            break;
        }
        cout << "No results found. Please try another search" << endl;
    }
    for(int i = 0; i < foundNodes.size(); i++){
            cout << loadedNodes.at(foundNodes.at(i)) << endl;
    }
    cout << endl << msg << endl << "Please insert now the id for the location:" << endl;
    return getUnsignedIntInputInclusive(0, loadedGraph.getNumNodes() - 1, "Invalid id. Please insert an id for a location presented on screen");
}

u_int getNodeInputExactSearch(string msg){
    string stringInput;
    bool foundResults = false;
    while(true) {
        getline(cin, stringInput);
        for (int i = 0; i < loadedNodes.size(); i++) {
            if (StringSearch::hasKmpMatch(loadedNodes.at(i), stringInput)) {
                cout << loadedNodes.at(i) << endl;
                foundResults = true;
            }
        }
        if(foundResults){
            break;
        }
        cout << "No results found. Please try another search" << endl;
    }
    cout << endl << msg << endl << "Please insert now the id for the location:" << endl;
    return getUnsignedIntInputInclusive(0, loadedGraph.getNumNodes() - 1, "Invalid id. Please insert an id for a location presented on screen");
}

void loadNodes(){
    Node currNode;
    for(size_t i = 0; i < loadedGraph.getNumNodes(); i++){
        currNode = loadedGraph.getNodeById(i);
        string currNodeName;
        if(currNode.getNumEdges() == 0) {
            currNodeName = to_string(currNode.getId()) + " - [Isolated]";
        }else{
            currNodeName = to_string(currNode.getId()) + " - ";
            for(int j = 0; j < currNode.getNumEdges(); j++){
                Edge e = currNode.getEdges().at(j);
                currNodeName += (e.name == "" ? "Unknown" : e.name);
                if(j != currNode.getNumEdges() - 1){
                    currNodeName += ", ";
                }
            }
        }
        currNodeName += " -> " + defaultDistricts.at(rand() % defaultDistricts.size());
        loadedNodes.push_back(currNodeName);
    }
}

void showNodes(){
    for(string s : loadedNodes){
        cout << s << endl;
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
    int windowWidth = max((int)(windowHeight * graphWidth/graphHeight), 700);
    GraphViewer *gv = new GraphViewer(windowWidth, windowHeight, false);
    gv->setBackground("background.jpg");
    gv->createWindow(windowWidth, windowHeight);
    gv->defineEdgeDashed(dashedEdges);
    gv->defineVertexColor(vertexColor);

    double yPercent, xPercent;

    for(size_t i = 0; i < loadedGraph.getNumNodes(); i++){
        Node n = loadedGraph.getNodeById(i);

        yPercent = 1.0 - ((n.getY() - minY)/graphHeight*0.9 + 0.05); //+5% to have margins
        xPercent = (n.getX() - minX)/graphWidth*0.9 + 0.05; //*90% to be within margins

        gv->addNode(i, (int)(xPercent*windowWidth), (int)(yPercent*windowHeight));
        gv->setVertexSize(i, vertexSize);
    }

        if(drawEdges) {
            int edgeId=0;
            vector<Edge> edges;
        for (u_int i = 0; i < loadedGraph.getNumNodes(); i++) {
            edges = loadedGraph.getNodeById(i).getEdges();
            for (Edge e : edges) {
                if (e.destNodeId < loadedGraph.getNumNodes()) {
                    gv->removeEdge(edgeId++);
                    gv->addEdge(edgeId++,i , e.destNodeId, EdgeType::DIRECTED);
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
                                 false, 4, "gray", true);

    return gv;
}

GraphViewer* showShortestPath(vector<u_int> path) {
    if (path.size() <= 1) {
        return nullptr;
    }

    GraphViewer *gv = generateGraphForNodes(path);
    //Generate styled path
    for (size_t i = 1; i < path.size(); i++) {
        gv->addEdge(i, path.at(i - 1), path.at(i), EdgeType::DIRECTED);
        gv->setEdgeDashed(i, false);
        gv->setEdgeThickness(i, 4);
        gv->setEdgeColor(i, "orange");
        if (i != path.size() - 1) {
            gv->setVertexColor(path.at(i), "yellow");
            gv->setVertexSize(path.at(i), 15);
        }
    }

    //Style start and finish
    gv->setVertexSize(path.at(0), 40);
    gv->setVertexSize(path.at(path.size() - 1), 40);
    gv->setVertexColor(path.at(0), "green");
    gv->setVertexColor(path.at(path.size() - 1), "red");
    gv->setVertexLabel(path.at(0), "Start location");
    gv->setVertexLabel(path.at(path.size() - 1), "Destination");
    gv->rearrange();

    return gv;
}

void dfsTwoNodes() {
    u_int startNodeId = getNodeInput("Please insert the starting location");
    u_int finishNodeId = getNodeInput("Please insert the finish location");

    DFS dfs = DFS(loadedGraph);

    milliseconds t1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    bool pathPossible = dfs.isPathPossible(startNodeId, finishNodeId);

    milliseconds t2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    if (pathPossible) {
        cout << "Ran Depth-First Search in " << t2.count() - t1.count() << " milliseconds and successfully found a path" << endl;
    } else {
        cout << "Ran Depth-First Search in " << t2.count() - t1.count() << " milliseconds and found no possible path" << endl;
    }

    closeFunction();
}

void showRegion(NodeHashTable region, u_int startNodeId) {

    GraphViewer *gv = generateGraphForNodes(region);
    //Generate styled path
    for(Node n : region){
        gv->setVertexColor(n.getId(), "orange");
    }

    Node n = *region.find(startNodeId);
    gv->setVertexColor(n.getId(), "blue");
    gv->setVertexSize(n.getId(), 50);

    gv->rearrange();

    closeFunction();

    gv->closeWindow();
    delete (gv);
}

GraphViewer *generateGraphForNodes(const NodeHashTable &region) {

    NodeHashTable::const_iterator it = region.begin();

    double minX = it->getX();
    double minY = it->getY();
    double maxX = it->getX();
    double maxY = it->getY();

    for(Node n : region){

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
                                 false, 8, "gray", true);
    return gv;
}

void closeViewer(GraphViewer* gv) {
    closeFunction();
    if(gv != nullptr) {
        gv->closeWindow();
        delete (gv);
    }
}