#include <bits/stdc++.h>
using namespace std;

map<int, int> M;

int main()
{
    int n;
    cin >> n; 
    
    vector<string> skyline(200, string(5001, '.'));
    skyline[199] = string(5001, '_');

    for(int i = 0; i < n; i++)
    {
        int h, x1, x2;
        cin >> h >> x1 >> x2; 

        M[x1] = max(M[x1], h);
        skyline[200-h].replace(x1, abs(x2-x1), abs(x2-x1), '_');
    }
    
    int y = 199,
        x = 0,
        lines = 0;

    while(x <= 5000)
    {
        if(M.count(x) != 0)
        {
            int top = 200 - M[x];
            
            if(y > top)
            {
                lines += 2;
                y = top;
            }
        }        
        else if(skyline[y][x] == '.')
        {
            while(skyline[y][x] == '.')
            {
                y++;
            }
            lines += 2;
        }
        x++;
    }
    cout << lines - 1 << endl;
}
