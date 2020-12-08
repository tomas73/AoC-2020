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

struct instruction {
    enum inst inst;
    int val;
};



void task1(void)
{
    ifstream in;
    map<string,enum inst> imap;
    imap["acc"] = ACC;
    imap["jmp"] = JMP;
    imap["nop"] = NOP;

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
    int accumulator = 0;
    int pc = 0;
    set<int> visitedRows;
    while (1){
        if (visitedRows.find(pc) != visitedRows.end()) {
            break;
        }
        visitedRows.insert(pc);
        struct instruction i=v[pc];
        switch (i.inst) {
        case ACC:
            accumulator += i.val;
            pc++;
            break;
        case JMP:
            pc += i.val;
            break;
        case NOP:
            pc++;
            break;
        };
    }
    cout << "ACC = " << accumulator << endl;
}


bool runProgram(vector<struct instruction> &v, set<int> &visitedRows)
{
    int accumulator = 0;
    int pc = 0;
    visitedRows.insert(pc);
    while (1){
        if (pc == v.size()) {
            cout << "ACC = " << accumulator << " Num visited = " << visitedRows.size() << endl; 
            return true;
        }
        struct instruction i=v[pc];
        switch (i.inst) {
        case ACC:
            accumulator += i.val;
            pc++;
            break;
        case JMP:
            pc += i.val;
            break;
        case NOP:
            pc++;
            break;
        };
        if (visitedRows.find(pc) != visitedRows.end()) {
            break;
        }
        visitedRows.insert(pc);
    }
    return false;
}

void task2()
{
    ifstream in;
    map<string,enum inst> imap;
    imap["acc"] = ACC;
    imap["jmp"] = JMP;
    imap["nop"] = NOP;

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
    cout << "Num visited rows = " << visitedRows.size() << endl;
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
