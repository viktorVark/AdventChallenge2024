#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "guard.cpp"
using namespace std;

int main(){
    string line;
    int line_count{0};
    ifstream inputFile("input.txt");
    Guard guard;
    vector<string> lab_map;
    bool in_bounds{true};
    int distinct_positions{0};
    string map_after;

    
    //initial position and direction
    //filling vector with playing field
    while(getline(inputFile, line)){
        if(line.find('^') < line.size()){
            guard.set_positions(line.find('^'), line_count);
            guard.set_direction('^');
        }

        lab_map.push_back(line);
        line_count++;
    }
    inputFile.close();


    //moving guard by rules
    while(in_bounds){
        //cout << guard.display_guard() << endl;
        in_bounds = guard.move_guard(lab_map);
    }


    cout << "The map after the guard left:\n\n";

    //counting the number of distint positions
    for(string line: lab_map){

        map_after += line + "\n";

        for(char c: line){
            if(c=='X'){
                distinct_positions++;
            }
        }
    }
    
    cout << map_after << endl;

    ofstream outputFile("output.txt");
    outputFile << map_after;
    outputFile.close();

    cout << "\n\n\nThe number of distinct positions is: \e[1m" + to_string(distinct_positions) + "\e[0m"<< endl;
    cout<<"Press Enter to exit..."; cin.get();
}
