 /*
 	Title: game.cpp
 	Name: Julie Yeung
    Date: November 30, 2018
    Purpose: implements Game.h class
    Shows: constructor, destructor, scope operator(::), for loops, if
    conditionals, random number generators, switch statements, including/
    linking necessary files
 */

#include <string>
#include <cstdio>

#include "game.h"
#include "int-string.h"

#include <iostream>
using namespace std;

/* 
 * Game()
 * Constructor for Game class; initializes board dimensions with user input
 * validates user input, calls on init_board() to initialize board
 */
Game::Game()
{
	totalScore = 0;
	cout << "Enter desired dimension of board: " << endl;
    int user_input;

    cin >> user_input;
    // checks for valid user input
    if (user_input <= 2) {
        cerr << "Dimension too small! Please enter a number greater than 2";
        exit(1);
    }

    cout << "Starting game! High score is " << list.highestScore() << endl;

    rows = user_input;                  
    cols = rows;

    num_empty_sq = rows * cols;
	init_board();
}

/* 
 * ~Game()
 * deletes dynamically allocated board
 */
Game::~Game() 
{
	for(int i = 0; i < rows; i++) {
		delete board[i]; 
	}
	delete board;
} 

/* 
 * random_pos_gen(int value)
 * randomly generates a position for tiles to be generated; feeds in
 * rand_2_or_4_gen() as int parameter
 */
void Game::random_pos_gen(int value)
{
	if(num_empty_sq != 0){
		int count = 0;
		int square = rand() % num_empty_sq;
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if (not(board[i][j].occupied) and square == count++){
					board[i][j].val = value;
					board[i][j].occupied = true;
					--num_empty_sq;
					return;	
				}
			}
		}
	}
}

/* 
 * print_number(string num)
 * spaces out tiles 6 spaces
 */
void Game::print_number(string num) {
    printf("%-6s", num.c_str());
}

/* 
 * shift_left()
 * checks if tiles to left unoccupied, left shifts occupied tiles to last
 * unoccupied tile
 */
void Game::shift_left(){
	for(int i = 0; i < rows; i++){
		for(int j = 1; j < cols; j++){
			if(board[i][j].occupied){
				for(int p = j; p > 0; p--){
					if(!board[i][p-1].occupied){
						board[i][p-1].val = board[i][p].val;
						board[i][p-1].occupied = true;
						board[i][p].val = -1;
						board[i][p].occupied = false;

					}
				}
			}

		}
	}
}

/* 
 * move_left()
 * starts on left edge, checks value to right, sums tiles of same value
 */
void Game::move_left()
{
	// call on shift first to fill up empty squares, sum up squares, then call
	// on shift again to fill up remaining blank tiles

	shift_left();

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols-1; j++){
			if(board[i][j].val == board[i][j+1].val and
			   board[i][j].occupied){
				board[i][j].val *= 2;
				board[i][j+1].val = -1;
				board[i][j+1].occupied = false;
				totalScore += board[i][j].val;
				// increment # empty squares each time val doubled
				num_empty_sq++; 
			}

		}
	}

	shift_left();
	random_pos_gen(random_2_or_4_gen());
	print_board();
}

/* 
 * shift_up()
 * checks if tiles above unoccupied, shifts up occupied tiles to last
 * unoccupied tile
 */
void Game::shift_up()
{
	for(int i = 1; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j].occupied){
				for(int p = i; p > 0; p--){
					if(!board[p-1][j].occupied){
						board[p-1][j].val = board[p][j].val;
						board[p-1][j].occupied = true;
						board[p][j].val = -1;
						board[p][j].occupied = false;
					}
				}
			}
		}
	}
}

/* 
 * move_up()
 * starts on left edge, checks value below, sums tiles of same value
 */
void Game::move_up()
{
	shift_up();
	for(int i = 0; i < rows - 1; i++){
		for(int j = 0; j < cols; j++){
			if(board[i][j].val == board[i+1][j].val and
			   board[i][j].occupied){
				board[i][j].val *= 2;
				board[i+1][j].val = -1;
				board[i+1][j].occupied = false;
				totalScore += board[i][j].val;
				num_empty_sq++; 
			}

		}
	}
	shift_up();
	random_pos_gen(random_2_or_4_gen());
	print_board();
}

/* 
 * shift_right()
 * checks if tiles to right unoccupied, shifts right occupied tiles to last
 * unoccupied tile
 */
