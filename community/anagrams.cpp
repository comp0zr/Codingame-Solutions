#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<char, int>> seconds, thirds, fourths;

int main()
{
    string phrase = "MLSOHYTA RMLESS";
    getline(cin, phrase);

    vector<int> lengths;
    phrase.push_back(' ');
    int x = 0;
    int y = 0;
    
    for(int i = 0; i < phrase.length(); i++)
    {
        int length;       
        x++;
                
        if(phrase[i] == ' ')
        {
            length = x-1;
            lengths.push_back(length);
            phrase.erase(i, 1);
            x = 0;
            i--;
            y++;
        }
    }
    vector<string> parts;
    x = lengths.size()-1;
    y = 0;
    
    string newPhrase = "";
    
    for(int j = 0; j < lengths.size(); j++)
    {
        string s;
        s.assign(phrase, y, lengths[x]);
        
        y = y+lengths[x];
        x--;
        newPhrase += s;
        
        if(j < lengths.size()-1) newPhrase += " ";
    }    
    phrase = newPhrase; 
    x=0;
    
    for(int i = 0; i < phrase.length(); i++)
    {
        pair<char, int> p;

        if(phrase[i] == 'D' || phrase[i] == 'H' || phrase[i] == 'L' || phrase[i] == 'P' || phrase[i] == 'T' || phrase[i] == 'X')
        {
            p = make_pair(phrase[i], i);
            fourths.push_back(p);
            x++;
        }
    }
        
    if(fourths.size() > 1)
    {
        x = fourths.size()-1;
        phrase[fourths[x].second] = fourths[x-1].first; 
        phrase[fourths[0].second] = fourths[x].first; 
       
        for(int j = 1; j < x; j++)
        {   
            phrase[fourths[j].second] = fourths[j-1].first;
        }
    }
    x = 0;
    
    for(int i = 0; i < phrase.length(); i++)
    {
        pair<char, int> p;

        if(phrase[i] == 'C' || phrase[i] == 'F' || phrase[i] == 'I' || phrase[i] == 'L' || phrase[i] == 'O' || phrase[i] == 'R' || phrase[i] == 'U') //|| phrase[i] == 'Y')
        {
            p = make_pair(phrase[i], i);
            thirds.push_back(p);
        }
    }
    
    x = thirds.size()-1;
    phrase[thirds[x].second] = thirds[0].first;    
    
    for(int j = x-1; j > -1; j--)
    {   
        phrase[thirds[j].second] = thirds[j+1].first;
        x--;
    }
    for(int i = 0; i < phrase.length(); i++)
    {
        pair<char, int> p;
        
        if(phrase[i] == 'B' || phrase[i] == 'D' || phrase[i] == 'F' || phrase[i] == 'H' || phrase[i] == 'J' || phrase[i] == 'L' || phrase[i] == 'N' || phrase[i] == 'P' || phrase[i] == 'R' || phrase[i] == 'T' || phrase[i] == 'V' || phrase[i] == 'X' || phrase[i] == 'Z')
        {
            p = make_pair(phrase[i], i);
            seconds.push_back(p);
            x++;
        }
    }   
    x = seconds.size()-1;
    
    for(int j = 0; j < seconds.size(); j++)
    {   
        phrase[seconds[j].second] = seconds[x].first;
        x--;
    }  
    cout << phrase << endl;  
}
