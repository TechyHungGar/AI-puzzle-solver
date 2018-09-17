
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

class Puzzle
{
public:
	Puzzle();
	Puzzle(vector<char>);
	~Puzzle();
	void printGrid();
	string outputGrid();
	bool puzzleComplete();
	vector<int> checkPossibleMoves();
	int checkEmptySpace();
	bool attemptMove(char);
	string autoComplete();
	vector<char> getCurrentState();
	int heuristic();

private:
	vector<char> state;
	int emptySpace;

};

