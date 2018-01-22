#include "stdafx.h"
#include "KnightMoves.h"

namespace AutoChess {
	std::list<ChessState> KnightMoves::getBlackKnightMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < KNIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	std::list<ChessState> KnightMoves::getWhiteKnightMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < KNIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	void KnightMoves::addBlackDirectionMoves(int moveArrayIndex)
	{
		ChessTile moveToTile = createMoveTile(moveArrayIndex);

		if (isLegalBlackMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	bool KnightMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (moveToTest.isInBoardBounds() &&
			(CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest)));
	}

	void KnightMoves::addWhiteDirectionMoves(int moveArrayIndex)
	{
		ChessTile moveToTile = createMoveTile(moveArrayIndex);

		if (isLegalWhiteMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	ChessTile KnightMoves::createMoveTile(int moveArrayIndex) {
		ChessTile moveToTile = ChessTile(KnightToMove.getX() + (KNIGHT_MOVES[moveArrayIndex][0]),
			KnightToMove.getY() + (KNIGHT_MOVES[moveArrayIndex][1]));

		return moveToTile;
	}

	bool KnightMoves::isLegalWhiteMove(ChessTile moveToTest) {
		return (moveToTest.isInBoardBounds() &&
			(CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceBlack(moveToTest)));
	}

	void KnightMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(KnightToMove, moveToAdd);
		PossibleMoves.push_front(CurrentState.CreateNextState(moveToMake));
	}
}
