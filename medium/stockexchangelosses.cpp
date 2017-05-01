#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n; 
    long long int maxLoss = 0, maxNum = 0, value, v, prev;
    
    cin >> n; cin.ignore();

    for (int i = 0; i < n; i++) 
    {
        cin >> v; cin.ignore();
        if(v == prev) continue;
        if(v == value) continue;
        prev = v;
        
        if(v > maxNum) maxNum = v;
        
        long long int loss;
        loss = v-maxNum;        
                
        if(loss < maxLoss)
        {
            maxLoss = loss;
            value = v;
        }
    }
    cout << maxLoss << endl;
}
