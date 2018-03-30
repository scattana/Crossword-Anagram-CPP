// board.cpp
// implementation of Board class
// used in Crossword Anagram Puzzle
// CSE-20311 Lab 9 Fall 2017
// Seth Cattanach

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "board.h"

// default implementation
Board::Board(){
	// make a 15x15 blank board, with blanks shown as underscores
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			data[i][j] = '_';
		}
	}
	// make all locations (0,0) to begin with
	for(int row=0; row<20; row++){
		for(int col=0; col<2; col++){
			locations[row][col] = 0;
		}
	}
	// "place" keeps track of which word in list goes to which location
	// start at 1 because first (longest) word will be placed before the
	// method is called that places the next word on the board
	place = 1;

	// direction keeps track of the orientation of the words placed
	for(int i=0; i<20; i++){
		direction[i] = " ";
	}
}

// destructor
Board::~Board() {}

// printBoard method displays the Board object (SOLUTION)
void Board::printBoard(){
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			cout << data[i][j];
			// add a space in between for visual purposes
			cout << " ";
		}
		cout << endl;
	}
}


// printHidden method prints the "disguised" crossword puzzle
void Board::printHidden(){
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			if(data[i][j]=='_') cout << '#';
			else cout << '_';
			// add a space in between for visual purposes
			cout << " ";
		}
		cout << endl;
	}
}


// setSpot method changes one character of the board
void Board::setSpot(char c, int row, int col) {
	data[row][col] = c;
}


// getRowLoc method returns the row at which a word was placed
int Board::getRowLoc(int x){
	return locations[x][0]+1; // add 1 so the coordinates go from 1-15, not 0-14
}


// getColLoc method returns the column at which a word was placed
int Board::getColLoc(int y){
	return locations[y][1]+1; // add 1 so the coordinates go from 1-15, not 0-14
}



// placeList method places list of words from main on the board
void Board::placeList(vector<string>& list){
	int hold;
	// list should already be sorted and all caps from main
	for(int i=0; i<list.size(); i++){
		if(i==0){
			for(int j=0; j<list[0].size(); j++){
				// place first (longest) word in middle, horizontally
				setSpot((list[0])[j], 7, (15-list[0].size())/2 + j);
				direction[0] = "ACROSS";
			}
			locations[0][0] = 7;
			locations[0][1] = (15-list[0].size())/2;
		} // end of i=0 if statement
		// alternate placing words vertically and horizontally
		// and if one doesn't work, try the other
		if(i!=0 && i%2==0){
			if(placeNextVer(list[i])){
				direction[i] = "DOWN";
			}
			else if(placeNextHor(list[i])){
				direction[i] = "ACROSS";
			}
			else{
				cout << "Could not place word: " << list[i] << endl;
				list[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
		else if(i!=0 && i%2!=0){
			if(placeNextHor(list[i])){
				direction[i] = "ACROSS";
			}
			else if(placeNextVer(list[i])){
				direction[i] = "DOWN";
			}
			else{
				cout << "Could not place word: " << list[i] << endl;
				list[i] = " ";
				place++;
				direction[i] = " ";
			}
		}
	} // end of outermost for loop
} // end of placeList method



// getSpot method returns the character at a specific index on the board
char Board::getSpot(int i, int j) {
	return data[i][j];
}

// getDir method returns the direciton of a specified placed word
string Board::getDir(int x){
	return direction[x];
}



// placeNextVer method tries to find and place next word on board, vertically
bool Board::placeNextVer(string word){
	int match = 0;
	bool isPlaced = 0, key = 0;
		for(int j=0; j<15; j++){
			for(int i=0; i<15+1-word.size(); i++){
				for(int k=0; k<word.size(); k++){
					if(getSpot(i+k,j)=='_' || getSpot(i+k,j)==word[k]){
						match++;
					}
					if(getSpot(i+k,j)==word[k]){
						if(getSpot(i+k+1,j)=='_' && getSpot(i+k-1,j)=='_'){
							match = match+2;
							key = 1;
						}
					}
					if(getSpot(i+k,j+1)=='_'&&getSpot(i+k,j-1)=='_'){
						match = match + 2;
					}
					if(getSpot(i-1,j)=='_' && getSpot((i+word.size()),j)=='_'){
						if(k==0) match = match + 2;
					}
				} // end of "k" for loop
				if(match == 3*word.size()+2 && key == 1 && isPlaced == 0){
					// place word
					for(int p=0; p<word.size(); p++){
						setSpot(word[p], i+p, j);
					}
					// set isPlaced to true
					isPlaced = 1;
					// assign coordinates to the newly-placed word
					locations[place][0] = i;
					locations[place][1] = j;
					place++;
					return 1;

				}
				match = 0;
				key = 0;
			} // end of second for loop (i)
		} // end of outermost for loop (j)
	return 0; // return false if the word was not able to be placed vertically
} // end of placeNextVer method



// placeNextHor method tries to find and place next word on board, horizontally
bool Board::placeNextHor(string word){
	int match = 0;
	bool isPlaced = 0, key = 0;
		for(int j=0; j<15; j++){
			for(int i=0; i<15+1-word.size(); i++){
				for(int k=0; k<word.size(); k++){
					if(getSpot(j,i+k)=='_' || getSpot(j,i+k)==word[k]){
						match++;
					}
					if(getSpot(j,i+k)==word[k]){
						if(getSpot(j,i+k+1)=='_' && getSpot(j,i+k-1)=='_'){
							match = match+2;
							key = 1;
						}
					}
					if(getSpot(j+1,i+k)=='_'&&getSpot(j-1,i+k)=='_'){
						match = match + 2;
					}
					if(getSpot(j,i-1)=='_' && getSpot(j,i+word.size())=='_'){
						if(k==0) match = match + 2;
					}
				} // end of "k" for loop
				if(match == 3*word.size()+2 && key == 1 && isPlaced == 0){
					// place word
					for(int p=0; p<word.size(); p++){
						setSpot(word[p], j,i+p);
					}
					locations[place][0] = j;
					locations[place][1] = i;
					place++;

					// set isPlaced to true
					isPlaced = 1;
					return 1;

				}
				match = 0;
				key = 0;
			} // end of second for loop (i)
		} // end of outermost for loop (j)
	return 0; // return false if the word was not able to be placed horizontally
} // end of placeNextVer method




// findMatch method returns 1 if at least 1 letter from the word
// was found on the board, and returns 0 if not
int Board::findMatch(string word){
	for(int i=0; i<15; i++){
		for(int j=0; j<15; j++){
			for(int k=0; k<word.size(); k++){
				if(word[k] == getSpot(i,j)) return 1 ;
			}
		}
	}
	return 0;
}


