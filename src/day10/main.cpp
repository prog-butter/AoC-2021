#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

vector<string> parse(ifstream input) {
    vector<string> data;
    string line;
    while(getline(input, line)) {
        data.push_back(line);
    }

    return data;
}

int getCorruptScore(char c) {
    if(c == ')') return 3;
    else if(c == ']') return 57;
    else if(c == '}') return 1197;
    else return 25137;
}

void p1(vector<string>& data) {
    int score = 0;
    for(auto d : data) {
        stack<char> s;
        for(auto c : d) {
            if(c == '{' || c == '(' || c == '[' || c == '<') s.push(c);
            else if((s.top() == '{' && c == '}') || (s.top() == '(' && c == ')') || (s.top() == '[' && c == ']') || (s.top() == '<' && c == '>')) s.pop();
            else {
                score += getCorruptScore(c);
                break;
            }
        }
    }

    cout << "P1: " << score << "\n";
}

int getIncompleteScore(char c) {
    if(c == '(') return 1;
    else if(c == '[') return 2;
    else if(c == '{') return 3;
    else return 4;
}

void p2(vector<string>& data) {
    vector<long long int> scores;
    for(auto d : data) {
        stack<char> s;
        long long int score = 0;
        for(auto c : d) {
            if(c == '{' || c == '(' || c == '[' || c == '<') s.push(c);
            else if((s.top() == '{' && c == '}') || (s.top() == '(' && c == ')') || (s.top() == '[' && c == ']') || (s.top() == '<' && c == '>')) s.pop();
            else {
                score = -1;
                break;
            }
        }
        if(score == -1) continue;
        else {
            while(s.size() != 0) {
                score *= 5;
                score += getIncompleteScore(s.top());
                s.pop();
            }
            scores.push_back(score);
        }
    }

    sort(scores.begin(), scores.end());

    cout << "P2: " << scores[scores.size() / 2] << "\n";
}

int main(int argc, char **argv) {
    vector<string> data = parse(ifstream(argv[1]));
    p1(data);
    p2(data);
    
    return 0;
}