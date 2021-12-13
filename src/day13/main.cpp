#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

pair<vector<pair<int, int>>, vector<pair<string, int>>> parse(ifstream input) {
    vector<pair<int, int>> points;
    vector<pair<string, int>> folds;
    string line;
    while(getline(input, line)) {
        if(!line.size()) continue;
        if(line[0] != 'f') points.push_back(pair<int, int>(stoi(line.substr(0, line.find(","))), stoi(line.substr(line.find(",") + 1))));
        else if(line[0] == 'f') folds.push_back(pair<string, int>(line.substr(line.find("=") - 1, 1), stoi(line.substr(line.find("=") + 1))));
    }

    return pair<vector<pair<int, int>>, vector<pair<string, int>>>(points, folds);
}

void p1_2(pair<vector<pair<int, int>>, vector<pair<string, int>>>& data, bool once) {
    vector<pair<int, int>> points = data.first;
    vector<pair<string, int>> folds = data.second;

    map<string, bool> space;
    for(auto p : points) space[to_string(p.first) + "," + to_string(p.second)] = 1;

    int maxX = 0, maxY = 0;
    for(auto f : folds) {
        for(auto itr = space.begin(); itr != space.end(); ++itr) {
            int x = stoi((itr->first).substr(0, (itr->first).find(",")));
            int y = stoi((itr->first).substr((itr->first).find(",") + 1));
            if(f.first == "x") {
                maxX = f.second;
                if(x > f.second) {
                    itr->second = 0;
                    string pointString = to_string(2*f.second - x) + "," + to_string(y);
                    space[pointString] = 1;
                }
            } else {
                maxY = f.second;
                if(y > f.second) {
                    itr->second = 0;
                    string pointString = to_string(x) + "," + to_string(2*f.second - y);
                    space[pointString] = 1;
                }
            }
        }

        if(once) {
            int cnt = 0;
            for(auto itr = space.begin(); itr != space.end(); ++itr) if(itr->second) cnt++;

            cout << "P1: " << cnt << "\n";
            return;
        }
    }

    cout << "P2:\n";
    for(int i = 0; i < maxY; ++i) {
        for(int j = 0; j < maxX; ++j) {
            string pointString = to_string(j) + "," + to_string(i);
            if(space[pointString]) cout << "#";
            else cout << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char **argv) {
    pair<vector<pair<int, int>>, vector<pair<string, int>>> data = parse(ifstream(argv[1]));
    p1_2(data, true);
    p1_2(data, false);

    return 0;
}