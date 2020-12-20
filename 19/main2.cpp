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

pair<string,string> valop;

// bool isNumber(char c)
// {
//     return (find(numbers.begin(), numbers.end(), c) != numbers.end());
// }
// bool isOperator(char c)
// {
//     return (find(operators.begin(), operators.end(), c) != operators.end());
// }

// int findMatchingParentesis(string expression)
// {
//     int numToFind = 1;
//     int numFound = 0;
//     int ix = 1;
//     for (ix = 1; ;ix++) {
//         if (expression[ix] == ')') numFound++;
//         if (expression[ix] == '(') numToFind++;
//         if (numFound == numToFind) break;
//     }
//     return ix;
// }

typedef struct node {
    int rule;
    bool done;
    set<string> myPatterns;
    vector<set<string>> lPatterns;
    vector<set<string>> rPatterns;
    set<string> lPatternsCombined;
    set<string> rPatternsCombined;
    vector<int> lRules;
    vector<int> rRules;
} node;

vector<node> rules;
vector<string> codeWords;

void printRules(void) {
    for (auto it = rules.begin(); it != rules.end(); ++it) {
        node p = *it;
        cout << p.rule << " :";
        if (p.done) {
            cout << "Target " << *(p.myPatterns.begin());
        } else {
            for (auto itl = p.lRules.begin(); itl != p.lRules.end(); ++itl) {
                cout << " " << *itl;
            }
            cout << " | ";
            for (auto itr = p.rRules.begin(); itr != p.rRules.end(); ++itr) {
                cout << " " << *itr;
            }
        }
        cout << endl;
    }
}

vector<node>::iterator findNode(int rule)
{
    vector<node>::iterator it;
    for (it = rules.begin(); it != rules.end(); ++it) {
        if ((*it).rule == rule) break;
    }
    return it;
}

set<string> getPatterns(int rule)
{
    vector<node>::iterator it = findNode(rule);
    if ((*it).done) {
        return ((*it).myPatterns);
    }

    for (auto i = (*it).lRules.begin(); i != (*it).lRules.end(); ++i) {
        (*it).lPatterns.push_back(getPatterns(*i));
    }
    for (auto i = (*it).rRules.begin(); i != (*it).rRules.end(); ++i) {
        (*it).rPatterns.push_back(getPatterns(*i));
    }

    // The left and right patterns are  filled, do the combinations;
    if ((*it).lPatterns.size() == 1) {
        (*it).lPatternsCombined.insert((*it).lPatterns[0].begin(), (*it).lPatterns[0].end());
    } else if ((*it).lPatterns.size() == 2) {
        set<string> s1 = (*it).lPatterns[0];
        set<string> s2 = (*it).lPatterns[1];
        for (auto is1 = s1.begin(); is1 != s1.end(); ++is1) {
            for (auto is2 = s2.begin(); is2 != s2.end(); ++is2) {
                string s = *is1;
                s += *is2;
                (*it).lPatternsCombined.insert(s);
            }
        }
    } else {
        cout << "THIS IS WRONG 1" << (*it).lPatterns.size() << endl;
    }

    if ((*it).rPatterns.size() == 0) {
        ;
    } else if ((*it).rPatterns.size() == 1) {
        (*it).rPatternsCombined.insert((*it).rPatterns[0].begin(), (*it).rPatterns[0].end());
    } else if ((*it).rPatterns.size() == 2) {
        set<string> s1 = (*it).rPatterns[0];
        set<string> s2 = (*it).rPatterns[1];
        for (auto is1 = s1.begin(); is1 != s1.end(); ++is1) {
            for (auto is2 = s2.begin(); is2 != s2.end(); ++is2) {
                string s = *is1;
                s += *is2;
                (*it).rPatternsCombined.insert(s);
            }
        }
    } else {
        cout << "THIS IS WRONG 2 " << (*it).rPatterns.size() << endl;
    }

    // Now we have the left and right sides, do the combinations
    (*it).myPatterns.insert((*it).lPatternsCombined.begin(), (*it).lPatternsCombined.end());
    (*it).myPatterns.insert((*it).rPatternsCombined.begin(), (*it).rPatternsCombined.end());
    (*it).done = true;
    return ((*it).myPatterns);
}


unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;
    in.open(input);
    string line;
    if (in.is_open()) {

        //Get the rules
        while (getline(in, line)) {
            if (line.size() == 0) break;
            node tmp;
            tmp.done = false;
            stringstream ss;
            ss.str(line);
            int rule;
            char junk;
            ss >> rule >> junk;
            tmp.rule = rule;
            if (count(line.begin(),line.end(),'"')) {
                char value;
                ss >> junk >> value >> junk;
                string s;
                s.push_back(value);
                tmp.myPatterns.insert(s);
                tmp.done = true;
            } else {
                int value;
                while (ss >> value) {
                    tmp.lRules.push_back(value);
                }
                if (ss.fail()) ss.clear();
                ss >> junk;
                while (ss >> value) {
                    tmp.rRules.push_back(value);
                }
            }
            rules.push_back(tmp);
        }
        // Get the code words
        int len, maxlen=0;
        while (getline(in, line)) {
            len = line.size();
            if (len > maxlen) maxlen = len;
            codeWords.push_back(line);
        }
        cout << "MaxLen = " << maxlen << endl;
    }
    set<string> s;
    set<string> s42;
    set<string> s31;
    s42 = getPatterns(42);
    s31 = getPatterns(31);
    for (auto it = s42.begin(); it != s42.end(); ++it) {
    
        for (auto it1 = s31.begin(); it1 != s31.end(); ++it1) {
            if (*it == *it1) cout << *it << " in both" << endl;
        }
    }

    int numMatched = 0;
    // Pattern to match is n*s42 + m*s42 + m*s31
    cout << "Num words " << codeWords.size() << endl;
    for (auto itc = codeWords.begin(); itc != codeWords.end(); ++itc) {
        int pos = 0;
        string s = (*itc).substr(pos,8);
        int n = 0;
        int m = 0;

        while (find(s42.begin(), s42.end(), s) != s42.end()) {
            n++;
            pos = pos + 8;
            s = (*itc).substr(pos,8);
        }
        if (n >= 2) {
            while (find(s31.begin(), s31.end(), s) != s31.end()) {
                m++;
                pos = pos + 8;
                s = (*itc).substr(pos,8);
            }
            if ((m > 0) &&
                (n > m)) {
                if ((*itc).size() == ((n*8) + (m*8))) {
                    numMatched++;
                }
            }
        }
    }
    return numMatched;


    return 0;
    s = getPatterns(0);
    cout << "size " << s.size() << endl;
    int i = 0;
    int numMatch = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << endl;
        for (auto itc = codeWords.begin(); itc != codeWords.end(); ++itc) {
            if ((*it) == *itc) numMatch++;
        }
        if ((++i % 1000) == 0) cout << i << endl;
    }

    return numMatch;
}




int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
}
