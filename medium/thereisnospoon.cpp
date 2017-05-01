#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    vector<string> lines;
    
    for (int i = 0; i < height; i++) 
    {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        lines.push_back(line);
    }
    
    for(int i = 0; i < lines.size(); i++)
    {
        int current[2], right[2], bottom[2];
        current[1] = i;
        
        size_t nextRight, pos = 0;
        bool endLoop = false;
        
        if(width == 1) 
        {
            current[0] = 0;
            right[0] = -1;
            right[1] = -1;
            
            if(i == height-1) 
            {
                bottom[0] = -1; 
                bottom[1] = -1;
                endLoop = true;
            }
            else
            {
                bottom[0] = 0;
                bottom[1] = i+1;
            }           
            cout << current[0] << ' ' << current[1] << ' ' << right[0] << ' ' 
                 << right[1] << ' ' << bottom[0] << ' ' << bottom[1] << endl;  
            
            continue;
        }
        
        for(int j = 0; j < lines[i].length(); j++)
        {
            if(lines[i][j] == '.') continue;
            pos = j+1;
            current[0] = j;

            if(i < height-1)
            {
                for(int y = i; y <= lines.size()-1; y++)
                {
                    if(y > i && lines[y][j] == '0') 
                    { 
                        bottom[0] = j; 
                        bottom[1] = y;
                        break;
                    }
                    else                      
                    {
                        bottom[0] = -1; 
                        bottom[1] = -1; 
                    }           
                }
            }
            else { bottom[0] = -1; bottom[1] = -1; }
            
            nextRight = lines[i].find("0", pos);
            
            if(nextRight != string::npos) 
            {
                right[0] = nextRight;
                right[1] = i;
                pos = nextRight+1;
            }
            else if((nextRight == string::npos) || nextRight > 1000000) 
            {
                right[0] = -1;
                right[1] = -1;
                endLoop = true;
            }

            cout << current[0] << ' ' << current[1] << ' ' << right[0] << ' ' 
                 << right[1] << ' ' << bottom[0] << ' ' << bottom[1] << endl;  
        }
        
        if(i + 1 == lines.size()) break;
    }    
}
