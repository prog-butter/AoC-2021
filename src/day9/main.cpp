#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

vector<vector<int>> parse(ifstream input) {
    vector<vector<int>> data;
    string line;
    while(getline(input, line)) {
        vector<int> row;
        regex rgx("([0-9])");
        auto curr = sregex_iterator(line.begin(), line.end(), rgx);
        auto last = sregex_iterator();
        smatch match;
        while(curr != last) {
            match = *curr;
            row.push_back(stoi(match.str()));
            curr++;
        }
        data.push_back(row);
    }

    return data;
}

vector<pair<int, int>> p1(vector<vector<int>>& data, bool print) {
    vector<pair<int, int>> lowpoints;
    int sum = 0;
    for(int i = 0; i < data.size(); ++i) {
        for(int j = 0; j < data[i].size(); ++j) {
            bool up = i - 1 < 0 ? true : data[i - 1][j] > data[i][j];
            bool down = i + 1 >= data.size() ? true : data[i + 1][j] > data[i][j];
            bool left = j - 1 < 0 ? true : data[i][j - 1] > data[i][j];
            bool right = j + 1 >= data[i].size() ? true : data[i][j + 1] > data[i][j];

            if(up && down && left && right) {
                sum += data[i][j] + 1;
                lowpoints.push_back(pair<int, int>(i, j));
            }
        }
    }

    if(print) cout << "P1: " << sum << "\n";
    return lowpoints;
}

int getBasinSize(vector<vector<int>>& data, int i, int j, vector<vector<bool>>& visited) {
    if(visited[i][j]) return 0;

    visited[i][j] = true;
    int size = 1;
    if(i - 1 >= 0 && data[i - 1][j] != 9 && data[i - 1][j] > data[i][j]) size += getBasinSize(data, i - 1, j, visited);
    if(j - 1 >= 0 && data[i][j - 1] != 9 && data[i][j - 1] > data[i][j]) size += getBasinSize(data, i, j - 1, visited);
    if(i + 1 < data.size() && data[i + 1][j] != 9 && data[i + 1][j] > data[i][j]) size += getBasinSize(data, i + 1, j, visited);
    if(j + 1 < data[i].size() && data[i][j + 1] != 9 && data[i][j + 1] > data[i][j]) size += getBasinSize(data, i, j + 1, visited);

    return size;
}

void p2(vector<vector<int>>& data) {
    vector<pair<int, int>> lowpts = p1(data, false);
    vector<int> basinSizes;

    for(auto p : lowpts) {
        vector<vector<bool>> v(data.size(), vector<bool>(data[p.first].size()));
        basinSizes.push_back(getBasinSize(data, p.first, p.second, v));
    }

    sort(basinSizes.rbegin(), basinSizes.rend());

    cout << "P2: " << basinSizes[0] * basinSizes[1] * basinSizes[2] << "\n";
}

int main(int argc, char **argv) {
    vector<vector<int>> data = parse(ifstream(argv[1]));
    p1(data, true);
    p2(data);

    return 0;
}