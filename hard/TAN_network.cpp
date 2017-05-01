#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>
#include <map> 

using namespace std;

struct Stop
{
    string id;
    string name;
    
    double lat;
    double lon;
};


map<string, set<string>> adj;
map<string, Stop> stopFromID;
map<pair<string, string>, double> travelDistance;
set<string> stopIDs;


double deg2rad(double d)
{
    return d * M_PI / 180.0;
}


long double GetDistance(string A, string B)
{
    double lat_a = deg2rad(stopFromID[A].lat), long_a = deg2rad(stopFromID[A].lon);
    double lat_b = deg2rad(stopFromID[B].lat), long_b = deg2rad(stopFromID[B].lon);    
 
    double d_x = (long_b - long_a) * cos((lat_a + lat_b) / 2),
           d_y = (lat_b - lat_a);
    
    return sqrtf((d_x*d_x) + (d_y*d_y)) * 6371;
}



string LowestDistance(set<string> &unsettled, string &source, map<string, double> &dist)
{
    string lowest;
    double minDist = 99999999999.999999;
    
    for(auto it : unsettled)
    {
        if(dist[it] < minDist)
        {
            minDist = dist[it];
            lowest = it;
        }
    }
    return lowest;
}



void Dijkstra(string S, string E)
{
    bool possible = false;
    
    map<string, double> dist;
    map<string, string> prev;
    set<string> unsettled, settled;
    
    for(auto s : stopIDs)
    {
        dist[s] = 999999999.9999;
        prev[s] = "-";
        
        unsettled.insert(s);
        
        if(adj[s].count(E) != 0) possible = true;
    }
    dist[S] = 0;

    while(!unsettled.empty())
    {
        string node = LowestDistance(unsettled, S, dist);

        if(node == E)
        {
            vector<string> path;
            string n = node;
            
            while(prev.count(n) != 0)
            {
                path.push_back(n);
                n = prev[n];
            }
            reverse(path.begin(), path.end());
            
            if(path.front() != S)
            {
                cout << "IMPOSSIBLE" << endl;
                exit(0);
            }
            
            for(auto it : path)
            {
                cout << stopFromID[it].name << endl;
            }
            exit(0);
        }

        settled.insert(node);
        unsettled.erase(node);
        
        for(auto it : adj[node])
        {
            if(settled.count(it) == 0)
            {
                double newDistance = dist[node] + travelDistance[{node, it}];
                
                if(dist[it] > newDistance)
                {
                    dist[it] = newDistance;
                    
                    prev[it] = node;
                    unsettled.insert(it);
                }
            }
        }
    }
    cout << "IMPOSSIBLE" << endl;
    exit(0);
}



int main()
{
    string start, end;
    int N, M;
    
    cin >> start >> end >> N; cin.ignore();
    
    for (int i = 0; i < N; i++) 
    {
        string stopInfo;
        getline(cin, stopInfo);
        
        size_t found1 = stopInfo.rfind('\"'),
               found2 = stopInfo.find_first_of("123456789-", found1),
               found3 = stopInfo.find(',', found2),
               found4 = stopInfo.find_last_of("1234567890-");
        
        Stop s 
        {
            stopInfo.substr(9, 4),
            stopInfo.substr(15, found1-15),
            stold(stopInfo.substr(found2, found3 - found2)), // - (found1 + 3))),
            stold(stopInfo.substr(found3 + 1, found4 - found3))
        };
        stopIDs.insert(s.id);
        stopFromID[s.id] = s;
    }    
    cin >> M; cin.ignore();
    
    for(int i = 0; i < M; i++) 
    {
        string route;
        getline(cin, route);
        
        string A = route.substr(9, 4),
               B = route.substr(23, 4);
        
        adj[A].insert(B);
        travelDistance[{A, B}] = GetDistance(A, B);
    }

    if(start == end)
    {
        cout << stopFromID[start.substr(9, 4)].name << endl;
        return 0;
    }
    Dijkstra(start.substr(9, 4), end.substr(9, 4));
}
