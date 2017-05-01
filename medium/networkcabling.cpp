#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <set>

using namespace std;

int FindMedian(vector<pair<int, int>> building)
{
    vector<int> yVals(building.size());
    for(int i=0; i<building.size(); i++) yVals[i] = building[i].second;
    
    sort(yVals.begin(), yVals.end());
    
    long sz = building.size();
    long median = (sz%2==0) 
                ? (yVals[sz/2] + yVals[(sz/2)-1])/2 
                : (yVals[((sz+1)/2)-1]);
    
    return median;
}


int main()
{
    int N;
    cin >> N;
    
    vector<pair<int, int>> building(N);
    
    for (int i = 0; i < N; i++) 
    {
        int X;
        int Y;
        cin >> X >> Y; cin.ignore();
        building[i] = make_pair(X, Y);
    }
    sort(building.begin(), building.end());
    long int median = FindMedian(building), total=0;

    for(int i=0; i<N; i++)
    {
        total += abs(median-building[i].second);
        if(i < N-1) total += abs(building[i+1].first-building[i].first);
    }
    cout<<total<<endl;
}
