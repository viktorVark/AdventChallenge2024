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
    int init_x, init_y;
    char init_dir;

    
    //initial position and direction
    //filling vector with playing field
    while(getline(inputFile, line)){
        if(line.find('^') < line.size()){
            init_x = line.find('^');
            init_y = line_count;
            init_dir = '^';
        }

        lab_map.push_back(line);
        line_count++;
    }
    inputFile.close();

    //setting initial position and direction for guard
    guard.set_positions(init_x, init_y);
    guard.set_direction(init_dir);

    //copying lab for part two of challenge
    vector<string> lab_map_part_2(lab_map);

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


    in_bounds = true;
    //setting initial position and direction for guard
    guard.set_positions(init_x, init_y);
    guard.set_direction(init_dir);
    //moving guard by rules
    while(in_bounds){
        //cout << guard.display_guard() << endl;
        in_bounds = guard.move_guard_part_2(lab_map_part_2);
    }

    string map_after_2;
    //counting the number of distint positions
    for(string line: lab_map_part_2){
        map_after_2 += line + "\n";
    }

    cout << map_after_2 << endl;

}
