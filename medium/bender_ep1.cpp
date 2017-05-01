#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;


vector<string> map;
vector<string> path;

enum directions {SOUTH=1, EAST, NORTH, WEST};

directions FindDirection(directions dir, int posX, int posY, bool checked, bool inversion)
{
    directions newD;
    directions nextDir;
    char c;
        
    if(checked)
    {
        if(inversion)
        {
            if(dir == SOUTH) nextDir = WEST;
            else nextDir = directions(dir-1);
        }
        else
        {
            if(dir == WEST) nextDir = SOUTH;
            else nextDir = directions(dir+1);   
        }
    }
    else nextDir = (inversion) ? WEST : SOUTH;

    if(nextDir == SOUTH)
    {
        c = map[posY+1][posX];
        
        if(c == 'X' || c == '#') 
        {
            if(inversion) return WEST; 
            return EAST;
        }
        else return SOUTH;
    }
    else if(nextDir == 2) 
    {
        c = map[posY][posX+1];

        if(c == 'X' || c == '#') 
        {
            if(inversion) return SOUTH; 
            return NORTH;
        }
            
        else return EAST;
    }
    else if(nextDir == 3) 
    {
        c = map[posY-1][posX];
        
        if(c == 'X' || c == '#') 
        {
            if(inversion) return EAST; 
            return WEST;
        }
        else return NORTH;
    }
    else if(nextDir == 4) 
    {
        c = map[posY][posX-1];
        
        if(c == 'X' || c == '#') 
        {
            if(inversion) return NORTH; 
            return SOUTH;
        }
        else return WEST;
    }    
}

void Teleport(int* currX, int* currY)
{   
    for(int i = 0; i < map.size(); i++)
    {
        size_t found = map[i].find("T");
        
        if(found != string::npos)
        {
            if(i == *currY && found == *currX) continue;
            else 
            {
                *currY = i;
                *currX = (int)found;
                return;
            }
        }
        else continue;
    }    
}

void PrintDirections(bool debug)
{
    for(int i = 0; i < path.size(); i++)
    {
        if(debug) cerr << path[i] << endl;
        else cout << path[i] << endl;
    }    
}


int main()
{
    int L;
    int C;
    cin >> L >> C; cin.ignore();
    bool foundStart, breakerMode, teleported, isLoop, inverted;
    
    int startRow;
    
    size_t start;
    
    for (int i = 0; i < L; i++) 
    {
        string row;
        getline(cin, row);
        map.push_back(row);
        
        if(!foundStart)
        {
            size_t s = row.find("@");
            
            if(s == string::npos) continue;
            else
            {
                startRow = i;
                start = s;
                foundStart = true;
            }
        }
    }
    int pos[2] = {startRow, start}, prevPos[2];
    directions d;
    d = SOUTH;
            
    while(1)
    {
        if(path.size() > 10000) { isLoop = true; }
        if(isLoop) { cout << "LOOP" << endl; return 0; }
        bool checked, inversion;
        char current = map[pos[0]][pos[1]];
                
        if(current == '$')
        {
            PrintDirections(false);
            return 0;
        }
        else if(current == 'I' && !inverted)
        {
            inversion = (inversion) ? false : inversion = true;
            inverted = true;
        }
        else if(current == 'T' && !teleported)
        {
            int* ptrY = &pos[0];
            int* ptrX = &pos[1];
            Teleport(ptrX, ptrY);
            teleported = true;            
            continue;
        }
        else if(current == 'S') d = SOUTH; 
        else if(current == 'E') d = EAST; 
        else if(current == 'N') d = NORTH; 
        else if(current == 'W') d = WEST; 
        else if(current == 'B') 
        { 
            if(pos[0] == prevPos[0] && pos[1] == prevPos[1])
            {
                prevPos[0] = -1;
                prevPos[1] = -1;
            }
            else
            {
                breakerMode = (breakerMode) ? false : true; 
                prevPos[0] = pos[0];
                prevPos[1] = pos[1];
            }
        }
        else if(inverted) inverted = false; 
        
        teleported = false; 
               
        switch(d)
        {
            case SOUTH:
            
                for(int i = 0; ; i++)
                {
                    char c = map[pos[0]+1][pos[1]];                
                    
                    if(c == '#' || c == 'X')
                    {                        
                        if(c == 'X' && breakerMode)
                        {
                            map[pos[0]+1][pos[1]] = '_';
                            path.push_back("SOUTH");
                            pos[0]++;
                        }
                        else
                        {
                            d = FindDirection(d, pos[1], pos[0], checked, inversion);
                            checked = true;
                        }
                        break;
                    }
                    
                    path.push_back("SOUTH");
                    pos[0]++;
                    checked = false;
                    break;
                }
                break;
        
            case EAST:
            
                for(int i = 0; ; i++)
                {
                    char c = map[pos[0]][pos[1]+1];
                                    
                    if(c == '#' || c == 'X')
                    {                        
                        if(c == 'X' && breakerMode)
                        {
                            map[pos[0]][pos[1]+1] = '_';
                            path.push_back("EAST");
                            pos[1]++;
                        }
                        else
                        {
                            d = FindDirection(d, pos[1], pos[0], checked, inversion);
                            checked = true;
                        }
                        break;
                    }                 
                    pos[1]++;
                    path.push_back("EAST");       
                    checked = false;
                    break;
                }
                break;
                
             case NORTH:
            
                for(int i = 0; ; i++)
                {
                    char c = map[pos[0]-1][pos[1]];                
                    
                    if(c == '#' || c == 'X')
                    {                        
                        if(c == 'X' && breakerMode)
                        {
                            map[pos[0]-1][pos[1]] = '_';
                            path.push_back("NORTH");
                            pos[0]--;
                        }
                        else
                        {
                            d = FindDirection(d, pos[1], pos[0], checked, inversion);
                            checked = true;
                        }
                        break;
                    }
                    
                    path.push_back("NORTH");
                    pos[0]--;   
                    checked = false;
                    break;
                }
                break;
                
            case WEST:
            
                for(int i = 0; ; i++)
                {
                    char c = map[pos[0]][pos[1]-1];
                    
                    if(c == '#' || c == 'X')
                    {                        
                        if(c == 'X' && breakerMode)
                        {
                            map[pos[0]][pos[1]-1] = '_';
                            path.push_back("WEST");
                            pos[1]--;
                        }
                        else
                        {
                            d = FindDirection(d, pos[1], pos[0], checked, inversion);
                            checked = true;
                        }
                        break;
                    }
                    
                    pos[1]--;
                    path.push_back("WEST");
                    checked = false;
                    break;
                }
                break;                
        }   
    }
}
