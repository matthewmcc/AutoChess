#pragma once

#include "stdafx.h"
#include "ChessState.h"

#include <list>

namespace AutoChess {
	class BishopMoves
	{
	public:
		BishopMoves(ChessState &currentState, ChessTile &bishopToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			BishopToMove = bishopToMove;
		};

		std::list<ChessState> getBlackBishopMoves();
		std::list<ChessState> getWhiteBishopMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile BishopToMove;

		void addBlackDirectionMoves(int moveArrayIndex);
		bool isLegalBlackMove(ChessTile moveToTest);

		void addWhiteDirectionMoves(int moveArrayIndex);
		bool isLegalWhiteMove(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex, int moveLengthMultipler);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}