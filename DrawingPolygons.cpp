#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cw=0, ccw=0;

int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<pair<int, int>>polygon(N);
    
    for (int i = 0; i < N; i++) 
    {
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        
        if(i<=N/2)
        {
            if(x >= polygon[i-1].first) cw++;
            else ccw++;
        }
        else 
        {
            if(x <= polygon[i-1].first) cw++;
            else ccw++;
        }
        polygon[i] = pair<int, int>(x, y);
    }
    if(polygon.back().second > polygon.front().second) ccw++;
    if(polygon.back().first > polygon.front().first) ccw++;
    
    if(cw > ccw) cout<<"CLOCKWISE"<<endl;
    else cout<<"COUNTERCLOCKWISE"<<endl;
}
