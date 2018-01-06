#pragma once

#include "stdafx.h"
#include "ChessState.h"
#include <list>

namespace AutoChess {
	class KingMoves
	{
	public:
		KingMoves(ChessState &currentState, ChessTile &kingToMove) {
			PossibleMoves = std::list<ChessState>();

			CurrentState = currentState;
			KingToMove = kingToMove;
		};

		std::list<ChessState> getBlackKingMoves();
		std::list<ChessState> getWhiteKingMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile KingToMove;

		ChessMove addBlackDirectionMove(int moveArrayIndex);
		bool isLegalBlackKingMove(ChessTile moveToTest);
		bool isLegalBlackMove(ChessTile moveToTest);

		ChessMove addWhiteDirectionMove(int moveArrayIndex);
		bool isLegalWhiteKingMove(ChessTile moveToTest);
		bool isLegalWhiteMove(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex, int moveLengthMultipler);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}