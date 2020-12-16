#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <string>
#include <cmath>

using namespace std;

void replace(char what, char with, string &str)
{
    size_t found = 0;
    while ((found = str.find(what,found)) != string::npos) {
        str[found] = with;
    }
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input2";
    ifstream in;


    map<int,deque<int>> numbers;
    vector <int> startingNumbers;

    string line;
    in.open(input);
    if (in.is_open()) {
        in >> line;
        replace(',',' ',line);
        cout << line << endl;
        stringstream ss;
        ss << line;
        int num;
        while (ss >> num) {

            startingNumbers.push_back(num);
        }
        int turn = 1;
        int lastSpoken;
        deque<int> turns;
        for (auto it = startingNumbers.begin(); it != startingNumbers.end(); ++it, ++turn) {
            turns.clear();
            lastSpoken=*it;
            turns.push_back(turn);
            numbers[lastSpoken] = turns;
        }

        int toSpeak;
        while (turn < 2021) {

            if (numbers[lastSpoken].size() == 1) { // spoken once
                toSpeak=0;
            } else {
                toSpeak = numbers[lastSpoken][1] - numbers[lastSpoken][0];
            }
            if (numbers.find(toSpeak) != numbers.end()) { //Already present
                numbers[toSpeak].push_back(turn);
                if (numbers[toSpeak].size() >= 3) {
                    numbers[toSpeak].pop_front();
                }
            } else { // new number
                turns.clear();
                turns.push_front(turn);
                numbers[toSpeak] = turns;
            }
            lastSpoken = toSpeak;
            turn++;
        }
        res = toSpeak;
    }
    return res;
}



long long task2()
{
       unsigned long long res = 0;
    string input = "input";
    ifstream in;


    map<int,int> numbers;
    vector <int> startingNumbers;

    string line;
    in.open(input);
    if (in.is_open()) {
        in >> line;
        replace(',',' ',line);
        cout << line << endl;
        stringstream ss;
        ss << line;
        int num;
        while (ss >> num) {

            startingNumbers.push_back(num);
        }
        int turn = 1;
        int lastSpoken;
        for (auto it = startingNumbers.begin(); it != startingNumbers.end(); ++it, ++turn) {
            lastSpoken=*it;
            numbers[lastSpoken] = turn;
        }

        int toSpeak;
        while (turn < 30000001) {
            if (numbers.find(lastSpoken) != numbers.end()) { // spoken before
                toSpeak = (turn - 1) - numbers[lastSpoken];
            } else { // last was first
                toSpeak = 0;
            }
            numbers[lastSpoken] = (turn - 1);

            lastSpoken = toSpeak;
            turn++;
            if ((turn % 1000000) == 0) cout << turn  << " " << numbers.size() << endl;
        }
        res = toSpeak;
    }
    return res;
}



int main()
{
    long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    long long res2 = task2();
    cout << "Task 2 = " << res2 <<endl;

}
