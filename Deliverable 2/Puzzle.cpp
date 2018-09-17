#include "stdafx.h"
#include "Puzzle.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <chrono>

using namespace std;

Puzzle::Puzzle()
{

}


Puzzle::Puzzle(vector<char> inputSequence)
{
	state = inputSequence;
	checkEmptySpace();
}

Puzzle::~Puzzle()
{
	state.clear();
}

/****Function to check possible moves****/
vector<int> Puzzle::checkPossibleMoves()
{
	vector<int> possibleMoves;

	switch (emptySpace)
	{
	case 0:
		possibleMoves.push_back(1);
		possibleMoves.push_back(5);
		break;
	case 1:
		possibleMoves.push_back(0);
		possibleMoves.push_back(2);
		possibleMoves.push_back(6);
		break;
	case 2:
		possibleMoves.push_back(1);
		possibleMoves.push_back(3);
		possibleMoves.push_back(7);
		break;
	case 3:
		possibleMoves.push_back(2);
		possibleMoves.push_back(4);
		possibleMoves.push_back(8);
		break;
	case 4:
		possibleMoves.push_back(3);
		possibleMoves.push_back(9);
		break;
	case 5:
		possibleMoves.push_back(0);
		possibleMoves.push_back(10);
		possibleMoves.push_back(6);
		break;
	case 9:
		possibleMoves.push_back(4);
		possibleMoves.push_back(8);
		possibleMoves.push_back(14);
		break;
	case 10:
		possibleMoves.push_back(5);
		possibleMoves.push_back(11);
		break;
	case 11:
		possibleMoves.push_back(6);
		possibleMoves.push_back(10);
		possibleMoves.push_back(12);
		break;
	case 12:
		possibleMoves.push_back(7);
		possibleMoves.push_back(11);
		possibleMoves.push_back(13);
		break;
	case 13:
		possibleMoves.push_back(8);
		possibleMoves.push_back(12);
		possibleMoves.push_back(14);
		break;
	case 14:
		possibleMoves.push_back(9);
		possibleMoves.push_back(13);
		break;
	default:
		possibleMoves.push_back(emptySpace - 1);
		possibleMoves.push_back(emptySpace + 1);
		possibleMoves.push_back(emptySpace - 5);
		possibleMoves.push_back(emptySpace + 5);
	}
	return possibleMoves;
}

/****Function to check for puzzle completion****/
bool Puzzle::puzzleComplete()
{
	if (state[0] == state[10] && state[1] == state[11] &&
		state[2] == state[12] && state[3] == state[13] && state[4] == state[14])
	{
		return true;
	}
	return false;
}

int Puzzle::heuristic()
{
	int counter = 0;
	bool used[15] = { false, false, false, false, false,
		false, false, false, false, false,
		false, false, false, false, false };


	for (int x = 0; x < 5; x++)
	{
		if (state[x] == state[x + 10])
		{
			used[x] = true;
			used[x + 10] = true;
		}
		else
		{
			char test;
			if (state[x] == ' ')
			{
				
				if (used[x + 5])
				{
					if (used[x + 4])
					{
						test = state[x + 6];
						used[x + 6] = true;
						counter+=2;
					}
					else
					{
						test = state[x + 4];
						used[x + 4] = true;
						counter+=2;
					}
				}
				else
				{
					test = state[x + 5];
					used[x + 5] = true;
					counter++;
				}				
			}
			else
			{
				test = state[x];
				used[x] = true;
			}
			int lowest = 5000, lowestIndex;
			for (int y = x + 1; y < 15; y++)
			{
				int temp = counter;
				if (test == state[y] && !used[y])
				{
					if (y >= 0 && y <= 4)
						temp += 2;
					else if (y >= 5 && y <= 9)
						temp += 1;

					temp = temp + abs(x - (y % 5));

					if (lowest > temp)
					{
						lowestIndex = y;
						lowest = temp;
					}
					
				}
			}
			counter = lowest;
			used[lowestIndex] = true;
		}

		
	}
	return counter;
}

/****Function to Print Grid****/
void Puzzle::printGrid()
{
	cout << endl << endl;
	cout << "\t  Puzzle Grid\t\t\t  Move Grid" << endl
		<< "---------------------------------------------------------------" << endl << "\t";
	for (int x = 0; x < state.size(); x++)
	{
		cout << "[" << state[x] << "]";

		//print instruction grid and skip line
		if ((x + 1) % 5 == 0)
		{
			cout << "\t\t|";
			if (x == 4)
				cout << "\t[A][B][C][D][E]" << endl << "\t";
			else if (x == 9)
				cout << "\t[F][G][H][I][J]" << endl << "\t";
			else
				cout << "\t[K][L][M][N][O]" << endl << "\t";
		}
	}
	cout << endl << "---------------------------------------------------------------" << endl;
}

