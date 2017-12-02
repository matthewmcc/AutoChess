// AutoChess.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "AlphaBetaSearch.h"
#include "ChessState.h"

class AutoChess : public AlphaBetaSearch<ChessState> {
public:
	ChessState currentState;
	
private:
	// Function that returns a Heuristic value calculated from the current game state.
	int heuristic(ChessState);

	// Function to test if the game has reach a conclusion
	bool terminalTest(ChessState);

	// Returns a list of all the next possible states from a current give state.
	std::vector<ChessState> nextMoves(ChessState);
};

int AutoChess::heuristic(ChessState)
{
	return 0;
}

bool AutoChess::terminalTest(ChessState)
{
	return false;
}

std::vector<ChessState> AutoChess::nextMoves(ChessState)
{
	return std::vector<ChessState>();
}
