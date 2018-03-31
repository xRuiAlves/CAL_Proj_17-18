#include <iostream>
#include "../Utilities/exceptions.h"
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/AStar.h"
#include "../Algorithms/DFS.h"
#include "../Algorithms/BFS.h"
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

int main() {

    std::cout << "Starting tests ..." << std::endl;


    /*************************************/
    /****          GRAPH INFO         ****/
    /*************************************/

    Graph g1 = Graph();

    generateRandomGridGraph(200, g1);

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
    u_int finishNodeID = 19000;



    /*************************************/
    /****           DIJKSTRA          ****/
    /*************************************/

    Dijkstra d = Dijkstra(g1);

    cout << "\n\n---------DIJKSTRA---------\n";
    milliseconds t1 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    d.calcOptimalPath(startNodeID, finishNodeID);
    d.printSolution();

    milliseconds t1b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );



    /*************************************/
    /****              A*             ****/
    /*************************************/

    AStar a = AStar(g1);

    cout << "\n\n---------A*---------\n";
    milliseconds t2 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.calcOptimalPath(startNodeID, finishNodeID);
    a.printSolution();

    milliseconds t2b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );



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



    cout << "\n\nDijkstra time: " << t1b.count() - t1.count() << " milliseconds" << endl;
    cout << "A* time: " << t2b.count() - t2.count() << " milliseconds" << endl;
    cout << "DFS time: " << t3b.count() - t3.count() << " milliseconds" << endl;
    cout << "BFS time: " << t4b.count() - t4.count() << " milliseconds" << endl;

    cout << "\nGraph Data:" << endl;
    cout << "Number of nodes: " << g1.getNumNodes() << endl;
    cout << "Number of edges: " << g1.getNumEdges() << endl << endl;

    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
