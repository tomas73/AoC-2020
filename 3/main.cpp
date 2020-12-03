#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

struct slope {
    int rightInc;
    int downInc;
};

int treesInSlope(vector<vector<char>> &vv, struct slope s, int modBase)
{
    int xPos=0;
    int yPos=0;
    int yPosMax;
    int numTrees=0;
    cout << s.rightInc << ":" << s.downInc << endl;

    yPosMax=vv.size();

    for (yPos = 0; \
         yPos < yPosMax; \
         yPos=yPos + s.downInc, xPos = xPos + s.rightInc) {
        char c = vv[yPos][xPos % modBase];
        if (c == '#') {numTrees++;}
    }
    cout << "numTrees = " << numTrees << endl;
    return numTrees;
}

int main()
{
    ifstream in;

    vector<vector<char>> vv;
    int modBase;

    in.open("input");
    if (in.is_open()) {
        string line;
        while (in >> line) {
            stringstream l;
            l << line;
            vector<char> v;
            char c;
            while (l >> c) {
                v.push_back(c);
            }
            modBase=v.size();
            vv.push_back(v);
        }
    }

    long long mult=1;
    vector<struct slope> slopes = {{1,1},{3,1},{5,1},{7,1},{1,2}};
    for (auto it=slopes.begin(); it != slopes.end(); ++it) {
        mult = mult * treesInSlope(vv, *it, modBase);
    }
    cout << "Tree Multiply = " << mult << endl;
}

