// board.h
// Header file for Board class used in crossword.cpp
// Lab 9 - Crossword Anagram Puzzle
// Seth Cattanach, Nov 2017
// CSE-20311 Fall 2017

#include <vector>
#include <string>

class Board {
	public:
		Board();
		~Board();
		char getSpot(int, int);
		int getRowLoc(int);
		int getColLoc(int);
		string getDir(int);
		void update();
		void setSpot(char, int, int);
		void placeList(vector<string>&);
		bool placeNextVer(string);
		bool placeNextHor(string);
		int findMatch(string);
		void printBoard();
		void printHidden();
	private:
		char data[15][15];
		int locations[20][2];
		string direction[20];
		int place;
};
