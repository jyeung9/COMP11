/*
    Title: highScoresList.cpp
    Name: Julie Yeung
    Date: 12.08.2018
    Purpose: implements highScoresList.h class
*/

#include <iostream>
#include <fstream>

#include "highScoresList.h"

using namespace std;
/* 
 * HighScoresList()
 * initializes the necessary private variables in game.h class
 */
HighScoresList::HighScoresList() {

    front = nullptr;
    load();
}

/* 
 * ~HighScoresList()
 * deallocate memory in heap for the linked list 
 */
HighScoresList::~HighScoresList(){
    clear();
}
/* 
 * load()
 * Reads the HIGH_SCORE_FILE and loads the contents of the file
 * into the linked list.
 * If the file does not exist, do nothing. 
 */
void HighScoresList::load() 
{  
    ifstream inFile;
    inFile.open(HIGH_SCORE_FILE);
    if (not inFile) {
        return;
    }
    string user;
    int score;

    while (inFile >> user) {
        if (user == SENTINEL) 
            break;

        inFile >> score;
        insert(user, score);
    }

    inFile.close();
}

/* 
 * HighScoresList::Node *HighScoresList::newNode(string name, int score)()
 * Creates a new node with given name and score
 */
HighScoresList::Node *HighScoresList::newNode(string name, int score) {
    Node *result = new Node;
    result->name = name;
    result->scores = score;
    result->next = NULL;
    return result; 
}

/* 
 * save()
 * Writes the names and scores to the HIGH_SCORE_FILE, followed by the 
 * sentinel.
 * This will overwrite what was originally in HIGH_SCORE_FILE.
 */
void HighScoresList::save() {

    Node *curr = front;
    ofstream outFile;
    outFile.open(HIGH_SCORE_FILE);
    
    if(not outFile){
        return;
    }

    while(curr != NULL){
        outFile << curr->name << " " << curr->scores << endl;
        curr = curr->next;
    }

    outFile << SENTINEL << endl;
    outFile.close();
}   

/* 
 * insert(string name, int score)
 * Inserts a given name, score correctly into a descending ordered linked list
 */
void HighScoresList::insert(string name, int score) {

    Node *curr = front;
    Node *prev = NULL;
  
    if(front == NULL){
        //empty list; newNode() inserts first node
        front = newNode(name,score);
    } else if(score >= front->scores){
        // add node at front
        Node *newFront = newNode(name,score);
        newFront->next = front;
        front = newFront;
    } else {
        // sort nodes that belong in middle, or are equal in value
        while(curr != NULL and score < curr->scores){
            prev = curr; 
            curr = curr->next;
        }
        prev->next = newNode(name,score);
        prev->next->next = curr;
    }
}

/* 
 * print()
 * prints out each user's name and score
 */
void HighScoresList::print()
{
    Node *curr = front;
    while(curr != NULL){
        std::cout << "Name: " << curr->name 
        << " Score: " << curr->scores << endl;
        curr = curr->next;
    }
}

/* 
 * highestScore()
 * prints out highest score in linked list, which is at front (descending list)
 */
int HighScoresList::highestScore()
{
    if(front == NULL){
        return 0;
    }
    return front->scores;
}

/* 
 * printTop5()
 * prints names and scores of top 5 all time scores
 */
void HighScoresList::printTop5()
{
    int idx = 0;
    Node *curr = front;

    if(curr == NULL){
        cout << "There are no saved scores " << endl;
    }
    while(idx < 5 and curr != NULL){
        cout << curr->name << " " << curr->scores << endl;
        idx++;
        curr = curr->next;
    }
}

/* 
 * keepTop10()
 * keeps the top 10 all-time high scores; if there are more than 10 scores,
 * this function keeps only 10 of the highest scores
 */
void HighScoresList::keepTop10()
{
    Node *storeExtras = NULL;
    Node *curr = front;
    int counter =  0;

    while(curr != NULL and counter < 9){
        counter++;
        curr = curr->next;
    }

    // when list longer than number of elements want to keep
    if(curr != NULL) {
        storeExtras = curr->next;
        curr->next = NULL;
    }

    curr = storeExtras;
    Node *nextNode = NULL;
    // delete extra nodes
     while(curr != NULL){
        nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
}

/* 
 * printUser(std::string user)
 * prints out all scores associated with given user; for the "show xxx" command
 */
void HighScoresList::printUser(std::string user)
{
    Node *curr = front;
    bool match = false;
    while(curr != NULL){
        if(curr->name.compare(user) == 0){
            match = true;
            cout << curr->scores << endl;
        }
        curr = curr->next;
    }
    if (not match){
        cout << "No matches! " << endl;
    }
};

/* 
 * clear()
 * deletes all entries on the high score list
 */
void HighScoresList::clear(){
   
    Node *curr = front;
    Node *nextNode = NULL;

    while(curr != NULL){
        nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }

    front = NULL;
}

