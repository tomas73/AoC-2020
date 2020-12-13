#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <string.h>

using namespace std;


int task1(void)
{
    int res;
    string input = "input";
    ifstream in;

    system("sed 's/,/ /g' input > apa");
    in.open("apa");
    if (in.is_open()) {
        int myArrival;
        in >> myArrival;
        cout << "myArrival = " << myArrival << endl;
        string str;
        int val, busId,nextBus,timeToWait,tmp;
        int minTimeToWait = 1000000;
        while (in >> str) {
            try {
                busId = stoi(str);
                cout << " " << busId;
                tmp = myArrival / busId;
                tmp++;
                nextBus = tmp * busId;
                timeToWait = nextBus - myArrival;
                if (timeToWait < minTimeToWait) {
                    minTimeToWait = timeToWait;
                    res = timeToWait * busId;
                }
            }
            catch (const std::invalid_argument& ia) {
                ;
            }
        }
        cout << endl;
    }
    return res;
}

bool isValid(long long t, int val, int diff)
{
    if (((t+diff) % val) == 0) return true;
    return false;
}

long long task2()
{
    int res;
    ifstream in;

    map<int,int> idPos;
    vector<int> ids;
    system("sed 's/,/ /g' input > apa");
    in.open("apa");
    if (in.is_open()) {
        int myArrival;
        in >> myArrival;
        string str;
        int busId;
        int pos = 0;
        while (in >> str) {
            try {
                busId = stoi(str);
                ids.push_back(busId);
                idPos[busId] = pos;
            }
            catch (const std::invalid_argument& ia) {
                ;
            }
            pos++;
        }
        for (auto it = ids.begin(); it != ids.end(); ++it) {
            cout << " " << *it;
        }
        cout << endl;

        /*
          This is cyclic with some repetition rate. Each event (bus busId arriving <pos>
          miutes after <timestamp> will be true every n*busId - pos minutes. I.e. the
          repetition rate is busId minutes.
          Everything slides, so the repetition rate of two events occuring is the
          product of the individual rates. I.e it will occur every n*busid1*busId2, and
          the fisrst occurance will happen at t < busId1 * busId2.
          Start from zero with interval busId0 and look for a valid occurance of
          busId1. Once found, continue the search from that position, now with
          interval busId0*busId1 to find a valid occurance of busId2 (which will
          happen before t = busId0*busId1*busId2. Rince and repeate.
         */
        long long t = 0;
        long long interval = 1;
        long long numIterations = 0;
        for (auto it = ids.begin(); it != ids.end(); ++it) {
            interval = interval *(*it);
            auto itNext = it + 1;
            if (itNext == ids.end()) {
                cout << " All Done: " << t << " in " << numIterations << " iterations " << endl;
                return t;
            }
            long long n = 1;
            cout << "Look for " << *itNext << " start " << t << " int " << interval << endl;
            while (! isValid(t, *itNext, idPos[*itNext]))
                {
                    numIterations++;
                    t = t + interval;
                }
        }
    }
    return res;
}



int main()
{
    long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    long long res2 = task2();
    cout << "Task 2 = " << res2 <<endl;

}
