#include "stdafx.h"
#include "QueenMoves.h"

namespace AutoChess {
	std::list<ChessState> QueenMoves::getBlackQueenMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	std::list<ChessState> QueenMoves::getWhiteQueenMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	ChessMove QueenMoves::addBlackDirectionMoves(int moveArrayIndex)
	{
		int moveLengthMultipler = 1;
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);

		for (; moveToTile.isInBoardBounds(); moveLengthMultipler++)
		{
			if (isLegalBlackMove(moveToTile))
				addPossibleMove(moveToTile);
			else
				return;

			moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);
		}
	}

	bool QueenMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest));
	}

	ChessMove QueenMoves::addWhiteDirectionMoves(int moveArrayIndex)
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

	ChessTile QueenMoves::createNextMoveTile(int moveArrayIndex, int moveLengthMultipler) {
		ChessTile moveToTile = ChessTile(QueenToMove.getX() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			QueenToMove.getY() + (DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		return moveToTile;
	}

	bool QueenMoves::isLegalWhiteMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceBlack(moveToTest));
	}

	void QueenMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(QueenToMove, moveToAdd);
		PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
	}
}
