#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    int one = 1;
    int i = 0, r = -1, index = -1;
    
    string ans = "", sub = "";
    set<int> rem;

    while(r != 0)
    {
        if(n > one)    
        {
            one *= 10;
        }
        
        int next = (int)floor(one / n);
        int prod = next * n;
        
        if(index == -1) ans += to_string(next);
        else sub += to_string(next);
        
        one -= prod;
        r = one % n;
        
        if(r == index)
        {
            ans = ans.substr(0, ans.find(sub));
            sub = "(" + sub + ")";
            break;
        }
        
        if(rem.count(r) != 0)
        {
            if(ans.front() == ans.back())
            {
                ans.pop_back();
                ans = "(" + ans + ")";
                break;
            }
            if(index == -1) index = r;
        }
        rem.insert(r);
        ++i;
    }
    cerr << ans << " | " << sub << endl;
    cout << "0." << ans << sub << endl;
}
