#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


char FindPalindromes(string word)
{
    bool even;
    int L=0, R=word.length()-1, count=0, mid_L, mid_R, diff=0;
    
    if(word.length() % 2 == 0)
    {
        even = true;
        mid_R = word.length()/2;
        mid_L = R-1;
    }
    else
    {
        even = false;
        mid_R = ceil(word.length()/2);
        mid_L = mid_R;
    }
    
    if(word.front() != word.back())
    {
        if(word[L+1]==word[R-1])
        {
            L++; 
            R--;
        }
        diff++;
    }
    
    while(R >= mid_R && L <= mid_L)
    {
        if(diff > 2) return '0';
        
        if(word[L] == word[R]) 
        {
            count++;
            L++;
            R--;            
            continue;
        }
        
        if(word[L] == word[R-1])
        {
            R--;
            diff++;
            mid_L--;
        }
        else if(word[R] == word[L+1])
        {
            L++;
            diff++;
            mid_R++;
        }
        else if(word[R-1] == word[L+1])
        {
            diff++;
            L++;
            R--;
        }
        else return '0';
    }
    if(even && count == word.length()/2) return '1';
    if(even && count == (word.length()/2)-1) return '1';
    if(!even && count >= ((word.length()+1)/2)-1) return '1';
    
    return '0';
}

int main()
{
    string answer = "";
    int N;
    cin >> N; cin.ignore();
    
    for (int i = 0; i < N; i++) 
    {
        string word;
        cin>>word;

        if(word.length()==1) 
        {
            answer += '1';
            continue;
        }
        else if(word.length()==2)
        {
            if(word[0] == word[1]) answer += '0';
            else answer += '1';
            continue;
        }
        else if(word.length()==3)
        {
            answer += '1';
            continue;
        }
        char ans = FindPalindromes(word);
        answer += ans;
    }
    cout<<answer<<endl;
}
