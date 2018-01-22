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

		inline void blackStraightMove();
		inline void doubleBlackStraightMove();
		inline void blackOffensiveMoves();

		inline bool blackAddLegalMove(ChessTile&);
		inline void blackAddLegalOffensiveMove(ChessTile&);

		inline ChessTile createBlackMoveTile(int);
		inline ChessTile createBlackOffensiveMoveTile(int);

		inline void addBlackPossibleMove(ChessTile &moveToAdd);
		inline ChessState isBlackPawnUpgrade(ChessState stateToCheck);


		inline void whiteStraightMove();
		inline void doubleWhiteStraightMove();
		inline void whiteOffensiveMoves();

		inline bool whiteAddLegalMove(ChessTile&);
		inline void whiteAddLegalOffensiveMove(ChessTile&);

		inline ChessTile createWhiteMoveTile(int);
		inline ChessTile createWhiteOffensiveMoveTile(int);

		inline void addWhitePossibleMove(ChessTile &moveToAdd);
		inline ChessState isWhitePawnUpgrade(ChessState stateToCheck);
	};
}