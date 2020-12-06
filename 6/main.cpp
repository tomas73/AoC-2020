#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;



void task1(void)
{
    ifstream in;

    set<char> s;
    vector<set<char>> v;

    in.open("input");
    if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            if (line.size() == 0)
                {
                    v.push_back(s);
                    s.clear();
                }
            for (auto it=line.begin(); it!=line.end(); ++it) {
                s.insert(*it);
            }
        }
        v.push_back(s);
    }
    int sum = 0;
    for (auto it=v.begin(); it!=v.end(); ++it) {
        sum += (*it).size();
    }
    cout << "Sum: " << sum << endl;
}

void task2(void)
{
    ;
}

int main()
{
    task1();
    task2();
}

