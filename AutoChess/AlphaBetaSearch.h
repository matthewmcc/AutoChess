#include "stdafx.h"
#include <list>


/// State class must include the current game board state, current teams turn and 
/// last move to get to the current state.
template <typename State>
class AlphaBetaSearch
{
protected:
	int MaxScore;
	int MaxSearchTime;

	AlphaBetaSearch<State>(int, int);

	// Uses the maxscore and minscore functions to calculate the best 
	// move within the given depth.
	State nextMove(State, int);

	// Recursive functions that call each other calculating the best possible move.
	double maxscore(State, int, double, double);
	double minscore(State, int, double, double);

	// Function that returns a Heuristic value calculated from the current game state.
	virtual int heuristic(State);

	// Function to test if the game has reach a conclusion
	virtual bool terminalTest(State);

	// Returns a list of all the next possible states from a current give state.
	virtual std::list<State> nextMoves(State);
};

