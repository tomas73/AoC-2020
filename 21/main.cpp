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

void eraseChar(char what, string &str)
{
  size_t found = 0;
  while ((found = str.find(what)) != string::npos) {
    str.erase(found, 1);
  }

}

void replace(char what, char with, string &str)
{
  size_t found = 0;
  while ((found = str.find(what,found)) != string::npos) {
    str[found] = with;
  }
}

void splitWords(string str, vector<string> &words)
{
  size_t pos = 0;
  string space_delimiter=" ";
  while ((pos = str.find(space_delimiter)) != string::npos) {
    words.push_back(str.substr(0, pos));
    str.erase(0, pos + space_delimiter.length());
  }
  words.push_back(str);
      for (auto it = words.begin(); it != words.end(); ++it) {
      cout << *it << endl;}
}

void splitRawLine(string line, string &ingredients, string &alergens)
{
  size_t n = line.find("(");
  ingredients = line.substr(0, n-1);
  alergens = line.substr(n + 10, line.size() - n - 11);
  eraseChar(',', alergens);
}

unsigned long long task1(void)
{
  unsigned long long res = 0;
  string input = "traininginput";
  ifstream in;
  in.open(input);
  string line;
  if (in.is_open()) {

    while (getline(in, line)) {
      cout << "Line: " << line << endl;
      string ingredients, alergens;
      splitRawLine(line, ingredients, alergens);
      cout << "ing: " << ingredients << endl;
      cout << "alg: " << alergens << endl;
      vector<string> wingredients;
      vector<string> walergens;
      splitWords(ingredients, wingredients);
      splitWords(alergens, walergens);
    }
  }
}
int main()
{
  unsigned long long res1 = task1();
  cout << "Task 1 = " << res1 <<endl;
}

