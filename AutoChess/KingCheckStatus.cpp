#include "stdafx.h"
#include "KingCheckStatus.h"


namespace AutoChess {
	bool KingCheckStatus::isSafeFromPawns() {
		ChessTile leftPawnAttack = ChessTile(KingToCheck.getX() + WHITE_PAWNS_ATTACK_MOVES[0][0],
			KingToCheck.getY() + WHITE_PAWNS_ATTACK_MOVES[0][1]);

		ChessTile rightPawnAttack = ChessTile(KingToCheck.getX() + WHITE_PAWNS_ATTACK_MOVES[1][0],
			KingToCheck.getY() + WHITE_PAWNS_ATTACK_MOVES[1][1]);

		return (tileFreeOfWhitePawn(leftPawnAttack) ||
			tileContainsWhitePawn(rightPawnAttack));
	}

	bool KingCheckStatus::tileFreeOfWhitePawn(ChessTile tileToCheck) {
		return CurrentState.getBoardTile(tileToCheck) != WHITE_PAWN;
	}

	bool KingCheckStatus::isSafeFromWhiteKnights() {
		for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
			ChessTile tileToCheck = getKnightAttackTile(j);
			
			if (tileFreeOfWhiteKnight(tileToCheck))
				return false;
		}

		return true;
	}

	ChessTile KingCheckStatus::getKnightAttackTile(int knightArrayIndex) {
		return ChessTile(KingToCheck.getX() + KNIGHT_MOVES[knightArrayIndex][0],
			KingToCheck.getY() + KNIGHT_MOVES[knightArrayIndex][1]);
	}

	bool KingCheckStatus::tileFreeOfWhiteKnight(ChessTile tileToCheck) {
		return CurrentState.getBoardTile(tileToCheck) != WHITE_KNIGHT;
	}

	bool isSafeFromStraightMoves() {

	}

	bool isSafeFromDiagonalMoves() {
		// King, Queen and Rook check
		for (int j = 0, int moveLengthMultipler = 1; j < STRAIGHT_ARRAY_LENGTH; j++)
		{
			ChessTile tileToCheck = getDiagonalAttackTile(j, moveLengthMultipler);

			while (tileToCheck.isInBoardBounds())
			{
				comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

				if (comparePiece == WHITE_QUEEN || comparePiece == WHITE_ROOK ||
					(multipler == 1 && comparePiece == WHITE_KING)) {
					return true;
				}
			}
		}
	}

	ChessTile KingCheckStatus::getDiagonalAttackTile(int diagonalArrayIndex, int moveLengthMultipler) {
		return ChessTile(KingToCheck.getX() + (STRAIGHT_MOVES[diagonalArrayIndex][0] * moveLengthMultipler),
			KingToCheck.getY() + (STRAIGHT_MOVES[diagonalArrayIndex][1] * moveLengthMultipler));
	}

	bool tileContainsWhite

}

// Checks if the black king is in a state of Check
inline bool ChessRules::isBlackInCheck(ChessState &currState, int *kingToCheck) {
	int moveTo[2];
	int multipler;

	char comparePiece;

	// King, Queen and Bishop check
	for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++)
	{
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);

		while (inRange(moveTo)) {
			comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

			if (comparePiece == WHITE_QUEEN || comparePiece == WHITE_BISHOP ||
				(multipler == 1 && comparePiece == WHITE_KING)) {
				return true;
			}

			multipler++;

			moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);
		}
	}

	// King, Queen and Rook check
	for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++)
	{
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (STRAIGHT_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (STRAIGHT_MOVES[j][1] * multipler);

		while (inRange(moveTo))
		{
			comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

			if (comparePiece == WHITE_QUEEN || comparePiece == WHITE_ROOK ||
				(multipler == 1 && comparePiece == WHITE_KING)) {
				return true;
			}
		}
	}

	return false;
}
