#include "stdafx.h"
#include "KingMoves.h"

namespace AutoChess {
	std::list<ChessState> KingMoves::getBlackKingMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMove(moveArrayIndex);
		}

		return PossibleMoves;
	}

	ChessMove KingMoves::addBlackDirectionMove(int moveArrayIndex)
	{
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex);

		if (isLegalBlackKingMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	bool KingMoves::isLegalBlackKingMove(ChessTile moveToTest) {
		if (CurrentState.isLegalBlackMoves(moveToTest) &&
			!isBlackInCheck(currState, moveToCheck))
			return true;
		else
			return false;
	}

	bool KingMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest));

	}

	std::list<ChessState> KingMoves::getWhiteKingMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMove(moveArrayIndex);
		}

		return PossibleMoves;
	}

	ChessMove KingMoves::addWhiteDirectionMove(int moveArrayIndex)
	{
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex);

		if (isLegalWhiteKingMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	bool KingMoves::isLegalWhiteKingMove(ChessTile moveToTest) {
		if (isLegalWhiteMove(moveToTest) &&
			!isWhiteInCheck(currState, moveToCheck))
			return true;
		else
			return false;
	}

	bool KingMoves::isLegalWhiteMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest));

	}


	ChessTile KingMoves::createNextMoveTile(int moveArrayIndex, int moveLengthMultipler) {
		ChessTile moveToTile = ChessTile(KingToMove.getX() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			KingToMove.getY() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		return moveToTile;
	}

	void KingMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(KingToMove, moveToAdd);
		PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
	}









	/*
	/// Finds all the possible moves a king can make that are not illegal
	inline void ChessRules::getKingMoves(std::list<ChessState> &moves, ChessState &currState, int *kingToMove)
	{
		// Holds the board location that are been checked for oppenent moves to.
		int moveToCheck[2];

		bool next;

		/// Checks all 8 possible moves around the king to make sure hes not moving into check.
		for (int i = 0; i < DIA_STRI_ARRAY_LENGTH; i++)
		{
			moveToCheck[0] = kingToMove[0] + (DIA_STRI_MOVES[i][0]);
			moveToCheck[1] = kingToMove[1] + (DIA_STRI_MOVES[i][1]);

			if (inRange(moveToCheck)) {
				next = false;

				/// Black moves
				if (currState.getWhichPlayersTurn() == BLACK_PLAYER) {
					// Stop checking this square if the piece occuping it is the same color.
					// And not the king itself.
					if ((currState.getBoardTile(moveToCheck[0], moveToCheck[1]) < 96) &&
						currState.getBoardTile(moveToCheck[0], moveToCheck[1]) != BLACK_KING)
						continue;

					if (isBlackInCheck(currState, moveToCheck))
						continue;
				}
				/// White moves
				else {
					// Stop checking this square if the piece occuping it is the same color. 
					// And not the king itself.
					if (currState.getBoardTile(moveToCheck[0], moveToCheck[1]) > 91)
						continue;

					if (isWhiteInCheck(currState, moveToCheck))
						continue;
				}

				// Creates and adds the move to the new move array.
				moves.push_back(createState(currState, kingToMove, moveToCheck));
			}
		}
	}*/
}
