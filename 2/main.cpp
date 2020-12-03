#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream in;
    char dash, colon;
    struct passwd {
        string passwd;
        char specialChar;
        int minVal;
        int maxVal;
    };

    size_t cnt;
    int num1Ok=0;
    int num2Ok=0;
    int num1Fail=0;

    in.open("input");
    if (in.is_open()) {
        int i = 0;
        struct passwd pwd;
        vector<struct passwd> passwords;
        while (in >> pwd.minVal >> dash >> pwd.maxVal >> pwd.specialChar >> colon >> pwd.passwd) {
            passwords.push_back(pwd);
        }

        for (vector<struct passwd>::iterator it = passwords.begin(); it != passwords.end(); ++it) {
            cout << it->minVal << " " << it->maxVal << " " << it->specialChar << " " << it->passwd << endl;   
            cnt = count(it->passwd.begin(), it->passwd.end(), it->specialChar);
            if (cnt >= it->minVal && cnt <= it->maxVal)
                {
                    num1Ok++;
                }
            else
                {
                    num1Fail++;
                }
            cnt=0;
            if (it->passwd[it->minVal - 1] == it->specialChar) {cnt++;}
            if (it->passwd[it->maxVal - 1] == it->specialChar) {cnt++;}

            if (cnt == 1) {
                num2Ok++;
            }
        }
    }
    cout << "Total: " << num1Ok + num1Fail << " Num1OK: " << num1Ok << " Num2OK: " << num2Ok << endl;
}


