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

//string input = "614752839";
int numCups=   1000000;
int numRounds=10000000;

string input = "389125467";

// Lagt till dest. Sätt den så att den pekar på den som kommer att var
// destination om aktuell är current, dvs. den som har val-1. För val = 1 blir
// det den med numCups. Nuvarande implemetation fungerar kanske, men tar lååång
// tid

typedef struct cup {
    struct cup *next;
    struct cup *dest;
    int val;
} cupType;

void printCircle(cupType *pCup)
{
    for (int i = 0; i < numCups; i++) {
        if (i < 5 || i > numCups -5) {
            cout << pCup->val << ":";
        }
        if (i == 6) {
            cout << "...";
        }
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
    for (int i = 10; i <= numCups; i++)
    {
        pCup = (cupType *)malloc(sizeof(cupType));
        pCup->val=i;
        pAnchor->next = pCup;
        pAnchor = pCup;
    }
    cout << "Last: " << pCup->val << endl;
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

    for (int i = 0; i <= numCups - 3; i++) {
        p=p->next;
        if (p->val== valOfDest) {
            return p;
        }
    }
    if (valOfDest == 1) {
        valOfDest = numCups;
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
        valOfDest = numCups;
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

unsigned long long task2(void)
{
    cupType *pCurrent=createCups(input);
    cupType *pRemoved;
    printCircle(pCurrent);
  
    for (int i = 0; i < numRounds; i++) { 
        pCurrent = doRound(pCurrent);
        if (i % 10000 == 0) printCircle(pCurrent);
    }
    printFinal(pCurrent);

    return 0;
}
int main()
{
    unsigned long long res1 = task2();
    cout << "Task 2 = " << res1 <<endl;
    return 0;
}

