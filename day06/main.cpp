#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "guard.cpp"
using namespace std;

void copy_vector(vector<string>&, vector<string>&);

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

    vector<array<int, 2>> distinct_pos_coordinates;
    string line_y;

    //counting the number of distint positions
    for(int i{0}; i<lab_map.size(); i++){
        line_y = lab_map.at(i);
        map_after += line_y + "\n";
        for(int j{0}; j<line_y.size(); j++){
            if(line_y.at(j)=='X'){
                if(j!=init_x && i!=init_y){
                    array<int,2> arr{j,i};
                    distinct_pos_coordinates.push_back(arr);         
                }

                distinct_positions++;
            }
        }
    }
    
    cout << map_after << endl;

    ofstream outputFile("output.txt");
    outputFile << map_after;
    outputFile.close();

    cout << "\n\n\nThe number of distinct positions is: \e[1m" + to_string(distinct_positions) + "\e[0m"<< endl;

    int coordinates[2]{0,0};
    int loop_options{0};
    string map_after_2;
    vector<string> lab_map_2_copy(lab_map_part_2);



    for(int pos {0}; pos < distinct_pos_coordinates.size(); pos++){
        lab_map_part_2.clear();
        copy_vector(lab_map_2_copy, lab_map_part_2);
        coordinates[0] = distinct_pos_coordinates.at(pos)[0];
        coordinates[1] = distinct_pos_coordinates.at(pos)[1];
        lab_map_part_2.at(coordinates[1]).replace(coordinates[0],1,1,'O');

        in_bounds = true;
        //setting initial position and direction for guard
        guard.set_positions(init_x, init_y);
        guard.set_direction(init_dir);
        guard.set_in_loop(false);

        //cout << pos << endl;
        //moving guard by rules
        while(in_bounds){
            in_bounds = guard.move_guard_part_2(lab_map_part_2);
            /* if(pos==123){
                cout<<guard.display_guard();
            } */
        }

        //lab_map_part_2.at(coordinates[1]).replace(coordinates[0],1,1,'.');

        if(guard.get_in_loop()){
            loop_options++;
        }

    }

    for(string l: lab_map_part_2){
        map_after_2 += l + "\n";
    }

    cout<<map_after_2;

    cout << "\n\n\nThe number of options for looping is: \e[1m" + to_string(loop_options) + "\e[0m"<< endl;
}


void copy_vector(vector<string> &from, vector<string> &to){
    for(string s: from){
        to.push_back(s);
    }
}