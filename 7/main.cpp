#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

set<string> bagsWhoCarries(string bag, map<string,set<string>> &m)
{
    set<string> canCarry;
    for (auto mit = m.begin(); mit != m.end(); ++mit) {
        string item = (*mit).first;
        set<string> s=(*mit).second;
        if (s.find(bag) != s.end()) {
            canCarry.insert(item);
        }
    }
    return canCarry;
}

void task1(void)
{
    ifstream in;

    in.open("input");
    if (in.is_open()) {
        string colorDesc, color, bag, contain, number;
        int num;
        map<string,set<string>> m;
        set<string> s;
        int i =0;
        while (in >> colorDesc >> color >> bag >> contain) {
            stringstream fullColor;
            fullColor << colorDesc << "-" << color;
            do {
                stringstream fullColor;
                in >> number;
                if (number == "no") {
                    // ff to end of line
                    in >> colorDesc >> bag;
                    break;
                }
                num=stoi(number);
                in >> colorDesc >> color >> bag;
                fullColor << colorDesc << "-" << color;
                s.insert(fullColor.str());
            } while (bag[bag.size() -1 ] == ',');
            m[fullColor.str()] = s;
            s.clear();
        }

        set<string> canCarry = bagsWhoCarries("shiny-gold", m);
        set<string> alreadyChecked;
        int oldSize=canCarry.size();
        int newSize=canCarry.size();

        do {
            oldSize=newSize;
            set<string> newThisLoop;
            for (auto it = canCarry.begin(); it != canCarry.end(); ++it) {
                string s = *it;
                if (alreadyChecked.find(s) == alreadyChecked.end()) {
                    set<string> cc=bagsWhoCarries(s, m);
                    for (auto it2 = cc.begin(); it2 != cc.end(); ++it2) {
                        newThisLoop.insert(*it2);
                    }
                    alreadyChecked.insert(s);
                }
            }
            for (auto it2 = newThisLoop.begin(); it2 != newThisLoop.end(); ++it2) {
                canCarry.insert(*it2);
            }
            newSize=canCarry.size();
        } while (oldSize < newSize);
        cout << " Shiny gold bags can be carried in " << oldSize << " bags" << endl;
    }
}


int bagsContained(string bag, map<string,map<string,int>> &m)
{
    int totNumBags = 0;

    map<string,int> s = m[bag];
    for (auto it = s.begin(); it != s.end(); ++it) {
        int num = (*it).second;
        string b = (*it).first;
        totNumBags += num + (num * bagsContained(b, m));
    }
    return totNumBags;
}

void task2(void)
{
    ifstream in;

    in.open("input");
    if (in.is_open()) {
        string colorDesc, color, bag, contain, number;
        int num;
        map<string,map<string,int>> m;
        map<string,int> s;
        int i =0;
        while (in >> colorDesc >> color >> bag >> contain) {
            stringstream fullColor;
            fullColor << colorDesc << "-" << color;
            do {
                stringstream fullColor;
                in >> number;
                if (number == "no") {
                    // ff to end of line
                    in >> colorDesc >> bag;
                    break;
                }
                num=stoi(number);
                in >> colorDesc >> color >> bag;
                fullColor << colorDesc << "-" << color;
                s[fullColor.str()] = num;
            } while (bag[bag.size() -1 ] == ',');
            m[fullColor.str()] = s;
            s.clear();
        }

        // So, find out whats in my shiny gold bag, count and recurse
        int numBags = bagsContained("shiny-gold", m);
        cout << "Tot Num bags in shiny-gold = " << numBags << endl;
    }
}


int main()
{
    task1();
    task2();
}
