
#include "stdafx.h"
#include "ChessState.h"
#include <list>

#pragma once
namespace AutoChess {
	class BlackKingCheckStatus
	{
	public:
		BlackKingCheckStatus(ChessState &currentState, ChessTile &kingToCheck) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			KingToCheck = kingToCheck;
		};

		bool isBlackKingInCheck();

	private:
		std::list<ChessState> PossibleMoves;

		ChessState CurrentState;
		ChessTile KingToCheck;

		inline bool isSafeFromPawns();
		inline bool tileNotWhitePawn(ChessTile tileToCheck);

		inline bool isSafeFromKnights();
		inline ChessTile getKnightAttackTile(int knightArrayIndex);
		inline bool tileNotWhiteKnight(ChessTile tileToCheck);


		inline bool isSafeFromDiagonalMoves();
		inline bool unsafeDiagonalMove(int diagonalArrayIndex);
		inline ChessTile getWhiteDiagonalAttackTile(int diagonalArrayIndex, int moveLengthMultipler);
		inline bool tileNotWhiteDiagonalPiece(ChessTile tileToTest, int moveLengthMultipler);
		inline bool haltWhiteDiagonalSearch(ChessTile tileToTest, int moveLengthMultipler);


		inline bool isSafeFromStraightMoves();
		inline bool unsafeStraightMove(int straightArrayIndex);
		inline ChessTile getWhiteStraightAttackTile(int straightArrayIndex, int moveLengthMultipler);
		inline bool tileNotWhiteStraightPiece(ChessTile tileToTest, int moveLengthMultipler);
		inline bool haltWhiteStraightSearch(ChessTile tileToTest, int moveLengthMultipler);
	};
}