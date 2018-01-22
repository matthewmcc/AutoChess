#include "stdafx.h"
#include "WhiteKingCheckStatus.h"

namespace AutoChess {
	bool WhiteKingCheckStatus::isWhiteKingInCheck() {
		if (isSafeFromPawns() &&
			isSafeFromKnights() &&
			isSafeFromDiagonalMoves() &&
			isSafeFromStraightMoves())
			return false;
		else
			return true;
	}

	bool WhiteKingCheckStatus::isSafeFromPawns() {
		ChessTile leftPawnAttack = ChessTile(KingToCheck.getX() + BLACK_PAWNS_ATTACK_MOVES[0][0],
			KingToCheck.getY() + BLACK_PAWNS_ATTACK_MOVES[0][1]);

		ChessTile rightPawnAttack = ChessTile(KingToCheck.getX() + BLACK_PAWNS_ATTACK_MOVES[1][0],
			KingToCheck.getY() + BLACK_PAWNS_ATTACK_MOVES[1][1]);

		return (tileNotBlackPawn(leftPawnAttack) ||
			tileNotBlackPawn(rightPawnAttack));
	}

	bool WhiteKingCheckStatus::tileNotBlackPawn(ChessTile tileToCheck) {
		if (tileToCheck.isInBoardBounds()) 
		{
			return CurrentState.getBoardTile(tileToCheck) == BLACK_PAWN;
		}
		return true;
	}

	bool WhiteKingCheckStatus::isSafeFromKnights() {
		for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
			ChessTile tileToCheck = getKnightAttackTile(j);
			
			if (tileIsBlackKnight(tileToCheck))
				return false;
		}

		return true;
	}

	ChessTile WhiteKingCheckStatus::getKnightAttackTile(int knightArrayIndex) {
		return ChessTile(KingToCheck.getX() + KNIGHT_MOVES[knightArrayIndex][0],
			KingToCheck.getY() + KNIGHT_MOVES[knightArrayIndex][1]);
	}

	bool WhiteKingCheckStatus::tileIsBlackKnight(ChessTile tileToCheck) {
		return CurrentState.getBoardTile(tileToCheck) == BLACK_KNIGHT;
	}

	bool WhiteKingCheckStatus::isSafeFromDiagonalMoves() {
		for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++)
		{
			if (unsafeDiagonalMove(j))
				return false;
		}

		return true;
	}

	bool WhiteKingCheckStatus::unsafeDiagonalMove(int diagonalArrayIndex) {
		int moveLengthMultipler = 1;
		ChessTile tileToCheck = getDiagonalAttackTile(diagonalArrayIndex, moveLengthMultipler);

		while (tileToCheck.isInBoardBounds())
		{
			if (tileIsBlackDiagonalPiece(tileToCheck, moveLengthMultipler)) 
				return true;
			else 
			{
				if (haltBlackDiagonalSearch(tileToCheck, moveLengthMultipler))
					return false;
			}
				

			moveLengthMultipler++;
			tileToCheck = getDiagonalAttackTile(diagonalArrayIndex, moveLengthMultipler);
		}

		return false;
	}

	ChessTile WhiteKingCheckStatus::getDiagonalAttackTile(int diagonalArrayIndex, int moveLengthMultipler) {
		return ChessTile(KingToCheck.getX() + (DIAGONAL_MOVES[diagonalArrayIndex][0] * moveLengthMultipler),
			KingToCheck.getY() + (DIAGONAL_MOVES[diagonalArrayIndex][1] * moveLengthMultipler));
	}

	bool WhiteKingCheckStatus::tileIsBlackDiagonalPiece(ChessTile tileToTest, int moveLengthMultipler) {
		char pieceToTest = CurrentState.getBoardTile(tileToTest);

		return (pieceToTest == BLACK_QUEEN || pieceToTest == BLACK_BISHOP ||
			(moveLengthMultipler == 1 && pieceToTest == BLACK_KING));
	}

	bool WhiteKingCheckStatus::haltBlackDiagonalSearch(ChessTile tileToTest, int moveLengthMultipler) {
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


	bool WhiteKingCheckStatus::isSafeFromStraightMoves() {
		// King, Queen and Rook check
		for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++)
		{
			if (unsafeStraightMove(j))
				return false;
		}

		return true;
	}

	bool WhiteKingCheckStatus::unsafeStraightMove(int straightArrayIndex) {
		int moveLengthMultipler = 1;
		ChessTile tileToCheck = getStraightAttackTile(straightArrayIndex, moveLengthMultipler);

		while (tileToCheck.isInBoardBounds())
		{
			if (tileIsBlackStraightPiece(tileToCheck, moveLengthMultipler))
				return true;
			else
			{
				if (haltBlackStraightSearch(tileToCheck, moveLengthMultipler))
					return false;
			}

			moveLengthMultipler++;
			tileToCheck = getStraightAttackTile(straightArrayIndex, moveLengthMultipler);
		}

		return false;
	}

	ChessTile WhiteKingCheckStatus::getStraightAttackTile(int straightArrayIndex, int moveLengthMultipler) {
		return ChessTile(KingToCheck.getX() + (STRAIGHT_MOVES[straightArrayIndex][0] * moveLengthMultipler),
			KingToCheck.getY() + (STRAIGHT_MOVES[straightArrayIndex][1] * moveLengthMultipler));
	}

	bool WhiteKingCheckStatus::tileIsBlackStraightPiece(ChessTile tileToTest, int moveLengthMultipler) {
		char pieceToTest = CurrentState.getBoardTile(tileToTest);

		return (pieceToTest == BLACK_QUEEN || pieceToTest == BLACK_ROOK ||
			(moveLengthMultipler == 1 && pieceToTest == BLACK_KING));
	}

	bool WhiteKingCheckStatus::haltBlackStraightSearch(ChessTile tileToTest, int moveLengthMultipler) {
		if (CurrentState.isTileEmpty(tileToTest))
			return false;

		else if (CurrentState.isTilesPieceBlack(tileToTest))
			return true;
		/// Because the black king hasn't been moved to it's new positon yet it should...
		/// ...be treated as an empty tile.
		else if (moveLengthMultipler == 1 && CurrentState.getBoardTile(tileToTest) == WHITE_KING)
			return false;

		else
			return true;
	}
}