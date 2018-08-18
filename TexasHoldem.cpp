#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstring>
#include <random>

using namespace std;

struct Card
{
    char val;
    char suit;
};

map<char, int> value =
{
    {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, 
    {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10},{'J', 11},{'Q', 12},
    {'K', 13},{'A', 14}
};

map<string, int> handValues =
{
    {"STRAIGHT_FLUSH", 9},
    {"FOUR_OF_A_KIND", 8},
    {"FULL_HOUSE", 7},
    {"FLUSH", 6},
    {"STRAIGHT", 5},
    {"THREE_OF_A_KIND", 4},
    {"TWO_PAIR", 3},
    {"PAIR", 2},
    {"HIGH_CARD", 1},
};

ostream& operator<<(ostream& os, const Card& C){ os << C.val << C.suit; return os;}

bool operator<(Card a, Card b)
{ 
    if(value[a.val] == value[b.val]) return a.suit < b.suit;
    
    if(a.suit == b.suit) return value[a.val] < value[b.val];
    else return value[a.val] < value[b.val];
}

vector<Card> P1, P2, COMM;
string player1Cards, player2Cards, community;

void GetCards()
{
    P1 =
    { 
        {player1Cards[0], player1Cards[1]}, 
        {player1Cards[3], player1Cards[4]} 
    };
    
    P2 =
    { 
        {player2Cards[0], player2Cards[1]}, 
        {player2Cards[3], player2Cards[4]} 
    };
    
    for(int i=0; i<community.length(); i+=3)
    {
        COMM.push_back(Card{community[i], community[i+1]});
    }
}


pair<string, vector<Card>> PossibleHands(vector<Card> player, vector<Card> community)
{
    vector<Card> combined = community;
    combined.insert(combined.end(), player.begin(), player.end());
    sort(combined.rbegin(), combined.rend());

    map<char, vector<int>> suitIndex;
    map<int, int> valueCount;
    map<string, vector<Card>> hands;

    int sameValueMax = -99999, sameSuitMax = 0; 
    char mostFrequentSuit, mostFrequentValue;
    
    for(auto it : combined) 
    {
        if(it.val == 'A') 
        {
            valueCount[1]++;
            Card C{'1', it.suit};
            combined.insert(combined.end(), C);
        }
        valueCount[value[it.val]]++;
        suitIndex[it.suit].push_back(value[it.val]);
        
        if(valueCount[value[it.val]] > sameValueMax)
        {
            sameValueMax = valueCount[value[it.val]];
            mostFrequentValue = it.val;
        }
    }

    string suits = "CDHS";
    
    for(char suit : suits)
    {
        if(suitIndex[suit].size() > sameSuitMax)
        {
            sameSuitMax = suitIndex[suit].size(); 
            mostFrequentSuit = suit;
        }
    }
    
    int consecutiveVals = 1;
    int consecutiveSuits = 1;
    
    Card prev{'0','0'};
    vector<Card> winningCards, temp;

    int maxConsecutive = 0;
    
    for(Card C : combined)
    {
        if(prev.val != '0')
        {
            if(value[C.val] == value[prev.val] - 1) 
            {
                ++consecutiveVals;
                
                if(C.suit == prev.suit) ++consecutiveSuits;
                else consecutiveSuits = 1;
                
                if(winningCards.empty()) winningCards.push_back(prev);
                winningCards.push_back(C);
            }
            else 
            {
                consecutiveVals = 1;
                temp = winningCards;
                winningCards.clear();
            }
        }
        prev = C;
        maxConsecutive = max(consecutiveSuits, maxConsecutive);
    }
    if(temp.size() > winningCards.size()) winningCards = temp;
    
    if(winningCards.size() >= 5)
    {
        if(winningCards.size() > 5)
        {
            if(winningCards.back().val == '1') 
            {
                winningCards.erase(winningCards.begin());
            }
            else winningCards.resize(5);
        }
        if(maxConsecutive >= 5) return {"STRAIGHT_FLUSH", winningCards};
        else return {"STRAIGHT", winningCards};
    }
    
    if(sameSuitMax >= 5)
    {
        winningCards.clear();
        for(auto C : combined) if(C.suit == mostFrequentSuit) winningCards.push_back(C);

        hands.insert({"FLUSH", winningCards});
    }
    
    for(int i=14; i>=1; --i)
    {
        vector<Card> winningCards;
        
        if(valueCount[i] >= 4) 
        {
            for(auto C : combined) if(value[C.val] == i) winningCards.push_back(C);
            
            return {"FOUR_OF_A_KIND", winningCards};
        }
        if(valueCount[i] >= 3)
        {
            for(auto C : combined) if(value[C.val] == i) winningCards.push_back(C);
            
            for(int j=14; j>=1; --j)
            {
                if(i==j) continue;
                if(valueCount[j] == 2) 
                {
                    vector<Card> temp = winningCards;
                    for(auto C : combined) if(value[C.val] == j) temp.push_back(C);
                    
                    return {"FULL_HOUSE", temp};
                }
            }
            if(hands.count("FLUSH") != 0) return {"FLUSH", hands["FLUSH"]};
            else if(hands.count("STRAIGHT") != 0) return {"STRAIGHT", hands["STRAIGHT"]};
            else return {"THREE_OF_A_KIND", winningCards};
        }
        else if(valueCount[i] == 2)
        {
            for(auto C : combined) if(value[C.val] == i) winningCards.push_back(C);
            
            hands.insert({"PAIR", winningCards});

            for(int j=14; j>=1; --j)
            {
                if(i==j) continue;

                if(valueCount[j] == 2) 
                {
                    for(auto C : combined) if(value[C.val] == j) winningCards.push_back(C);
                    
                    if(hands.count("FLUSH") != 0) return {"FLUSH", hands["FLUSH"]};
                    else if(hands.count("STRAIGHT") != 0) return {"STRAIGHT", hands["STRAIGHT"]};                    
                    return{"TWO_PAIR", winningCards};
                }
            }
            if(hands.count("FLUSH") != 0) return {"FLUSH", hands["FLUSH"]};
            else if(hands.count("STRAIGHT") != 0) return {"STRAIGHT", hands["STRAIGHT"]};            
            return {"PAIR", hands["PAIR"]};
        }
    }
    return {"HIGH_CARD", {*max_element(combined.begin(), combined.end())}};
}


void GetBestHand(pair<string, vector<Card>> *(bestHand))
{
    P1.insert(P1.end(), COMM.begin(), COMM.end());
    P2.insert(P2.end(), COMM.begin(), COMM.end());
    
    sort(bestHand[0].second.rbegin(), bestHand[0].second.rend());
    sort(bestHand[1].second.rbegin(), bestHand[1].second.rend());
    sort(P1.rbegin(), P1.rend());
    sort(P2.rbegin(), P2.rend());
    
    for(int i=0; i<2; ++i)
    {
        int index = 0;
        
        while(bestHand[i].second.size() < 5) 
        {
            Card C = (i==0) ? P1[index] : P2[index];
            bool valid = true;
            
            for(auto it : bestHand[i].second)
            {
                if(it.val == C.val && it.suit == C.suit)
                {
                    valid = false;
                    break;
                }
            }
            if(valid) bestHand[i].second.push_back(C);
            ++index;
        }
    }        
}



void PrintWinner(int winner, string hand, vector<Card> cards)
{
    cout << winner << ' ' << hand << ' ';
    
    for(auto C : cards)
    {
        (C.val == '1') ? cout << 'A' : cout << C.val;
    }
    cout << endl;
    exit(0);
}



int main()
{
    getline(cin, player1Cards);
    getline(cin, player2Cards);
    getline(cin, community);
    GetCards();

    pair<string, vector<Card>> bestHand[2];
    bestHand[0] = PossibleHands(P1, COMM);
    bestHand[1] = PossibleHands(P2, COMM);

    int winner = (handValues[bestHand[0].first] > handValues[bestHand[1].first]) ? 1
               : (handValues[bestHand[1].first] > handValues[bestHand[0].first]) ? 2
                                                                                 : 0;
                                                                                 
    GetBestHand(bestHand);

    if(winner != 0) PrintWinner(winner, bestHand[winner-1].first, bestHand[winner-1].second);
    else
    {
        for(int i=0; i < 5; i++)
        {
            if(value[bestHand[0].second[i].val] > value[bestHand[1].second[i].val])
            {
                PrintWinner(1, bestHand[0].first, bestHand[0].second);
            }
            else if(value[bestHand[1].second[i].val] > value[bestHand[0].second[i].val])
            {
                PrintWinner(2, bestHand[1].first, bestHand[1].second);
            }
        }
        cout << "DRAW" << endl;
    }
}
