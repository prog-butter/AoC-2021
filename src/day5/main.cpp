#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

vector<vector<int>> parse(ifstream input) {
    vector<vector<int>> data;
    vector<int> d;
    string line;
    regex rgx("([0-9]+),([0-9]+) -> ([0-9]+),([0-9]+)");
    smatch match;
    while(getline(input, line)) {
        regex_search(line, match, rgx);
        for(int i = 1; i < match.size(); ++i) d.push_back(stoi(match[i]));
        data.push_back(d);
        d.clear();
    }

    return data;
}

void p1_2(vector<vector<int>>& data, bool diag) {
    int cnt = 0;
    bool diagCond;
    map<string, int> grid;
    for(auto line : data) {
        if(diag) diagCond = abs(line[3]-line[1]) == abs(line[2]-line[0]);
        if(line[0] == line[2] || line[1] == line[3] || diag) {
            int dx = line[2] == line[0] ? 0 : (line[2] - line[0]) / abs(line[2] - line[0]);
            int dy = line[3] == line[1] ? 0 : (line[3] - line[1]) / abs(line[3] - line[1]);

            for(int x = line[0], y = line[1];; x += dx, y += dy) {
                string point = to_string(x) + "," + to_string(y);
                grid[point]++;
                if(x == line[2] && y == line[3]) break;
            }
        }
    }

    for(auto g : grid) {
        if(g.second >= 2) cnt++;
    }

    if(!diag) cout << "P1: " << cnt << "\n";
    if(diag) cout << "P2: " << cnt << "\n";
}

int main(int argc, char **argv) {
    vector<vector<int>> data = parse(ifstream(argv[1]));
    p1_2(data, false);
    p1_2(data, true);

    return 0;
}