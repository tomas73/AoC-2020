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

bool sortOnSize(set<char> s1, set<char> s2)
{
    return (s1.size() < s2.size());
}

void task2(void)
{
    ifstream in;

    set<char> s;
    vector<set<char>> vs;
    vector<vector<set<char>>> vvs;

    in.open("input");
    if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            s.clear();
            if (line.size() > 0) {
                for (auto it=line.begin(); it!=line.end(); ++it) {
                    s.insert(*it);
                }
                vs.push_back(s);
            } else {
                vvs.push_back(vs);
                vs.clear();
            }
        }
    }
    vvs.push_back(vs);

    int elementsInAll=0;
    for (auto vvsit = vvs.begin(); vvsit != vvs.end(); ++vvsit) {
        vector<set<char>> vs = *vvsit;
        sort(vs.begin(), vs.end(), sortOnSize);
        // vs contain sets of chars with the smallest set first.
        // for a char to exist in all sets, I just need to check
        // the ones present in the smallest set, (a value not present i a set
        // is by definition not included in all sets
        set<char> smallest = *(vs.begin());
        //  For each value, loop through all sets, checking for elememt presense
        for (auto sit = smallest.begin(); sit != smallest.end(); ++sit) {
            char element = *sit;
            bool elementInAll = true;
            for (auto vsit = vs.begin(); vsit != vs.end(); ++vsit) {
                set<char> s = *vsit;
                if (s.find(element) == s.end()) {
                    // At least not present in one set
                    elementInAll=false;
                    break;
                }
            }
            if (elementInAll) elementsInAll++;
        }
    }
    cout << "emementsInAll: " << elementsInAll << endl;
}

int main()
{
    task1();
    task2();
}
