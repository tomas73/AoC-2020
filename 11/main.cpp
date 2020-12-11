#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <string.h>

using namespace std;

#define ROWS (98)
#define COLS (90)

//#define ROWS (10)
//#define COLS (10)

enum direction {
    N = 1,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW,
    END_DIR
};

void printFloor(char fl[ROWS][COLS])
{

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            cout << fl[r][c];
        }
        cout << endl;
    }
    cout << endl;
}

enum direction nextDir(enum direction dir)
{
    enum direction nd;
    switch (dir)
        {
        case N:
            nd = NE;
            break;
        case NE:
            nd = E;
            break;
        case E:
            nd = SE;
            break;
        case SE:
            nd = S;
            break;
        case S:
            nd = SW;
            break;
        case SW:
            nd = W;
            break;
        case W:
            nd = NW;
            break;
        case NW:
            nd = END_DIR;
            break;
        }
    return nd;
}

bool goDirection(enum direction dir, int &row, int &col)
{
    switch (dir)
        {
        case N:
            row--;
            break;
        case NE:
            row--;
            col++;
            break;
        case E:
            col++;
            break;
        case SE:
            row++;
            col++;
            break;
        case S:
            row++;
            break;
        case SW:
            row++;
            col--;
            break;
        case W:
            col--;
            break;
        case NW:
            row--;
            col--;
            break;
        }
    if (row < 0) return false;
    if (row >= ROWS) return false;
    if (col < 0) return false;
    if (col >= COLS) return false;
    return true;
}

bool seatOccupied(char c)
{
    return (c == '#' ? true:false);
}

bool hasChair(char c)
{
    return (c == '.' ? false:true);
}

int countTakenSeats(char fl[ROWS][COLS])
{
    int numTaken = 0;

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (seatOccupied(fl[r][c])) numTaken++;
        }
    }
    return (numTaken);
}

void updateSeating(char fl[ROWS][COLS], char flTmp[ROWS][COLS])
{
    int x,y;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int seatTaken=0;
            if (hasChair(fl[r][c])) {
                for (enum direction d = N; d < END_DIR; d = nextDir(d)) {
                    y=r;
                    x=c;
                    if(goDirection(d,y,x)) {
                        if (fl[y][x] == '#') seatTaken++;
                    }
                }
                if (seatOccupied(fl[r][c]) && (seatTaken >= 4)) {
                    flTmp[r][c] = 'L';
                } else if ((!seatOccupied(fl[r][c])) && seatTaken == 0) {
                    flTmp[r][c] = '#';
                }
            }
        }
    }
}

void updateSeating2(char fl[ROWS][COLS], char flTmp[ROWS][COLS])
{
    int x,y;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int seatTaken=0;
            if (hasChair(fl[r][c])) {
                for (enum direction d = N; d < END_DIR; d = nextDir(d)) {
                    y=r;
                    x=c;
                    while (goDirection(d,y,x)) {
                        if (hasChair(fl[y][x])) {
                            if (fl[y][x] == '#') {
                                seatTaken++;
                            }
                            break;
                        }
                    }
                }
                if (seatOccupied(fl[r][c]) && (seatTaken >= 5)) {
                    flTmp[r][c] = 'L';
                } else if ((!seatOccupied(fl[r][c])) && seatTaken == 0) {
                    flTmp[r][c] = '#';
                }
            }
        }
    }
}





pair<int,int> inputSize(string input)
{
    ifstream in;
    int rows = 0;
    int cols = 0;
    in.open(input);
    if (in.is_open()) {
        string line;
        while (in >> line) {
            rows++;
            cols = line.size();
        }
    }
    cout << "R= " << rows << " Cols = " << cols << endl;
    return (make_pair(rows,cols));
}


int task1(void)
{
    string input = "input";
    int res = 0;

    vector<int> v;
    ifstream in;

    // not used since I could not get dynamic size of array to work
    pair <int,int> dim = inputSize(input);

    char floor[ROWS][COLS];
    char floorUpdated[ROWS][COLS];
    char *fp = &floor[0][0];
    in.open(input);
    if (in.is_open()) {
        string line;
        while (in >> line) {
            stringstream l;
            l << line;
            char c;
            while (l >> c) {
                *fp=c;
                fp++;
            }
        }
    }

    int num = 0;

    memcpy(floorUpdated, floor, sizeof(floor));
    while (1) {
        num += 1;
        memcpy(floor, floorUpdated, sizeof(floor));
        updateSeating(floor, floorUpdated);
        if (memcmp(floor, floorUpdated, sizeof(floor)) == 0) break;
    }
    cout << "Stable after : " << num << endl;
    return countTakenSeats(floor);

    return res;
}




long long task2(int res1)
{
    string input = "input";
    int res = 0;

    vector<int> v;
    ifstream in;

    // not used since I could not get dynamic size of array to work
    pair <int,int> dim = inputSize(input);

    char floor[ROWS][COLS];
    char floorUpdated[ROWS][COLS];
    char *fp = &floor[0][0];
    in.open(input);
    if (in.is_open()) {
        string line;
        while (in >> line) {
            stringstream l;
            l << line;
            char c;
            while (l >> c) {
                *fp=c;
                fp++;
            }
        }
    }

    int num = 0;

    memcpy(floorUpdated, floor, sizeof(floor));
    while (1) {
        num += 1;
        memcpy(floor, floorUpdated, sizeof(floor));
        updateSeating2(floor, floorUpdated);
        if (memcmp(floor, floorUpdated, sizeof(floor)) == 0) break;
    }
    cout << "Stable after : " << num << endl;
    return countTakenSeats(floor);

    return res;

}


int main()
{
    int res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    long long res2 = task2(0);
    cout << "Task 2 = " << res2 <<endl;

}
