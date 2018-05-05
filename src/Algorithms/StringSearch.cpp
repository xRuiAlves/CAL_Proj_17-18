//
// Created by reeckset on 05-05-2018.
//

#include "StringSearch.h"

using namespace std;

int StringSearch::kmpMatcher(string text, string pattern) {
    unsigned int n = text.size();
    unsigned int m = pattern.size();

    vector<int> pi = getPrefixFunc(pattern);
    int q = 0;
    int matchesCounter = 0;

    for(int i = 0; i < n; i++){

        while(q > 0 && pattern[q] != text[i]){
            q = pi[q-1];
        }

        if(pattern[q] == text[i]){
            q++;;
        }

        if(q == m){
            matchesCounter++;
            //cout << "Found match! " << i - m + 1<< "\n";
            q = pi[q-1];
        }
    }

    return matchesCounter;
}

vector<int> StringSearch::getPrefixFunc(string p){
    unsigned int length = p.size();
    vector<int> prefixVals(length);
    prefixVals[0] = 0;
    int k = 0;

    for(unsigned int i = 1; i < length; i++){
        while(k > 0 && p[k] != p[i]){
            k = prefixVals[k - 1];
        }
        if(p[k] == p[i]){
            k++;
        }
        prefixVals[i] = k;
    }

    return prefixVals;
}

int StringSearch::searchString(std::string text, std::string pattern){
    return StringSearch::kmpMatcher(text, pattern);
}