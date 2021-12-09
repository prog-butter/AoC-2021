#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <map>

using namespace std;

vector<pair<vector<string>, vector<string>>> parse(ifstream input) {
    vector<pair<vector<string>, vector<string>>> data;
    string line, l, r;
    while(getline(input, line)) {
        l = line.substr(0, line.find("|") - 1);
        r = line.substr(line.find("|") + 2);
        vector<string> left, right;

        regex rgx("([a-z]+)");
        auto curr = sregex_iterator(l.begin(), l.end(), rgx);
        auto last = sregex_iterator();
        smatch match;
        while(curr != last) {
            match = *curr;
            left.push_back(match.str());
            curr++;
        }
        curr = sregex_iterator(r.begin(), r.end(), rgx);
        while(curr != last) {
            match = *curr;
            right.push_back(match.str());
            curr++;
        }
        data.push_back(pair<vector<string>, vector<string>>(left, right));
    }

    return data;
}

void p1(vector<pair<vector<string>, vector<string>>>& data) {
    int cnt = 0;
    for(auto d : data) {
        vector<string> right = d.second;
        for(auto r : right) {
            if(r.size() == 2 || r.size() == 3 || r.size() == 4 || r.size() == 7) cnt++;
        }
    }

    cout << "P1: " << cnt << "\n";
}

string stringDiff(string aa, string bb) {
    map<char, int> l;
    for(auto a : aa) l[a]++;
    for(auto b : bb) l[b]--;
    string c = "";
    for(auto itr = l.begin(); itr != l.end(); ++itr) if(itr->second > 0) c += itr->first;

    return c;
}

bool AhasB(string aa, string bb) {
    map<char, int> l;
    for(auto b : bb) l[b]++;
    for(auto a : aa) l[a]--;

    for(auto itr = l.begin(); itr != l.end(); ++itr) if(itr->second > 0) return false;
    return true;
}

void p2(vector<pair<vector<string>, vector<string>>>& data) {
    int sum = 0;
    for(auto d : data) {
        int num = 0;
        vector<string> left = d.first;
        vector<string> right = d.second;

        vector<string> digits(10, "");
        for(auto l : left) {
            if(l.size() == 2) digits[1] = l;
            if(l.size() == 3) digits[7] = l;
            if(l.size() == 4) digits[4] = l;
            if(l.size() == 7) digits[8] = l;
        }

        for(auto r : right) {
            num *= 10;
            if(r.size() == 2) num += 1;
            if(r.size() == 3) num += 7;
            if(r.size() == 4) num += 4;
            if(r.size() == 7) num += 8;
            if(r.size() == 6) { // 0, 6, 9
                if(AhasB(r, digits[4])) num += 9;
                else if(AhasB(r, digits[7])) num += 0;
                else num += 6;
            }
            if(r.size() == 5) { // 2, 3, 5
                if(AhasB(r, digits[1])) num += 3;
                else if(AhasB(r, stringDiff(digits[8], digits[4]))) num += 2;
                else num += 5;
            }
        }
        sum += num;
    }

    cout << "P2: " << sum << "\n";
}

int main(int argc, char **argv) {
    vector<pair<vector<string>, vector<string>>> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);

    return 0;
}