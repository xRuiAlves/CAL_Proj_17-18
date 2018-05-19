//
// Created by reeckset on 05-05-2018.
//

#ifndef CAL_STRINGSEARCH_H
#define CAL_STRINGSEARCH_H

#include <iostream>
#include <vector>

namespace StringSearch {
    bool hasKmpMatch(const std::string & text, const std::string & pattern);
    std::vector<int> getPrefixFunc(const std::string & p);
    int stringDistance(const std::string & text, const std::string & pattern);
    std::vector<int> getStringsByDistance(const std::vector<std::string> & text, const std::string & pattern);
    int getBestDistance(std::string text, std::string pattern);
    std::vector<std::string> split(std::string source, char character);
    };


#endif //CAL_STRINGSEARCH_H
