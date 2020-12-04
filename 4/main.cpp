#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

using namespace std;

void task1(vector<map<string,string>> &pps)
{
    int numOk = 0;
    cout << "Num passwords = " << pps.size() << endl;
    for (auto it = pps.begin(); it != pps.end(); ++it) {
        map<string,string> pp;
        pp = *it;
        if (pp.size() == 8) {
            numOk++;
        } else if (pp.size() == 7 && (pp.find("cid") == pp.end())) {
            numOk++;
        }
    }
    cout << endl << "Num OK passports = " << numOk << endl;
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
                    value = element.substr(pos);
                    elements[key]=value;
                }
            }
        }
        passports.push_back(elements);
        // All passports read
        task1(passports);
    }
}
