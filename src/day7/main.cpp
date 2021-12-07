#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

vector<int> parse(ifstream input) {
    vector<int> data;
    string line;
    getline(input, line);
    regex rgx("([0-9]+)");
    auto curr = sregex_iterator(line.begin(), line.end(), rgx);
    auto last = sregex_iterator();
    smatch match;
    while(curr != last) {
        match = *curr;
        data.push_back(stoi(match.str()));
        curr++;
    }

    return data;
}

int calculateFuel(vector<int>& data, int pos) {
    int fuel = 0;
    for(auto d : data) fuel += abs(d - pos);

    return fuel;
}

void p1(vector<int>& data) {
    sort(data.begin(), data.end());
    int med;
    if(data.size() % 2) {
        med = data[data.size() / 2];
    } else {
        med = (data[data.size() / 2] + data[data.size() / 2 - 1]) / 2;
    }

    cout << "P1: " << calculateFuel(data, med) << "\n";
}

int calculateFuelCompound(vector<int>& data, int pos) {
    int fuel = 0, t;
    for(auto d : data) {
        t = abs(d - pos);
        fuel += (t*(t+1)/2);
    } 

    return fuel;
}

void p2(vector<int>& data) {
    int min = 1000000000, max = 0, t;
    for(auto d : data) if(d > max) max = d;

    cout << max << "\n";
    for(int i = 0; i <= max; ++i) {
        t = calculateFuelCompound(data, i);
        if(t < min) {
            cout << "i: " << i << ", min: " << min << "\n";
           min = t;
        }
    }

    cout << "P2: " << min << "\n";
}

int main(int argc, char **argv) {
    vector<int> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);
    
    return 0;
}