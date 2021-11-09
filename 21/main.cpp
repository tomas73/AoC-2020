#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <deque>
#include <string>
#include <cmath>

using namespace std;
typedef struct food {
    set<string> ingredients;
    set<string> alergens;
} sFood;


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
}

void splitRawLine(string line, string &ingredients, string &alergens)
{
    size_t n = line.find("(");
    ingredients = line.substr(0, n-1);
    alergens = line.substr(n + 10, line.size() - n - 11);
    eraseChar(',', alergens);
}

typedef struct {
    string alergen;
    set<string> ingredients;
} algIngListStruct;


void printSet(set<string> &s)
{
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}


set<string> commonItems(set<string> a, set<string> b)
{
    set<string> common;

    //cout << "Common:" << endl;
    // printSet(a);
    //printSet(b);

    for ( auto it = a.begin(); it != a.end(); ++it) {
        if (b.find(*it) != b.end()) {
            common.insert(*it);
        }
    }
    //printSet(common);
    return common;
}

set<string> removeSet(set<string> &rem , set<string> &from)
{
    set<string> diff;
    //cout << "Remove:";
    //printSet(rem);
    //printSet(from);
    for (auto it = from.begin(); it != from.end(); ++it) {
        if (rem.find(*it) == rem.end()) {
            diff.insert(*it);
        }
    }
    //printSet(diff);
    return diff;
}  

void printAlergenList(vector<algIngListStruct> &a)
{
    for ( auto it = a.begin(); it != a.end(); ++it) {
        cout << it->alergen << ": ";
        for (auto iti = it->ingredients.begin(); iti != it->ingredients.end(); ++iti) {
            cout << *iti << ", ";
        }
        cout << endl;
    }
}

typedef struct {
    string ingredient;
    string alergen;
} IngAlg;

void removeIngredient(string ing, vector<algIngListStruct> &a)
{
    for (auto it = a.begin(); it != a.end(); ++it) {
        it->ingredients.erase(ing);
    }
}


void printiaList(vector<IngAlg> ial)
{
    for (auto it = ial.begin(); it != ial.end(); ++it) {
        cout << it->ingredient << " : " << it->alergen << endl;
    }
}

bool compareIngAlg(IngAlg a, IngAlg b)
{
    return a.alergen < b.alergen;
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    //string input = "traininginput";
    string input = "input";
    ifstream in;
    in.open(input);
    string line;
    set<string> allIngredients;
    set<string> allAlergens;
    vector<sFood> foods;
    unsigned long occurs = 0;    
    vector<algIngListStruct> algsWithIngs;
    if (in.is_open()) {

        int lineCnt=0;
        while (getline(in, line)) {
            string ingredients, alergens;
            splitRawLine(line, ingredients, alergens);
            vector<string> wingredients;
            vector<string> walergens;
            splitWords(ingredients, wingredients);
            splitWords(alergens, walergens);
            // cout << "ING: " << ingredients << endl;
            sFood food;
            for ( auto it = wingredients.begin(); it != wingredients.end(); ++it) {
                allIngredients.insert(*it);
                food.ingredients.insert(*it);
            }
            for ( auto it = walergens.begin(); it != walergens.end(); ++it) {
                allAlergens.insert(*it);
                food.alergens.insert(*it);
            }
            foods.push_back(food);
        }

        cout << "Processed input" << endl;
        // For each alergen, collect the sets of ingredients it could contained
        // in
        for ( auto itAlergen = allAlergens.begin(); itAlergen != allAlergens.end(); ++itAlergen) {
            algIngListStruct a;
            a.alergen=*itAlergen;
            int i = 0;
            for ( auto itFood = foods.begin(); itFood != foods.end(); ++itFood) {
                if ( itFood->alergens.find(*itAlergen) != itFood->alergens.end()) {
                    // This food contains this alergen, add ingredients to list
                    if ( i == 0) {
                        a.ingredients=itFood->ingredients;
                        i++;
                    } else {
                        a.ingredients=commonItems(a.ingredients, itFood->ingredients);
                    }   
                }
            }
            algsWithIngs.push_back(a);
        }
        printAlergenList(algsWithIngs);
        // algsWithIngs now holds sets of possible ingredients for each alergen
        // ingredients not in here can not possibly contain an alergen
        set<string> safeIngredients=allIngredients;
        for (auto it = algsWithIngs.begin(); it != algsWithIngs.end(); ++it) {
            safeIngredients = removeSet(it->ingredients, safeIngredients);        
        }
        //    cout << "Safe Ingredients:" << endl;
        //    printSet(safeIngredients);

        // All that is left is to count the times they occur

        for (auto it = safeIngredients.begin(); it != safeIngredients.end(); ++it) {
            for ( auto itFood = foods.begin(); itFood != foods.end(); ++itFood) {
                if ( itFood->ingredients.find(*it) != itFood->ingredients.end()) {
                    occurs++;
                }
            }
        }
    }
    cout << "Task1: " << occurs << endl;

    vector<IngAlg> iaList;
    while (algsWithIngs.size() != 0) {
        cout << "algsWith Ings size: " << algsWithIngs.size() << endl;
        for ( auto it = algsWithIngs.begin(); it != algsWithIngs.end(); ++it) {
            if (it->ingredients.size() == 1) {
                cout << "Found " << it->alergen << endl;
                IngAlg ia;
                ia.ingredient=*it->ingredients.begin();
                ia.alergen=it->alergen;
                iaList.push_back(ia);
                algsWithIngs.erase(it);
                removeIngredient(ia.ingredient, algsWithIngs);
                break;
            }
        }
    };
    printiaList(iaList);
    sort(iaList.begin(), iaList.end(), compareIngAlg);
    cout << "Sorted" << endl;
    printiaList(iaList);
    
    for (auto it = iaList.begin(); it != iaList.end(); ++it) {
        cout << it->ingredient << ",";
    }
    cout << endl;
    return occurs;
}
int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    return 0;
}

