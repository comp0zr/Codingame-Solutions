#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <set>

using namespace std;

bool EarliestFinish(pair<int, int> a, pair<int, int> b)
{
    if(a.second == b.second)
    {
        return (a.first < b.first);
    }
    return a.second < b.second;
}


int main()
{
    int calculations;
    scanf("%d", &calculations);  
    
    pair<int, int> times[calculations];
    
    for(int i=0; i<calculations; i++)
    {
        scanf("%d %d", &times[i].first, &times[i].second);
        times[i].second+=times[i].first;
    }
    sort(times, times+calculations, EarliestFinish);
    int count=0, length=sizeof(times)/sizeof(pair<int, int>);
    
    for(int i=0; i<length; i++)
    {
        int end = times[i].second;

        for(int j=i+1; j<length; j++)
        {
            if(times[j].first >= end) 
            {
                count++;
                i=j-1;
                break;
            }
        }
    }
    printf("%d\n", count+1);
    return 0;
}
