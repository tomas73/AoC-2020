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

typedef struct tile {
    int tileNumber;
    bool locked;
    int xPos;
    int yPos;
    int up;
    int down;
    int left;
    int right;
} tile;

vector<tile> tiles;
set<int> edgeTiles;
set<int> cornerTiles;
set<int> innerTiles;

unsigned int inverse(unsigned int val)
{
    unsigned int res = 0;
    for (int i = 0; i < 10; i++) {
        if (val & (1 << i)) res |= (1 << (9-i));
    }
    return res;
}

unsigned int stringToInt(string s)
{
    unsigned int val = 0;

    cout << "S: " << s << " ";

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '#') val |= (1 << i);
    }
    cout << val << " " << inverse(val) << endl;
    return (val);
}

void countEdges(vector<vector<char>> &vv, tile &t)
{

    string s1,s2,s3,s4;
    for (int i = 0; i < 10; i++) {
        s1.push_back(vv[0][i]);
    }
    t.up = stringToInt(s1);

    for (int i = 0; i < 10; i++) {
        s2.push_back(vv[9][i]);
    }
    t.down = stringToInt(s2);

    for (int i = 0; i < 10; i++) {
        s3.push_back(vv[i][0]);
    }
    t.left = stringToInt(s3);

    for (int i = 0; i < 10; i++) {
        s4.push_back(vv[i][9]);
    }
    t.right = stringToInt(s4);
    cout << endl;
}

int numUnMatched(tile t1, tile t2)
{
    int res = 0;
    vector<unsigned int>vt1,vt2;
    vt1.push_back(t1.up);
    vt1.push_back(t1.down);
    vt1.push_back(t1.left);
    vt1.push_back(t1.right);
    vt2.push_back(t2.up);
    vt2.push_back(t2.down);
    vt2.push_back(t2.left);
    vt2.push_back(t2.right);
    vt2.push_back(inverse(t2.up));
    vt2.push_back(inverse(t2.down));
    vt2.push_back(inverse(t2.left));
    vt2.push_back(inverse(t2.right));

    for (auto it1 = vt1.begin(); it1 != vt1.end(); ++it1) {
        bool match = false;
        for (auto it2 = vt2.begin(); it2 != vt2.end(); ++it2) {
            if (*it1 == *it2) match = true;
        }
        if (!match) res++;
    }
    return res;
}

bool edgeMatchesTile(unsigned int edge, tile t)
{
    bool match = false;
    vector<unsigned int>vt;
    vt.push_back(t.up);
    vt.push_back(t.down);
    vt.push_back(t.left);
    vt.push_back(t.right);
    vt.push_back(inverse(t.up));
    vt.push_back(inverse(t.down));
    vt.push_back(inverse(t.left));
    vt.push_back(inverse(t.right));
    for (auto it = vt.begin(); it != vt.end(); ++it) {
        if (*it == edge) match = true;
    }
    return match;
}

void sortTiles(void)
{
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        cout << "T: " << (*it).tileNumber << " " << (*it).up << " " << (*it).down << " " << (*it).left << " " << (*it).right << endl;
         int numMatches = 0;
         for (auto iti = tiles.begin(); iti != tiles.end(); ++iti) {
             if (it == iti) continue;
             if (edgeMatchesTile((*it).up, *iti)) numMatches++;
             if (edgeMatchesTile((*it).down, *iti)) numMatches++;
             if (edgeMatchesTile((*it).left, *iti)) numMatches++;
             if (edgeMatchesTile((*it).right, *iti)) numMatches++;
         }
         cout << "NumMatches " << numMatches << endl;
              if (numMatches == 2) cornerTiles.insert((*it).tileNumber);
         if (numMatches == 3) edgeTiles.insert((*it).tileNumber);
         if (numMatches == 4) innerTiles.insert((*it).tileNumber);
    }
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;
    in.open(input);
    string line;
    if (in.is_open()) {

        while (getline(in, line)) {
            if (line.size() == 0) continue;
            tile t;
            t.locked = false;
            stringstream ss;
            string junk;
            int number;
            char colon;
            ss.str(line);
            ss >> junk >> number >> colon;
            t.tileNumber = number;
            t.xPos = -1;
            t.yPos = -1;
            vector<vector<char>> vv;
            for (int i = 0; i < 10; i++) {
                vector<char> v;
                getline(in,line);
                for (auto it = line.begin(); it != line.end(); ++it) {
                    v.push_back(*it);
                    cout << *it;
                }
                cout << endl;
                vv.push_back(v);
            }
            countEdges(vv, t);
            tiles.push_back(t);
        }
        cout << "NumTiles = " << tiles.size() << endl;
    }
    sortTiles();
    cout << "Corner tiles: ";
    res = 1;
    for (auto it=cornerTiles.begin(); it != cornerTiles.end(); ++it) {
        cout << " " << *it;
        res *= *it;
    }
    cout << endl;

    cout << "Edge tiles: ";
    for (auto it=edgeTiles.begin(); it != edgeTiles.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    cout << "Inner tiles: ";
    for (auto it=innerTiles.begin(); it != innerTiles.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    return res;
}




int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
}
