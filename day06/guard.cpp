#include "guard.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor for class Guard
Guard::Guard(int x, int y, char dir):
pos_x{x}, pos_y{y}, direction{dir}{}

//Copy Constructor for class Guard
Guard::Guard(Guard &g):
pos_x{g.pos_x}, pos_y{g.pos_y}, direction{g.direction}{}

//Destructor for class Guard
Guard::~Guard(){}

//Getters and Setters
int Guard::get_x() const {return pos_x;}
int Guard::get_y() const {return pos_y;}
void Guard::set_positions(int x,int y){pos_x=x; pos_y=y;}
char Guard::get_direction() const {return direction;}
void Guard::set_direction(char dir) {direction = dir;}

//Inrcrements and decrements for positions
void Guard::increment_x(){pos_x++;}
void Guard::increment_y(){pos_y++;}
void Guard::decrement_x(){pos_x--;}
void Guard::decrement_y(){pos_y--;}

string Guard::display_guard(){
    string dir;

    switch (direction)
    {
    case '^':
        dir = "up";
        break;
    case 'v':
        dir = "down";
        break;
    case '<':
        dir = "left";
        break;
    case '>':
        dir = "right";
        break;
    default:
        break;
    }

    return "The guards position is: \n\tX: "+ to_string(pos_x) + "\n\tY: " + to_string(pos_y) +"\nTheir direction is: " + dir;
    }


    //moves guard by one point in specified direction
    //rotates right and moves by one if obstacle(#) encountered
    bool Guard::move_guard(vector<string> &field){

        //defining the bounds
        int y_max_size = field.size();
        int x_max_size = field.at(0).size() - 1; //excluding \0 EoL character 

        //changing the current position on playing field to X
        field.at(pos_y).replace(pos_x, 1,1,'X');

        //each case checks if players next move is in playing field
        switch (direction){
            case '^':
                if(pos_y-1 >= 0){
                    if(field.at(pos_y-1)[pos_x]=='#'){
                        direction = '>';
                        increment_x();
                    }else{
                        decrement_y();
                    }
                }else{
                    return false;
                }
                break;
            case '>':
                if(pos_x+1 <= x_max_size){
                    if(field.at(pos_y)[pos_x+1]=='#'){
                        direction = 'v';
                        increment_y();
                    }else{
                        increment_x();
                    }
                }else{
                    return false;
                }
                break;
            case 'v':
                if(pos_y+1 <= y_max_size){
                    if(field.at(pos_y+1)[pos_x] == '#'){
                        direction = '<';
                        decrement_x();
                    }else{
                        increment_y();
                    }
                }else{
                    return false;
                }
                break;
            case '<':
                if(pos_x-1 >= 0){
                    if(field.at(pos_y)[pos_x-1] == '#'){
                        direction = '^';
                        decrement_y();
                    }else{
                        decrement_x();
                    }
                }else{
                    return false;
                }
                break;
            default:
                break;
        }

        return true;
    }