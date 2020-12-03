#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool ascending(int i, int j) { return (i < j); }
bool decending(int i, int j) { return (i > j); }


int main() {
    ifstream in;
    in.open("input");

    vector<int> asc,desc;
    int element;
    if (in.is_open())
        {
            int i = 0;
            while (in >> element) {
                asc.push_back(element);
                desc.push_back(element);
            }
        }
    sort(asc.begin(), asc.end(), ascending);
    sort(desc.begin(), desc.end(), decending);

    cout << "Size : " << asc.size();
    cout << "Size : " << desc.size();

    for (vector<int>::iterator it=asc.begin(); it!=asc.end() ; ++it) {
        cout << ' ' << *it;
    }
    cout << '\n';

    for (vector<int>::iterator it=desc.begin(); it!=desc.end() ; ++it) {
        cout << ' ' << *it;
    }
    cout << '\n';

    for (vector<int>::iterator itd=desc.begin(); itd!=desc.end() ; ++itd) {
        for (vector<int>::iterator ita=asc.begin(); ita!=asc.end() ; ++ita) {
            int sum2 = (*itd + *ita);
            cout << "\nRES: " << *itd << " + " << *ita << " = " << sum2 << '\n';
            if (*itd + *ita > 2020) {
                break;
            }

            int rest = 2020 - sum2;
            for (vector<int>::iterator ita2=asc.begin(); ita2!=asc.end() ; ++ita2) {
                int sum3 = (sum2 + *ita2);
                int res = *ita * *itd * *ita2;
                cout << "\nRES: " << sum2 << " + " << *ita2 << " = " << sum3 << " => " << res;
                if ((sum2 + *ita2) == 2020) {
                    cout << "\nRES: " << sum2 << " + " << *ita2 << " = " << (sum2 + *ita2) << " => " << res << '\n';
                    exit(0);
                }
                if (sum3 > 2020) {
                    break;
                }
            }
        }
    }
}
