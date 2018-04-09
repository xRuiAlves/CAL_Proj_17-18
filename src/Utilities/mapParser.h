
#ifndef CAL_MAPPARSER_H
#define CAL_MAPPARSER_H

#include "../Graph/Graph.h"
#include <iostream>
#include <fstream>
#include <map>

// Parses a 3-File model from Open-Street-Maps to a Graph
Graph parseMap(std::string filePathA, std::string filePathB, std::string filePathC);

#endif //CAL_MAPPARSER_H
