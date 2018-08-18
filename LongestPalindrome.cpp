#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s; 
    
    vector<string> ans;
    int largest = 0;
    
    for(int i = 0; i<s.length(); i++)
    {
        for(int even = 0; even < 2; even++)
        {
            int L = (even == 0) ? i-1 : i;
            int R = i;
            
            string pal = "";
            
            while(L >= 0 && R < s.length() && s[L] == s[R])
            {
                if(s[L] == s[R])
                {
                    if(L != R) 
                    {
                        pal.insert(pal.begin(), s[L]);
                    }
                    pal += s[R];
                }
                L--, R++;
            }
            
            if(pal.size() > largest)
            {
                ans.clear();
                largest = pal.size();
                ans.push_back(pal);
                pal.clear(); 
            }
            else if(pal.size() == largest)
            {
                ans.push_back(pal);
            }
        }
    }
    
    sort(begin(ans), end(ans), [&](string a, string b) 
    { 
        if(a.length() == b.length())
        {
            return s.find(a) < s.find(b);
        }
        return a < b;
    });
 
    for(auto it : ans) cout << it << endl;
}
