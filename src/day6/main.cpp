#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<long long int> parse(ifstream input) {
    vector<long long int> data(9, 0); // freq
    string line;
    getline(input, line);
    int last = 0, next = 0;
    while ((next = line.find(",", last)) != string::npos) {
        data[stoi(line.substr(last, next-last))]++;
        last = next + 1;
    }
    data[stoi(line.substr(last))]++;

    return data;
}

long long int shiftLeft(vector<long long int>& data) {
    long long int zeroCount = data[0];
    for(int i = 0; i < data.size() - 1; ++i) {
        data[i] = data[i + 1];
    }

    return zeroCount;
}

long long int totalFishes(vector<long long int>& data) {
    long long int cnt = 0;
    for(auto d : data) cnt += d;

    return cnt;
}

long long int p1_2(vector<long long int> data, int dayTill) {
    long long int zc;
    for(int day = 0; day < dayTill; ++day) {
        zc = shiftLeft(data);
        data[6] += zc;
        data[8] = zc;
    }

    return totalFishes(data);
}

int main(int argc, char **argv) {
    vector<long long int> data = parse(ifstream(argv[1]));
    cout << "P1: " << p1_2(data, 80) << "\n";
    cout << "P2: " << p1_2(data, 256) << "\n";

    return 0;
}