#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
    int N;
    cin >> N; cin.ignore();
    map<string, int> prefix;

    for (int i = 0; i < N; i++) 
    {
        string telephone;
        cin >> telephone; cin.ignore();
        string pre = "";
        
        for(int j=0; j<telephone.length(); j++)
        {
            pre+=telephone[j];
            prefix[pre]++;
        }
    }
    cout<<prefix.size()<<endl;
    return 0;
}
