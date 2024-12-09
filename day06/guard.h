#ifndef _GUARD_H_
#define _GUARD_H_


#include <vector>
#include <string>

using namespace std;


/*
Guard has attribues:
    - position with coordinates of x and y
    - direction it's facing (up, down, lwft, right)

Definitions for Constructors, Destructor, Getters, Setters, increments, decrements and display

Functions for movement
*/

class Guard{
private:
    int pos_x, pos_y;
    char direction;
    bool in_loop;

public:
    Guard(int x=0,int y=0,char dir='^', bool in_loop=false);
    Guard(Guard &g);
    ~Guard();

    int get_x() const;
    int get_y() const;
    void set_positions(int,int);
    char get_direction() const;
    void set_direction(char);
    bool get_in_loop() const;
    void set_in_loop(bool);

    void increment_x();
    void increment_y();
    void decrement_x();
    void decrement_y();

    string display_guard();

    bool move_guard(vector<string> &field);
    bool move_guard_part_2(vector<string> &field);

    bool move_up(vector<string> *field);
    bool move_right(vector<string> *field);
    bool move_left(vector<string> *field);
    bool move_down(vector<string> *field);
};

#endif