
#ifndef CAL_MAPPARSER_H
#define CAL_MAPPARSER_H

#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>
#include <map>

Graph parseMap(std::string filePathA, std::string filePathB, std::string filePathC);
void parseFileA(std::ifstream & fileA, Graph & graph, std::map<int, int> & idMap);
void parseFileB(std::ifstream & fileB, std::map<int, std::pair<std::string, bool> > & edgeMap);
void parseFileC(std::ifstream & fileC, Graph graph, const std::map<int, int> & idMap, const std::map<int, std::pair<std::string, bool>>& edgeMap);

#endif //CAL_MAPPARSER_H
