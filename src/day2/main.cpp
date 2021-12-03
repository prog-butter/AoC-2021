#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

vector<pair<string, int>> parse(ifstream input) {
    vector<pair<string, int>> v;
    string line;
    regex rgx("([a-z]+) ([0-9]+)");
    smatch match;
    while(getline(input, line)) {
        regex_search(line, match, rgx);
        v.push_back(pair<string, int>(match[1], stoi(match[2])));
    }

    return v;
}

void p1(vector<pair<string, int>>& input) {
    int x = 0, d = 0;
    for(auto i : input) {
        if(i.first == "forward") x += i.second;
        else if(i.first == "down") d += i.second;
        else d -= i.second;
    }

    cout << "P1: " << x*d << "\n";
}

void p2(vector<pair<string, int>>& input) {
    int x = 0, d = 0, a = 0;
    for(auto i : input) {
        if(i.first == "forward") {
            x += i.second;
            d += a*i.second;
        } else if(i.first == "down") a += i.second;
        else a -= i.second;
    }

    cout << "P2: " << x*d << "\n";
}

int main(int argc, char **argv) {
    vector<pair<string, int>> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);

    return 0;
}