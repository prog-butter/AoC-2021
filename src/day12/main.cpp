#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, vector<string>> parse(ifstream input) {
    map<string, vector<string>> data;
    string line, left, right;
    while(getline(input, line)) {
        left = line.substr(0, line.find('-'));
        right = line.substr(line.find('-') + 1);
        data[left].push_back(right);
        data[right].push_back(left);
    }

    return data;
}

bool isSmallCave(string node) {
    if(node[0] >= 'a' && node[0] <= 'z') return true;
    else return false;
}

map<string, bool> findSmallCaveNodes(map<string, vector<string>>& data) {
    map<string, bool> m;
    for(auto itr = data.begin(); itr != data.end(); ++itr) {
        if(isSmallCave(itr->first) && itr->first != "start" && itr->first != "end") m[itr->first] = true;
        for(auto i : itr->second) {
            if(isSmallCave(i) && i != "start" && i != "end") m[i] = true;
        }
    }

    return m;
}

void dfs(map<string, vector<string>>& data, string currNode, map<string, int>& visited, vector<string>& path, map<string, bool>& paths, string doubleSmallCaveNode) {
    if(currNode == "end") {
        path.push_back("end");
        string cPath = "";
        for(auto p : path) cPath += (p + ",");
        paths[cPath] = true;
        return;
    }

    path.push_back(currNode);
    if(isSmallCave(currNode)) visited[currNode]++;
    for(auto neighbour : data[currNode]) {
        if(!visited[neighbour] || (neighbour == doubleSmallCaveNode && visited[neighbour] < 2)) {
            map<string, int> newVisited(visited);
            vector<string> newPath(path);
            dfs(data, neighbour, newVisited, newPath, paths, doubleSmallCaveNode);
        }
    }
}

void p1(map<string, vector<string>>& data) {
    map<string, bool> paths;
    for(auto neighbour : data["start"]) {
        map<string, int> visited;
        vector<string> path;
        dfs(data, "start", visited, path, paths, "");
    }

    cout << "P1: " << paths.size() << "\n";
}

void p2(map<string, vector<string>>& data) {
    map<string, bool> paths;
    map<string, bool> smallCaveNodes = findSmallCaveNodes(data);
    for(auto neighbour : data["start"]) {
        for(auto itr = smallCaveNodes.begin(); itr != smallCaveNodes.end(); ++itr) {
            map<string, int> visited;
            vector<string> path;
            dfs(data, "start", visited, path, paths, itr->first);
        }
    }

    cout << "P2: " << paths.size() << "\n";
}

int main(int argc, char **argv) {
    map<string, vector<string>> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);

    return 0;
}