#include "stdafx.h"
#include "ChessState.h"
#include <algorithm>

namespace AutoChess {
	// Initializes the new state as the game start state
	ChessState ChessState::CreateStartState(bool isMaxPlayer)
	{
		ChessState chessState = ChessState();

		chessState.initNewBoard();
		chessState.setWhichPlayersTurn(WHITE_PLAYER);
		chessState.setHeuristsValue(0);
		chessState.setIsMaxPlayer(isMaxPlayer);
	}

	// Creates a new state given the current board state and a move to do.
	ChessState ChessState::CreateNextState(ChessMove moveToDo)
	{
		ChessState newState = ChessState();

		newState.copyBoardState(*this);
		newState.makeMove(moveToDo);

		return newState;
	}

	// Copies the board state to passed
	void ChessState::copyBoardState(ChessState stateToCopy) {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				setBoardTile(i, j, stateToCopy.getBoardTile(i, j));
			}
		}
	}

	void ChessState::makeMove(ChessMove move) {
		char pieceToMove = getBoardTile(move.getMoveFromTile);

		setBoardTile(move.getMoveToTile, pieceToMove);
		setBoardTile(move.getMoveFromTile, EMPTY_TILE);

		LastMove = move;
	}

	// If this is the first board created it'll have this structure.
	void ChessState::initNewBoard()
	{
		char tempBoardState[8][8] = { { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
						{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
						{'_', '_', '_', '_', '_', '_', '_', '_'},
						{'_', '_', '_', '_', '_', '_', '_', '_'},
						{'_', '_', '_', '_', '_', '_', '_', '_'},
						{'_', '_', '_', '_', '_', '_', '_', '_'},
						{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
						{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'} };

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				BoardState[i][j] = tempBoardState[i][j];
			}
		}
	}
}