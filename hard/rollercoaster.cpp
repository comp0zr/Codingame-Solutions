#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

vector<int> indices;
vector<pair<long long int, int>> M;

void MakeTable(deque<long int> line, int maxPlaces)
{
    int i=0;
    deque<long int> line2 = line;
    M.reserve(indices.size());

    while(i<line.size())
    {
        long long int peeps = 0; 
        int index = 0;

        while(index < line2.size())
        {
            peeps += line.back();
            line.push_front(line.back());
            line.pop_back();
            index++;

            if(peeps + line.back() > maxPlaces) break;
        }
        int nextIndex = i + index;
 
        if(nextIndex >= line2.size())
        {
            nextIndex = (nextIndex-line2.size());
        }
        
        M[i] = pair<long long int, int>(peeps, nextIndex);
        i++;
        line2.push_front(line2.back());
        line2.pop_back();
        line = line2;
    }    
}

int main()
{
    int maxPlaces, maxRuns, groups;
    scanf("%d %d %d", &maxPlaces, &maxRuns, &groups);
    deque<long int> line;
   
    for (int i = 0; i < groups; i++) 
    {
        long int people;
        scanf("%ld", &people);
        line.push_front(people);
        indices.push_back(i);
    }
    
    MakeTable(line, maxPlaces);
    
    unsigned long long int money=0;
    int run=0, index=0;
    
    while(run < maxRuns)
    {
        money += M[index].first;
        index = M[index].second;
        run++;
    }
    printf("%llu\n", money);
}
