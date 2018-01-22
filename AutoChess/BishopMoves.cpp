#include "stdafx.h"
#include "BishopMoves.h"

namespace AutoChess {
	std::list<ChessState> BishopMoves::getBlackBishopMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_ARRAY_LENGTH; moveArrayIndex++)
		{
			addBlackDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	std::list<ChessState> BishopMoves::getWhiteBishopMoves() {
		/// Checks all possible straight moves
		for (int moveArrayIndex = 0; moveArrayIndex < DIAGONAL_ARRAY_LENGTH; moveArrayIndex++)
		{
			addWhiteDirectionMoves(moveArrayIndex);
		}

		return PossibleMoves;
	}

	void BishopMoves::addBlackDirectionMoves(int moveArrayIndex)
	{
		int moveLengthMultipler = 1;
		ChessTile moveToTile = createNextMoveTile(moveArrayIndex, moveLengthMultipler);

		for (; moveToTile.isInBoardBounds(); moveLengthMultipler++)
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

	bool BishopMoves::isLegalBlackMove(ChessTile moveToTest) {
		return (CurrentState.isTileEmpty(moveToTest) ||
			CurrentState.isTilesPieceWhite(moveToTest));
	}

	void BishopMoves::addWhiteDirectionMoves(int moveArrayIndex)
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

	ChessTile BishopMoves::createNextMoveTile(int moveArrayIndex, int moveLengthMultipler) {
		ChessTile moveToTile = ChessTile(BishopToMove.getX() + (DIAGONAL_MOVES[moveArrayIndex][0] * moveLengthMultipler),
			BishopToMove.getY() + (DIAGONAL_MOVES[moveArrayIndex][1] * moveLengthMultipler));

		return moveToTile;
	}

	void BishopMoves::addPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(BishopToMove, moveToAdd);
		PossibleMoves.push_front(CurrentState.CreateNextState(moveToMake));
	}
}
