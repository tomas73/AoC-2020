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

pair<int,int> makeRange(string &s)
{


    stringstream ss;
    ss << s;
    int a,b;
    ss >> a >> b;
    pair<int,int>res {a,b};
    return res;
}

bool valInRange(int val, pair<int,int> &range)
{
    if ((val >= range.first) && (val <= range.second)) {
        return true;
    } else {
        return false;
    }
}

bool valInRanges(int val, vector<pair<int,int>> &ranges)
{
    for (auto it = ranges.begin(); it != ranges.end(); ++it)
        {
            if (valInRange(val, *it)) return true;
        }
    return false;
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;

    vector<pair<int,int>> ranges;
    vector<int> invalidNumbers;
    in.open(input);
    if (in.is_open()) {
        // Read ranges
        string field, sr1, sr2, junk;
        string line;
        while (getline(in, line)) {
            if (line.size() == 0) break;
            stringstream ss;
            size_t found = line.find(":");
            field = line.substr(0,found);
            line = line.substr(found);
            ss << line;
            ss >> field;
            ss >> sr1 >> junk >> sr2;
            replace('-',' ',sr1);
            replace('-',' ',sr2);
            pair<int,int> r1 = makeRange(sr1);
            pair<int,int> r2 = makeRange(sr2);

            ranges.push_back(r1);
            ranges.push_back(r2);
        }
        // read my ticket;
        getline(in, line); //your...
        getline(in, line); //n,m,k,...
        getline(in, line); //
        getline(in, line); //nearby...
        while(getline(in, line)) {
            replace(',',' ',line);
            stringstream ss;
            ss << line;
            int val;
            while(ss >> val) {
                if (!valInRanges(val, ranges)) {
                    invalidNumbers.push_back(val);
                }
            }
        }
        for (auto it = invalidNumbers.begin(); it != invalidNumbers.end(); ++it)
            {
                res += *it;
            }


    }
    return res;
}


bool inFieldRange(int val, pair<pair<int,int>,pair<int,int>> r)
{
    if (((val >= r.first.first) && (val <= r.first.second)) ||
        ((val >= r.second.first) && (val <= r.second.second))) {
        return true;
    }
    return false;
}

long long task2()
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;

    vector<pair<int,int>> ranges;
    vector<pair<pair<int,int>,pair<int,int>>> fieldRanges;
    vector<int> invalidNumbers;
    vector<string> fieldNames;
    vector<int> myTicket;
    in.open(input);
    if (in.is_open()) {
        // Read ranges
        string field, sr1, sr2, junk;
        string line;

        // Read in the ranges
        while (getline(in, line)) {
            if (line.size() == 0) break;
            stringstream ss;
            size_t found = line.find(":");
            field = line.substr(0,found);
            fieldNames.push_back(field);
            line = line.substr(found + 2);
            ss << line;
            ss >> sr1 >> junk >> sr2;
            replace('-',' ',sr1);
            replace('-',' ',sr2);
            pair<int,int> r1 = makeRange(sr1);
            pair<int,int> r2 = makeRange(sr2);
            ranges.push_back(r1);
            ranges.push_back(r2);
            pair<pair<int,int>,pair<int,int>> r;
            r.first=r1;
            r.second=r2;
            fieldRanges.push_back(r);
        }
        int i = 0;
        // read my ticket;
        vector<vector<int>> values;
        vector<int> v;
        int val;
        stringstream ss;
        getline(in, line); //your...
        getline(in, line); //n,m,k,...
        replace(',',' ',line);
        ss << line;
        while(ss >> val) {
            v.push_back(val);
            myTicket.push_back(val);
        }
        values.push_back(v);

        // Read all other tickets
        getline(in, line); //
        getline(in, line); //nearby...

        while(getline(in, line)) {
            v.clear();
            replace(',',' ',line);
            stringstream ss;
            ss << line;
            bool validTicket=true;
            while(ss >> val) {
                v.push_back(val);
                if (!valInRanges(val, ranges)) {
                    validTicket=false;
                }
            }
            if (validTicket) {
                values.push_back(v);
            }
        }

        // values[][] keeps all values for all tickets
        // Figure out the possible fields for each column
        // For each column, add all the fields for which the value
        // in the first row is valid to the set of possible fields
        // For each following row; remove the invalid fields found
        // from the set of possible fields for this column
        // No additions need to be made since a field can not
        // be vaild unless it is also valid for the first row.

        int col = 0;
        int row = 0;
        vector<set<int>> possibleFields;
        set<int> s;
        int numCols = values[0].size();
        for (col = 0; col < numCols ; ++col) {
            s.clear();
            possibleFields.push_back(s);

            row = 0;
            for (auto it = values.begin(); it != values.end(); ++it, ++row) {
                vector<int> v =*it;
                int val = v[col];
                // Check all ranges
                int field = 0;

                if (row == 0) { //first row
                    for (auto itfr = fieldRanges.begin(); itfr != fieldRanges.end(); ++itfr, ++field) {
                        if (inFieldRange(val, fieldRanges[field])) {
                            // Add to set of possible fields for col
                            possibleFields[col].insert(field);
                        }
                    }
                } else { // Following rows
                    for (auto itfr = fieldRanges.begin(); itfr != fieldRanges.end(); ++itfr, ++field) {
                        if (!inFieldRange(val, fieldRanges[field])) {
                            // Remove from set of possible fields for col
                            if (possibleFields[col].find(field) != possibleFields[col].end()) {
                                possibleFields[col].erase(field);
                            }
                        }
                    }
                }
            }
        }

        // Now we have a vector containing the sets of possible fields for each column
        // Luckily there seem to be 1 with 1 valid, 1 with two and so on.
        // 1 Find the column with just one valid field
        // 2 Store it in map with field name
        // 3 Remove it as a possibility from all other columns
        // 4 goto 1 while all are not empty.

        map<string,int> fieldPosition;
        bool allDone;

        do {
            col = 0;
            allDone = true;
            for (auto it = possibleFields.begin(); it != possibleFields.end(); ++it, ++col) {
                set<int> s=*it;
                if (s.size() == 1) {
                    int val = *(s.begin());
                    string name = fieldNames[val];
                    fieldPosition[name] = col;
                    allDone = false;

                    // remove this field from all sets
                    for (auto it2 = possibleFields.begin(); it2 != possibleFields.end(); ++it2) {
                        ( *it2).erase(val);
                    }
                }
            }
        } while (!allDone);


        res = 1;
        for (auto it = fieldPosition.begin(); it != fieldPosition.end(); ++it) {
            pair<string,int> p = *it;
            string s = p.first;
            if (s.find("departure") != s.npos) {
            res *= myTicket[it->second];
            }

        }
    }
    return res;
}


int main()
{
    long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    long long res2 = task2();
    cout << "Task 2 = " << res2 <<endl;

}
