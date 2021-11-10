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

string input = "614752839";
//string input = "389125467";
typedef struct cup {
    struct cup *next;
    int val;
} cupType;

void printCircle(cupType *pCup)
{
    for (int i = 0; i <= sizeof(input); i++) {
        cout << pCup->val << ":";
        pCup=pCup->next;
    }
    cout << endl;
}

cupType *createCups(string sequence)
{
    stringstream ss(sequence);
    cupType *pCup = NULL;
    cupType *pFirst = NULL;   
    cupType *pAnchor = NULL;   
    char c;
    while (ss >> c) {
        pCup = (cupType *)malloc(sizeof(cupType));
        pCup->val=(c-48);
        if (pAnchor != NULL) {
            pAnchor->next = pCup;
        }
        pAnchor = pCup;
        if (pFirst == NULL) {
            pFirst = pCup;
        }
        cout << "cup = " << c << endl;
    };
    pAnchor->next=pFirst;
    return pFirst;
}

cupType *removeThree(cupType *p)
{
    cupType *pRemoved = p->next;
    p->next=p->next->next->next->next;
    return pRemoved;
}

void insertThree(cupType *pCircle, cupType *pRemoved)
{
    cupType *pNext;
    pNext = pCircle->next;
    pRemoved->next->next->next=pNext;
    pCircle->next=pRemoved;
}

cupType *findDestination(cupType *p, int valOfDest)
{

    for (int i = 0; i <= sizeof(input) - 3; i++) {
        p=p->next;
        if (p->val== valOfDest) {
            return p;
        }
    }
    if (valOfDest == 1) {
        valOfDest = 9;
    } else {
        valOfDest--;
    }
    return findDestination(p, valOfDest);
}

cupType *doRound(cupType *pCurrent)
{
    int valOfDest;

    cupType *pDestination;
    cupType *pRemoved=removeThree(pCurrent);
    valOfDest = pCurrent->val - 1;
    if (valOfDest < 1) {
        valOfDest = 9;
    }
    pDestination = findDestination(pCurrent, valOfDest);
    insertThree(pDestination, pRemoved);
    return pCurrent->next;
}

void printFinal(cupType *p)
{
    stringstream ss;
    while (p->val != 1) {
        p=p->next;
    };
    p=p->next;
    for (int i = 0; i < sizeof(input); i++) {
        ss << p->val;
        p=p->next;
    }
    cout << ss.str() << endl;
}

unsigned long long task1(void)
{
    cupType *pCurrent=createCups(input);
    cupType *pRemoved;
    printCircle(pCurrent);
  
    for (int i = 0; i < 100; i++) { 
        pCurrent = doRound(pCurrent);
        printCircle(pCurrent);
    }
    printFinal(pCurrent);

    return 0;
}
int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    return 0;
}

