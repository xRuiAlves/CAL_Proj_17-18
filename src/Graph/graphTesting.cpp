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
#include "../Algorithms/AStarBiDir.h"
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

void generateTestGraph(Graph & g) {
    u_int id0 = g.addNode(2, 6, "Place 0");
    u_int id1 = g.addNode(0, 7, "Place 1");
    u_int id2 = g.addNode(0, 5, "Place 2");
    u_int id3 = g.addNode(1, 0, "Place 3");
    u_int id4 = g.addNode(3, 7, "Place 4");
    u_int id5 = g.addNode(3, 6, "Place 5");
    u_int id6 = g.addNode(3, 5, "Place 6");
    u_int id7 = g.addNode(6, 6, "Place 7");
    u_int id8 = g.addNode(5, 5, "Place 8");
    u_int id9 = g.addNode(5, 4, "Place 9");
    u_int id10 = g.addNode(6, 1, "Place 10");
    u_int id11 = g.addNode(7, 2, "Place 11");

    g.addEdge(id0,id1,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id1)), "Road 0");
    g.addEdge(id0,id2,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id2)), "Road 1");
    g.addEdge(id0,id4,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id4)), "Road 2");
    g.addEdge(id0,id5,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id5)), "Road 3");
    g.addEdge(id0,id6,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id5)), "Road 4");
    g.addEdge(id1,id2,g.getNodeById(id1).getDistanceToOtherNode(g.getNodeById(id2)), "Road 5");
    g.addEdge(id1,id6,g.getNodeById(id1).getDistanceToOtherNode(g.getNodeById(id6)), "Road 6");
    g.addEdge(id2,id3,g.getNodeById(id2).getDistanceToOtherNode(g.getNodeById(id3)), "Road 7");
    g.addEdge(id2,id6,g.getNodeById(id2).getDistanceToOtherNode(g.getNodeById(id6)), "Road 8");
    g.addEdge(id3,id2,g.getNodeById(id3).getDistanceToOtherNode(g.getNodeById(id2)), "Road 9");
    g.addEdge(id3,id9,g.getNodeById(id3).getDistanceToOtherNode(g.getNodeById(id9)), "Road 10");
    g.addEdge(id4,id5,g.getNodeById(id4).getDistanceToOtherNode(g.getNodeById(id5)), "Road 11");
    g.addEdge(id5,id6,g.getNodeById(id5).getDistanceToOtherNode(g.getNodeById(id6)), "Road 12");
    g.addEdge(id5,id7,g.getNodeById(id5).getDistanceToOtherNode(g.getNodeById(id7)), "Road 13");
    g.addEdge(id6,id0,g.getNodeById(id6).getDistanceToOtherNode(g.getNodeById(id0)), "Road 14");
    g.addEdge(id6,id8,g.getNodeById(id0).getDistanceToOtherNode(g.getNodeById(id1)), "Road 15");
    g.addEdge(id7,id11,g.getNodeById(id7).getDistanceToOtherNode(g.getNodeById(id11)), "Road 16");
    g.addEdge(id8,id9,g.getNodeById(id8).getDistanceToOtherNode(g.getNodeById(id9)), "Road 17");
    g.addEdge(id9,id3,g.getNodeById(id9).getDistanceToOtherNode(g.getNodeById(id3)), "Road 18");
    g.addEdge(id9,id6,g.getNodeById(id9).getDistanceToOtherNode(g.getNodeById(id6)), "Road 19");
    g.addEdge(id10,id11,g.getNodeById(id10).getDistanceToOtherNode(g.getNodeById(id11)), "Road 20");
    g.addEdge(id11,id10,g.getNodeById(id11).getDistanceToOtherNode(g.getNodeById(id10)), "Road 21");
}

int not_main() {

    std::cout << "Starting tests ..." << std::endl;


    /*************************************/
    /****          GRAPH INFO         ****/
    /*************************************/

    Graph g1 = Graph();

    //generateRandomGridGraph(100, g1);



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

    u_int startNodeID = 1;
    u_int finishNodeID = 5;



    /*************************************/
    /****           DIJKSTRA          ****/
    /*************************************/

    Dijkstra d = Dijkstra(g1);

    cout << "\n\n---------DIJKSTRA---------\n";
    milliseconds t1 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    d.calcOptimalPath(startNodeID, finishNodeID);

    milliseconds t1b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << d.getSolutionWeight() << endl;

    /*************************************/
    /****              A*             ****/
    /*************************************/

    AStar a = AStar(g1);

    cout << "\n\n---------A*---------\n";
    milliseconds t2 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.calcOptimalPath(startNodeID, finishNodeID);

    milliseconds t2b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );


    cout << a.getSolutionWeight() << endl;

    /*************************************/
    /****              DFS            ****/
    /*************************************/

    DFS dfs = DFS(g1);

    cout << "\n\n---------DFS---------\n";
    milliseconds t3 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    NodeHashTable dfsResult = dfs.performSearch(startNodeID);
    //dfs.printSolution();

    milliseconds t3b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );



    /*************************************/
    /****              BFS            ****/
    /*************************************/

    BFS bfs = BFS(g1);

    cout << "\n\n---------BFS---------\n";
    milliseconds t4 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    NodeHashTable bfsResult = bfs.performSearch(startNodeID);
    //bfs.printSolution();

    milliseconds t4b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    /*************************************/
    /****  ASTAR BI DIRECTIONAL    ****/
    /*************************************/

    cout << "\n\n---------AStar Bidirectional---------\n";

    AStarBiDir dbd = AStarBiDir(g1);


    milliseconds t5 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    dbd.calcOptimalPath(startNodeID, finishNodeID);

    milliseconds t5b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << dbd.getSolutionWeight() << endl;


    /*************************************/
    /****     TSP Nearest Neighbor    ****/
    /*************************************/
/*
    cout << "\n\n---------TSP Nearest Neighbor---------\n";

    TSPNearestNeighbor t = TSPNearestNeighbor(g1);
    vector<u_int> tsp_pois = {6,4,20,25};

    milliseconds t6 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    vector<u_int> v = t.calcPath(startNodeID, finishNodeID, tsp_pois);

    milliseconds t6b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    vector<u_int> visitOrder = t.getVisitOrder();

    /*************************************/
    /***  2-opt Iterative Improvement  ***/
    /*************************************/
/*
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

    cout << "\n\nDijkstra time: " << t1b.count() - t1.count() << " milliseconds" << endl;
    cout << "A* time: " << t2b.count() - t2.count() << " milliseconds" << endl;
    cout << "DFS time: " << t3b.count() - t3.count() << " milliseconds" << endl;
    cout << "BFS time: " << t4b.count() - t4.count() << " milliseconds" << endl;
    cout << "AStarBiDir time: " << t5b.count() - t5.count() << " milliseconds" << endl;
  /*  cout << "\n\nTSP Nearest Neighbor time: " << t6b.count() - t6.count() << " milliseconds" << endl;
    cout << "2-Opt time: " << t7b.count() - t7.count() << " milliseconds" << endl;*/

    cout << "\nGraph Data:" << endl;
    cout << "Number of nodes: " << g1.getNumNodes() << endl;
    cout << "Number of edges: " << g1.getNumEdges() << endl << endl;

    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
