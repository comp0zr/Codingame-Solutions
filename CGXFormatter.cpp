#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

string invalid = "()\t ";
vector<string> CGX;

bool quote = false;
int index;
int indentLevel = 0;



void Reformat(string s)
{
    string str = "";
    
    for(int i=0; i<s.length(); i++)
    {
        char c = s[i];
        string indent(indentLevel*4, ' ');
        
        if(c == '\\' && s[i+1] == 't')
        {
            str += "    ";
            i++;
            continue;
        }
        
        if(quote)
        {
            str += c;
            if(c != '\'') continue;
        }
        else if(invalid.find(c) == string::npos) str += c;
        
        
        switch(c)
        {
            case '\'':
            {
                if(str.empty())
                {
                    cout << indent << str;
                    str.clear();
                    str = "\'";
                }
                quote = !quote;
                break;
            }
            
            case '(':
            {
                if(!str.empty())
                {
                    cout << indent << str << endl;
                    str.clear();
                }
                indentLevel++;
                cout << indent << '(' << endl;
                break;
            }
            
            case ')':
            {
                if(!str.empty())
                {
                    cout << indent << str << endl;
                    str.clear();
                }
                indentLevel--;
                
                if(indent.length() > 4) indent = indent.substr(4);
                else indent.clear();
                
                if(i < s.length()-1)
                {
                    size_t found = s.find_first_not_of(" ", i+1);
                    
                    if(s[found] == ';')
                    {
                        cout << indent << ");" << endl;
                        i = s.find_first_not_of(" ", i+1);
                    }
                    else cout << indent << ')' << endl;
                }
                else cout << indent << ')' << endl;
                
                break;
            }
            
            case ';':
            {
                cout << indent << str << endl;
                str.clear();
                break;       
            }
        }
    }
    string indent(indentLevel*4, ' ');
    
    if(!str.empty()) 
    {
        cout << indent << str;
        
        if(str.back() != '=') cout << endl;
        else if (index < CGX.size()-1)
        {
            string next = CGX[index+1];
            size_t found = next.find_first_not_of(" ");
            if(next[found] == '(') cout << endl;
        }
    }
}


int main()
{
    int N;
    cin >> N; cin.ignore();
    CGX.resize(N);
    
    for (int i = 0; i < N; i++) 
    {
        string CGXLine;
        getline(cin, CGXLine);
        CGX[i] = CGXLine;
    }
    for(auto s : CGX)
    {
        Reformat(s);
        index++;
    }
}
