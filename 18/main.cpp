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

set<char> numbers = {'0','1','2','3','4','5','6','7','8','9'};
set<char> operators = {'+','*'};

bool isNumber(char c)
{
    return (find(numbers.begin(), numbers.end(), c) != numbers.end());
}
bool isOperator(char c)
{
    return (find(operators.begin(), operators.end(), c) != operators.end());
}

int findMatchingParentesis(string expression)
{
    int numToFind = 1;
    int numFound = 0;
    int ix = 1;
    for (ix = 1; ;ix++) {
        if (expression[ix] == ')') numFound++;
        if (expression[ix] == '(') numToFind++;
        if (numFound == numToFind) break;
    }
    return ix;
}

unsigned long long evalExpr(string exp)
{
    int pos = 0;
    int npos = 0;
    stringstream myExp;
    do {
        string element;
        size_t found = exp.find(' ', pos);
        if (found != string::npos) {
            element = exp.substr(pos, (found - pos));
        } else {
            element = exp.substr(pos);
        }
        if (isNumber(element[0])) {
            myExp << element;
            npos = pos + element.size() + 1;
        } else if (isOperator(element[0])) {
            myExp << element;
            npos = pos + element.size() + 1;
        } else {
            string expr = exp.substr(pos);
            int matchingPar = findMatchingParentesis(expr);
            expr = expr.substr(0, matchingPar + 1);
            npos = pos + expr.size() + 1;
            expr = expr.substr(1, matchingPar - 1);
            myExp << evalExpr(expr);
        }
        pos = npos;
    } while (pos <= exp.size());


    unsigned long long acc, val;
    char op;
    myExp >> acc;
    while (myExp >> op >> val) {
        if (op == '+') acc = acc + val;
        if (op == '*') acc = acc * val;
    }
    return acc;
    // When we get here we have string of just numbers and operators
    // Find the fist prio operators, evaluate and replase expr with result

    // string s=myExp.str();
    // int ix=0;
    // char op;
    // int v1,v2;
    // for (;;) {
    //     if (s.find('+') == string::npos) break;
    //     for(;;) {
    //         myExp >> v1;
    //         myExp >> op;
    //         if (op == '+') break;
    //     }
    //     myExp >> v2;
    //     int val = v1 + v2;
    //     cout <<"EXP = " << v1 << " " << op << " " << v2 << " == " << val << endl;
    //     stringstream ss;
    //     ss << v1 << '+' << v2;
    //     size_t p = s.find(ss.str());
    //     cout << "found " << ss.str() << " at pos " << p << " in " << s << endl;
    //     s.replace(p,ss.str().size(),to_string(val));
    //     cout << "res " << s << endl;
    // }
    // only * operators left
    // cout << "Final: " << s << endl;
    // replace('*',' ',s);
    // cout << "Final: " << s << endl;
    // stringstream ss;
    // ss << s;
    // int acc = 1;
    // int val;
    // while (ss >> val) {
    //     acc = acc * val;
    // }
    // cout << "acc = " << acc << endl;
    // return (acc);
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    string input = "input";
    ifstream in;
    in.open(input);
    string line;
    if (in.is_open()) {

        while (getline(in, line)) {
            int pos = 0;
            int npos = 0;
            res += evalExpr(line);

            cout << "RES = " << evalExpr(line) << endl;;
        }
    }
    return res;
}




int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
}
