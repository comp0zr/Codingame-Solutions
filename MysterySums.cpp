#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;


map<int, vector<int>> mystery;
set<int> mysteryIndices;

set<string> ops =
{
    "+", "-", "*", "/"
};

void Solve(vector<string> parts)
{
    int ans = 0;
    vector<int> nums;
    string op = "?";
    
    for(int i=0; i<parts.size(); i++)
    {
        if(ops.count(parts[i]) != 0)
        {
            op = parts[i];
        }
        else if(parts[i] == "=")
        {
            if(ans == stoi(parts[i+1]))
            {
                for(int j=0; j<parts.size(); j++)
                {
                    cout << parts[j];
                    if(j < parts.size()-1) cout << ' ';
                    else cout << endl;
                }
                exit(0);
            }
        }
        else
        {
            nums.push_back(stoi(parts[i]));
            
            if(op != "?")
            {
                if(op == "+") 
                {
                    ans = (nums[0] + nums[1]);
                }
                if(op == "-") 
                {
                    ans = (nums[0] - nums[1]);
                    
                    nums.clear();
                    nums.push_back(ans);
                    continue;
                }
                if(op == "*") ans = (nums[0] * nums[1]);
                if(op == "/" && nums[1] != 0)
                {
                    if(nums[0] % nums[1] != 0) return;
                    
                    ans = (nums[0] / nums[1]);
                }
            }
        }
    }
}

void FindAnswer(vector<string> parts, pair<int, int> lastChanged = {-1, -1})
{
    Solve(parts);
    
    vector<int> indices(mysteryIndices.rbegin(), mysteryIndices.rend());
    
    for(auto it : indices)
    {
        vector<string> temp = parts;

        if(it < lastChanged.first) continue;
        
        while(mystery[it][0] != '9')
        {
            int it2 = mystery[it].back();
            
            if(lastChanged != make_pair(it, it2))
            {
                while(temp[it][it2] < '9')
                {
                    if(temp[indices.back()][mystery[indices.back()].back()] != '9')
                    {
                        vector<string> temp2 = temp;
                        temp2[indices.back()][mystery[indices.back()].back()]++;
                        FindAnswer(temp2, {it, -1});
                    }
                    temp[it][it2]++;
                    lastChanged = {it, lastChanged.second};
                    FindAnswer(temp, lastChanged);
                }
                if(mystery[it].size() > 1)
                {
                    if(temp[it][mystery[it][0]] == '9') 
                    {
                        lastChanged = {it, it2};
                        break;
                    }
                    
                    temp[it][mystery[it][0]]++;
                    temp[it][it2] = '0';
                    FindAnswer(temp, lastChanged);
                }
            }
        }
    }
}

int main()
{
    string expression;
    getline(cin, expression);

    string s = "";
    vector<string> parts;
    
    for(int i=0; i<=expression.length(); i++)
    {
        if(i==expression.length() || expression[i] == ' ')
        {
            if(s.find('?') != string::npos)
            {
                mysteryIndices.insert(parts.size());
                
                for(int j=0; j<s.length(); j++)
                {
                    if(s[j] == '?')
                    {
                        mystery[parts.size()].push_back(j);
                        s[j] = (j==0) ? '1' : '0';
                    }
                }
            }
            parts.push_back(s);
            s.clear();
            continue;
        }
        s += expression[i];         
    }
    FindAnswer(parts);
}
