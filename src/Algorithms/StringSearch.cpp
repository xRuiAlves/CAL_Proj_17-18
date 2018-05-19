//
// Created by reeckset on 05-05-2018.
//

#include "StringSearch.h"
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

bool StringSearch::hasKmpMatch(const string & text, const string & pattern) {
    unsigned int n = text.size();
    unsigned int m = pattern.size();

    vector<int> pi = getPrefixFunc(pattern);
    int q = 0;

    for(int i = 0; i < n; i++){

        while(q > 0 && pattern[q] != text[i]){
            q = pi[q-1];
        }

        if(pattern[q] == text[i]){
            q++;
        }

        if(q == m){
            return true;
        }
    }

    return false;
}

vector<int> StringSearch::getPrefixFunc(const string & p){
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

vector<int> StringSearch::getStringsByDistance(const vector<string> & text, const string & pattern) {
    multimap<int, int> distances;

    vector<string> keywords = StringSearch::split(pattern, ' ');

    for (int i = 0; i < text.size(); i++) { // for each source string, find its distance value to the pattern (aka keywords)
        int totalDistance = 0;
        for (int k = 0; k < keywords.size(); k++) {
            int currDistance = getBestDistance(text[i], keywords[k]);

            totalDistance += (currDistance == INT32_MAX) ? keywords[k].length() : currDistance;
        }
        if (totalDistance == pattern.length() - (keywords.size() - 1)){ // If totalDistance is equal to the amount of characters of the keywords -> means there is no match
            totalDistance = INT32_MAX;
        }
        distances.insert(pair<int, int>(totalDistance, i));
    }

    vector<int> results;
    int resultSize = 15;
    for (multimap<int, int>::iterator it = distances.begin(); it != distances.end() && resultSize > 0; it++) {
        if(it->first == INT32_MAX){
            break;
        }
        results.push_back(it->second);
        resultSize--;
    }

    return results;
}

int StringSearch::getBestDistance(string text, string pattern){
    int minDistance = INT32_MAX;

    if(pattern.length() > text.length()) {
        string tmp = text;
        text = pattern;
        pattern = tmp;
    }

    for(int i = 0; i < text.length()-pattern.length();i++){
        string newText = text.substr(i, pattern.length());
        int currDistance = stringDistance(newText, pattern);
        if(currDistance < minDistance){
            minDistance = currDistance;
        }
    }

    if(minDistance > 0.3*pattern.length()){
        minDistance = INT32_MAX;
    }
    return minDistance;
}

int StringSearch::stringDistance(const string & text, const string & pattern) {
    vector<int> distance;

    // Initialization
    for (int j=0 ; j<text.size() ; j++) {
        distance.push_back(j);
    }

    // Computing distance
    int newVal, oldVal;
    for (int i=1 ; i<pattern.size() ; i++) {
        oldVal = distance[0];
        distance[0] = i;

        for (int j=1 ; j<text.size() ; j++) {
            if (pattern[i] == text[j]) {
                newVal = oldVal;
            } else {
                newVal = 1 + min(distance[j-1], min(oldVal, distance[j]));
            }

            oldVal = distance[j];
            distance[j] = newVal;
        }
    }

    // The last distance vector element contains the distance value between 'text' and 'pattern'
    return distance[text.size()-1];
}

vector<string> StringSearch::split(string source, char character){
    vector<string> result;
    string nextString = "";

    for(int i = 0; i < source.length(); i++){
        if(source[i] == character){
            result.push_back(nextString);
            nextString = "";
            continue;
        }
        nextString += source[i];
    }
    result.push_back(nextString);
    return result;
}
