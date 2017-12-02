#include "stdafx.h"
#include "ChessState.h"
#include <algorithm>


ChessState::ChessState()
{
	initNewBoard();
	movePlayer = 'W';
	heuristicVal = 0;
}

// Copys the state the board is been passed into a new one.
ChessState::ChessState(char *state, int *move)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			boardState[i][j] = state[(i * 8) + j];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			lastMove[i][j] = move[(i * 2) + j];
		}
	}
}

ChessState::~ChessState()
{
}

// If this is the first board created it'll have this structure.
void ChessState::initNewBoard() 
{
	char bS[8][8] = { { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
					{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
					{'_', '_', '_', '_', '_', '_', '_', '_'},
					{'_', '_', '_', '_', '_', '_', '_', '_'},
					{'_', '_', '_', '_', '_', '_', '_', '_'},
					{'_', '_', '_', '_', '_', '_', '_', '_'},
					{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
					{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} };

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			boardState[i][j] = bS[i][j];
		}
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {
			lastMove[i][j] = ' ';
		}
	}
}
