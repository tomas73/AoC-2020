#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;


int traverseString(string s, char lower, char upper)
{
    int base = 0;
    int range = 1 << s.size();

    for (int i = 0; i < s.size() ; i++ )
        {
            range = range >> 1;
            if (s[i] == upper) {
                base = base + range;
            }
        }
    return base;
}

void task1(void)
{
    ifstream in;

    in.open("input");
    if (in.is_open()) {
        string line;
        string sRow,sSeat;
        int iRow,iSeat,res;
        int maxRes = 0;
        while (getline(in, line)) {
            sRow=line.substr(0,7);
            sSeat=line.substr(7);
            iRow=traverseString(sRow, 'F', 'B');
            iSeat=traverseString(sSeat, 'L', 'R');
            res=(iRow * 8) + iSeat;
            if (res > maxRes) maxRes = res;
        }
        cout << "Max =  " << maxRes << endl;
    }

}

void printRow(int ix, vector<int> seats)
{
    string row = "........";
    for (auto it = seats.begin(); it != seats.end(); ++it) {
        row[*it] = 'X';
    }
    cout << row << " " << ix << endl;
}
void task2(void)
{
    ifstream in;

    vector<int> rows [128];
    in.open("input");
    if (in.is_open()) {
        string line;
        string sRow,sSeat;
        int iRow,iSeat,res;
        int maxRes = 0;
        while (getline(in, line)) {
            sRow=line.substr(0,7);
            sSeat=line.substr(7);
            iRow=traverseString(sRow, 'F', 'B');
            iSeat=traverseString(sSeat, 'L', 'R');
            rows[iRow].push_back(iSeat);
        }
        for (int i = 0; i < 128 ; i++) {
            printRow(i, rows[i]);
        }
        cout << "Max =  " << maxRes << endl;
    }

 
}

int main()
{
    task1();
    task2();
}

