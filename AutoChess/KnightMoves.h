#pragma once

#include "stdafx.h"
#include "ChessState.h"
#include <list>

namespace AutoChess {
	class KnightMoves
	{
	public:
		KnightMoves(ChessState &currentState, ChessTile &rookToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			KnightToMove = rookToMove;
		};

		inline std::list<ChessState> getBlackKnightMoves();
		inline std::list<ChessState> getWhiteKnightMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile KnightToMove;

		void addBlackDirectionMoves(int moveArrayIndex);
		bool isLegalBlackMove(ChessTile moveToTest);

		void addWhiteDirectionMoves(int moveArrayIndex);
		bool isLegalWhiteMove(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex, int moveLengthMultipler);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}
