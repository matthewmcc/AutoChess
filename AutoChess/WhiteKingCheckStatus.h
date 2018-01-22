
#include "stdafx.h"
#include "ChessState.h"
#include <list>

#pragma once
namespace AutoChess {
	class WhiteKingCheckStatus
	{
	public:
		WhiteKingCheckStatus(ChessState &currentState, ChessTile &kingToCheck) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			KingToCheck = kingToCheck;
		};

		bool isWhiteKingInCheck();

	private:
		std::list<ChessState> PossibleMoves;

		ChessState CurrentState;
		ChessTile KingToCheck;

		inline bool isSafeFromPawns();
		inline bool tileNotBlackPawn(ChessTile tileToCheck);

		inline bool isSafeFromKnights();
		inline ChessTile getKnightAttackTile(int knightArrayIndex);
		inline bool tileIsBlackKnight(ChessTile tileToCheck);

		bool isSafeFromDiagonalMoves();
		bool unsafeDiagonalMove(int diagonalArrayIndex);
		ChessTile getDiagonalAttackTile(int diagonalArrayIndex, int moveLengthMultipler);
		bool tileIsBlackDiagonalPiece(ChessTile tileToTest, int moveLengthMultipler);
		bool haltBlackDiagonalSearch(ChessTile tileToTest, int moveLengthMultipler);


		bool isSafeFromStraightMoves();
		bool unsafeStraightMove(int straightArrayIndex);
		ChessTile getStraightAttackTile(int straightArrayIndex, int moveLengthMultipler);
		bool tileIsBlackStraightPiece(ChessTile tileToTest, int moveLengthMultipler);
		bool haltBlackStraightSearch(ChessTile tileToTest, int moveLengthMultipler);
	};
}