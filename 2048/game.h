/* 
    Title: game.h
    Name: Julie Yeung
    Date: November 30, 2018
    Purpose: defines member functions and variables of Game class
    Shows: classes & member functions and variables, #include/linking of files
*/
#ifndef GAME_H
#define GAME_H

#include <string>
using namespace std;
#include <iostream>

#include "highScoresList.h"
const int ROW = 1;
const int COL = 4;
const int LEFT = 1;
const int RIGHT = 2;
const int UP = 3;
const int DOWN = 4;

class Game {
    public:
        Game();
        ~Game();
        void play();

    private:
        void init_board();
        void print_board();
        void print_number(std::string num);
        void move_left();
        void shift_left();
        void move_right();
        void shift_right();
        void move_up();
        void shift_up();
        void move_down();
        void shift_down();
        void random_pos_gen(int value);

        int random_2_or_4_gen(); 

        bool lose();
        bool isEqualToNeighbor(int direction, int r, int c);

        // occupied = false if no numeric tile
        // val = -1 if unoccupied, 2 or its multiples if there is a tile
        struct cell {
            bool occupied;
            int val;
        };

        // list of possible commands that user can type
        const string upComm = "w";
        const string downComm = "s";
        const string rightComm = "d";
        const string leftComm = "a";
        const string hiScoreComm = "h";
        const string quitComm = "q";
        const string showUserComm = "show";
        const string showUserKeepComm = "keep";
        const string clearComm = "clear";

        // dynamically allocated 2D array of 'cell' structs
        struct cell **board;
        HighScoresList list;
        int totalScore;
        int num_empty_sq;
        int cols;
        int rows;       
};

#endif
