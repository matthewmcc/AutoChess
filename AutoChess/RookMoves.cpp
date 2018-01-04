#include "stdafx.h"
#include "RookMoves.h"

namespace AutoChess {
	std::list<ChessState> RookMoves::getRookMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < STRAIGHT_ARRAY_LENGTH; moveArrayIndex++)
		{
			addDirectionsMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	ChessMove RookMoves::addDirectionsMoves(int moveArrayIndex) 
	{
		int moveLengthMultipler = 1;
		ChessMove moveToMake = createNextMove(moveArrayIndex, moveLengthMultipler);

		for (;moveToTile.isInBoardBounds(); moveLengthMultipler++)
		{
			// Checks if the square been moved to is free or if the pieces involved are different case.
			if (CurrentState.isTileEmpty(moveToTile) ||
				(isupper(movingTo) ^ isupper(movingPiece))) 
			{
				PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
			}
			else
				break;

			moveToMake = createNextMove(moveArrayIndex, moveLengthMultipler);
		}
	}

	ChessMove RookMoves::createNextMove(int moveArrayIndex, int moveLenghtMultipler) {
		ChessTile moveToTile = ChessTile(RookToMove.getX() + (STRAIGHT_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			RookToMove.getY() + (STRAIGHT_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		ChessMove moveToMake = ChessMove::CreateMove(RookToMove, moveToTile);

		return moveToMake;
	}
}
