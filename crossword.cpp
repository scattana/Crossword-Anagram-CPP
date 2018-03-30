// crossword.cpp
// main driver for the crossword anagram puzzle program
// CSE-20311 Lab 9, Fall 2017
// Seth Cattanach

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

#include "board.h"

void sortHighLow(vector<string>&);
void makeCaps(vector<string>&);
bool checkForLetters(string);

int main(int argc, char *argv[]){
	// display welcome message
	cout << "\n\n------------------------------------------------" << endl;
	cout << "Welcome to the Crossword Anagram Puzzle Program" << endl;
	cout << "------------------------------------------------\n\n" << endl;
	// create a vector list of strings either from user input
	// or from a text file passed at command line
	vector<string> list;
	string temp;

	if(argc == 1) {
		// create vector<string> list from user input
		cout << "Entering manual input mode" << endl;
		cout << "Instructions: Enter  a list of up to 20 words, max 15";
		cout << " letters each.\nType RETURN after each word, and enter a period";
		cout << " '.' after the final word:" << endl;
		getline(cin, temp);
		while(temp[0] != '.'){
			if(list.size()==20){
				cout << "--------------------------------------------" << endl;
				cout << "20 words have been placed - Maximum Reached" << endl;
				cout << "--------------------------------------------" << endl;
				cout << "\n" << endl;
				break;
			}
			if(checkForLetters(temp)){
				list.push_back(temp);
			}
			else{
				cout << "Error: " << temp << " is not a valid word";
				cout << " or has too many letters (max 15)" << endl;
			}

			getline(cin, temp);
		}

		cout << "\nThank you, the list has been saved.\n" << endl;
	}
	if(argc==2 || argc==3) {
		// read data file from argument and create vector<string> list
		ifstream ifs;
		string file = argv[1];
		ifs.open(file);

		// check for valid file; if not valid, prompt for valid file or exit
		while(!ifs){
			cout << "\nInvalid file name. Please enter valid file, ";
			cout << "or type 'quit' to exit the program: " << endl;
			getline(cin, file);
			if(file=="quit"||file=="Quit"||file=="QUIT"){
				return 1;
			}
			ifs.open(file);
		}

		// populate list from file
		while(ifs.peek() != '.'){
			if(list.size()==20){
				cout << "--------------------------------------------" << endl;
				cout << "20 words have been placed - Maximum Reached" << endl;
				cout << "--------------------------------------------" << endl;
				cout << "\n" << endl;
				break;
			}
			getline(ifs, temp, '\n');
			if(checkForLetters(temp)){
				list.push_back(temp);
			}
			else{
				cout << "Error: " << temp << " is not a valid word";
				cout << " or has too many letters (max 15)" << endl;
			}
		}
	}

	// create Board object
	Board board;

	// sort list and make all capital
	sortHighLow(list);
	makeCaps(list);

	// print list in sorted order
	cout << "\nHere's the list of words to be placed: " << endl;
	cout << "--------------------------------------" << endl;
	for(int a=0; a<list.size(); a++){
		cout << list[a] << endl;
	}
	cout << endl;

	// place list on board
	board.placeList(list);

	// print solution board
	cout << "---------------------------------------------" << endl;
	cout << "Your crossword puzzle has been generated!" << endl;
	cout << "Here's the solution:\n" << endl;
	board.printBoard();

	// print "disguised" crossword
	cout << "\n\nHere's the hidden crossword puzzle:\n" << endl;
	board.printHidden();

	// generate and display clues (anagrams)
	cout<<"\n\nHere are the clues! Each clue is an anagram of its solution\n"<<endl;
	for(int s=0; s<list.size(); s++){
		random_shuffle(list[s].begin(), list[s].end());
	}

	for(int t=0; t<list.size(); t++){
		if(list[t][0] != ' '){
			cout << "Row: "<<board.getRowLoc(t)<<", Column: "<<board.getColLoc(t);
			cout << "\t" << board.getDir(t);
			cout << "\t\t" << list[t] << endl;
		}
	}

	// lastly, if 3 arguments are provided at the command line, output
	// the words, solution, crossword, and clues to the file
	if(argc==3){
		ofstream ofs;
		string fileout = argv[2];
		ofs.open(fileout);
		if(!ofs){
			cout << "\n-------------------------------------" << endl;
			cout << "Error: Could not open file '" << fileout << "'" << endl;
			cout << "-------------------------------------\n" << endl;
		}

		ofs << "\n-----------------------------" << endl;
		ofs << "   CROSSWORD PUZZLE SOLUTION   " << endl;
		ofs << "-----------------------------\n" << endl;
		// output to file the solution board
		for(int i=0; i<15; i++){
			for(int j=0; j<15; j++){
				ofs << board.getSpot(i,j) << " ";
			}
			ofs << endl;
		}
		ofs << "\n\n" << endl;

		// output to file the  hidden board
		ofs << "\n-----------------------------" << endl;
		ofs << "  GENERATED CROSSWORD PUZZLE   " << endl;
		ofs << "-----------------------------\n" << endl;
		for(int i=0; i<15; i++){
			for(int j=0; j<15; j++){
				if(board.getSpot(i,j)=='_') ofs << "# ";
				else ofs << "_ ";
			}
			ofs << endl;
		}
		ofs << "\n\n" << endl;

		// lastly, output to file the anagram clues
		ofs << "Here are the clues! Each clue is an anagram of its solution" << endl;
		ofs <<"-----------------------------------------------------------" << endl;
		for(int t=0; t<list.size(); t++){
			if(list[t][0] != ' '){
				ofs << "Row: "<<board.getRowLoc(t)<<", Column: "<<board.getColLoc(t);
				ofs << "\t\t" << board.getDir(t);
				ofs << "\t\t" << list[t] << endl;
			}
		}

		ofs.close();
	} // end of "if(argc==3)" statement

	return 0;
} // END OF MAIN


// sorts the list from longest to shortest words
void sortHighLow(vector<string>& list){
	string temp;
	// run bubble sort algorithm
	for(int i=0; i<list.size()-1; i++){
		for(int j=0; j<list.size()-i-1; j++){
			if(list[j].size() < list[j+1].size()){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

// makes all letters in the list capital
void makeCaps(vector<string>& list){
	for(int i=0; i<list.size(); i++){
		for(int j=0; j<list[i].size(); j++){
			(list[i])[j] = toupper((list[i])[j]);
		}
	}
}


// returns true if all characters in the word are true, else false
bool checkForLetters(string word){
	// first, check if the word is 15 characters or less
	if(word.size()>15) return false;
	// next, check if the word contains all valid letters
	// using ascii values for valid uppercase and lowercase letters
	for(int i=0; i<word.size(); i++){
		if(word[i]<65 || word[i]>122 || (word[i]>90&&word[i]<97)){
			return false;
		}
	}
	// if the function "makes it out" without returning false, then all
	// characters are valid letters - return true
	return true;
}
