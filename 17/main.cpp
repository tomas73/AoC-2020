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

void printSpace(vector<vector<vector<char>>> &space)
{
    int z;
    z = -(space.size() / 2);

    for (auto its = space.begin(); its != space.end(); ++its) {
        cout << "z = " << z << endl;
        vector<vector<char>> rows = *its;
        for (auto itr = rows.begin(); itr != rows.end(); ++itr) {
            vector<char> cols = *itr;
            for (auto itc = cols.begin(); itc != cols.end(); ++itc) {
                cout << *itc;
            }
            cout << endl;
        }
        z++;
    }
}

vector<vector<vector<char>>> prepareSpace(int rows, int cols, int numCycles)
{
    vector<vector<vector<char>>> space;

    for (int z = 0; z < 1 + 2*(numCycles + 1); z++) {
        vector<vector<char>> vy;
        for (int y = 0; y < rows + 2*(numCycles + 1); y++) {
            vector<char> vx;
            for (int x = 0; x < cols + 2*(numCycles + 1); x++) {
                vx.push_back('.');
            }
            vy.push_back(vx);
        }
        space.push_back(vy);
    }
    return space;
}

void setActive(char &c)
{
    c = '#';
}

void setInActive(char &c)
{
    c = '.';
}

bool isActive(char c)
{
    return (c == '#');
}

char nextVal(vector<vector<vector<char>>> &org, int zPos, int rPos, int cPos)
{
    char c, cr;
    int numActive = 0;

    for (int z = -1; z <= 1; z++) {
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                if (z == 0 && row == 0 && col == 0) {
                    continue;
                }
                if (isActive(org[zPos + z][rPos + row][cPos + col])) {
                    numActive++;
                }
            }
        }
    }
    c = org[zPos][rPos][cPos];
    cr = c;
    if (isActive(c)) {
        if (numActive == 2) {
            setActive(cr);
        } else if (numActive == 3) {
            setActive(cr);
        } else {
            setInActive(cr);
        }
    } else { // inactive
        if (numActive == 3) {
            setActive(cr);
        } else {
            setInActive(cr);
        }
    }

    return cr;
}


void updateSpace(vector<vector<vector<char>>> &org, vector<vector<vector<char>>> &upd)
{
    int numRows, numCols, numLayers;
    numLayers = org.size() - 2;
    numRows= org[0].size() - 2;
    numCols = org[0][0].size() -2;

    // Walk through every position, exept for the frame of space
    for (int z = 1; z <= numLayers; z++) {
        for (int y = 1; y <= numRows; y++) {
            for (int x = 1; x <= numCols; x++) {
                char c = nextVal(org, z, y, x);
                upd[z][y][x] = c;
            }
        }
    }
}

int countActive(vector<vector<vector<char>>> &org)
{
    int numRows, numCols, numLayers, numActive;
    numLayers = org.size() - 2;
    numRows= org[0].size() - 2;
    numCols = org[0][0].size() -2;
    numActive = 0;


    // Walk through every position, exept for the frame of space
    for (int z = 1; z <= numLayers; z++) {
        for (int y = 1; y <= numRows; y++) {
            for (int x = 1; x <= numCols; x++) {
                if (isActive(org[z][y][x])) numActive++;
            }
        }
    }
    return numActive;
}


unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;
    int numCycles = 6;

    vector<vector<vector<char>>> copyA;
    vector<vector<vector<char>>> copyB;

    in.open(input);
    string line;
    if (in.is_open()) {
        // Determine dimentions
        int rows = 0;
        int cols = 0;

        while (getline(in, line)) {
            rows++;
        }
        cols = line.size();
        cout << "Rows = " << rows << " Cols = " << cols << endl;
        // Prepare pocketSpace, needs to be + 2*numCycles in each direction
        copyA = prepareSpace(rows, cols, numCycles);

        // Rewind input;
        in.clear();
        in.seekg(0);
        int row = 0;
        while (getline(in, line)) {
            stringstream ss;
            ss << line;
            char c;
            int col = 0;
            while (ss >> c) {
                copyA[numCycles + 1][numCycles + row + 1][numCycles + col + 1] = c;
                col++;
            }
            row++;
        }
        copyB = copyA;


        for (int i = 0; i < numCycles; ++i) {
            updateSpace(copyA, copyB);
            copyA = copyB;
            cout << "After " << i + 1 << " cycles" << endl;
            cout << "NumActive = " << countActive(copyA) << endl;

        }
        res = countActive(copyA);
    }
    return res;
}




int main()
{
    long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
}
