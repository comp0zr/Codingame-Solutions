#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <forward_list>
#include <deque>
#include <utility>

using namespace std;

enum direction {DOWN=1, RIGHT, UP, LEFT};
int matrix[50][50];
int crank[50][50];

deque<int> ring;
vector<pair<int, int>> indices;

void MakeRing(pair<int, int> UL, pair<int, int> DL, pair<int, int> DR, pair<int, int> UR)
{
    direction dir;
    int y = UL.first, x = UL.second; 
    dir = DOWN;
    
    int i = 0;
    
    while(i < 4)
    {
        switch(i)
        {
        //  DOWN
            case 0: 
                while(y<DL.first)
                {
                    int num = matrix[y][x];
                    ring.push_back(num);
                    indices.push_back(make_pair(y, x));
                    y++;
                }
                break;
                
        //  RIGHT
            case 1:
                while(x<DR.second)
                {
                    int num = matrix[y][x];
                    ring.push_back(num);
                    indices.push_back(make_pair(y, x));
                    x++;
                }
                break;
            
        //  UP
            case 2:
                while(y>UR.first)
                {
                    int num = matrix[y][x];

                    ring.push_back(num);
                    indices.push_back(make_pair(y, x));
                    y--;
                }
                break;
                
        //  LEFT
            case 3:
                while(x>UL.second)
                {
                    int num = matrix[y][x];

                    ring.push_back(num);
                    indices.push_back(make_pair(y, x));
                    x--;
                }
                break;
            }
        i++;
    }
}

int main()
{
    int W, H, X;
    cin >> W >> H >> X;
    
    int midX, midY;
    midX = (W%2==0) ? (W/2) - 1 : W/2;
    midY = (H%2==0) ? (H/2) - 1 : H/2;
    
    for(int i = 0; i < H; i++) 
    {
        for(int j = 0; j < W; j++) 
        {
            int v;
            cin >> v; cin.ignore();
            matrix[i][j] = v;
        }
        cerr << endl;
    }
    
    int x = 0, y = 0, xIndex = 0, yIndex = 0, rotateNum = 0, xTarget = W-1, yTarget = H-1;

    while(1)
    {
        pair<int, int> UL = make_pair(yIndex, xIndex),      // UL
        DL = make_pair(yTarget, xIndex),                    // DL
        DR = make_pair(yTarget, xTarget),                   // DR
        UR = make_pair(yIndex, xTarget);                    // UR
            
        cerr << "X START: " << xIndex << "\nY START: " << yIndex << "\nX Target: " << xTarget << "\nY Target: " << yTarget << endl << endl;

        MakeRing(UL, DL, DR, UR);
    
        while(rotateNum < X)
        {
            ring.push_front(ring.back());
            ring.pop_back();
            rotateNum++;
        }    
        for(int i = 0; i < indices.size(); i++)
        {
            matrix[indices[i].first][indices[i].second] = ring[i];
        }
        ring.clear();
        indices.clear();
        rotateNum = 0;
        
        xIndex++;
        yIndex++;
        xTarget--;
        yTarget--;
        
        if(yIndex >= yTarget || xIndex > xTarget)
        {
            break;
        }
    }
    
    for(int i = 0; i < H; i++)
    {
        for(int j = 0; j < W; j++)
        {
            cout << matrix[i][j];
            if(j < W-1) cout << ' ';
        }
        cout << endl;
    }
}
