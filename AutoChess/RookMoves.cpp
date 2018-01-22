#include "stdafx.h"
#include "RookMoves.h"

namespace AutoChess {
	std::list<ChessState> RookMoves::getBlackRookMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	std::list<ChessState> RookMoves::getWhiteRookMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
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
			if (CurrentState.isTileEmpty(moveToTile))
				addPossibleMove(moveToTile);
			else if (CurrentState.isTilesPieceWhite(moveToTile)) {
				addPossibleMove(moveToTile);
				break;
			}
			else
				break;

			moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);
		}
	}

	void RookMoves::addWhiteDirectionMoves(int moveArrayIndex)
	{
		int moveLengthMultipler = 1;
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);

		for (; moveToTile.isInBoardBounds(); moveLengthMultipler++)
		{
			if (CurrentState.isTileEmpty(moveToTile))
				addPossibleMove(moveToTile);
			else if (CurrentState.isTilesPieceBlack(moveToTile)) {
				addPossibleMove(moveToTile);
				break;
			}
			else
				break;

			moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);
		}
	}

	ChessTile RookMoves::createNextMoveTile(int moveArrayIndex, int moveLengthMultipler) {
		ChessTile moveToTile = ChessTile(RookToMove.getX() + (STRAIGHT_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			RookToMove.getY() + (STRAIGHT_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		return moveToTile;
	}

	void RookMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(RookToMove, moveToAdd);
		PossibleMoves.push_front(CurrentState.CreateNextState(moveToMake));
	}
}
