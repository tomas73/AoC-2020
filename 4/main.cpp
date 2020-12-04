#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

bool validateInt(string s, int yMin, int yMax)
{
    bool retval = false;
    int y;
    try {
        y=stoi(s);
        if (y >= yMin && y <= yMax) retval = true;
    }

    catch (std::invalid_argument e) {
        cout <<  "Int invalid format: " << s << endl;
    }

    return retval;
}

bool byrValid(string s)
{
    //    byr (Birth Year) - four digits; at least 1920 and at most 2002.
    return validateInt(s, 1920, 2002);
}

bool iyrValid(string s)
{
    //    iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    return validateInt(s, 2010, 2020);
}

bool eyrValid(string s)
{
    //    eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    return validateInt(s, 2020, 2030);
}


bool hgtValid(string hgt)
{
    //    hgt (Height) - a number followed by either cm or in:
    //        If cm, the number must be at least 150 and at most 193.
    //        If in, the number must be at least 59 and at most 76.
    int pos=hgt.find("cm");
    if (pos != string::npos) {
        string s=hgt.substr(0,pos);
        return validateInt(s, 150, 193);
    }
    pos=hgt.find("in");
    if (pos != string::npos) {
        string s=hgt.substr(0,pos);
        return validateInt(s, 59, 76);
    }

    return false;
}

bool validateChar(char c, set<char> &s)
{
    if (s.find(c) != s.end()) return true;
    return false;
}

bool hclValid(string hcl)
{
    set <char>s;
    //    hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    if (hcl.size() != 7) return false;

    s = {'#'};
    if (!validateChar(hcl[0], s)) return false;

    s.clear();
    s = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

    for (int i = 1; i <= 6; ++i) {
        if (!validateChar(hcl[i], s)) return false;
    }

    return true;
}


bool eclValid(string ecl)
{
    //    ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    set<string> s = {"amb","blu","brn","gry","grn","hzl","oth"};
    if (s.find(ecl) == s.end()) return false;
    return true;
}

bool pidValid(string pid)
{
    set <char>s;
    s = {'0','1','2','3','4','5','6','7','8','9'};
    //    pid (Passport ID) - a nine-digit number, including leading zeroes.
    if (pid.size() != 9) return false;

    for (int i = 0; i <= 8; ++i) {
        if (!validateChar(pid[i], s)) return false;
    }

    return true;
}


int validatePassport(map<string,string> p)
{
    if (!byrValid(p["byr"])) return 0;
    if (!iyrValid(p["iyr"])) return 0;
    if (!eyrValid(p["eyr"])) return 0;
    if (!hgtValid(p["hgt"])) return 0;
    if (!hclValid(p["hcl"])) return 0;
    if (!eclValid(p["ecl"])) return 0;
    if (!pidValid(p["pid"])) return 0;

    return 1;
}

void task2(vector<map<string,string>> &pps)
{
    int numOk = 0;
    for (auto it = pps.begin(); it != pps.end(); ++it) {
        map<string,string> pp;
        pp = *it;
        if (pp.size() == 8 || (pp.size() == 7 && (pp.find("cid") == pp.end()))) {
            numOk += validatePassport(pp);
        }
    }
    cout << endl << "Task2 Num OK passports = " << numOk << endl;
}

void task1(vector<map<string,string>> &pps)
{
    int numOk = 0;
    for (auto it = pps.begin(); it != pps.end(); ++it) {
        map<string,string> pp;
        pp = *it;
        if (pp.size() == 8) {
            numOk++;
        } else if (pp.size() == 7 && (pp.find("cid") == pp.end())) {
            numOk++;
        }
    }
    cout << endl << "Task1 Num OK passports = " << numOk << endl;
}

int main()
{
    ifstream in;
    map<string,string> elements;
    vector<map<string,string>> passports;

    in.open("input");
    if (in.is_open()) {
        string line;
        while (getline(in, line)) {
            if (line.size() == 0) {
                // Handle passport
                passports.push_back(elements);
                elements.clear();
            } else {
                // Ok, we have a line, plit it in its segments
                stringstream l;
                l << line;
                string element;
                map<string,string> m;
                while (l >> element) {
                    // Split element in key:value
                    string key, value;
                    size_t pos = element.find(":");
                    key = element.substr(0,pos);
                    value = element.substr(pos + 1);
                    elements[key]=value;
                }
            }
        }
        passports.push_back(elements);
        // All passports read
        cout << "Num passwords = " << passports.size() << endl;
        task1(passports);
        task2(passports);
    }
}
