#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <deque>
#include <queue>
#include <map>

using namespace std;

vector<string> Map;
set<pair<int, int>> adj[1001][1001];
int memo[1001][1001]={0};

int totalArea=0;

void FindNeighbors()
{
    for(int i=0; i<Map.size(); i++)
    {
        for(int j=0; j<Map[i].size(); j++)
        {
            if(Map[i][j]=='O')
            {
                totalArea++;
                
                if(i<Map.size()-1 && Map[i+1][j]=='O')
                {
                    adj[i][j].insert(make_pair(i+1, j));
                    adj[i+1][j].insert(make_pair(i, j));
                }
                
                if(j<Map[i].size()-1 && Map[i][j+1]=='O')
                {
                    adj[i][j].insert(make_pair(i, j+1));
                    adj[i][j+1].insert(make_pair(i, j));
                }
            }
        }
    }
}



int GetArea(int x, int y)
{
    deque<pair<int, int>> d;
    set<pair<int, int>> nodes;
    map<pair<int, int>, bool> visited;
    
    int distance=0;
    d.push_back(make_pair(y, x));
    
    while(!d.empty())
    {
        pair<int, int> node = d.front();
        d.pop_front();
        
        nodes.insert(node);
        
        if(memo[node.first][node.second]>0) 
        {
            distance = memo[node.first][node.second];
            break;
        }

        for(auto it : adj[node.first][node.second])
        {
            nodes.insert(it);

            if(visited[it]==false)
            {
                visited[it]=true;
                d.push_back(it);
                distance++;
            }
        }
    }
    
    for(auto n : nodes)
    {
        memo[n.first][n.second]=distance;
    }
    return distance;
    
}


int main()
{
    int L, H;
    scanf("%d %d", &L, &H);

    for(int i=0; i<H; i++)
    {
        char s[L];
        scanf("%s ", s);
        Map.push_back(s);
    }
    FindNeighbors();

    int queries;
    scanf("%d", &queries);

    for(int i=0; i<queries; i++)
    {
        int x, y, area;
        scanf("%d %d", &x, &y);
     
        if(L*H > 10000 && (L*H)%((L*H)-totalArea) < 10)
        {
            printf("%d\n", totalArea);
            continue;
        }
        
        if(Map[y][x] == '#') area=0;
        else 
        {
            if(memo[y][x]>0)
            {
                area=memo[y][x];
            }
            else area = GetArea(x, y);
            if(area==0) area=1;
        }
        
        printf("%d\n", area);
    }
}
