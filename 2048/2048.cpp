/*
 * Driver for 2048 
 * COMP11 Spring 2018
    Title: 2048.cpp
    Name: Julie Yeung
    Date: November 30, 2018
    Purpose: implements gameplay, score display at end
 */

#include "game.h"
#include <string>

int main() {
    Game game;
   	game.play();
    return 0;
}

/* 
 * play()
 * as long as game is not lost and 'q' key not pressed, keep prompting
 * user for commands
 */
void Game::play()
{
    string command;
    string user; 
	print_board();

    // use the const strings defined in game class earlier!
    while (not(lose()) and command != quitComm){
        cin >> command;
        if (command == leftComm){
            move_left();
        }
        if(command == rightComm){
            move_right();
        }
        if(command == upComm){
            move_up();
        }
        if(command == downComm){
            move_down();
        }
        if(command == hiScoreComm){
            list.printTop5();
        }
        if(command.compare(showUserComm) == 0){
            cin >> user;
            list.printUser(user);
        }
        if(command.compare(showUserKeepComm) == 0){
            list.keepTop10();
        }
        if(command.compare(clearComm) == 0){
            list.clear();
        }
    }

    cout << "Game over! Enter your name to record your score: ";
    cin >> user;
    list.insert(user,totalScore);
    list.save();
    list.printTop5();
}