#include <bits/stdc++.h>
using namespace std;

map<pair<long long, long long>, long long> memo;


long long GetStaircase(long long int start, long long int bricks)
{
    if(memo.count({start, bricks}) != 0)
    {
        return memo[{start, bricks}];
    }
    long long result = 1;
    
    for(int i=floor(bricks/2); i>start; i--)
    {
        if(i == bricks - i) continue;

        int l = i;
        int r = bricks - i;
        int partial = floor(r / 2);

        long long sum = 1;

        if(partial > i) 
        {
            if(r - partial == partial) 
            {
                partial--;
                l++;
            }
            if(i+1 < (r - partial + abs(partial - (i+1))) / 2)
            {
                sum += GetStaircase(i, bricks-i) - 1;
            }
            else sum += abs(partial - i);
        }
        result += sum;
    }
    memo[{start, bricks}] = result;
    return result;
}


int main()
{
    int N;
    cin >> N;
    
    long long ans = 0;
    
    for(int i=1; i<=floor(N/2); i++)
    {
        if(i == N-i) continue;
        
        ans += GetStaircase(i, N-i);
    }
    cout << ans << endl;
}
