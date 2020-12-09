#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <deque>

using namespace std;

#define PREAMBLE_SIZE (25)

void printVector(vector<long long> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << " " << *it;
    }
    cout << endl;
}
bool valInLastRange(long long val, vector<long long> &v)
{
    int max = v.size();
    for (int i = max - 1; i >= 0; i--) {
        for (int j = 0; i < max; j++) {
            if (j == i) break;
            if (v[i] == v[j]) break;
            if (v[i] + v[j] > val) break;
            if (v[i] + v[j] == val) {
                return true;
            }
        }
    }
    return false;
}

void task1(void)
{
    ifstream in;
    deque<long long> fifo;
    vector<long long> sorted;
    long long val;
    in.open("input");
    if (in.is_open()) {
        // read preamble
        for (int i = 0; i < PREAMBLE_SIZE; ++i) {
            in >> val;
            fifo.push_front(val);
            sorted.push_back(val);
        }
        // Preamble done.
        sort(sorted.begin(), sorted.end());
        // For each following number...
        while (in >> val) {
            if (valInLastRange(val, sorted)) {
                long long tmpVal = fifo.back();
                fifo.pop_back();
                fifo.push_front(val);
                auto it = find(sorted.begin(), sorted.end(), tmpVal);
                *it=val;
                sort(sorted.begin(), sorted.end());
            } else {
                cout << "invalid number: " << val << endl;
                break;
            }
        }
    }
}




void task2()
{
    ifstream in;
    vector<long long> numbers;
    long long val;
    in.open("input");
    if (in.is_open()) {
        while (in >> val) {
            numbers.push_back(val);
        }
    }
    bool done = false;
    int first = 0;
    int last = 0;
    long long target = 41682220;
    long long acc = numbers[0];
    while (! done) {
        last++;
        acc += numbers[last];
        if (acc > target) {
            acc -= numbers[last];
            last--;
            acc -=numbers[first];
            first++;
        } else if (acc == target) {
            cout << "Target found " << first << " : " << last << " ( " << numbers[first] << " " << numbers[last] << endl;
            sort(numbers.begin() + first, numbers.begin() + last + 1);
            long long res = numbers[first] + numbers[last];
            cout << "Weakness = " << res;
            done = true;
        }
    }
}


int main()
{
    task1();
    task2();
}
