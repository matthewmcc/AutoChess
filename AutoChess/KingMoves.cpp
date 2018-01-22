#include "stdafx.h"
#include "KingMoves.h"
#include "BlackKingCheckStatus.h"
#include "WhiteKingCheckStatus.h"

namespace AutoChess {
	std::list<ChessState> KingMoves::getBlackKingMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMove(moveArrayIndex);
		}

		return PossibleMoves;
	}

	void KingMoves::addBlackDirectionMove(int moveArrayIndex)
	{
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex);

		if (isLegalBlackKingMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	bool KingMoves::isLegalBlackKingMove(ChessTile moveToTest) {
		return (isLegalBlackMove(moveToTest) &&
			blackKingNotInCheck(moveToTest));
	}

	bool KingMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (moveToTest.isInBoardBounds() &&
			(CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest)));
	}

	bool KingMoves::blackKingNotInCheck(ChessTile moveToTest) {
		BlackKingCheckStatus blackKingCheck = BlackKingCheckStatus(CurrentState, moveToTest);
		
		if (blackKingCheck.isBlackKingInCheck())
			return false;
		else
			return true;
	}

	std::list<ChessState> KingMoves::getWhiteKingMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMove(moveArrayIndex);
		}

		return PossibleMoves;
	}

	void KingMoves::addWhiteDirectionMove(int moveArrayIndex)
	{
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex);

		if (isLegalWhiteKingMove(moveToTile))
			addPossibleMove(moveToTile);
	}

	bool KingMoves::isLegalWhiteKingMove(ChessTile moveToTest) {
		return (isLegalWhiteMove(moveToTest) &&
			whiteKingNotInCheck(moveToTest));
	}

	bool KingMoves::isLegalWhiteMove(ChessTile moveToTest) {
		return (moveToTest.isInBoardBounds() &&
			(CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceBlack(moveToTest)));
	}

	bool KingMoves::whiteKingNotInCheck(ChessTile moveToTest) {
		WhiteKingCheckStatus whiteKingCheck = WhiteKingCheckStatus(CurrentState, moveToTest);

		if (whiteKingCheck.isWhiteKingInCheck())
			return false;
		else
			return true;
	}

	ChessTile KingMoves::createNextMoveTile(int moveArrayIndex) {
		ChessTile moveToTile = ChessTile(KingToMove.getX() + DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][0],
			KingToMove.getY() + DIAGONAL_STRAIGHT_MOVES[moveArrayIndex][1]);

		return moveToTile;
	}

	void KingMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(KingToMove, moveToAdd);
		PossibleMoves.push_front(CurrentState.CreateNextState(moveToMake));
	}
}
