#include <iostream>
#include "../Utilities/exceptions.h"
#include "Graph.h"
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/AStar.h"
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
                        g.addEdge((i * j), ((i + di) * (j + dj)), dis(gen));
                    }
                }
            }
        }
    }
}

int main() {

    std::cout << "Starting tests ..." << std::endl;



    Graph g1 = Graph();



    generateRandomGridGraph(100, g1);

    /*
    u_int id0 = g1.addNode(0,0,"Rio Tinto");
    u_int id1 = g1.addNode(10, 10, "Maia");
    u_int id2 = g1.addNode(2,2,"Areosa");
    u_int id3 = g1.addNode(-10, -10, "Sra da Hora");
    u_int id4 = g1.addNode(-15, -15, "Matosinhos");
    u_int id5 = g1.addNode(-10, -5, "S. Mamede");
    u_int id6 = g1.addNode(-1000, 1000, "Castro d'Aire");

    g1.addEdge(id0,id2,2);
    g1.addEdge(id0,id1,2);
    g1.addEdge(id1, id3, 4);
    g1.addEdge(id3, id1, 3);
    g1.addEdge(id3, id4, 2);
    g1.addEdge(id5,id4,1);
    g1.addEdge(id4,id5,1);
    */


    Dijkstra d = Dijkstra(g1);



    /*
    // Impossible Case #1
    d.calcOptimalPath(g1.getNodeById(id5), g1.getNodeById(id3));
    d.printSolution();

    // Regular Scenario
    d.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id5));
    d.printSolution();

    // Impossible Case #2 (Isolated Node)
    d.calcOptimalPath(g1.getNodeById(id6), g1.getNodeById(id0));
    d.printSolution();

    // Self-Node path
    d.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id0));
    d.printSolution();

    */

    milliseconds t0 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    d.calcOptimalPath(g1.getNodeById(3), g1.getNodeById(73));
    d.printSolution();

    milliseconds t0b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );


    d.calcOptimalPath(g1.getNodeById(34), g1.getNodeById(65));
    d.printSolution();


    milliseconds t1 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    AStar a = AStar(g1);


    // Impossible Case #1
    /*a.calcOptimalPath(g1.getNodeById(id5), g1.getNodeById(id3));
    a.printSolution();

    // Regular Scenario
    a.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id5));
    a.printSolution();

    // Impossible Case #2 (Isolated Node)
    a.calcOptimalPath(g1.getNodeById(id6), g1.getNodeById(id0));
    a.printSolution();

    // Self-Node path
    a.calcOptimalPath(g1.getNodeById(id0), g1.getNodeById(id0));
    a.printSolution();

    */


    milliseconds t2 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.calcOptimalPath(g1.getNodeById(3), g1.getNodeById(73));
    a.printSolution();


    milliseconds t2b = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    a.calcOptimalPath(g1.getNodeById(34), g1.getNodeById(65));
    a.printSolution();

    milliseconds t3 = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );

    cout << "Dijkstra time #1: " << t0b.count() - t0.count() << " milliseconds" << endl;
    cout << "A* time #1: " << t2b.count() - t2.count() << " milliseconds" << endl;

    cout << "Dijkstra time #2: " << t1.count() - t0b.count() << " milliseconds" << endl;
    cout << "A* time #2: " << t3.count() - t2b.count() << " milliseconds" << endl;

    std::cout << "\nProgram ran successfully." << std::endl;

    return 0;
}
