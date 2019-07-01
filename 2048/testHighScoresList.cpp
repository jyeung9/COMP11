/*
	Title: testHighScoresList.cpp
	Name: Julie Yeung
	Date: 12.08.2018
	Purpose: tests linked list outputs
	Shows: whether linked list is printing correctly
*/
#include "highScoresList.h"
using namespace std;
#include <iostream>

int main(){

	HighScoresList list;
	cout << "before insert! "<< endl;
	int testSc;
	int name = 'A';
	string convertedName;

	for(int i = 0; i < 5; i++){
		cout << "number? ";
		cin >> testSc;
		convertedName += name + i;
		list.insert(convertedName, testSc);
		list.print();
	}
}
