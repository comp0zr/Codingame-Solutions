#include <bits/stdc++.h>
using namespace std;

set<string> expressions;
int K;

void GetExpressions(string s, string expression, int total)
{
    if(s.empty())
    {   
        if(total == K) 
        {
            expressions.insert(expression);
        }
        return;
    }
    
    for(int i=1; i<=s.length(); i++)
    {
        string num = s.substr(0, i);
        GetExpressions(s.substr(i), expression + '+' + num, total + stoi(num));
        GetExpressions(s.substr(i), expression + '-' + num, total - stoi(num));
    }
}


int main()
{
    string N;
    
    getline(cin, N);
    cin >> K; 
    
    for(int i=1; i<=N.length(); i++)
    {
        GetExpressions(N.substr(i), N.substr(0, i), stoi(N.substr(0, i)));
    }
    vector<string> ans(expressions.begin(), expressions.end());
    
    sort(ans.begin(), ans.end(), [](string a, string b)
    {
        int found1 = a.find_first_of("+-"), found2 = b.find_first_of("+-");
        int pos1, pos2;
        
        while(found1 != string::npos && found2 != string::npos)
        {
            pos1 = found1;
            pos2 = found2;
            
            if(pos1 != pos2)
            {
                return pos1 < pos2;
            }
            if(a[pos1] != b[pos2]) 
            {
                return (a[pos1] == '-');
            }
            found1 = a.find_first_of("+-", pos1+1);
            found2 = b.find_first_of("+-", pos2+1);
        }
    });
    
    for(int i = ans.size()-1; i>=0; i--)
    {
        cout << ans[i] << endl;
    }
}
