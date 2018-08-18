#include <bits/stdc++.h>
using namespace std;

pair<int, int> dir[4] =
{
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}
};

map<pair<int, int>, char> direction =
{
    {{ 1, 0}, 'v'},
    {{ 0, 1}, '>'},
    {{-1, 0}, '^'},
    {{ 0,-1}, '<'}
};

struct Node
{
    Node(int X, int Y) : x(X), y(Y){}
    int x, y;
    Node* next = NULL;
    Node* root = NULL;
};


int W, H;
vector<string> MAP;
map<pair<int, int>, set<vector<pair<int, int>>>> M;
set<pair<int, int>> tees;


void FindPath(Node* node, int shots, pair<int, int> d)
{
    if(MAP[node->y][node->x] == 'H')
    {
        vector<pair<int, int>> P;
        Node* check = node->root;

        while(check != NULL)
        {
            P.push_back({check->y, check->x});
            check = check->next;
        }
        M[{node->root->y, node->root->x}].insert(P);
        delete check;
        return;
    }
    if(shots == 0) return;
    
    for(int i=0; i<shots; i++)
    {
        int x = node->x + d.second;
        int y = node->y + d.first;
    
        if(x >= W || y >= H || x < 0 || y < 0) return;
    
        node->next = new Node(x, y);
        node->next->root = node->root;
        node = node->next;
    }
    
    if(MAP[node->y][node->x] == 'X') return;
    
    for(auto d2 : dir)
    {
        if((direction[d] == '<' && direction[d2] == '>') 
        ||(direction[d] == '>' && direction[d2] == '<')
        ||(direction[d] == '^' && direction[d2] == 'v')
        ||(direction[d] == 'v' && direction[d2] == '^')) continue;
        Node* nextNode = node;
        FindPath(nextNode, shots-1, d2);
    }
}

void Answer(set<pair<int, int>> &T, vector<string> &newMap)
{
    if(T.empty())
    {
        for(auto it : newMap)
        {
            for(auto c : it)
            {
                cout << (c == '*' ? '.' : c);
            }
            cout << endl;
        }
        exit(0);
    }
    
    pair<int, int> it = *T.begin();

    for(auto path : M[it])
    {
        set<pair<int, int>> t_temp = T;
        vector<string> m_temp = newMap;

        for(int i=0; i<path.size(); i++)        
        {
            if(i == path.size()-1) 
            {
                if(MAP[path[i].first][path[i].second] == 'H') 
                {
                    m_temp[path[i].first][path[i].second] = '*';
                    t_temp.erase(it);
                    Answer(t_temp, m_temp);
                }
                break;
            }
            if(newMap[path[i+1].first][path[i+1].second] != '.') break;

            pair<int, int> xy = {0, 0}; 
            
            if(path[i+1].first > path[i].first) xy.first++;
            else if(path[i+1].first < path[i].first) xy.first--;
            
            if(path[i+1].second > path[i].second) xy.second++;
            else if(path[i+1].second < path[i].second) xy.second--;
            
            m_temp[path[i].first][path[i].second] = direction[xy];
        }
    }
}



int main()
{
    cin >> W >> H;
    
    for(int i = 0; i < H; i++) 
    {
        string row;
        cin >> row; 
        MAP.push_back(row);
    }
    
    for(int i=0; i<H; i++)
    {
        for(int j=0; j<W; j++)
        {
            if(isdigit(MAP[i][j]))
            {
                tees.insert({i, j});
                
                for(auto d : dir)
                {
                    Node* root = new Node(j, i);
                    root->root = root;
                    FindPath(root, MAP[i][j] - '0', d);
                    delete root;
                }
            }
        }
    }
    vector<string> newMap(H, string(W, '.'));
    Answer(tees, newMap);
}
