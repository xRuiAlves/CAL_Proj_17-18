#include <iostream>
#include "../Utilities/exceptions.h"
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/AStar.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"
#include "../Algorithms/DijkstraBiDir.h"
#include "../Algorithms/Two_Opt.h"
#include "../Algorithms/TSPNearestNeighbor.h"
#include <ctime>
#include <chrono>
#include <random>

using namespace std::chrono;

void generateRandomGridGraph(int n, Graph & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string name = "Node" + to_string(i) + "-" + to_string(j);
            g.addNode(i, j, name);
            //g.addVertex(make_pair(i,j));
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if ((di != 0) != (dj != 0) && i + di >= 0 && i + di < n && j + dj >= 0 && j + dj < n) {
                        //g.addEdge(make_pair(i,j), make_pair(i+di,j+dj), dis(gen));
                        g.addEdge((i * j),
                                  ((i + di) * (j + dj)),
                                  g.getNodeById(i*j).getDistanceToOtherNode(g.getNodeById((i + di) * (j + dj))));
                        //g.addEdge((i * j), ((i + di) * (j + dj)), dis(gen));
                    }
                }
            }
        }
    }
}

int not_main() {

    std::cout << "Starting tests ..." << std::endl;


    /*************************************/
    /****          GRAPH INFO         ****/
    /*************************************/

    Graph g1 = Graph();

    generateRandomGridGraph(60, g1);
/*


    u_int id0 = g1.addNode(0,0,"Rio Tinto");
    u_int id1 = g1.addNode(10, 0, "Maia");
    u_int id2 = g1.addNode(2,0,"Areosa");
    u_int id3 = g1.addNode(-10, 0, "Sra da Hora");
    u_int id4 = g1.addNode(-15, 0, "Matosinhos");
    u_int id5 = g1.addNode(-10, 0, "S. Mamede");
    u_int id6 = g1.addNode(90, 0, "Castro d'Aire");
    u_int id7 = g1.addNode(20, 0, "Santo Tirso");
    u_int id8 = g1.addNode(20, 0, "Nova Iorque");  // Nova Iorque fica mesmo ao lado de Santo Tirso
    u_int id9 = g1.addNode(15, 0, "Vila Nova de Gaia");

    g1.addEdge(id0, id2,2);
    g1.addEdge(id0, id1,10);
    g1.addEdge(id0, id6, 4);
    g1.addEdge(id1, id3, 20);
    g1.addEdge(id3, id1, 20);
    g1.addEdge(id3, id4, 5);
    g1.addEdge(id5, id4, 5);
    g1.addEdge(id4, id5, 5);
    g1.addEdge(id6, id5, 100);
*/
    u_int startNodeID = 2;
    u_int finishNodeID = 100;



    /*************************************/
    /****           DIJKSTRA          ****/
    /*************************************/
/*
    Dijkstra d = Dijkstra(g1);

    cout << "\n\n---------DIJKSTRA---------\n";
    milliseconds t1 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    d.calcOptimalPath(startNodeID, finishNodeID);

    milliseconds t1b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    d.printSolution();
*/

    /*************************************/
    /****              A*             ****/
    /*************************************/
/*
    AStar a = AStar(g1);

    cout << "\n\n---------A*---------\n";
    milliseconds t2 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.calcOptimalPath(startNodeID, finishNodeID);

    milliseconds t2b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.printSolution();

*/

    /*************************************/
    /****              DFS            ****/
    /*************************************/
/*
    DFS dfs = DFS(g1);

    cout << "\n\n---------DFS---------\n";
    milliseconds t3 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    NodeHashTable dfsResult = dfs.performSearch(startNodeID);
    dfs.printSolution();

    milliseconds t3b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );


*/
    /*************************************/
    /****              BFS            ****/
    /*************************************/
/*
    BFS bfs = BFS(g1);

    cout << "\n\n---------BFS---------\n";
    milliseconds t4 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    NodeHashTable bfsResult = bfs.performSearch(startNodeID);
    bfs.printSolution();

    milliseconds t4b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );


*/
    /*************************************/
    /****  DIJKSTRA BI DIRECTIONAL    ****/
    /*************************************/
/*
    cout << "\n\n---------Dijkstra Bidirectional---------\n";

    DijkstraBiDir dbd = DijkstraBiDir(g1);
    NodeHashTable pois;
    pois.insert(g1.getNodeById(1));
    pois.insert(g1.getNodeById(100));
    pois.insert(g1.getNodeById(302));

    milliseconds t5 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    dbd.calcOptimalPath(startNodeID, finishNodeID, pois);

    milliseconds t5b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    dbd.printSolution();

    AStar testBidir1 = AStar(g1);
    AStar testBidir2 = AStar(g1);

    cout << "Checking validity of solution:" << endl;

    for(NodeHashTable::iterator it = pois.begin(); it != pois.end(); it++){
        cout << "CALCULATING WEIGHT THROUGH POI " << (*it).getId() << endl;
        testBidir1.calcOptimalPath(startNodeID, (*it).getId());
        testBidir2.calcOptimalPath((*it).getId(), finishNodeID);
        cout << testBidir1.getSolutionWeight() + testBidir2.getSolutionWeight() << endl;
    }

*/
    /*************************************/
    /****     TSP Nearest Neighbor    ****/
    /*************************************/

    cout << "\n\n---------TSP Nearest Neighbor---------\n";

    TSPNearestNeighbor t = TSPNearestNeighbor(g1);
    vector<u_int> tsp_pois = {6,4,20,25,50,60,65,180,155,44};

    milliseconds t6 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    vector<u_int> v = t.calcPath(startNodeID, finishNodeID, tsp_pois);

    milliseconds t6b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    t.printSolution();

    vector<u_int> visitOrder = t.getVisitOrder();

    /*************************************/
    /***  2-opt Iterative Improvement  ***/
    /*************************************/
    milliseconds t7;
    milliseconds t7b;

    if (!v.empty()) {
        cout << "\n\n---------2-Opt Iterative Improvement---------\n";

        Two_Opt topt(g1);

        t7 = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );

        vector<u_int> vOrder = topt.performImprovement(visitOrder, t.getSolutionWeight(), 4);

        t7b = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );

        double w;
        vector<u_int> solution = topt.buildSolution(vOrder, w);

        cout << "\nWeight: " << w << endl;
        for (u_int i : solution) {
            cout << i << " ";
        }
    }





    /*************************************/
    /****      TIME TEST RESULTS      ****/
    /*************************************/

    //cout << "\n\nDijkstra time: " << t1b.count() - t1.count() << " milliseconds" << endl;
    //cout << "A* time: " << t2b.count() - t2.count() << " milliseconds" << endl;
    //cout << "DFS time: " << t3b.count() - t3.count() << " milliseconds" << endl;
    //cout << "BFS time: " << t4b.count() - t4.count() << " milliseconds" << endl;
    //cout << "DijkstraBiDir time: " << t5b.count() - t5.count() << " milliseconds" << endl;
    cout << "\n\nTSP Nearest Neighbor time: " << t6b.count() - t6.count() << " milliseconds" << endl;
    cout << "2-Opt time: " << t7b.count() - t7.count() << " milliseconds" << endl;
/*
    cout << "\nGraph Data:" << endl;
    cout << "Number of nodes: " << g1.getNumNodes() << endl;
    cout << "Number of edges: " << g1.getNumEdges() << endl << endl;
*/
    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
