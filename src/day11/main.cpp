#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> parse(ifstream input) {
    vector<vector<int>> data;
    string line;
    while(getline(input, line)) {
        vector<int> d;
        for(auto l : line) d.push_back(l - '0');
        data.push_back(d); 
    }

    return data;
}

vector<pair<int, int>> getNeighbours(vector<vector<int>>& data, int i, int j) {
    vector<pair<int, int>> neighbours;
    if(i - 1 >= 0) neighbours.push_back(pair<int, int>(i - 1, j));
    if(i - 1 >= 0 && j + 1 < data[i - 1].size()) neighbours.push_back(pair<int, int>(i - 1, j + 1));
    if(j + 1 < data[i].size()) neighbours.push_back(pair<int, int>(i, j + 1));
    if(i + 1 < data.size() && j + 1 < data[i + 1].size()) neighbours.push_back(pair<int, int>(i + 1, j + 1));
    if(i + 1 < data.size()) neighbours.push_back(pair<int, int>(i + 1, j));
    if(i + 1 < data.size() && j - 1 >= 0) neighbours.push_back(pair<int, int>(i + 1, j - 1));
    if(j - 1 >= 0) neighbours.push_back(pair<int, int>(i, j - 1));
    if(i - 1 >= 0 && j - 1 >= 0) neighbours.push_back(pair<int, int>(i - 1, j - 1));

    return neighbours;
}

int countFlashes(vector<vector<int>>& data, vector<vector<bool>>& flashed, int i, int j) {
    int cnt = 1;
    if(data[i][j] <= 9) return 0;

    flashed[i][j] = true;
    data[i][j] = 0;
    vector<pair<int, int>> neighbours = getNeighbours(data, i, j);
    for(auto n : neighbours) if(!flashed[n.first][n.second]) data[n.first][n.second]++;
    for(auto n : neighbours) if(!flashed[n.first][n.second]) cnt += countFlashes(data, flashed, n.first, n.second);

    return cnt;
}

void p1(vector<vector<int>> data) {
    int cnt = 0;
    for(int step = 0; step < 100; ++step) {
        vector<vector<bool>> flashed = vector<vector<bool>>(data.size(), vector<bool>(data[0].size(), false));
        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data[i].size(); ++j) data[i][j]++;
        }
        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data[i].size(); ++j) cnt += countFlashes(data, flashed, i, j);
        }
    }

    cout << "P1: " << cnt << "\n";
}

void p2(vector<vector<int>>& data) {
    for(int step = 0;; ++step) {
        bool flag = 1;
        vector<vector<bool>> flashed = vector<vector<bool>>(data.size(), vector<bool>(data[0].size(), false));
        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data[i].size(); ++j) data[i][j]++;
        }
        for(int i = 0; i < data.size(); ++i) {
            for(int j = 0; j < data[i].size(); ++j) countFlashes(data, flashed, i, j);
        }
        for(auto dd : data) {
            for(auto d : dd) if(d) flag = 0;
        }

        if(flag) {
            cout << "P2: " << step + 1 << "\n";
            break;
        }
    }

}

int main(int argc, char **argv) {
    vector<vector<int>> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);
    
    return 0;
}