void Game::shift_right()
{
	for(int i = rows - 1; i >= 0; i--){
		for(int j = cols - 2; j >= 0; j--){
			if(board[i][j].occupied){
				for(int p = j; p < cols - 1; p++){
					if(!board[i][p+1].occupied){
						board[i][p+1].val = board[i][p].val;
						board[i][p+1].occupied = true;
						board[i][p].val = -1;
						board[i][p].occupied = false;
					}
				}
			}
		}
	}
}
/* 
 * move_right()
 * starts on right edge, checks value to left, sums tiles of same value
 */ 
void Game::move_right()
{
	shift_right();
	for(int i = rows-1; i >= 0; i--){
		for(int j = cols - 1; j >= 0; j--){
			if(board[i][j].val == board[i][j-1].val and
			   board[i][j].occupied){
				board[i][j].val *= 2;
				board[i][j-1].val = -1;
				board[i][j-1].occupied = false;
				totalScore += board[i][j].val;
				num_empty_sq++;
			}

		}
	}
	shift_right();
	random_pos_gen(random_2_or_4_gen());
	print_board();
}

/* 
 * shift_down()
 * checks if tile below not occupied, shifts down occupied tiles to last
 * unoccupied tile
 */
void Game::shift_down()
{
	for(int i = rows - 1; i >= 0; i--){
		for(int j = cols - 1; j >= 0; j--){
			if(board[i][j].occupied){
				for(int p = i; p < rows - 1; p++){
					if(!board[p+1][j].occupied){
						board[p+1][j].val = board[p][j].val;
						board[p+1][j].occupied = true;
						board[p][j].val = -1;
						board[p][j].occupied = false;
					}
				}
			}
		}
	}
}

/* 
 * move_down()
 * starts on bottom right corner, checks value above, sums tiles of same value
 */
void Game::move_down()
{
	shift_down();
	for(int i = rows-1; i > 0; i--){
		for(int j = cols-1; j >= 0; j--){		
			if(board[i][j].val == board[i-1][j].val and
			   board[i][j].occupied){
				board[i][j].val *= 2;
				board[i-1][j].val = -1;
				board[i-1][j].occupied = false;
				totalScore += board[i][j].val;
				num_empty_sq++;
			}

		}
	}
	shift_down();
	random_pos_gen(random_2_or_4_gen());
	print_board();
}

/* 
 * init_board()
 * initializes gameboard to unoccupied spaces, generates 2 at 2 random
 * positions at start of game
 */
void Game::init_board()
{
	board = new cell*[rows];
	for(int i = 0; i < rows; i++) {
		board[i] = new cell[cols]; 
	}

	for(int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			board[i][j].val = -1;
			board[i][j].occupied = false;
		}
	}

	random_pos_gen(2);
	random_pos_gen(2);
}

/* 
 * print_board()
 * prints/updates board
 */
void Game::print_board()
{
	cout << "Current score: " << totalScore << endl;
	for (int i = 0; i < rows; i++){
		cout << endl;
		for(int j = 0; j < cols; j++) {
			if (board[i][j].occupied == false){
				print_number("-");
			}
			else{
				print_number(int2string(board[i][j].val));
			}
		}
	}
	cout << endl;
}

/* 
 * random_2_or_4_gen()
 * generates random 2 or 4 tile; parameter of random_pos_gen() function
 * prob(2) = 90%, prob(4) = 10%
 */
int Game::random_2_or_4_gen() {

	int randNum = 0;
	if (rand()%100 < 90) {
		randNum = 2;
		return randNum;
	}
	randNum = 4;
	return randNum;
}

/* 
 * lose()
 *  checks if game is lost (no possible sums, all squares filled)
 */
bool Game::lose()
{
	if (num_empty_sq == 0){
		for (int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(isEqualToNeighbor(LEFT,i,j) or 
				   isEqualToNeighbor(RIGHT,i,j) or 
				   isEqualToNeighbor(UP,i,j) or 
				   isEqualToNeighbor(DOWN,i,j))
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

/* 
 * isEqualToNeighbor()
 * checks if any possible sums in given direction
 * the different directions are defined as constants in the game class
 */
bool Game::isEqualToNeighbor(int direction, int r, int c)
{
	bool isEqual = false;
	switch(direction){
		case LEFT: 
			if (c > 0 and board[r][c].val == board[r][c-1].val) {
				isEqual = true;
			}
			break;

		case RIGHT:
			if (c < cols - 1 and board[r][c].val == board[r][c+1].val){
				isEqual = true;

			}
			break;

		case UP:
			if (r > 0 and board[r][c].val == board[r-1][c].val){
				isEqual = true;

			}
			break;

		case DOWN: 
			if (r < rows - 1 and board[r][c].val == board[r+1][c].val){
				isEqual = true;

			}
			break;

		default: 
			cerr << "Invalid direction! " << direction << endl;
			break;
	}
	return isEqual;
}

