#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int CheckFit(vector<string> shape, vector<string> rows, int l, int r)
{
    for(int i=0; i<shape.size(); i++)
    {
        int k = 0;
        for(int j=l; j<r; j++)
        {
            if(rows[i][j] == '*' && shape[i][k] == '*') 
            {
                return 0;     
            }
            if(rows[i][j] == '.' && shape[i][k] == '*') rows[i][j] = '*';
            k++;
        }
    }
    int count = 0;
    for(auto it : rows)
    {    
        if(std::count(it.begin(), it.end(), '*') == it.length()) count++;
    }
    return count;
}


bool CheckVertical(vector<string> field, int index, int l, int r)
{
    while(l < r)
    {
        for(int i=index-1; i>=0; i--)
        {
            if(field[i][l] == '*') return false;
        }
        l++;
    }
    return true;
}



int main()
{
    int SH, SW, FH, FW;
    cin >> SW >> SH;
    
    vector<string> shape(SH), field;
    for(int i=0; i<SH; i++) cin >> shape[i];
    
    cin >> FW >> FH;
    field.resize(FH);
    for(int i=0; i<FH; i++) cin >> field[i];
    
    int maxCleared = -9999, X=0, Y=0;
    
    for(int i=FH-SH; i >= 0; i--)
    {
        int space_l = field[i].find('.'), 
            space_r = field[i].find_first_not_of(".", space_l+1);
        
        if(space_r == -1) 
        {
            space_r = field[i].find_last_of(".")+1;
        }
        
        if(space_r - space_l >= SW)
        {
            vector<string> lines(SH);
            
            for(int j=0; j<SH; j++)
            {
                lines[j] = field[i+j];
            }
            
            while(space_l != space_r) 
            {
                int cleared = CheckFit(shape, lines, space_l, space_r);            
                
                if(!CheckVertical(field, i, space_l, space_r))
                {
                    space_l++;
                    continue;
                }
                if(cleared > maxCleared)
                {
                    Y = FH-i-1; 
                    X = space_l;
                    maxCleared = cleared;
                }
                space_l++;
            }
        }
    }
    cout << X << ' ' << Y << endl << maxCleared << endl;
}
