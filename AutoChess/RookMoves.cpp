#include "stdafx.h"
#include "RookMoves.h"

namespace AutoChess {
	std::list<ChessState> RookMoves::getBlackRookMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	std::list<ChessState> RookMoves::getWhiteRookMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	void RookMoves::addBlackDirectionMoves(int moveArrayIndex) 
	{
		int moveLengthMultipler = 1;
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);

		for (;moveToTile.isInBoardBounds(); moveLengthMultipler++)
		{
			if (isLegalBlackMove(moveToTile))
				addPossibleMove(moveToTile);
			else 
				return;

			moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);
		}
	}

	bool RookMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest));
	}

	void RookMoves::addWhiteDirectionMoves(int moveArrayIndex)
	{
		int moveLengthMultipler = 1;
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);

		for (; moveToTile.isInBoardBounds(); moveLengthMultipler++)
		{
			if (isLegalWhiteMove(moveToTile))
				addPossibleMove(moveToTile);
			else
				return;

			moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);
		}
	}

	ChessTile RookMoves::createNextMoveTile(int moveArrayIndex, int moveLengthMultipler) {
		ChessTile moveToTile = ChessTile(RookToMove.getX() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			RookToMove.getY() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		return moveToTile;
	}

	bool RookMoves::isLegalWhiteMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceBlack(moveToTest));
	}

	void RookMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(RookToMove, moveToAdd);
		PossibleMoves.push_front(CurrentState.CreateNextState(moveToMake));
	}
}
