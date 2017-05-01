#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> dictionary, original;
vector<pair<string, int>> scores;
string answer;

int GetPoints(char c)
{
    if(c == 'e' || c == 'a' || c == 'i' || c =='o' || c == 'n' || c == 'r' || c == 't' || c == 'l' || c == 's' || c == 'u') return 1;          
    else if(c == 'd' || c == 'g') return 2;
    else if(c == 'b' || c == 'c' || c == 'm' || c == 'p') return 3;
    else if(c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y') return 4;
    else if(c == 'k') return 5;
    else if(c == 'j' || c == 'x') return 8;
    else if(c == 'q' || c == 'z') return 10;
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    
    for (int i = 0; i < N; i++) 
    {
        string W;
        getline(cin, W);
        dictionary.push_back(W);
    }
    string LETTERS;
    getline(cin, LETTERS);
    
    original = dictionary;
    sort(dictionary.begin(), dictionary.end());
    sort(LETTERS.begin(), LETTERS.end());

    for(int i = 0; i < dictionary.size(); i++)
    {
        string s = LETTERS;        
        size_t found = s.find(dictionary[i][0]);

        if(found == string::npos) { continue; }
        else
        {
            int score = 0;
            string str = "";
            str += s[found];
            score += GetPoints(s[found]);
            s.erase(found, 1);
            
            for(int j = 1; j < dictionary[i].length(); j++)
            {    
                found = s.find(dictionary[i][j]);

                if(found == string::npos) 
                { 
                    if(j == dictionary[i].length()-1) 
                    {
                        cerr << str << endl;
                        break;
                    }
                    else break; 
                }
                else 
                {
                    str += s[found];
                    score += GetPoints(s[found]);
                    s.erase(found, 1);
                }           
            }
            if(str == dictionary[i]) 
            {
                pair<string, int> p;
                p = make_pair(str, score);
                scores.push_back(p);
            }
        }       
    }
  
    int highestScore = 0, index;
    string bestWord;
    
    for(int i = 0; i < scores.size(); i++)
    {
        if(highestScore == 0 || scores[i].second > highestScore) 
        {
            highestScore = scores[i].second;
            bestWord = scores[i].first; 
            index = i;
        }
        else if(scores[i].second == highestScore)
        {
            for(int j = 0; j < original.size(); j++)
            {
                if(original[j] == scores[i].first) 
                {
                    bestWord = scores[i].first;
                    index = i;
                    break;
                }
                else if(original[j] == scores[index].first) 
                {
                    bestWord = scores[index].first;
                    break;   
                }
            }            
        }
    }
    answer = bestWord;
    cout << answer << endl;
}
