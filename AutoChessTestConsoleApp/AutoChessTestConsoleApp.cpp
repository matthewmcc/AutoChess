// AutoChessTestConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChessRules.h"
#include "ChessState.h"

void recurseToDepth(std::list<AutoChess::ChessState> moves, int depth) {
	if (depth >= 40) {
		return;
	}

	AutoChess::ChessRules chessRules = AutoChess::ChessRules::getInstance();

	for (AutoChess::ChessState move : moves)
	{
		std::list<AutoChess::ChessState> nextMoves = chessRules.getMoves(move);
		
		if (nextMoves.size() == 0) {
			delete &nextMoves;
			return;
		}

		int nextDepth = depth + 1;
		recurseToDepth(nextMoves, nextDepth);
	}

	delete &moves;
}

int main()
{
	AutoChess::ChessRules chessRules = AutoChess::ChessRules::getInstance();

	AutoChess::ChessState chessState = AutoChess::ChessState::CreateStartState(true);
	std::list<AutoChess::ChessState> moves = chessRules.getMoves(chessState);


	recurseToDepth(moves, 0);

    return 0;
}
