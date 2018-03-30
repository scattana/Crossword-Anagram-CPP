README file for Crossword Anagram Project
Author: Seth Cattanach
Fall 2017

This project is a C++ implementation of an anagram crossword puzzle 
generator.

-----------------------
Usage and Instructions
-----------------------

By running the provided "crossword" executable (or creating the executable 
with the given repository files and Makefile), the user can input a list 
of words (up to 20) and the program will attempt to place each word on 
the board. When end-of-input has been specified (CRTL-d or '.' 
character), the program will output three items: the "solution" board 
with all words placed appropriately, the "puzzle" board with blank 
spaces indicated by the '_' character, and a list of clues to solve the 
puzzle.

Each clue in the puzzle is an anagram of the target word. For example, a 
given clue might give a coordinate and read "GOCIND" - solving this 
anagram would yield the word "CODING" which would be placed at the given 
coordinate.

The user can also run the executable with a list of words already 
specified in a text file as a command line argument. Example:

./crossword samplewords.txt

This will bypass the "manual word entry" and the program will 
immediately generate and display a crossword.

To save the program's output to a textfile, simply specify a file as 
another command line argument, and the program will save the solution 
board, puzzle board, and anagram clues to the specified file. Example:

./crossword samplewords.txt output.txt

This will run the "crossword" executable with input words from 
"samplewords.txt" and save the generated crossword to "output.txt"


The provided Makefile allows the user to easily compile the project's 
source code. To do so, simply run "make" in the project directory. Run 
"make clean" to remove all intermediate object files created during the 
compiling/linking processes as well as the executable.




