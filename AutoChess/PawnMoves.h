#pragma once

#include "stdafx.h"
#include "ChessState.h"
#include <list>

namespace AutoChess {
	class PawnMoves
	{
	public:
		PawnMoves(ChessState &currentState, ChessTile &pawnToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			PawnToMove = pawnToMove;
		};

		/// White and black moves divided for effciency 
		std::list<ChessState> getBlackPawnMoves();
		std::list<ChessState> getWhitePawnMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile PawnToMove;

		inline void blackStraightMoves();
		inline void blackTwoTileStraightMove();

		inline void blackOffensiveMoves();
		inline void blackAddLegalMove(ChessTile&);

		inline ChessTile createNextBlackMoveTile(int);

		inline void whiteStraightMoves();
		inline void whiteTwoTileStraightMove();

		inline void whiteOffensiveMoves();
		inline void whiteAddLegalMove(ChessTile&);

		inline ChessTile createNextWhiteMoveTile(int);

		inline void addPossibleMove(ChessTile&);
	};
}