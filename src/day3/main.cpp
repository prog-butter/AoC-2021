#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<string> parse(ifstream input) {
    vector<string> v;
    string line;
    while(getline(input, line)) {
        v.push_back(line);
    }

    return v;
}

int binToDec(string bin) {
    int dec = 0;
    for(int i = bin.size() - 1; i >= 0; --i) {
        if(bin[i] == '1') dec += pow(2, bin.size() - 1 - i);
    }

    return dec;
}

void p1(vector<string>& input) {
    int cnt = 0, g = 0;
    for(int d = 0; d < input[0].size(); ++d) {
        cnt = 0;
        for(auto i : input) {
            if(i[input[0].size() - d - 1] == '1') cnt++;
            else cnt--;
        }
        if(cnt > 0) g += pow(2, d);
    }

    int mask = (1 << input[0].size()) - 1;
    cout << "P1: " << g*(~g & mask) << "\n";
}

void p2(vector<string>& input) {
    vector<bool> valid(input.size(), true);
    int cnt, left, index;
    for(int d = 0; d < input[0].size(); ++d) {
        cnt = left = 0;
        for(int i = 0; i < input.size(); ++i) {
            if(valid[i]) {
                left++;
                if(input[i][d] == '1') cnt++;
                else cnt--;
            }
        }
        if(left <= 1) break;
        if(cnt >= 0) {
            for(int i = 0; i < input.size(); ++i) if(input[i][d] == '0' && valid[i]) valid[i] = false;
        } else {
            for(int i = 0; i < input.size(); ++i) if(input[i][d] == '1' && valid[i]) valid[i] = false;
        }
    }
    for(index = 0; valid[index] != true; index++);
    int o = binToDec(input[index]);

    for(auto v : valid) v = true;
    for(int d = 0; d < input[0].size(); ++d) {
        cnt = left = 0;
        for(int i = 0; i < input.size(); ++i) {
            if(valid[i]) {
                left++;
                if(input[i][d] == '1') cnt++;
                else cnt--;
            }
        }
        if(left <= 1) break;
        if(cnt >= 0) {
            for(int i = 0; i < input.size(); ++i) if(input[i][d] == '1' && valid[i]) valid[i] = false;
        } else {
            for(int i = 0; i < input.size(); ++i) if(input[i][d] == '0' && valid[i]) valid[i] = false;
        }
    }
    for(index = 0; valid[index] != true; index++);
    int c = binToDec(input[index]);

    cout << "P2: " << o*c << "\n";
}

int main(int argc, char **argv) {
    vector<string> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);

    return 0;
}