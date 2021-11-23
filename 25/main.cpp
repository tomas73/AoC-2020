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

const unsigned long long divider = 20201227;

void loop(unsigned long long &value, unsigned long long subjectnumber)
{
    value = value * subjectnumber;
    value = value % divider;
}

int getLoopSize(unsigned long long pub)
{
    unsigned long long value = 1;
    int i = 0;
    while (true) {
        loop(value, 7);
        i++;
        if (value == pub) {
            cout << "Match: secret loop size = " << i << endl;
            break;
        }
    }
    return i;
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    //string input = "mini";
    //string input = "traininginput";
    string input = "input";
    ifstream in;
    string line;
    unsigned long long pubKey,pubDoor;

    in.open(input);
    if (in.is_open()) {
        in >> pubKey >> pubDoor;
        cout << "Key = " << pubKey << endl;
        cout << "Door = " << pubDoor << endl;
    }

    int sd,sk;
    sk=getLoopSize(5764801);
    sk=getLoopSize(pubKey);
    sd=getLoopSize(pubDoor);
    
    // Calculate encryption key

    unsigned long long e1=1;
    unsigned long long e2=1;

    for (int i = 0; i < sk; i++) {
        loop(e1, pubDoor);
    }

    for (int i = 0; i < sd; i++) {
        loop(e2, pubKey);
    }
    cout << "e1 = " << e1 << endl;
    cout << "e2 = " << e2 << endl;



    return 0;
}

int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    return 0;
}

