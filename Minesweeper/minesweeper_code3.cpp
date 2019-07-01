/* 
 * minesweeper.cpp 
 *
 * A text-based minesweeper game that runs in the terminal.
 *
 * COMP11 Fall 2018
 * Modified by: Julie Yeung
 * Date: 10.19.18

   Purpose:
   Notes: This design exhibits modularity as there are a total of 2 
   structs and 8 functions. Each struct and functions has its own use case. 
   The use cases include keeping track of cell elements, getting user input,
   prompting user for input, validating that input, checking to assign mine, 
   calculating mines adjacent to each cell, uncovering mines for printing, 
   and printing the board.
 */

#include <iostream>
#include <time.h> 
#include <cstdlib>

using namespace std;
#undef TESTING
#ifdef TESTING
const int ROWS = 3;
const int COLS = 3;
const bool CHEAT_MODE = true;
#define RANDOMSEED 1
#else
const int ROWS = 9;
const int COLS = 9;
const bool CHEAT_MODE = false;
#define RANDOMSEED time(NULL)
#endif

const bool GAME_MODE = false;

struct cell {
    bool uncovered; // makes sure user doesn't click on already uncovered cell
    bool has_mine;  // assigned to true if prob <= 0.3
    int adj_mines;  // stores number of adjacent mines to cell
};

// PURPOSE: stores user input of row/col
struct cell_coord {
    int row;
    int col;
};

int init_board(struct cell (&board)[ROWS][COLS]);
void print_board(struct cell board[][COLS], bool cheat_mode);
void play_game(struct cell board[][COLS], int safe_squares);
struct cell_coord get_validated_input (struct cell board[][COLS]);
bool is_valid (int user_row, int user_col);
bool assign_mine ();
void calc_adj_mines (struct cell (&board)[ROWS][COLS], 
                     struct cell_coord current);
void uncover_mine_cells (struct cell board[][COLS]);
void long_term_prob (int total); // tests long-term prob of mines

// PURPOSE: glues program together by calling on functions
int main ()
{

    // testing long-term probability of mines; larger the int passed, closer
    // the prob to 0.3
    long_term_prob(2000);
    long_term_prob(20000);
    
    struct cell board[ROWS][COLS]; // 2D array of cell structs
    int safe_squares = init_board(board);
    print_board(board,CHEAT_MODE);
    cerr << "init" << endl;

    play_game(board, safe_squares);

    return 0;
}

void long_term_prob (int total)
{
    float mine_ct = 0.0;
    for (int i = 0; i < total; i++){
        if (assign_mine())
            ++mine_ct;
    }
    cout << "Long Term Prob:" <<  (mine_ct / total) << endl;
}

// PURPOSE: Calls on function which prompts user input until user loses/wins
void play_game(struct cell board[][COLS], int safe_squares)
{
    string message = "";
        do{
            // gets validified user input
            cell_coord input = get_validated_input(board); 
            board[input.row][input.col].uncovered = true;
            if (board[input.row][input.col].has_mine) {
                uncover_mine_cells(board); 
                message = "GAME OVER. YOU LOST!";
            } else if (--safe_squares == 0) {
                message = "GAME OVER. YOU WON!";
            }

            print_board(board,GAME_MODE);
            cerr << "wat" << endl;
            if (not message.empty()) {
                cout << message << endl;
                return;
            }
        } while(true);
}

// Purpose: Repeatedly prompts user for coordinate. Checks for validity of
// input (if the coordinate is within range, and if cell already uncovered)
struct cell_coord get_validated_input (struct cell board[][COLS])
{
    cell_coord current;
        do {
            cout << "Enter the row and column of the square to uncover: ";
            cin >> current.row
                >> current.col;
            if(is_valid(current.row, current.col)) { 
                if (board[current.row][current.col].uncovered)
                    cout << "Bad input. Select another square" << endl;
                else
                    return current;
            }
            else 
                cout << "Bad input. Row and col must be >= 0 and < 9." << endl;
        } while(true);

}

// PURPOSE: Initializes board by initializing fields in cell struct. 
// Calls on calc_adj_mine() after mines set (has_mines()/not). Returns
// total_safe_cells for use later to see if user wins based off of number 
// of safe cells left.
bool arry[3][3] = 
{   
    {false,true,false},
    {false,false,true},
    {true,false,false}

};

int init_board(struct cell (&board)[ROWS][COLS])
{
    /*
        - initialized value: decrements each time mine planted
        - playing game: decrements each time safe cell uncovered
        - if total_safe_cells = 0, user wins
    */

    int total_safe_cells = ROWS * COLS;                         

    srand(RANDOMSEED); 

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j].uncovered = false;
#ifdef TESTING
            board[i][j].has_mine = arry[i][j];
#else
            board[i][j].has_mine = assign_mine();
#endif
            cerr << "has mine? " << board[i][j].has_mine << endl;
                if (board[i][j].has_mine){
                    cerr << "i: " << i << "j: "<< j << endl;
                    total_safe_cells--;
                }
            board[i][j].adj_mines = 0;
        }
    }
    // calculates adjacent mines once all mines placed above
    struct cell_coord current;
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
             current.row = i;
             current.col = j;
             calc_adj_mines(board, current); 
        }
    }
    cout << "val: " << board[0][2].adj_mines << endl;
    
    return total_safe_cells;
    
}


// purpose: iterate through each cell to print char for each cell struct takes 
//          care of format of the board
void print_board(struct cell board[][COLS], bool cheat_mode) 
{
    cout << " ";
    for (int k = 0; k < COLS; k++) {
        cout << " " << k;
    }
    cout << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << i << " ";
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].uncovered or cheat_mode)
                if (board[i][j].has_mine)
                    cout << 'x' << " ";
                else { 
                    cout << board[i][j].adj_mines << " ";
                }
            else 
                cout << '-' << " ";
        }
        cout << endl;
    } 

}


// PURPOSE: checks whether user input is within range. The range is 
//          when input 0 <= and < 9.
bool is_valid (int user_row, int user_col)
{

    if ((user_row >= 0 and user_row < ROWS) and
        (user_col >= 0 and user_col < COLS)) {
            return true;
    } else 
        return false;
    
}

// PURPOSE: assign probability to each cell struct in the 2D array. 
//          Returns true if random probability <= 0.3
bool assign_mine () {

    // generate a random float, prob
    // if (prob <= 0.3) then return true, else false;
    int prob = rand() % 100;
    if (prob <= 29)
        return true;
    else 
        return false;
}

// PURPOSE: calculates number of neighboring mines for each cell.
//          Returns that value into the int adj_mines field inside
//          cell struct.
void calc_adj_mines (struct cell (&board)[ROWS][COLS], struct cell_coord
                     current)
{
    cout << "row: " << current.row << " col: " << current.col << endl;
    for (int i = current.row - 1; i <= current.row + 1; i++) {
        for (int j = current.col -1; j <= current.col + 1; j++) {
            cout << "row: " << i << " col: " << j << endl;
            cout << "validity: " << is_valid(i,j) << endl; 
            if ((is_valid(i,j)) and board[i][j].has_mine) {
                ++board[current.row][current.col].adj_mines;
                cerr << "mines: " << board[current.row][current.col].adj_mines
                     << endl;
            }
        }
    }
}

// PURPOSE: uncovers cells with mines when user loses. Only when x's are 
//          uncovered will print_board also be able to update/print the x's
void uncover_mine_cells (struct cell board[][COLS])
{

      for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j].has_mine)
                    board[i][j].uncovered = true;
            }
      }

}
