#pragma once

#include "stdafx.h"
#include "ChessState.h"
#include <list>

namespace AutoChess {
	class QueenMoves
	{
	public:
		QueenMoves(ChessState &currentState, ChessTile &queenToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			QueenToMove = queenToMove;
		};

		std::list<ChessState> getBlackQueenMoves();
		std::list<ChessState> getWhiteQueenMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile QueenToMove;

		ChessMove addBlackDirectionMoves(int moveArrayIndex);
		bool isLegalBlackMove(ChessTile moveToTest);

		ChessMove addWhiteDirectionMoves(int moveArrayIndex);
		bool isLegalWhiteMove(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex, int moveLengthMultipler);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}