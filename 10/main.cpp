#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <deque>

using namespace std;

void printVector(vector<int> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;
}

int vDiffBuckets(vector<int> &v)
{
    int oldVal=0;
    int newVal;
    int diff;
    int arr[3] = {0,0,0};

    for (auto it = v.begin(); it != v.end(); ++it) {
        newVal = *it;
        diff = newVal - oldVal;
        oldVal=newVal;
        arr[diff - 1] += 1;
    }
    // Add the last adapter, max + 3
    arr[2] +=1 ;
    return (arr[0] * arr[2]);

}

int task1(void)
{
    int res = 0;
    int val;
    vector<int> v;
    ifstream in;
    in.open("input");
    if (in.is_open()) {
        while (in >> val) {
            v.push_back(val);
        }
    }
    sort(v.begin(), v.end());
    return (vDiffBuckets(v));
}




long long task2(int res1)
{
    int res2 = res1;

    int val;
    vector<int> v;
    ifstream in;
    in.open("input");
    if (in.is_open()) {
        v.push_back(0); // Insert the base element first
        while (in >> val) {
            v.push_back(val);
        }
    }
    sort(v.begin(), v.end());
    int numElements = v.size();
    long long reachable[numElements];
    // the last element for sure can only reach the final target
    reachable[numElements - 1] = 1;

    for (int ix = numElements -2; ix >= 0; --ix) {
        reachable[ix] = 0;

        for (int i = 1; (i < 4) && ((i + ix) < numElements); i++) {
            if (v[ix + i] - v[ix] > 3) break;
            reachable[ix] += reachable[ix+ i];
        }
    }
    return reachable[0];
}


int main()
{
    int res1 = task1();
    long long res2 = task2(res1);
    cout << "Task 1 = " << res1 <<endl;
    cout << "Task 2 = " << res2 <<endl;

}
