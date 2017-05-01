#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> lines;
    int W, H;
    cin >> W >> H; 

    for (int i = 0; i < H; i++) 
    {
        string LINE; 
        getline(cin, LINE);
        lines.push_back(LINE);
    }
    int EX; 
    cin >> EX; 
    
    while (1) 
    {
        int XI;
        int YI;
        int nextY, nextX; 
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();
        
        int x = 0;
        string room = "";
        
        for(int i = 0; i < lines[YI].length(); i++)
        {
            if(lines[YI][i] == ' ') { continue; }
            else if (x == XI) 
            { 
                room += lines[YI][i];  
                if(lines[YI][i+1] != ' ') room += lines[YI][i+1];
                break;
            }
            else if(lines[YI][i+1] != ' ') { continue; } 
            else x++;
        }
        int roomNum = atoi(room.c_str());

        switch(roomNum) 
        {
            case 0:
                break;
                
            case 1:
                if(POS == "TOP") { nextY = YI+1; nextX = XI; }
                else if(POS == "LEFT") { nextY = YI+1; nextX = XI; }
                else if(POS == "RIGHT") { nextY = YI+1; nextX = XI; }
                break;
                
            case 2:
                if(POS == "LEFT") { nextY = YI; nextX = XI+1; }
                else if(POS == "RIGHT") { nextY = YI; nextX = XI-1; }
            
            case 3:
                if(POS == "TOP") { nextY = YI+1; nextX = XI; }
                break;
            
            case 4:
                if(POS == "TOP") { nextY = YI; nextX = XI-1; }
                else if(POS == "RIGHT") { nextY = YI+1; nextX = XI; }
                break;
                
            case 5:
                if(POS == "TOP") { nextY = YI; nextX = XI+1; }
                else if(POS == "LEFT") { nextY = YI+1; nextX = XI; }
                break;
                                
            case 6:
                if(POS == "LEFT") { nextY = YI; nextX = XI+1; }
                else if(POS == "RIGHT") { nextY = YI; nextX = XI-1; }
                break;                
                
            case 7:
                if(POS == "TOP") { nextY = YI+1; nextX = XI; }
                else if(POS == "RIGHT") { nextY = YI+1; nextX = XI; }
                break;
            
            case 8:
                if(POS == "LEFT") { nextY = YI+1; nextX = XI; }
                else if(POS == "RIGHT") { nextY = YI+1; nextX = XI; }
                break;

            case 9:
                if(POS == "TOP") { nextY = YI+1; nextX = XI; }
                else if(POS == "LEFT") { nextY = YI+1; nextX = XI; }
                break;
                
            case 10:
                if(POS == "TOP") { nextY = YI; nextX = XI-1; }
                break;
            
            case 11:
                if(POS == "TOP") { nextY = YI; nextX = XI+1; }
                break;

            case 12:
                if(POS == "RIGHT") { nextY = YI+1; nextX = XI; }
                break;
            
            case 13:
                if(POS == "LEFT") { nextY = YI+1; nextX = XI; }
                break;           
        }
        cout << nextX << ' ' << nextY << endl;
    }
}
