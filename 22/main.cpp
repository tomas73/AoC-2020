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


void getCardsFromInput(ifstream &input, vector<int> &deck)
{
    string player;
    int tmp;
    int number;
    char colon;
    input >> player >> number >> colon;
    while (input >> number) {
        deck.push_back(number);      
    };
    input.clear();
}
void printDeck(vector<int> deck) {
    cout << "Deck:" << endl;
    for (auto it = deck.begin(); it != deck.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

bool playRound(vector<int> &a, vector<int> &b)
{
    int ac,bc;

    ac=a.front();
    a.erase(a.begin());
    bc=b.front();
    b.erase(b.begin());
    if (ac > bc) {
        a.push_back(ac);
        a.push_back(bc);
    } else {
        b.push_back(bc);
        b.push_back(ac);
    }
    if ((a.size() == 0) || (b.size() == 0)) {
        return false;
    }else{
        return true;
    } 
}

unsigned long long deckScore(vector<int> deck)
{
    unsigned long long score = 0;
    int mult=deck.size();
    for ( auto it = deck.begin(); it != deck.end(); ++it) {
        score = score + (mult * *it);
        mult -= 1;
    }
    return score;
}

string deckScore2(vector<int> deck)
{

    stringstream ss;
    int mult=deck.size();
    for ( auto it = deck.begin(); it != deck.end(); ++it) {
        ss << *it << ",";
    }
    return ss.str();
}


int playGame(int gameNo, vector<int> &p1, vector<int> &p2)
{
    int size=p1.size() + p2.size();
    cout << "GAME " << gameNo << ", " << size << " Cards in play" << endl;
    int winner = 0;
    int ac,bc;
    string sa, sb;
    set<string> hist1, hist2;
    int cnt = 0;
    while (true) {
        cnt++;
        // This was not very clear in the instructions, I had && and did not
        // get the correct result
        sa=deckScore2(p1);
        sb=deckScore2(p2);
        if ((hist1.find(sa) != hist1.end()) || (hist2.find(sb) != hist2.end())) {
            winner=1;
            cout << "LOOP! P1 wins " << gameNo << " " << cnt << " " << sa << endl;
            break;
        }
        hist1.insert(sa);
        hist2.insert(sb);
        //
        // Draw cards
        ac=p1.front();
        p1.erase(p1.begin());
        bc=p2.front();
        p2.erase(p2.begin());

        // Booth able to recurse? -> winner of round is determined by sub game
        if ((p1.size() >= ac) && (p2.size() >= bc)) {
            vector<int>d1,d2;
            for (int i = 0; i < ac; i++) {
                d1.push_back(p1.at(i));
            }

            for (int i = 0; i < bc; i++) {
                d2.push_back(p2.at(i));
            }

            winner=playGame(gameNo + 1, d1, d2);    
        } else {
            // Not able to recurse -> highest card wins
            if (ac > bc) {
                winner = 1;
            } else {
                winner = 2;
            }
        }
        //
        // Present the cards to the winner
        if ( winner == 1) {
            p1.push_back(ac);
            p1.push_back(bc);
        } else {
            p2.push_back(bc);
            p2.push_back(ac);
        }
        //
        // Are one plyer out of cards? -> Game over, winner is player with
        // cards
        if (p1.size() == 0) {
            winner=2;
            cout << "P1 out of cards, P2 Wins " << cnt << endl;
            break;
        }
        if (p2.size() == 0) {
            winner = 1;
            cout << "P2 out of cards, P1 Wins " << cnt << endl;
            break;
        }
    };
    if (winner < 1 || winner > 2) {
        cout << "ERROR";
        exit(1);
    }
    cout << "End of game " << gameNo << " " << cnt << "Winner: " << winner << endl;
    return winner;
}

unsigned long long task1(void)
{
    unsigned long long res = 0;
    //string input = "traininginput";
    string input = "input";
    //string input = "imptest";
    ifstream in;
    string line;
    unsigned long occurs = 0;    
    vector<int> p1, p2;
    in.open(input);
    if (in.is_open()) {

        getCardsFromInput(in, p1);
        getCardsFromInput(in, p2);
    }
    cout << "Initial:" << endl;
    printDeck(p1);
    printDeck(p2);
    // save for Task2
    vector<int> d1=p1;
    vector<int> d2=p2;

    while (playRound(p1,p2)) {;};
    cout << "After: " << endl;
    printDeck(p1);
    printDeck(p2);

    cout << "P1: " << deckScore(p1) << endl;
    cout << "P2: " << deckScore(p2) << endl;


    // Ok, time for task2
    int winner=playGame(1, d1, d2);
    cout << "Winner is: " << winner << endl;
    cout << "P1: " << deckScore(d1) << endl;
    cout << "P2: " << deckScore(d2) << endl;

    return 0;
}
int main()
{
    unsigned long long res1 = task1();
    cout << "Task 1 = " << res1 <<endl;
    return 0;
}

