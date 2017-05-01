#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum alignment { LEFT = 1, RIGHT, CENTER, JUSTIFY };

int main()
{
    vector<string> t, t2;
    alignment a;
    string align;
    getline(cin, align);
    
    if(align == "LEFT") a = LEFT;
    else if(align == "RIGHT") a = RIGHT;
    else if(align == "CENTER") a = CENTER;
    else if(align == "JUSTIFY") a = JUSTIFY;
    
    int N;
    cin >> N; cin.ignore();
    
    int length, longest = -1;
    
    for (int i = 0; i < N; i++) 
    {
        string text;
        getline(cin, text);
        t.push_back(text);
        length = text.length();
        
        if(length > longest || longest == -1) longest = length;
        
    }    
    int i = 0;
    size_t pos = 0;
    
    while(i < N)
    {
        string s = t[i];
        int diff = longest - t[i].length();

        switch(a)
        {
            case LEFT:
                t2.push_back(t[i]);
                i++;
                break;
                
            case RIGHT:
                s.insert(0, diff, ' ');
                t2.push_back(s);
                i++;
                break;
            
            case CENTER:
                diff /= 2;
                s.insert(0, diff, ' ');
                t2.push_back(s);
                i++;
                break;
                
            case JUSTIFY:
                int l = t[i].length();
                int spaceCount = 0;
                diff = longest-l;

                for(int j = 0; j < s.length(); j++)
                {
                    if(s[j] == ' ')
                    {
                        spaceCount++;
                    }
                }
                cerr << "LENGTH: " << l << endl;
                cerr << "SPACES: " << spaceCount << endl;
                cerr << "DIFFERENCE = " << diff << endl << endl;
                
                if(diff == 0) t2.push_back(t[i]);
                else
                {
                    int k = 0;
                    
                    while(spaceCount < diff)
                    {
                        if(s[k] == ' ')
                        {
                            s.insert(k, 2, ' ');
                            spaceCount++;
                            k+=2;
                        }
                        k++;
                    }
                    t2.push_back(s);
                }
                i++;
                break;
        }
    }
    for(int i = 0; i < t2.size(); i++)
    {
        cout << t2[i] << endl;
    }
}
