#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
map<string, unsigned long long int> index;
vector<string> lines(20);

void ConvertAnswer(unsigned long long int n, int height, int length)
{
    int levels;
    if(n>=1280000000) levels=8;
    else if(n>=64000000) levels=7;
    else if(n>=3200000) levels=6;
    else if(n>=160000) levels=5;
    else if(n>=8000) levels=4;
    else if(n>=400) levels=3;
    else if(n>=20) levels=2;
    else if(n>=1) levels=1;
    
    while(levels--)
    {
        int q = n/pow(20, levels);
        string s="";
        
        if(length==1)
        {
            s.assign(lines[q]);
            cout<<s<<endl;
            s.clear();
            n-=q*pow(20, levels);
            continue;
        }
        
        for(int i=0; i<lines[q].length(); )
        {
            s.assign(lines[q], i, height);
            cout<<s<<endl;
            s.clear();
            i+=height;
        }
        n-=q*pow(20, levels);
    }
}

int main()
{
    int L, H;
    cin >> L >> H; 
    string num1="", num2="";
    vector<vector<string>> nums(20, vector<string>(H));
    
    for (int i = 0; i < H; i++) 
    {
        string numeral;
        cin >> numeral;
        
        int count=0;
        string line = "";
        
        for(int j=0; j<numeral.length(); )
        {
            line.assign(numeral, j, L);
            nums[count][i]=line;
            lines[count]+=line;
            j+=L;
            count++;
        }
    }
    
    for(int z=0; z<lines.size(); z++) index[lines[z]]=z;
    
    int S1, S2, level1, level2, count=0;
    unsigned long long int a=0, b=0, x=0, y=0;
    cin >> S1; 
    level1=(S1/H)-1;

    for (int i = 0; i < S1; i++) 
    {
        string num1Line;
        cin >> num1Line;
        num1+=num1Line;
        count++;
        
        if(count==H)
        {
            x=index[num1];
            x*=(pow(20, level1));
            a+=x;

            count=0;
            level1--;
            num1.clear();
        }
    }

    cin >> S2; 
    level2=(S2/H)-1;
    count=0;

    for (int i = 0; i < S2; i++) 
    {
        string num2Line;
        cin >> num2Line;
        num2+=num2Line;
        count++;
        
        if(count==H)
        {
            y=index[num2];
            y*=(pow(20, level2));
            b+=y;

            count=0;
            level2--;
            num2.clear();
        }
    }
    string operation;
    cin >> operation; 

//////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned long long int arabic;
    
    if(operation=="+") arabic=a+b;
    else if(operation=="*") arabic=a*b;
    else if(operation=="-") arabic=a-b;
    else if(operation=="/") arabic=a/b;

    cerr<<"ANSWER: "<<arabic<<endl;
    
    if(arabic==0) 
    {
        int i=0;
        string s="";
        
        while(i<lines[0].length())
        {
            s.assign(lines[0], i, L);
            cout<<s<<endl;
            s.clear();
            i+=H;
        }
        return 0;
    }
    ConvertAnswer(arabic, H, L);
}
