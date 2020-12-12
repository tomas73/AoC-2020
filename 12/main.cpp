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


struct instruction {
    char cmd;
    int val;
};

struct state {
    int dir;
    int xPos;
    int yPos;
    int wx;
    int wy;
};



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
    return true;
}



int task1(void)
{
    vector<struct instruction> v;
    string input = "input";
    ifstream in;

    in.open(input);
    if (in.is_open()) {
        string line;
        int val;
        char cmd;
        while (in >> cmd >> val) {
            struct instruction i;
            i.cmd=cmd;
            i.val=val;
            v.push_back(i);
        }

        struct state state={90,0,0};
        set<char> move={'N','E','S','W'};
        set<char> turn={'R','L'};
        for (auto it = v.begin(); it != v.end(); ++it) {
            struct instruction i = *it;
            switch (i.cmd) {
            case 'N':
                state.yPos += i.val;
                break;
            case 'E':
                state.xPos += i.val;
                break;
            case 'S':
                state.yPos -= i.val;
                break;
            case 'W':
                state.xPos -= i.val;
                break;
            case 'R':
                state.dir += i.val;
                state.dir = state.dir % 360;
                break;
            case 'L':
                state.dir -= i.val;
                state.dir = state.dir % 360;
                if (state.dir < 0) {
                    state.dir = 360 + state.dir;
                }
                break;
            case 'F':
                switch (state.dir) {
                case 0:
                    state.yPos += i.val;
                    break;
                case 90:
                    state.xPos += i.val;
                    break;

                case 180:
                    state.yPos -= i.val;
                    break;

                case 270:
                    state.xPos -= i.val;
                    break;
                }
                break;
            }
        }
        int res = abs(state.xPos) + abs(state.yPos);
        return res;
    }
}



void rotateWP(struct state &s, struct instruction i)
{
    int x,y;
    if (i.cmd == 'R') {
        x = s.wy;
        y = -s.wx;
    } else {
        x = -s.wy;
        y = s.wx;
    }
    s.wx=x;
    s.wy=y;
    i.val = i.val - 90;
    if (i.val > 0) rotateWP(s,i);
}


long long task2(int res1)
{
    vector<struct instruction> v;
    string input = "input";
    ifstream in;

    in.open(input);
    if (in.is_open()) {
        string line;
        int val;
        char cmd;
        while (in >> cmd >> val) {
            struct instruction i;
            i.cmd=cmd;
            i.val=val;
            v.push_back(i);
        }
        struct state state={90,0,0,10,1};
        for (auto it = v.begin(); it != v.end(); ++it) {
            struct instruction i = *it;
            switch (i.cmd) {
            case 'N':
                state.wy += i.val;
                break;
            case 'E':
                state.wx += i.val;
                break;
            case 'S':
                state.wy -= i.val;
                break;
            case 'W':
                state.wx -= i.val;
                break;
            case 'R':
                rotateWP(state, i);
                break;
            case 'L':
                rotateWP(state, i);
                break;
            case 'F':
                state.xPos = state.xPos + (i.val * state.wx);
                state.yPos = state.yPos + (i.val * state.wy);
                break;
            }
        }

        int res = abs(state.xPos) + abs(state.yPos);
        return res;
    }
}


int main()
{
    int res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    long long res2 = task2(0);
    cout << "Task 2 = " << res2 <<endl;

}
