#pragma once

#include "stdafx.h"
#include "ChessState.h"
#include <list>

namespace AutoChess {
	class RookMoves
	{
	public:
		RookMoves(ChessState &currentState, ChessTile &rookToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			RookToMove = rookToMove;
		};

		std::list<ChessState> getBlackRookMoves();
		std::list<ChessState> getWhiteRookMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile RookToMove;

		void addBlackDirectionMoves(int moveArrayIndex);
		bool isLegalBlackMove(ChessTile moveToTest);

		void addWhiteDirectionMoves(int moveArrayIndex);
		bool isLegalWhiteMove(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex, int moveLengthMultipler);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}