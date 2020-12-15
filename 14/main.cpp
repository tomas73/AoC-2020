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

void printMask(unsigned long long mask) {
    for (int i = 35; i >= 0; i--) {
        if (mask & (1ULL << i)) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << endl;
}

void updateOrMask(unsigned long long &mask, string &str)
{
    unsigned long long m;
    size_t found = 0;
    while ((found = str.find('1', found)) != string::npos) {
        m = (1ULL << (35 - found));
        mask |= m;
        found++;
        if (found > 35) break;
    }
}

void updateAndMask(unsigned long long &mask, string &str)
{
    size_t found = 0;
    while ((found = str.find('0', found)) != string::npos) {
        mask ^= (1ULL << (35 - found));
        found++;
        if (found > 35) break;
    }
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;
    string key, garbage, value;

    unsigned long long andMask = 0xFFFFFFFFFULL;
    unsigned long long orMask  = 0x00000;

    map<unsigned long long,unsigned long long> mem;

    in.open(input);
    if (in.is_open()) {
        while (in >> key >> garbage >> value) {
            if (key.find("mask") != string::npos) {
                // mask
                andMask = 0xFFFFFFFFFULL;
                orMask  = 0x00000;
                updateOrMask(orMask, value);
                updateAndMask(andMask, value);
            } else {
                // mem
                key.erase(0,4);
                key.erase(key.find(']'));
                unsigned long long v = stoull(value);
                v &= andMask;
                v |= orMask;
                mem[stoull(key)] = v;
            }
        }
        for (auto it = mem.begin(); it != mem.end(); ++it) {
            res += (*it).second;
        }
    }
    return res;
}

void updateFloating(vector<unsigned int> &fl, string &str)
{
    size_t found = 0;
    while ((found = str.find('X', found)) != string::npos) {
        fl.push_back((35 - found));
        found++;
        if (found > 35) break;
    }
}


void updateAndMask2(unsigned long long &mask, string &str)
{
    size_t found = 0;
    while ((found = str.find('X', found)) != string::npos) {
        mask ^= (1ULL << (35 - found));
        found++;
        if (found > 35) break;
    }
}

long long task2()
{
    long long res = 0;
    string input = "input";
    ifstream in;
    string key, garbage, value;

    unsigned long long orMask  = 0x00000;
    unsigned long long andMask = 0xFFFFFFFFFULL;

    map<unsigned long long,unsigned long long> mem;
    vector<unsigned int> floating;

    in.open(input);
    if (in.is_open()) {
        while (in >> key >> garbage >> value) {
            if (key.find("mask") != string::npos) {
                // mask
                floating.clear();
                orMask  = 0x00000;
                andMask = 0xFFFFFFFFFULL;
                updateOrMask(orMask, value);
                updateAndMask2(andMask, value);
                updateFloating(floating, value);
            } else {
                // mem
                unsigned long long addr;
                key.erase(0,4);
                key.erase(key.find(']'));
                addr = stoull(key);
                unsigned long long v = stoull(value);
                addr |= orMask;
                addr &= andMask;
                for (unsigned long long i = 0; i < pow(2,floating.size()); i++) {
                    unsigned long long tmpAddr=addr;
                    for (int j = 0; j < floating.size(); j++) {
                        if (i & (1ULL << j)) {
                            tmpAddr |= (1ULL << floating[j]);
                        }
                    }
                    mem[tmpAddr] = v;
                }
            }
        }
        for (auto it = mem.begin(); it != mem.end(); ++it) {
            res += (*it).second;
        }
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
