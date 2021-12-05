#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

pair<vector<int>, vector<vector<vector<int>>>> parse(ifstream input) {
    vector<int> numOrder;
    vector<vector<vector<int>>> grids;
    string line;
    
    getline(input, line);
    int last = 0, next = 0;
    while ((next = line.find(",", last)) != string::npos) {
        numOrder.push_back(stoi(line.substr(last, next-last)));
        last = next + 1;
    }
    numOrder.push_back(stoi(line.substr(last)));

    int cnt = 0;
    vector<vector<int>> grid;
    vector<int> row;
    while(getline(input, line)) {
        if(cnt % 5 == 0) {
            getline(input, line);
        }
        int f;
        for(int j = 0; j < line.size();) {
            if(line[j] == ' ') j++;
            else {
                for(f = j; line[f] != ' ' && f < line.size(); ++f);
                row.push_back(stoi(line.substr(j, f - j + 1)));
                j = f;
            }
        }

        grid.push_back(row);
        row.clear();
        if(++cnt % 5 == 0) {
            grids.push_back(grid);
            grid.clear();
        }
    }

    return pair<vector<int>, vector<vector<vector<int>>>>(numOrder, grids);
}

int sumUp(vector<vector<int>>& grid) {
    int sum = 0;
    for(auto a : grid) {
        for(auto b : a) {
            if(b != -1) sum += b;
        }
    }

    return sum;
}

bool checkGrid(vector<vector<int>>& grid, int j, int k) {
    int flag = 1;
    for(int b = 0; b < grid.size(); ++b) {
        if(grid[b][k] != -1) flag = 0;
    }
    if(flag) return true;
    flag = 1;
    for(int b = 0; b < grid[j].size(); ++b) {
        if(grid[j][b] != -1) flag = 0;
    }
    if(flag) return true;
    else return false;
}

void p1(pair<vector<int>, vector<vector<vector<int>>>> input) {
    vector<int> numOrder = input.first;
    vector<vector<vector<int>>> grids = input.second;

    for(auto num : numOrder) {
        for(int i = 0; i < grids.size(); ++i) {
            for(int j = 0; j < grids[i].size(); ++j) {
                for(int k = 0; k < grids[i][j].size(); ++k) {
                    if(grids[i][j][k] == num) {
                        grids[i][j][k] = -1;
                        if(checkGrid(grids[i], j, k)) {
                            cout << "P1: " << num*sumUp(grids[i]) << "\n";
                            return;
                        }
                    }
                }
            }
        }
    }
}

void p2(pair<vector<int>, vector<vector<vector<int>>>>& input) {
    vector<int> numOrder = input.first;
    vector<vector<vector<int>>> grids = input.second;

    vector<bool> gridStatus(grids.size(), false);
    int cnt = grids.size();

    for(auto num : numOrder) {
        for(int i = 0; i < grids.size(); ++i) {
            for(int j = 0; j < grids[i].size(); ++j) {
                for(int k = 0; k < grids[i][j].size(); ++k) {
                    if(grids[i][j][k] == num) {
                        grids[i][j][k] = -1;
                        if(checkGrid(grids[i], j, k) && !gridStatus[i]) {
                            gridStatus[i] = true;
                            cnt--;
                            if(!cnt) {
                                cout << "P2: " << num*sumUp(grids[i]) << "\n";
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

}

int main(int argc, char **argv) {
    pair<vector<int>, vector<vector<vector<int>>>> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);

    return 0;
}