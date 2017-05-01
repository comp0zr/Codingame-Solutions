#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
stringstream ss;

vector<int> Conway(vector<int> vec)
{
    vector<int> newVec;
    
    for(int i=0; i<vec.size(); )
    {
        int count=0, num=vec[i];
        
        if(i!=vec.size()-1 && vec[i] == vec[i+1])
        {
            int j=i;
            
            while(j<vec.size() && vec[j]==num)
            {
                count++;
                j++;
            }
            i=j;
            newVec.push_back(count);
            newVec.push_back(num);    
            continue;
        }
        else count=1;
        
        newVec.push_back(count);
        newVec.push_back(num);
        i++;
    }
    return newVec;
}

int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();
    vector<int> vec(1), conway;
    
    vec[0] = R;
    
    if(L==1)
    {
        cout<<R<<endl;
        return 0;
    }
    while(--L)
    {
        conway.clear();
        conway=Conway(vec);
        vec = conway;
    }
    
    for(int i=0; i<conway.size(); i++)
    {
        cout<<conway[i];
        if(i==conway.size()-1) cout<<endl;
        else cout<<' ';
    }
}