/****Function to Print Grid****/
string Puzzle::outputGrid()
{
	string output;
	output = "\n\n";
	output += "\t  Puzzle Grid\t\t\t  Move Grid\n";
    output += "---------------------------------------------------------------\n\t";

	for (int x = 0; x < state.size(); x++)
	{
		output += "[";
		output += state[x];
		output += "]";

		//print instruction grid and skip line
		if ((x + 1) % 5 == 0)
		{
			output += "\t\t|";
			if (x == 4)
				output += "\t[A][B][C][D][E]\n\t";
			else if (x == 9)
				output += "\t[F][G][H][I][J]\n\t";
			else
				output += "\t[K][L][M][N][O]\n";
		}
	}
	output += "---------------------------------------------------------------\n";

	return output;
}

int Puzzle::checkEmptySpace()
{
	emptySpace = -1;

	for (int x = 0; x < state.size(); x++)
	{
		if (state[x] == ' ')
		{
			emptySpace = x;
			break;
		}
	}
	return emptySpace;
}

bool Puzzle::attemptMove(char move)
{
	char moveToChar[15] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O' };
	int moveIndex = (int)(move)-97;
	vector<int> possibleMoves = checkPossibleMoves();

	for (int x = 0; x < possibleMoves.size(); x++)
	{
		if (moveToChar[possibleMoves[x]] == move - 32)
		{
			state[emptySpace] = state[moveIndex];
			state[moveIndex] = ' ';
			emptySpace = moveIndex;
			return true;
		}
	}

	return false;
}

struct node {
	Puzzle state;
	string movesFromStart;
	int h = 0;
};

string Puzzle::autoComplete()
{
	char moveToChar[15] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' };

	stack<node> openList;
	stack<node> closedList;

	node initial;
	initial.state = state;
	openList.push(initial);

	while (!openList.empty())
	{
		vector<node> findLowest;
		while (!openList.empty())
		{
			findLowest.push_back(openList.top());
			openList.pop();
		}
		int lowestIndex = 0;
		for (int x = 1; x < findLowest.size(); x++)
		{
			if (findLowest[lowestIndex].h > findLowest[x].h)
				lowestIndex = x;
		}
		node Parent = findLowest[lowestIndex];
		for (int x = 0; x < findLowest.size(); x++)
		{
			if (x != lowestIndex)
				openList.push(findLowest[x]);
		}
		closedList.push(Parent);

		//check all the next possible moves
		vector<int> possibleMoves = Parent.state.checkPossibleMoves();

		//make each move state and put them at the back of the open list
		for (int x = 0; x < possibleMoves.size(); x++)
		{
			Puzzle tempState = (Parent.state);
			node temp;
			temp.state = Parent.state;


			if (tempState.attemptMove(moveToChar[possibleMoves[x]]))
			{

				//add to openList	
				temp.state = tempState;
				temp.movesFromStart = Parent.movesFromStart + moveToChar[possibleMoves[x]];
				temp.h = Parent.state.heuristic() + tempState.heuristic();				

				stack<node> tempOpenList = openList;
				stack<node> tempClosedList = closedList;

				vector<char> tempTestState = temp.state.getCurrentState();

				bool exsists = false;

				while (!tempOpenList.empty())
				{
					vector<char> testState = tempOpenList.top().state.getCurrentState();
					tempOpenList.pop();

					if (testState[0] == tempTestState[0] &&
						testState[1] == tempTestState[1] &&
						testState[2] == tempTestState[2] &&
						testState[3] == tempTestState[3] &&
						testState[4] == tempTestState[4] &&
						testState[5] == tempTestState[5] &&
						testState[6] == tempTestState[6] &&
						testState[7] == tempTestState[7] &&
						testState[8] == tempTestState[8] &&
						testState[9] == tempTestState[9] &&
						testState[10] == tempTestState[10] &&
						testState[11] == tempTestState[11] &&
						testState[12] == tempTestState[12] &&
						testState[13] == tempTestState[13] &&
						testState[14] == tempTestState[14])
					{
						exsists = true;
					}
				}
				while (!tempClosedList.empty() && exsists == false)
				{
					vector<char> testState = tempClosedList.top().state.getCurrentState();
					tempClosedList.pop();

					if (testState[0] == tempTestState[0] &&
						testState[1] == tempTestState[1] &&
						testState[2] == tempTestState[2] &&
						testState[3] == tempTestState[3] &&
						testState[4] == tempTestState[4] &&
						testState[5] == tempTestState[5] &&
						testState[6] == tempTestState[6] &&
						testState[7] == tempTestState[7] &&
						testState[8] == tempTestState[8] &&
						testState[9] == tempTestState[9] &&
						testState[10] == tempTestState[10] &&
						testState[11] == tempTestState[11] &&
						testState[12] == tempTestState[12] &&
						testState[13] == tempTestState[13] &&
						testState[14] == tempTestState[14])
					{
						exsists = true;
					}
				}

				if (!exsists)
				{
					openList.push(temp);
				}
				
			}

			if (tempState.puzzleComplete())
			{
				return temp.movesFromStart;
			}

		}

	}

	return " ";
}

vector<char> Puzzle::getCurrentState()
{
	return state;
}

