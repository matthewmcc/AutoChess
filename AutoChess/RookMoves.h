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

		std::list<ChessState> getRookMoves();

	private:
		std::list<ChessState> PossibleMoves;
		ChessState CurrentState;
		ChessTile RookToMove;
	};
}