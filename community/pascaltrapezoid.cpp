#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string Numbers(string a, string b)
{
    unsigned long long num_a = stoull(a);
    unsigned long long num_b = stoull(b);
    
    return to_string(num_a + num_b); 
}


int main()
{
    int E, L, N;
    cin >> E >> L >> N; cin.ignore();
    
    string start;
    getline(cin, start);
    
    int found = start.find(' ');
    int index = 1;
    vector<string> curr;
    
    while(curr.size() < E)
    {
        curr.push_back(start.substr(0, found));
        start = start.substr(found+1);
        found = start.find(' ');
    }
    
    if(N == 1)
    {
        cout << curr.front() << endl;
        return 0;
    }

    if(N > L)
    {
        if((N + 1 - L) % E == 0)
        {
            cout << curr.back() << endl;
            return 0;
        }        
        
        int limit = (N+1)-L;
        
        if(limit == E-1)
        {
            while(1)
            {
                vector<string> next;
                string a = curr[curr.size()-2];
                string b = curr.back();
                
                if(a.find_first_not_of("0123456789") == string::npos && b.find_first_not_of("0123456789") == string::npos)
                {
                    next.push_back(Numbers(a, b));
                }            
                else next.push_back(a + b);
                
                if(index == L-1) 
                {
                    cout << next.back() << endl;
                    return 0;
                }
                next.push_back(curr.back());
                curr = next;
                index++;
            }
        }
    }
    
    while(index < L)
    {
        vector<string> next;
        next.reserve(N);
        next.push_back(curr[0]);
        
        for(int i = 1; i<curr.size(); i++)
        {
            if(i >= N) break;
            
            string a = curr[i-1], b = curr[i];
            
            if(a.find_first_not_of("0123456789") == string::npos && b.find_first_not_of("0123456789") == string::npos)
            {
                next.push_back(Numbers(a, b)); 
                
                if(index == L-2 && next.size() == N) 
                {
                    cout << Numbers(next[next.size()-2], next.back()) << endl;
                    return 0;
                }
            }
            else
            {
                next.push_back(a + b);
                
                if(index == L-2 && next.size() == N) 
                {
                    cout << next[next.size()-2] + next.back() << endl;
                    return 0;
                }                
            }
        }
        if(next.size() < N) next.push_back(curr.back());
        curr = next;
        index++;
    }
}
