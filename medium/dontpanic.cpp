#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int nbFloors; // number of floors
    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    vector<int> elevators(nbFloors);
    vector<bool> blocks(nbFloors);
    vector<int> blockPos(nbFloors);
    fill(blocks.begin(), blocks.end(), false);
    
    for (int i = 0; i < nbElevators; i++) 
    {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        elevators[elevatorFloor] = elevatorPos;
    }

    cerr << "Exit: F" << exitFloor << ", P" << exitPos << endl; 
    
    while (1) 
    {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        
        cerr << "Clone floor: " << cloneFloor << "\nClone position: " << clonePos << endl;
        
        if(clonePos==width-1 || clonePos==0) 
        {
            cout << "BLOCK" << endl;
        }
        else if(elevators[cloneFloor] != 0)
        {
            if(!blocks[cloneFloor])
            {
                blocks[cloneFloor]=true; 
                blockPos[cloneFloor]=clonePos;
                
                if(clonePos<elevators[cloneFloor] && direction=="LEFT" 
                || clonePos>elevators[cloneFloor] && direction=="RIGHT") 
                {
                    cout << "BLOCK" << endl;
                    if(cloneFloor>1) continue;
                }
            }
        }
        else if(cloneFloor == exitFloor && exitFloor != 0)
        {
            if(!blocks[cloneFloor])
            {
                if(clonePos<exitPos && direction=="LEFT") cout << "BLOCK" << endl;
                else if(clonePos>exitPos && direction=="RIGHT") cout << "BLOCK" << endl;
                
                blocks[cloneFloor]=true; 
            }
        }
        cout << "WAIT" << endl;
    }
}
