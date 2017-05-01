#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, C;
    cin >> N >> C;
    
    vector<int> budget(N);
    int total=0;
    
    for (int i = 0; i < N; i++) 
    {
        cin >> budget[i];
        total+=budget[i];
    }
    if(total<C) 
    {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    
    sort(budget.begin(), budget.end());
    
    for(int i=0; i<N; i++)
    {
        int mean = C/(N-i);
        cerr<<"mean = "<<mean<<endl;
        
        if(mean>budget[i]) 
        {
            C-=budget[i];
        }
        else 
        {
            budget[i]=mean;
            C-=budget[i];
        }
    }
    for(int x=0; x<N; x++) cout<<budget[x]<<endl;
}
