#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> parse(ifstream input) {
    vector<int> v;
    string line;
    while(getline(input, line)) {
        v.push_back(stoi(line));
    }

    return v;
}

void p1(vector<int>& data) {
    int cnt = 0;
    for(int i = 1; i < data.size(); ++i) {
        if(data[i] > data[i-1]) cnt++;
    }

    cout << "P1: " << cnt << "\n";
}

void p2(vector<int>& data) {
    int cnt = 0;
    for(int i = 3; i < data.size(); ++i) {
        if(data[i] > data[i-3]) cnt++;
    }

    cout << "P2: " << cnt << "\n";
}

int main() {
    vector<int> data = parse(ifstream("src/day1/input.txt"));
    p1(data);
    p2(data);

    return 0;
}