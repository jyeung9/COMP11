/*
    Title: highScoresList.h
    Name: Julie Yeung
    Date: 12.08.2018
    Purpose: 
    Shows: classes & member functions/variables

*/

#ifndef HIGHSCORESLIST_H
#define HIGHSCORESLIST_H

#include <string>

class HighScoresList {
    public:
        HighScoresList();
        ~HighScoresList();
        void save();
        int highestScore();
        void print();
        void printTop5();
        void keepTop10();
        void insert(std::string user, int score);
        void clear();
        void printUser(std::string user);
        void deleteUser(std::string user);   // A JFFE, not required

    private:
        const std::string SENTINEL = "-1";
        const std::string HIGH_SCORE_FILE = "highScores.txt";
        struct Node{
            std::string name;
            int scores;
            Node *next;
        };
        Node *front;

        void load();  
        Node *newNode(std::string name, int score);
        void traverse(Node *curr, std::string name, int score);
        void sort(std::string name, int score);

};

#endif
