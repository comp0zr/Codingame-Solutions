#include <bits/stdc++.h>
using namespace std;

pair<int, int> dir[4] =
{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}
};


int W, H;
int startY, startX, endY, endX;

vector<string> MAP;
vector<vector<set<vector<int>>>> neighbors[2];

map<char, string> valid =
{
    {'.',".-|OX"},
    {'+', "+-|X"},
    {'X',   ".+"},
    {'-',   ".+"},
    {'|',   ".+"},
    {'O',    "."}
};

void GetNeighbors(int level)
{
    vector<string> map = MAP;
    
    for(int i=1; i<H-1; i++)
    {
        for(int j=1; j<W-1; j++)
        {
            char tile = map[i][j];
            
            for(auto d : dir)
            {
                int y = i + d.first;
                int x = j + d.second;
                char next = map[y][x];
                
                if(valid[tile].find_first_of(next) == string::npos) continue;
                
                switch(tile)
                {
                    case '.':
                        if((next == '-' && y != i) || (next == '|' && x != j)) break;
                        neighbors[level][i][j].insert({level, y, x});
                        break;
                    
                    case '-':
                        if(y != i) break;
                        else if(next == '+') neighbors[level][i][j].insert({1, y, x});
                        else if(next == '.') neighbors[level][i][j].insert({0, y, x});
                        break;
                    
                    case '|':
                        if(x != j) break;
                        else if(next == '+') neighbors[level][i][j].insert({1, y, x});
                        else if(next == '.') neighbors[level][i][j].insert({0, y, x});
                        break;
                    
                    case 'X':
                        neighbors[level][i][j].insert({level, y, x});
                        break;
                    
                    case 'O':
                        neighbors[level][i][j].insert({0, y, x});
                        break;
                    
                    case '+':
                        if(level != 1) break;
                        neighbors[level][i][j].insert({1, y, x});
                        break;
                }
            }
        }
    }
}

int shortest = 999999;

void FindPath(int level, int i, int j, set<vector<int>> vis)
{
    if(vis.size() >= shortest) return;
    
    if(level == 0 && i == endY && j == endX)
    {
        if(vis.size() < shortest)
        {
            shortest = vis.size();
        }
        return;
    }
    
    for(auto N : neighbors[level][i][j])
    {
        int l = N[0];
        int y = N[1];
        int x = N[2];
        
        if(vis.count({l, y, x}) != 0) continue;
        
        set<vector<int>> temp = vis;
        temp.insert({l, y, x});
        FindPath(l, y, x, temp);
    }
}


int main()
{
    cin>>startY>>startX;
    cin>>endY>>endX;
    cin>>H>>W;
    
    neighbors[0].resize(H);
    fill(neighbors[0].begin(), neighbors[0].end(), vector<set<vector<int>>>(W));
    neighbors[1] = neighbors[0];
    
    for(int i=0; i<H; i++)
    {
        string row;
        cin >> row;
        
        MAP.push_back(row);
    }
    GetNeighbors(0);
    GetNeighbors(1);
    FindPath(0, startY, startX, {});

    cout << shortest << endl;
}
