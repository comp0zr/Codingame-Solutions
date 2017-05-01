#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>

using namespace std;

multimap<int, pair<int, int>> M;

int Path(int a, int b, int total)
{
    pair<multimap<int, pair<int, int>>::iterator, multimap<int, pair<int, int>>::iterator> it; 
    it = M.equal_range(b);
    
    if(M.count(b)==0)
    {
        return total+1;
    }
    else
    {
        multimap<int, pair<int, int>>::iterator x = it.first;

        int i=x->second.first, j=x->second.second;
        M.erase(x);
        total = Path(i, j, total+1);
    }
}

int main()
{
    int n;
    cin>>n;
    vector<pair<int, int>> pairs(n);    

    for(int i=0; i<n; i++)
    {
        int a, b;
        cin>>a>>b;
        pairs[i]=make_pair(a, b);
        
        M.insert(pair<int, pair<int, int>>(a, pairs[i]));
    }
    sort(pairs.begin(), pairs.end());
    
    int count=0, max=0;
    multimap<int, pair<int, int>> M2=M;
    
    for(int x=0; x<pairs.size(); x++)
    {
        count = Path(pairs[x].first, pairs[x].second, 1);
        if(count>max) max=count;
        M=M2;
    }
    cout<<max<<endl;
}
