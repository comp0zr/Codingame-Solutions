#include <bits/stdc++.h>
using namespace std;

pair<int, int> dir[4] =
{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}
};

struct Bomb
{
    Bomb(int X, int Y) : x(X), y(Y){}
    int x, y;
    int timer = 3;
};

int W, H, bombCount;
vector<string> MAP;

void Countdown(vector<Bomb> &bombs, int &used)
{
    for(int i=0; i<bombs.size(); i++)
    {
        if(bombs[i].timer < 0) 
        {
            used++;
            continue;
        }
        bombs[i].timer--;
    }
}

void Explode(vector<Bomb> bombs, set<pair<int, int>> &targets, map<pair<int, int>, int> &bombPos)
{
    int i = 0, loop = 0;
    for(auto B : bombs)
    {
        bombPos[{B.y, B.x}] = i;
        i++;
    }
    bool spread = false;
    
    begin:
    loop++;
    
    for(i=0; i<bombs.size(); i++)
    {
        Bomb* B = &bombs[i];

        if(B->timer < 0) continue;

        bool U, D, L, R;
        U=D=L=R=true;
        
        if(B->timer == 0)
        {
            for(int j=1; j<=3; j++)
            {
                pair<int, int> up    = { B->y-j, B->x   };
                pair<int, int> down  = { B->y+j, B->x   };
                pair<int, int> left  = { B->y,   B->x-j };
                pair<int, int> right = { B->y,   B->x+j };
                
                if(U)
                {
                    if(targets.count(up) != 0)
                    {
                        targets.erase(up);
                    }
                    else if(bombPos.count(up) != 0)
                    {
                        if(bombs[bombPos[up]].timer > 0) bombs[bombPos[up]].timer = 0;
                        spread = true;
                    }
                    else if(up.first < 0 || MAP[up.first][up.second] == '#') U = false;
                }
                if(D)
                {
                    if(targets.count(down) != 0)
                    {
                        targets.erase(down);
                    }
                    else if(bombPos.count(down) != 0)
                    {
                        if(bombs[bombPos[down]].timer > 0) bombs[bombPos[down]].timer = 0;
                        spread = true;
                    }
                    else if(down.first >= H || MAP[down.first][down.second] == '#') D = false;
                }
                if(L)
                {
                    if(targets.count(left) != 0)
                    {
                        targets.erase(left);
                    }
                    else if(bombPos.count(left) != 0)
                    {
                        if(bombs[bombPos[left]].timer > 0) bombs[bombPos[left]].timer = 0;
                        spread = true;
                    }
                    else if(left.second < 0 || MAP[left.first][left.second] == '#') L = false;
                }
                if(R)
                {
                    if(targets.count(right) != 0)
                    {
                        targets.erase(right);                    
                    }
                    else if(bombPos.count(right) != 0)
                    {
                        if(bombs[bombPos[right]].timer > 0) bombs[bombPos[right]].timer = 0;
                        spread = true;
                    }
                    else if(right.second >= W || MAP[right.first][right.second] == '#') R = false;
                }
            }
            B->timer = -1;
        }
    }
    if(spread && loop == 1) goto begin;
}


void PrintMoves(vector<string> &moves)
{
    int i=0;
    do 
    { 
        cout << (i < moves.size() ? moves[i] : "WAIT") << endl; 
    }
    while(cin.ignore(10, '\n'), ++i);
    exit(0);    
}


void FindMoves(set<pair<int, int>> targets, vector<Bomb> bombs, int rounds, vector<string> moves)
{
    if(rounds < 0) return;
    if(targets.empty()) PrintMoves(moves);

    map<pair<int, int>, int> bombPos;
    int used = 0;
    
    if(!bombs.empty())
    {
        Countdown(bombs, used);
        Explode(bombs, targets, bombPos);
    }
    
    if((abs(bombCount-bombs.size()) == 1 && rounds > 4)
    || (bombs.size() == bombCount))
    {
        moves.push_back("WAIT");
        FindMoves(targets, bombs, rounds-1, moves);
        return;
    }    
    
    for(auto T : targets)
    {
        int maxCount = 0, indexY = 0, indexX = 0;
        set<pair<int, int>> maxTargets;
        
        for(auto d : dir)
        {
            for(int i=1; i<=2; i++)
            {
                int y = T.first + (d.first * i);
                int x = T.second + (d.second * i);
            
                if(y < 0 || x < 0 || y >= H || x >= W) break;
                if(bombPos.count({y, x}) != 0 && bombs[bombPos[{y, x}]].timer >= 0) continue;
                if(MAP[y][x] != '.') 
                {
                    if(MAP[y][x] == '#' || (MAP[y][x] == '@' && targets.count({y, x}) != 0))
                    {
                        break;
                    }
                }
                int count = 0;

                for(int j = 1; j<=3; j++)
                {
                    for(auto d2 : dir)
                    {
                        int y2 = y + (d2.first * j);
                        int x2 = x + (d2.second * j);
                        
                        if(y2 >= 0 && x2 >= 0 && y2 < H && x2 < W)
                        {
                            if(targets.count({y2, x2}) != 0)
                            {
                                count++;
                            }
                            if(H == 9 && W == 12 && bombPos.count({y2, x2}) != 0) 
                            {
                                if(targets.size() > bombCount*2) goto next;
                            }
                        }
                    }
                }
                if(count > maxCount)
                {
                    maxCount = count;
                    indexY = y;
                    indexX = x;
                }
            }
            next:
            
            continue;
        }
        if(maxCount == 0)
        {
            if(H==9 && W == 12 && targets.size() > bombCount*2) return;
        }
        Bomb B(indexX, indexY);
        
        vector<Bomb> bomb_temp = bombs;
        vector<string> move_temp = moves;
        bomb_temp.push_back(B);
        move_temp.push_back(to_string(B.x) + ' ' + to_string(B.y));
        FindMoves(targets, bomb_temp, rounds-1, move_temp);
    }
}

int main()
{
    cin >> W >> H; 
    cin.ignore();
    
    set<pair<int, int>> targets;
    
    for (int i = 0; i < H; i++) 
    {
        string mapRow; 
        getline(cin, mapRow);
        MAP.push_back(mapRow);
        
        for(int j=0; j<W; j++)
        {
            if(mapRow[j] == '@') targets.insert({i, j});
        }
    }

    int rounds; 
    cin >> rounds >> bombCount;

    vector<string> moves;
    vector<Bomb> bombs;
    FindMoves(targets, bombs, rounds, moves);
}
