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

		return chessState;
	}

	// Creates a new state given the current board state and a move to do.
	ChessState ChessState::CreateNextState(ChessMove moveToDo)
	{
		ChessState newState = ChessState();

		newState.copyBoardState(*this);
		newState.calculateHeuristicsValue(*this, getBoardTile(moveToDo.getMoveToTile()));
		newState.makeMove(moveToDo);
		newState.setNextPlayer(*this);

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
		char pieceToMove = getBoardTile(move.getMoveFromTile());

		setBoardTile(move.getMoveToTile(), pieceToMove);
		setBoardTile(move.getMoveFromTile(), EMPTY_TILE);

		LastMove = move;
	}

	void ChessState::calculateHeuristicsValue(ChessState lastState, char pieceTaken) {
		if (IsMaxPlayer)
			setHeuristsValue(lastState.getHeuristsValue() + PIECE_VALUES.at(pieceTaken));
		else 
			setHeuristsValue(lastState.getHeuristsValue() - PIECE_VALUES.at(pieceTaken));
	}

	void ChessState::setNextPlayer(ChessState lastState) {
		if (lastState.getWhichPlayersTurn() == BLACK_PLAYER)
			setWhichPlayersTurn(WHITE_PLAYER);
		else
			setWhichPlayersTurn(BLACK_PLAYER);

		IsMaxPlayer = !lastState.isMaxPlayer();
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

	ChessTile ChessState::getBlackKingLocation() {
		return getPieceLocation(BLACK_KING);
	}

	ChessTile ChessState::getWhiteKingLocation() {
		return getPieceLocation(WHITE_KING);
	}

	// Gets a pieces location. Throws a piece not found exception on failure
	inline ChessTile ChessState::getPieceLocation(char pieceToFind) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (getBoardTile(i, j) == pieceToFind)
					return ChessTile(i, j);
			}
		}

		throw PieceNotFoundException(*this, pieceToFind);
	}
}