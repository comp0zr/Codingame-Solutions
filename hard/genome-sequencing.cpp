#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

int minLength = 999999;
set<string> allSubs;


bool IsValid(string S)
{
    for(auto it : allSubs)
    {
        cerr << "\t--" << S.find(it) << endl;
        
        if(S.find(it) == string::npos) return false;
    }
    return true;
}


void ShortestSupersequence(string S, vector<string> subs)
{
    if(subs.empty() && IsValid(S))
    {
        if(S.length() < minLength)
        {
            minLength = S.length();
            cerr << S << endl;
            cerr << S.length();
            cerr << "\n===========\n";
        }
    }

    for(int i=0; i<subs.size(); i++)
    {
        string s = subs[i];
        
        if(S.find(s) <= S.length()-s.length()) 
        {
            vector<string> temp = subs; 
            temp.erase(temp.begin() + i);

            ShortestSupersequence(S, temp);               
        }
        
        for(int j=0; j<s.length(); j++)
        {
            string pre = s.substr(0, j+1);
            string suff = s.substr(pre.length());

            cerr << "P = " << pre << " | S = " << suff << endl;

            if(S.find(suff) == 0)
            {
                vector<string> temp = subs; 
                temp.erase(temp.begin() + i);

                ShortestSupersequence(pre + S, temp);
            }
            
            if(S.find(pre) == S.length()-pre.length())
            {
                vector<string> temp = subs; 
                temp.erase(temp.begin() + i);
                
                ShortestSupersequence(S + suff, temp);                
            }
            else 
            {
                string s2 = "";
                string found = "";
                
                for(int k=0; k<pre.length(); k++)
                {
                    s2 += pre[k];

                    if(S.find(s2) != string::npos)
                    {
                        found = pre.substr(s2.length());
                    }
                    else break;
                }
                
                if(!found.empty()) 
                {
                    vector<string> temp = subs; 
                    temp.erase(temp.begin() + i);                    
                    
                    ShortestSupersequence(S + found, temp);
                }
            }
        }
    }
}


int main()
{
    int N;
    cin >> N; 
    
    vector<string> subs(N);
    
    for(int i = 0; i < N; i++) 
    {
        string subseq;
        cin >> subseq; 
        allSubs.insert(subseq);
        subs[i] = subseq;
    }
    
    sort(subs.begin(), subs.end(), [](string a, string b) 
    {
        return (a.length() < b.length());
    });
    
    
    if(subs.size() == 1) 
    {
        cout << subs[0].length() << endl;
        return 0;
    }
    if(subs.size() == 2)
    {
        if(subs[1].find(subs[0]) != string::npos)
        {
            cout << subs[1].length() << endl;
            return 0;
        }
    }
    ShortestSupersequence(subs.back(), subs);

    cout << minLength << endl;
    return 0;
}
