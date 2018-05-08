#include <iostream>
#include <vector>
#include <string>

using namespace std;

int stringDistance(const string & pattern, const string & text) {
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

int main() {
    cout << stringDistance("O meu nome é Rui","O meu nome é LOL");
	return 0;
}