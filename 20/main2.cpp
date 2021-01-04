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
    int col;
    int row;
    int up;
    int down;
    int left;
    int right;
    bool flipped;
    int numTurns;
    vector<vector<char>> vv;
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

void flip(tile &t)
{
    unsigned int tmp;

    tmp=t.up;
    t.up = t.down;
    t.down = tmp;
    t.left = inverse(t.left);
    t.right = inverse(t.right);

    t.flipped = ((t.flipped == false) ? true : false);
}

void rotate(tile &t)
{
    unsigned int tmp1, tmp2;

    tmp1 = t.up;
    t.up = t.right;

    tmp2 = t.left;
    t.left = inverse(tmp1);

    tmp1 = t.down;
    t.down = tmp2;

    t.right = inverse(tmp1);

    t.numTurns = (t.numTurns + 1) % 4;
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

bool edgeMatchesAnyTile(unsigned int edge, tile t)
{
    bool match = false;
    int numMatches = 0;
    for (auto iti = tiles.begin(); iti != tiles.end(); ++iti) {
        if (t.tileNumber == (*iti).tileNumber) continue;
        if (edgeMatchesTile(edge, *iti)) match = true;
    }
    return match;
}

vector<tile>::iterator findTileRight(tile t)
{
    vector<tile>::iterator iti;

    for ( iti = tiles.begin(); iti != tiles.end(); ++iti) {
        if (t.tileNumber == (*iti).tileNumber) continue;
        if (edgeMatchesTile(t.right, *iti)) break;
    }
    return iti;
}

vector<tile>::iterator findTileDown(tile t)
{
    vector<tile>::iterator iti;

    for ( iti = tiles.begin(); iti != tiles.end(); ++iti) {
        if (t.tileNumber == (*iti).tileNumber) continue;
        if (edgeMatchesTile(t.down, *iti)) break;
    }
    return iti;
}

void printPuzzle(void)
{
    
}

void layPuzzle(void)
{
    // take a corner and make it upper left
    int ulTileNumber = *(cornerTiles.begin());

    auto it = find_if(tiles.begin(), tiles.end(), [ulTileNumber](const tile& obj) {return obj.tileNumber == ulTileNumber;});

    cout << "Tile Number = " << (*it).tileNumber << endl;
    while(edgeMatchesAnyTile((*it).up, *it) || edgeMatchesAnyTile((*it).left, *it)) {
        rotate(*it);
    }
    (*it).row = 0;
    (*it).col = 0;

    // We have a correctly oriented upper left tile
    // Find and orient the tiles in the upper row... Then the following rows

    auto itc = it;
    auto itr = it;

    int row = 0;
    int col = 1;

    do {
        do {
            unsigned int rightEdge = (*itc).right;
            itc = findTileRight(*itc);
            if (itc != tiles.end()) { // orient it
                for (;;) {
                    if ((*itc).left == rightEdge) break;
                    rotate(*itc);
                    if ((*itc).numTurns == 0) flip(*itc);
                }
                (*itc).row = row;
                (*itc).col = col++;
                cout << " Tile " << (*itc).tileNumber << " Rotate " << (*itc).numTurns << " FLipped " << (*itc).flipped << endl;
            }
        } while (itc != tiles.end());
        unsigned int downEdge = (*itr).down;
        cout << "itr num " << (*itr).tileNumber << endl;
        itr = findTileDown(*itr);
        itc = itr;
        if (itr != tiles.end()) { // orient it
            for (;;) {
                if ((*itr).up == downEdge) break;
                rotate(*itr);
                if ((*itr).numTurns == 0) flip(*itr);
            }
            cout << "itr2 num " << (*itr).tileNumber << endl;
        }
        (*itc).row = ++row;
        (*itc).col = 0;
    } while (itr != tiles.end());
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
            t.flipped = false;
            t.numTurns = 0;
            stringstream ss;
            string junk;
            int number;
            char colon;
            ss.str(line);
            ss >> junk >> number >> colon;
            t.tileNumber = number;
            t.col = -1;
            t.row = -1;
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
            t.vv = vv;
            tiles.push_back(t);
        }
        cout << "NumTiles = " << tiles.size() << endl;
    }
    sortTiles();
    cout << "Corner tiles: ";
    for (auto it=cornerTiles.begin(); it != cornerTiles.end(); ++it) {
        cout << " " << *it;
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

    for (auto it=cornerTiles.begin(); it != cornerTiles.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;

    // Ok start laying the puzzle;
    layPuzzle();

    return res;
}




int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
}
