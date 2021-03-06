// Deliverable 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <stack>
#include "Puzzle.h"
#include <chrono>

using namespace std;

//array of characters to move from index to char
char moveToChar[15] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' };

/****Main****/
int main()
{
	/***Parse input file***/
	//Declare Variables
	ifstream inputFile;					//text file input stream variable	
	vector<char> inputCandies;			//one input sequence
	vector<vector<char>> inputSequence;	//all input sequences
	vector<int> possibleMoves;			//vector keeping track of possible moves
									
	inputFile.open("input.txt");
	string str;

	cout << "Parsing input file..." << endl;

	//Parse input file
	while (getline(inputFile, str))
	{
		istringstream ss(str);	//create a string stream to parse getline
		char candy;				//this is each input candy

		while (ss >> candy)	   //while there is a character to read
		{
			//check for empty space
			if (candy == 'e')
			{
				candy = ' ';
			}

			inputCandies.push_back(candy);	//push the input candy to the temp vector			
		}

		inputSequence.push_back(inputCandies);  //push read line as a new seqeunce
		inputCandies.clear();	//clear the temp vector for another input sequence

	}
	inputFile.close();

	/***MENU***/
	while (1)
	{
	menu:
		char menuSelection; // Menu selection variable
		
		system("CLS");		// Clear Command Line

		//check to make sure a puzzle file was read
		if (inputSequence.empty())
		{
			cout << "No input sequnces found... exiting!" << endl;
			system("PAUSE");
			return -1;
		}
		else
			cout << "Number of puzzles inputted = " << inputSequence.size() << endl;

		cout << "CHOOSE ONE OF THE FOLLOWING OPTIONS: " << endl;	

		cout << "a\tAUTO COMPLETE ALL" << endl;
		cout << "m\tManual Mode" << endl;
		cout << "z\tExit Game" << endl;

		//Prompting user for input and data validation
		do
		{
			cout << "Puzzle Number: ";
			menuSelection = cin.get();
			cin.ignore(256, '\n');
			menuSelection = tolower(menuSelection);	//validation
		} while (menuSelection != 'a' && menuSelection != 'z' && menuSelection != 'm');

		//Exit Game
		if (menuSelection == 'z')
			break;

		if(menuSelection == 'm')
			while (1)
			{
				cout << "CHOOSE ONE OF THE FOLLOWING INPUTTED PUZZLES: " << endl;

				//print a list of puzzles that inputed that the user can choose
				for (int x = 0; x < inputSequence.size(); x++)
				{
					cout << x + 1 << "\t";

					for (int y = 0; y < inputSequence[x].size(); y++)
						cout << "[" << inputSequence[x][y] << "]";

					cout << endl;
				}

				cout << inputSequence.size() + 1 << "\tExit Manual Mode" << endl;
			
				string menuSel;
				int test;
				//Prompting user for input and data validation
				do
				{	
					cout << "Puzzle Number: ";
					cin >> menuSel;
					test = stoi(menuSel);
					cin.ignore(256, '\n');
					
				} while ((test < 1 || test > inputSequence.size()+1));

				//Exit to menu
				if (test == inputSequence.size()+1)
					break;

				bool legalMove = true;	//flag for illegal move
				Puzzle puzzle = inputSequence[test-1];	//Create Puzzle Object
				char inputMove;
				while (1)
				{
					system("CLS"); // Clear Command Line
					cin.clear();   // Clear the input

					//Illegal Move message
					if (!legalMove)
						cout << endl << "Illegal Move";

					//Print Puzzle
					puzzle.printGrid();

					//Check puzzle
					if (puzzle.puzzleComplete())
					{
						cout << endl << "***YOU FINISHED THE PUZZLE***" << endl;

						system("PAUSE");
						break;
					}
					else
					{
						//Print Possible Moves
						possibleMoves = puzzle.checkPossibleMoves();
						cout << "Possible Moves: ";
						for (int x = 0; x < possibleMoves.size(); x++)
						{
							cout << moveToChar[possibleMoves[x]] << " ";
						}

						//Prompt For Move
						cout << endl << "Enter Cell Letter to Move ('Z' for menu):";
						inputMove = cin.get();
						cin.ignore(256, '\n');	//validation
						inputMove = tolower(inputMove);	//validation

						//exit puzzle check
						if (inputMove == 'z' || inputMove == 'Z')
							break;
						else
							legalMove = puzzle.attemptMove(inputMove);

					}

				}

			}		

		if (menuSelection == 'a')
		{
			int totalCount = 0;
			ofstream outfile;// declaration of file pointer named outfile
			outfile.open("output.txt", ios::out); // opens file named "filename" for output

			ofstream outfileMoves;// declaration of file pointer named outfile
			outfileMoves.open("outputMoves.txt", ios::out); // opens file named "filename" for output
			for (int x = 0; x < inputSequence.size(); x++)
			{
				auto startTime = chrono::high_resolution_clock::now();
				string result;
				Puzzle puzzle = inputSequence[x];	//Create Puzzle Object
				result = puzzle.autoComplete();

				auto endTime = chrono::high_resolution_clock::now();				
				
				totalCount += result.size(); 
				outfile << result << endl;
				outfile << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << endl;

				system("CLS");
				cout << "Auto Complete In Progress..." << endl;
				cout << "Number of Puzzles Solved = [" << x+1 << "]";

				outfileMoves << "Puzzle: " << x << endl;
				for (int z = 0; z < result.size(); z++)
				{
					puzzle.attemptMove(result[z]);
					outfileMoves << "Move: " << result[z];
					outfileMoves << puzzle.outputGrid();
				}

			}
			outfile << "Total Moves: " << totalCount << endl;
			cout << endl << "Auto Completed All Puzzles!" << endl;
			system("PAUSE");
			
		}	

	}	
	return 0;
}

