#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <deque>
#include <string>
#include <cmath>

using namespace std;

bool isBlack(pair<int,int> t, set<pair<int,int>> &s)
{
    if (s.find(t) != s.end()) {
        return true;
    } else {
        return false;
    }
}

int minPos=-150;
int maxPos=150;

void handleTile(pair<int,int> t, set<pair<int,int>> &next, set<pair<int,int>> &bt)
{
    // count black adjacent tiles

    int y,x;
    y=t.first;
    x=t.second;
    int numBlack=0;
    if (isBlack(make_pair(y+1,x+1), bt)) { numBlack++; }
    if (isBlack(make_pair(y,x+2), bt)) { numBlack++; }
    if (isBlack(make_pair(y-1,x+1), bt)) { numBlack++; }
    if (isBlack(make_pair(y-1,x-1), bt)) { numBlack++; }
    if (isBlack(make_pair(y,x-2), bt)) { numBlack++; }
    if (isBlack(make_pair(y+1,x-1), bt)) { numBlack++; }
    // Determine color of current tile
    bool ib=isBlack(t, bt);

    // Add / remove from black set as needed
    if (ib) {
        if (y == minPos || y == maxPos || x == minPos || x == maxPos) {
            cout << "##### Black on outer rim" << endl;
        }
        if ((numBlack == 0) || (numBlack > 2)) {
            next.erase(t);
        }
    } else {
        if (numBlack ==2) {
            next.insert(t);
        }
    }
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    //string input = "mini";
    //string input = "traininginput";
    string input = "input";
    ifstream in;
    string line;

    set<pair<int,int>> blackTiles;
    in.open(input);
    if (in.is_open()) {
        char c1, c2;
        while (getline(in, line)) {
            stringstream ss;
            ss.str(line);
            cout << line << endl;
            int xPos=0;
            int yPos=0;
            while (ss >> c1) {
                int xInc=0, yInc=0;
                if (c1 == 'e') {
                    xInc=2;
                }
                if (c1 == 'w') {
                    xInc=-2;
                }
                if ((c1 == 'n') || (c1 == 's')) {
                    ss >> c2;
                    if (c1 == 'n') {
                        yInc=1;
                    }
                    if (c1 == 's') {
                        yInc=-1;
                    }
                    if (c2 == 'e') {
                        xInc=1;
                    }
                    if (c2 == 'w') {
                        xInc=-1;
                    }

                }
                xPos += xInc;
                yPos += yInc;
            }
            cout << "yPos=" << yPos << endl;
            cout << "xPos=" << xPos << endl;
            pair<int,int>p(yPos,xPos);
            if (blackTiles.find(p) == blackTiles.end()) {
                blackTiles.insert(p);
                cout << "Add" << p.first << ":" << p.second << endl;
            } else {
                blackTiles.erase(p);
                cout << "Delete" << p.first << ":" << p.second << endl;
            }
        }
        cout << "Number of black: " << blackTiles.size() << endl;

        for (int i = 0; i < 100; i++) {
            set<pair<int,int>> tmp=blackTiles;
            for (int y=minPos; y < maxPos; y++) {
                for (int x=minPos; x < maxPos; x++) {
                    handleTile(make_pair(y,x), tmp, blackTiles);
                }
            }
            blackTiles=tmp;
            cout << "Number of black: " << blackTiles.size() << endl;
        }
    }
    return 0;
}

int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    return 0;
}

