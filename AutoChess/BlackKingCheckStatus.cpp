#include "stdafx.h"
#include "BlackKingCheckStatus.h"

namespace AutoChess {
	bool BlackKingCheckStatus::isBlackKingInCheck() {
		if (isSafeFromPawns() &&
			isSafeFromKnights() &&
			isSafeFromDiagonalMoves() &&
			isSafeFromStraightMoves())
			return false;
		else
			return true;
	}

	bool BlackKingCheckStatus::isSafeFromPawns() {
		ChessTile leftPawnAttack = ChessTile(KingToCheck.getX() + WHITE_PAWNS_ATTACK_MOVES[0][0],
			KingToCheck.getY() + WHITE_PAWNS_ATTACK_MOVES[0][1]);

		ChessTile rightPawnAttack = ChessTile(KingToCheck.getX() + WHITE_PAWNS_ATTACK_MOVES[1][0],
			KingToCheck.getY() + WHITE_PAWNS_ATTACK_MOVES[1][1]);

		return (tileNotWhitePawn(leftPawnAttack) ||
			tileNotWhitePawn(rightPawnAttack));
	}

	bool BlackKingCheckStatus::tileNotWhitePawn(ChessTile tileToCheck) {
		return CurrentState.getBoardTile(tileToCheck) != WHITE_PAWN;
	}

	bool BlackKingCheckStatus::isSafeFromKnights() {
		for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
			ChessTile tileToCheck = getKnightAttackTile(j);
			
			if (tileNotWhiteKnight(tileToCheck))
				return false;
		}

		return true;
	}

	ChessTile BlackKingCheckStatus::getKnightAttackTile(int knightArrayIndex) {
		return ChessTile(KingToCheck.getX() + KNIGHT_MOVES[knightArrayIndex][0],
			KingToCheck.getY() + KNIGHT_MOVES[knightArrayIndex][1]);
	}

	bool BlackKingCheckStatus::tileNotWhiteKnight(ChessTile tileToCheck) {
		return CurrentState.getBoardTile(tileToCheck) != WHITE_KNIGHT;
	}

	bool BlackKingCheckStatus::isSafeFromDiagonalMoves() {
		// King, Queen and Rook check
		for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++)
		{
			if (unsafeDiagonalMove(j))
				return false;
		}

		return true;
	}

	bool BlackKingCheckStatus::unsafeDiagonalMove(int diagonalArrayIndex) {
		int moveLengthMultipler = 1;
		ChessTile tileToCheck = getWhiteDiagonalAttackTile(diagonalArrayIndex, moveLengthMultipler);

		while (tileToCheck.isInBoardBounds())
		{
			if (tileNotWhiteDiagonalPiece(tileToCheck, moveLengthMultipler)) 
			{
				if (haltWhiteDiagonalSearch(tileToCheck, moveLengthMultipler))
					return false;
			}
			else
				return true;

			moveLengthMultipler++;
			tileToCheck = getWhiteDiagonalAttackTile(diagonalArrayIndex, moveLengthMultipler);
		}

		return false;
	}

	ChessTile BlackKingCheckStatus::getWhiteDiagonalAttackTile(int diagonalArrayIndex, int moveLengthMultipler) {
		return ChessTile(KingToCheck.getX() + (DIAGONAL_MOVES[diagonalArrayIndex][0] * moveLengthMultipler),
			KingToCheck.getY() + (DIAGONAL_MOVES[diagonalArrayIndex][1] * moveLengthMultipler));
	}

	bool BlackKingCheckStatus::tileNotWhiteDiagonalPiece(ChessTile tileToTest, int moveLengthMultipler) {
		char pieceToTest = CurrentState.getBoardTile(tileToTest);

		return (pieceToTest != WHITE_QUEEN || pieceToTest != WHITE_BISHOP ||
			(moveLengthMultipler == 1 && pieceToTest != WHITE_KING));
	}

	bool BlackKingCheckStatus::haltWhiteDiagonalSearch(ChessTile tileToTest, int moveLengthMultipler) {
		if (CurrentState.isTileEmpty(tileToTest))
			return false;

		else if (CurrentState.isTilesPieceWhite(tileToTest))
			return true;
		/// Because the black king hasn't been moved to it's new positon yet it should...
		/// ...be treated as an empty tile.
		else if (moveLengthMultipler == 1 && CurrentState.getBoardTile(tileToTest) == BLACK_KING)
			return false;

		else
			return true;
	}


	bool BlackKingCheckStatus::isSafeFromStraightMoves() {
		// King, Queen and Rook check
		for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++)
		{
			if (unsafeStraightMove(j))
				return false;
		}

		return true;
	}

	bool BlackKingCheckStatus::unsafeStraightMove(int straightArrayIndex) {
		int moveLengthMultipler = 1;
		ChessTile tileToCheck = getWhiteStraightAttackTile(straightArrayIndex, moveLengthMultipler);

		while (tileToCheck.isInBoardBounds())
		{
			if (tileNotWhiteStraightPiece(tileToCheck, moveLengthMultipler))
			{
				if (haltWhiteStraightSearch(tileToCheck, moveLengthMultipler))
					return false;
			}
			else
				return true;

			moveLengthMultipler++;
			tileToCheck = getWhiteStraightAttackTile(straightArrayIndex, moveLengthMultipler);
		}

		return false;
	}

	ChessTile BlackKingCheckStatus::getWhiteStraightAttackTile(int straightArrayIndex, int moveLengthMultipler) {
		return ChessTile(KingToCheck.getX() + (STRAIGHT_MOVES[straightArrayIndex][0] * moveLengthMultipler),
			KingToCheck.getY() + (STRAIGHT_MOVES[straightArrayIndex][1] * moveLengthMultipler));
	}

	bool BlackKingCheckStatus::tileNotWhiteStraightPiece(ChessTile tileToTest, int moveLengthMultipler) {
		char pieceToTest = CurrentState.getBoardTile(tileToTest);

		return (pieceToTest != WHITE_QUEEN || pieceToTest != WHITE_ROOK ||
			(moveLengthMultipler == 1 && pieceToTest != WHITE_KING));
	}

	bool BlackKingCheckStatus::haltWhiteStraightSearch(ChessTile tileToTest, int moveLengthMultipler) {
		if (CurrentState.isTileEmpty(tileToTest))
			return false;

		else if (CurrentState.isTilesPieceWhite(tileToTest))
			return true;
		/// Because the black king hasn't been moved to it's new positon yet it should...
		/// ...be treated as an empty tile.
		else if (moveLengthMultipler == 1 && CurrentState.getBoardTile(tileToTest) == BLACK_KING)
			return false;

		else
			return true;
	}
}