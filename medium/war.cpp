#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;
queue<int> reserve_p1, reserve_p2;

vector<int> GetCards(int total)
{
    vector<int> cards(total);
    
    for(int i=0; i<total; i++)
    {
        string s;
        int num;
        cin>>s;
        
        if(s[0]=='A') num=14;
        else if(s[0]=='K') num=13;
        else if(s[0]=='Q') num=12;
        else if(s[0]=='J') num=11;
        else if(s[0]=='1' && s[1]=='0') num=10;
        else num=s[0]-'0';
        
        cards[i]=num;
    }
    return cards;
}


void RotateDeck(int player, vector<int>& deck)
{
    queue<int> reserve = (player==1) ? reserve_p1 : reserve_p2;
    
    while(reserve.size()!=0)
    {
        deck.push_back(reserve.front());
        reserve.pop();
    }
    (player==1) ? reserve_p1=reserve : reserve_p2=reserve;
}


int Battle(vector<int>& P1, vector<int>& P2, int& p1_index, int& p2_index)
{
    int i = p1_index, j = p2_index;
    
    while(P1[i]==P2[j])
    {
        i+=4; j+=4;
        
        if(i>=P1.size())
        {
            if(reserve_p1.size()<(i-P1.size())) return 3;
            RotateDeck(1, P1);
        }
        if(j>=P2.size())
        {
            if(reserve_p2.size()<(j-P2.size())) return 3;
            RotateDeck(2, P2);
        }
    }
    
    if(P1[i]>P2[j])
    {
        for(int x=p1_index; x<=i; x++) reserve_p1.push(P1[x]);
        for(int x=p2_index; x<=j; x++) reserve_p1.push(P2[x]);
    }
    else if(P2[j]>P1[i])
    {
        for(int x=p1_index; x<=i; x++) reserve_p2.push(P1[x]);
        for(int x=p2_index; x<=j; x++) reserve_p2.push(P2[x]);
    }
    p1_index=i;
    p2_index=j;
    return 0;
}


int main()
{
    int cards_p1, cards_p2;
    cin>>cards_p1;
    vector<int> P1 = GetCards(cards_p1);   
    
    cin>>cards_p2;
    vector<int> P2 = GetCards(cards_p2);
    
    int winner=0, p1_index=0, p2_index=0, rounds=0;
    
    while(winner==0)
    {
        int c1=P1[p1_index], c2=P2[p2_index];

        if(c1>c2)
        {
            reserve_p1.push(c1);
            reserve_p1.push(c2);
        }
        else if(c2>c1)
        {
            reserve_p2.push(c1);
            reserve_p2.push(c2);
        }
        else if(c1==c2) winner = Battle(P1, P2, p1_index, p2_index);
        
        p1_index++;
        p2_index++;
        rounds++;
        
        if(p1_index==P1.size())
        {
            if(reserve_p1.size()==0)
            {
                winner=2;
                break;
            }
            P1.clear();
            RotateDeck(1, P1);
            p1_index=0;
        }
        
        if(p2_index==P2.size())
        {
            if(reserve_p2.size()==0)
            {
                winner=1;
                break;
            }
            P2.clear();
            RotateDeck(2, P2);
            p2_index=0;
        }
    }
    if(winner==1) cout<<1<<' '<<rounds<<endl;
    else if(winner==2) cout<<2<<' '<<rounds<<endl;
    else if(winner==3) cout<<"PAT"<<endl;
}
