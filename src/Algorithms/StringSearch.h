//
// Created by reeckset on 05-05-2018.
//

#ifndef CAL_STRINGSEARCH_H
#define CAL_STRINGSEARCH_H

#include <iostream>
#include <vector>

namespace StringSearch {
    int kmpMatcher(std::string text, std::string pattern);
    std::vector<int> getPrefixFunc(std::string p);
    int searchString(std::string text, std::string pattern);
};


#endif //CAL_STRINGSEARCH_H
