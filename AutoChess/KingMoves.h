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

		void addBlackDirectionMove(int moveArrayIndex);
		bool isLegalBlackKingMove(ChessTile moveToTest);
		bool isLegalBlackMove(ChessTile moveToTest);
		bool blackKingNotInCheck(ChessTile moveToTest);

		void addWhiteDirectionMove(int moveArrayIndex);
		bool isLegalWhiteKingMove(ChessTile moveToTest);
		bool isLegalWhiteMove(ChessTile moveToTest);
		bool whiteKingNotInCheck(ChessTile moveToTest);

		ChessTile createNextMoveTile(int moveArrayIndex);
		void addPossibleMove(ChessTile &moveToAdd);
	};
}