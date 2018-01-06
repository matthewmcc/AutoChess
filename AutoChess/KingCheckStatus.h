
#include "stdafx.h"
#include "ChessState.h"
#include <list>

#pragma once
namespace AutoChess {
	class KingCheckStatus
	{
	public:
		KingCheckStatus(ChessState &currentState, ChessTile &kingToCheck) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			KingToCheck = kingToCheck;
		};

	private:
		std::list<ChessState> PossibleMoves;

		ChessState CurrentState;
		ChessTile KingToCheck;

		inline bool isSafeFromPawns();
		inline bool tileContainsWhitePawn(ChessTile tileToCheck);

		inline bool isSafeFromWhiteKnights();
		inline ChessTile getKnightAttackTile(int knightArrayIndex);
		inline bool tileContainsWhiteKnight(ChessTile tileToCheck);


	};
}