#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

enum inst {
    ACC,
    JMP,
    NOP
};

map<string,enum inst> imap {
    {"acc", ACC },
    {"jmp", JMP },
    {"nop", NOP }
};

struct instruction {
    enum inst inst;
    int val;
};

struct state {
    int pc;
    int acc;
};


void stepInstruction(struct instruction i, struct state &s)
{
    switch (i.inst) {
    case ACC:
        s.acc += i.val;
        s.pc++;
        break;
    case JMP:
        s.pc += i.val;
        break;
    case NOP:
        s.pc++;
        break;
    };
}

bool runProgram(vector<struct instruction> &v, set<int> &visitedRows)
{
    struct state s{0,0};

    visitedRows.insert(s.pc);
    while (1){
        if (s.pc == v.size()) {
            cout << "Normal Termination, ACC = " << s.acc << endl;
            return true;
        }
        stepInstruction(v[s.pc], s);
        if (visitedRows.find(s.pc) != visitedRows.end()) {
            break;
        }
        visitedRows.insert(s.pc);
    }
    return false;
}


void task1(void)
{
    ifstream in;
    vector<struct instruction> v;

    in.open("input");
    if (in.is_open()) {
        string s;
        int value;
        while (in >> s >> value) {
            struct instruction inst;
            inst.inst = imap[s];
            inst.val = value;
            v.push_back(inst);
        }
    }
    struct state s{0,0};
    set<int> visitedRows;

    while (1){
        if (visitedRows.find(s.pc) != visitedRows.end()) {
            break;
        }
        visitedRows.insert(s.pc);
        stepInstruction(v[s.pc], s);
    }
    cout << "ACC = " << s.acc << endl;
}



void task2()
{
    ifstream in;

    vector<struct instruction> v;

    in.open("input");
    if (in.is_open()) {
        string s;
        int value;
        while (in >> s >> value) {
            struct instruction inst;
            inst.inst = imap[s];
            inst.val = value;
            v.push_back(inst);
        }
    }
    set<int> visitedRows;
    runProgram(v, visitedRows);

    // Modify each of the visited rows, one at a time
    int cnt = 0;
    for (auto it = visitedRows.begin(); it != visitedRows.end(); ++it) {
        cnt++;
        set<int> vr;
        struct instruction i1,i2;
        i1 = v[*it];
        i2.val = i1.val;
        if (i1.inst == ACC) continue;
        if (i1.inst == NOP) {
            i2.inst = JMP;
        } else {
            i2.inst = NOP;
        }
        v[*it] = i2;
        if (runProgram(v, vr)) {
            cout << "Normal Termination!" << endl;
            break;
        }
        v[*it] = i1;
    }
}


int main()
{
    task1();
    task2();
}
